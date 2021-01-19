/**
 * @file VideoDisplay.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Widget for displaying video in QT GUI
 * @version 0.1
 * @date 2020-12-02
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <QVBoxLayout>

#include "VideoDisplay.h"
/**
 * @brief Construct a new Video Display object
 * @param parent
 */
VideoDisplay::VideoDisplay(QWidget *parent) : QWidget(parent)
{
    video = new QLabel(this);

    //Initial set up to allow resizing of video
    video->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    video->setScaledContents(false);

    //Initial setup for window display
    auto layout = new QVBoxLayout(this);
    layout->addWidget(video);

    this->setLayout(layout);
}

/**
 * @brief Deconstuctor for VideoDisplay object
 */
VideoDisplay::~VideoDisplay(){
}

/**
 * @brief Displays image on the video display widget
 * @param QImage image
 */
void VideoDisplay::updateImage(const QImage image)
{
    int width = video->width();
    int height = video->height();
    // Updates the image each time it passes through the video
    video->setPixmap(QPixmap::fromImage(image).scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation));
}
