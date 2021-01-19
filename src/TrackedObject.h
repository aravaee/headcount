/**
 * @file TrackedObject.h
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Represents an object being tracked in the video
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef TRACKEDOBJECT_H
#define TRACKEDOBJECT_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

/**
 * @brief Class represent object being tracked
 * 
 */
class TrackedObject {
    public:
        /**
         * Enumeration to track whether the object is currently outside or inside.
         */
        enum State {
            Unknown,
            Outside,
            Inside
        };

        TrackedObject(const cv::Mat& frame, const cv::Rect bbox);
        ~TrackedObject();

        void update(cv::Mat& frame);
        const cv::Rect& getBBox() const;

        cv::Point getPosition() const;
        bool isFound() const;

        State getState() const;
        std::string getStateString() const;
        void setState(const State state);

    private:
        cv::Ptr<cv::Tracker> tracker;
        cv::Rect bbox;

        bool found;
        State state;
};

#endif // TRACKEDOBJECT_H
