/**
 * @file VideoSource.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Class which feeds the video/video frames to the object tracker
 * @version 1.0
 * @date 2020-12-02
 * @copyright Copyright (c) 2020
 */
#include "VideoSource.h"

/**
 * @brief Constructor for VideoSource object. Sets clock to time video
 * 
 * @param parent 
 */
VideoSource::VideoSource(QObject *parent) : QObject(parent) {
    timer.setTimerType(Qt::PreciseTimer);
    connect(&timer, &QTimer::timeout, this, &VideoSource::captureFrame);
}

/**
 * @brief Destroy the Video Source object
 * 
 */
VideoSource::~VideoSource() {

}

/**
 * @brief Opens video file and records video fps
 * 
 * @param filepath 
 */
bool VideoSource::openFile(const QString filepath) {
    if (capture.open(filepath.toStdString())) {
        fps = capture.get(cv::CAP_PROP_FPS);
        play();
        return true;
    } else {
        stop();
        return false;
    }
}

/**
 * @brief Starts recording from live camera footage and records footage fps
 * 
 * @param camera 
 * @param captureFPS 
 */
bool VideoSource::openCamera(const int camera, const int captureFPS) {
    if (capture.open(camera)) {
        fps = captureFPS;
        play();
        return true;
    } else {
        stop();
        return false;
    }
}

/**
 * @brief plays the video/live video
 * 
 */
void VideoSource::play() {
    if (capture.isOpened()) {
        timer.start(1000 / fps);
    }
}

/**
 * @brief stops the video/live video
 * 
 */
void VideoSource::stop() {
    timer.stop();
}

/**
 * @brief gets frame from video source
 * 
 */
void VideoSource::captureFrame() {
    if (capture.read(frame)) {
        emit frameCaptured(frame);
    } else {
        stop();
    }
}
