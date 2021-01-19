#ifndef OBJECTTRACKER_H
#define OBJECTTRACKER_H

#include <vector>

#include <QImage>

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

#include "TrackedObject.h"

/**
 * The number of consecutive frames for which fast object tracking will occur.
 * After this, a slower, more computationally expensive object detection algorithm is used for one frame.
 */
#define FAST_TRACKING_FRAMES 30

/**
 * The path to the .prototxt file containg the network architecture stored in Caffe framework's format.
 */
#define MODEL_PROTOTXT_FILE "models/mobilenet_ssd/MobileNetSSD_deploy.prototxt"

/**
 * The path to the .caffemodel file containing the learned network stored in Caffe framework's format.
 */
#define MODEL_CAFFEMODEL_FILE "models/mobilenet_ssd/MobileNetSSD_deploy.caffemodel"

/**
 * The class ID for a detected person as returned by the neural network.
 */
#define PERSON_CLASS_ID 15

/**
 * The minimum confidence level required for a detection by the neural network to be considered.
 */
#define MIN_CONFIDENCE_LEVEL 0.4

/**
 * @brief Class that tracks people as they enter/exit.
 * Class that tracks people as they enter/exit a building.
 * Utilizes a hybrid approach between detection and tracking for improved performance (real-time).
 */
class ObjectTracker : public QObject {
    Q_OBJECT

    public:
        /**
         * Enumeration used to specify the direction people must walk to enter.
         * In other words, which side of the video ihe enterance is towards.
         */
        enum EnterDirection {
            Up, Down, Left, Right
        };

        /**
         * Enumeration used to specify what information should be drawn on processed frames.
         */
        enum DrawFlag {
            // Draw rectangles for the bounding boxes of tracked objects
            DrawBoundingBoxes = 0x01,
            // Draw small circles at the centroid positions of tracked objects
            DrawCentroids     = 0x02,
            // Draw lines to indicate the inside/outside thresholds
            DrawThresholds    = 0x04,
            // Display the inside/outside state of objects
            ShowStates        = 0x08,
            // Display the current frame number
            ShowFrameNumber   = 0x10,
            // Display the current frame's tracking status (Waiting, Detecting, Tracking)
            ShowFrameStatus   = 0x20
        };

        Q_DECLARE_FLAGS(DrawFlags, DrawFlag)
        Q_FLAG(DrawFlags)

        ObjectTracker(QObject *parent = 0);

        ~ObjectTracker();

        DrawFlags getDrawFlags() const;

        void setDrawFlags(const DrawFlags flags);

        EnterDirection getEnterDirection() const;

        void setEnterDirection(const EnterDirection direction);

    public slots:
        void processFrame(cv::Mat frame);

        void reset();

    signals:
        void frameProcessed(QImage image);

        void personEntered();

        void personExited();

    private:
        /**
         * The neural network used to detect objects in a frame.
         */
        cv::dnn::Net net;

        /**
         * The names of layers in the neural network with unconnected outputs.
         * Forward passes are run to compute outputs of these layers.
         */
        std::vector<cv::String> layers;

        /**
         * List of currently tracked objects.
         */
        std::vector<TrackedObject> objects;

        /**
         * The current frame number. Used to alternate between object detection and tracking.
         */
        unsigned int frameNumber;

        /**
         * The direction towards which the enterance is. Used to determine if objects are inside or outside.
         */
        EnterDirection enterDirection;

        /**
         * Flags used to control what visual elements should be drawn on processed frames.
         */
        DrawFlags drawFlags;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ObjectTracker::DrawFlags)

#endif // OBJECTTRACKER_H
