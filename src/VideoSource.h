/**
 * @file VideoSource.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Class which feeds the video/video frames to the object tracker
 * @version 1.0
 * @date 2020-12-02
 * @copyright Copyright (c) 2020
 */
#ifndef VIDEOSOURCE_H
#define VIDEOSOURCE_H

#include <QObject>
#include <QString>
#include <QTimer>

#include <opencv2/opencv.hpp>

#define DEFAULT_CAPTURE_FPS 24

/**
 * @brief Class which feeds the video/video frames to the object tracker
 * 
 */
class VideoSource : public QObject {
    Q_OBJECT

    public:
        VideoSource(QObject *parent = 0);

        ~VideoSource();

        bool openFile(const QString filepath);

        bool openCamera(const int camera, const int captureFPS = DEFAULT_CAPTURE_FPS);

        void play();

        void stop();

    signals:
        void frameCaptured(const cv::Mat& frame);

    private slots:
        void captureFrame();

    private:
        cv::VideoCapture capture;

        cv::Mat frame;

        QTimer timer;

        int fps;
};

#endif // VIDEOSOURCE_H
