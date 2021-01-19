/**
 * @file VideoDisplay.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Widget for displaying video in QT GUI
 * @version 1.0
 * @date 2020-12-01
 * @copyright Copyright (c) 2020
 *
 */
#ifndef VIDEODISPLAY_H
#define VIDEODISPLAY_H

#include <QLabel>
#include <QImage>
#include <QWidget>

/**
 * @brief Class that represent window widget for displaying videos in QT GUI
 */
class VideoDisplay : public QWidget {

public:
    VideoDisplay(QWidget *parent = 0);

    ~VideoDisplay();

public slots:
    void updateImage(QImage image);

private:
    QLabel *video;
};

#endif
