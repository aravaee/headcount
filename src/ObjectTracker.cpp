#include "ObjectTracker.h"

#include <algorithm>
#include <string>
#include <iostream>

/**
 * @brief Constructs a new ObjectTracker object.
 * @param parent the parent Qt object of this object.
 */
ObjectTracker::ObjectTracker(QObject *parent) : QObject(parent) {
    net = cv::dnn::readNetFromCaffe(MODEL_PROTOTXT_FILE, MODEL_CAFFEMODEL_FILE);
    layers = net.getUnconnectedOutLayersNames();
    frameNumber = 0;
}

/**
 * @brief Destructs an ObjectTracker object.
 */
ObjectTracker::~ObjectTracker() {

}

/**
 * @brief Returns the currently set draw flags.
 * @return the currently set draw flags.
 */
ObjectTracker::DrawFlags ObjectTracker::getDrawFlags() const {
    return drawFlags;
}

/**
 * @brief Sets the draw flags for frame processing.
 * Available draw flags are part of the DrawFlags enum and can be OR'd together to combine them.
 * @param flags the draw flags to set.
 */
void ObjectTracker::setDrawFlags(const ObjectTracker::DrawFlags flags) {
    drawFlags = flags;
}

/**
 * @brief Returns the currently set enter direction.
 * @return the currently set enter direction.
 */
ObjectTracker::EnterDirection ObjectTracker::getEnterDirection() const {
    return enterDirection;
}

/**
 * @brief Sets the enter direction for frame processing.
 * @param direction the enter direction to set.
 */
void ObjectTracker::setEnterDirection(const ObjectTracker::EnterDirection direction) {
    enterDirection = direction;
}

/**
 * @brief Porcesses the given frame and performs object tracking and drawing on it.
 * Processes the given frame by detecting objects every FAST_TRACKING_FRAMES and tracking
 * objects in intermediate frames. Then performs drawing on the frame as specified by
 * the draw flags. Finally, a signal with the processed frame is emitted.
 * @param frame the frame to process.
 */
void ObjectTracker::processFrame(cv::Mat frame) {
    // Get the number of rows (height) and columns (width) in the frame
    const int rows = frame.rows;
    const int cols = frame.cols;

    // Get the center (x, y) coordinate of the frame
    const auto center = cv::Point(cols / 2, rows / 2);

    // Keep track of the frame's tracking status
    QString status = "Waiting";

    // Use the slower, more computationally expensive object detection every N frames
    if (frameNumber % FAST_TRACKING_FRAMES == 0) {
        // Create a 4D blob from the frame
        cv::Mat blob = cv::dnn::blobFromImage(frame, 0.007843, cv::Size(cols, rows), cv::Scalar(127.5));
        net.setInput(blob);

        // Run a forward pass on the neural network to detect objects
        std::vector<cv::Mat> output;
        net.forward(output, layers);

        // Clear the currently tracked objects, we will create new ones based on detected objects
        objects.clear();

        // Set the frame's status to detecting sicne we are running our object detector
        status = "Detecting";

        // Neural network produces output blob with a shape of 1x1xNx7 where N is the number of detections
        // Every detection is a vector of values [batchId, classId, confidence, left, top, right, bottom]
        for (std::size_t k = 0; k < output.size(); k++) {
            const float *data = (float *) output[k].data;

            for (std::size_t i = 0; i < output[k].total(); i += 7) {
                const float confidence = data[i + 2];

                // Ignore weak detections that do not satisfy the minimum confidence level
                if (confidence >= MIN_CONFIDENCE_LEVEL) {
                    const int classId = (int) data[i + 1];

                    // Ignore detections which are not of class "person"
                    if (classId != PERSON_CLASS_ID) {
                        continue;
                    }

                    // Calculate the bounding box for the object
                    const int x = (int) (data[i + 3] * cols);
                    const int y = (int) (data[i + 4] * rows);
                    const int w = (int) (data[i + 5] * cols) - x;
                    const int h = (int) (data[i + 6] * rows) - y;

                    cv::Rect bbox(x, y, w, h);

                    // Initialize a tracked object with this known bounding for it
                    // and store it so it can be used during fast detection frames
                    objects.push_back(TrackedObject(frame, bbox));
                }
            }
        }
    } else {
        // In intermediate frames, update the previously detected objects
        for (auto& object : objects) {
            object.update(frame);

            // Set the frame's status to tracking sice we had at least one object that we are tracking
            status = "Tracking";
        }
    }

    for (auto& object : objects) {
        // Get the object's position and determine whether it is inside or not
        const auto position = object.getPosition();

        // Determine if the object is inside or not
        // Add a 10% buffer on each side of the threshold to improve the detection probability
        bool inside;

        switch (enterDirection) {
            case EnterDirection::Up:
                inside = position.y < center.y - rows * 0.1;
                break;
            case EnterDirection::Down:
                inside = position.y > center.y + rows * 0.1;
                break;
            case EnterDirection::Left:
                inside = position.x < center.x - cols * 0.1;
                break;
            case EnterDirection::Right:
                inside = position.x > center.y + cols * 0.1;
                break;
        }

        // Get the object's current state and update it accordingly
        const auto state = object.getState();

        if (inside) {
            if (state == TrackedObject::Outside) {
                // Object entered...
                emit personEntered();
                std::cout << "[" << frameNumber << "] object entered" << std::endl;
            }

            object.setState(TrackedObject::Inside);
        } else {
            if (state == TrackedObject::Inside) {
                // Object exited...
                emit personExited();
                std::cout << "[" << frameNumber << "] object exited" << std::endl;
            }

            object.setState(TrackedObject::Outside);
        }

        // Draw the bounding box of the object if required
        if (drawFlags.testFlag(DrawFlag::DrawBoundingBoxes)) {
            cv::rectangle(frame, object.getBBox(), cv::Scalar(255, 0, 0), 1, cv::LINE_AA);
        }

        // Draw the centroid of the object if required
        if (drawFlags.testFlag(DrawFlag::DrawCentroids)) {
            cv::circle(frame, position, 2, cv::Scalar(0, 255, 255), -1, cv::LINE_AA);
        }

        // Display the object's current state if required
        if (drawFlags.testFlag(DrawFlag::ShowStates)) {
            const auto text = object.getStateString();
            const auto size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, NULL);
            const auto screenPos = position + cv::Point(-size.width / 2, size.height + 5);

            cv::putText(frame, text, screenPos, cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }
    }

    // Draw the enter/exit threshold as a line if required
    if (drawFlags.testFlag(DrawFlag::DrawThresholds)) {
        cv::Point p1, p2;

        if (enterDirection == EnterDirection::Up || enterDirection == EnterDirection::Down) {
            p1 = cv::Point(0, rows / 2);
            p2 = cv::Point(cols, rows / 2);
        } else {
            p1 = cv::Point(cols / 2, 0);
            p2 = cv::Point(cols / 2, rows);
        }

        cv::line(frame, p1, p2, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    }

    // Display frame number and status information if required
    QString infoText = "";

    if (drawFlags.testFlag(DrawFlag::ShowFrameNumber)) {
        infoText = QString("Frame: %1").arg(frameNumber);
    }

    if (drawFlags.testFlag(DrawFlag::ShowFrameStatus)) {
        infoText = QString("%1 (%2)").arg(infoText).arg(status);
    }

    if (infoText != "") {
        const auto size = cv::getTextSize(infoText.toStdString(), cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, NULL);
        const auto screenPos = cv::Point(0, size.height);
        cv::putText(frame, infoText.toStdString(), screenPos, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0), 1, cv::LINE_AA);
    }

    // Increment the frame number
    frameNumber++;

    // Convert the processed frame into a QImage and emit a signal containing it
    QImage image(cols, rows, QImage::Format_RGB888);

    cv::Mat mat(rows, cols, CV_8UC3, image.bits(), image.bytesPerLine());
    cv::resize(frame, mat, mat.size(), 0, 0, cv::INTER_AREA);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);

	emit frameProcessed(image);
}

/**
 * @brief Resets the object tracking state (frame number and tracked objects) of this object.
 */
void ObjectTracker::reset() {
    frameNumber = 0;
    objects.clear();
}
