/**
 * @file TrackedObject.cpp
 * @author Ahmed El Farra , Ahmed Faid , Issar Farid , Ali Ravaee , Muhammad Haris Rafique Zakar
 * @brief Represents an object being tracked in the video
 * @version 1.0
 * @date 2020-12-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "TrackedObject.h"

/**
 * @brief Construct a TrackedObject which will represents/track a person in the video
 * First param is current video frame and second param is the surrounding rectangle of object
 * @param frame 
 * @param bbox 
 */
TrackedObject::TrackedObject(const cv::Mat &frame, const cv::Rect bbox)
{
    // Initialize a tracker with this known bounding box for the object
    tracker = cv::TrackerKCF::create();
    tracker->init(frame, bbox);

    // Store the initial bounding box
    this->bbox = bbox;

    // Objects are initially always located
    this->found = true;

    // Objects inside/outside state is initially unknown
    this->state = State::Unknown;
}

/**
 * @brief Destroy the Tracked Object object
 * 
 */
TrackedObject::~TrackedObject()
{
}

/**
 * @brief Updates the tracked object in a new frame
 * 
 * @param frame 
 */
void TrackedObject::update(cv::Mat &frame)
{
    // Update the tracked, find the new most likely bounding box for the object
    // Store whether the tracked could locate the object in the given frame
    found = tracker->update(frame, bbox);
}

/**
 * @brief Returns surronding rectangle object for tracked object
 * 
 * @return const cv::Rect& 
 */
const cv::Rect &TrackedObject::getBBox() const
{
    return bbox;
}

/**
 * @brief Returns positon of the tracked object
 * 
 * @return cv::Point 
 */
cv::Point TrackedObject::getPosition() const
{
    return 0.5 * (bbox.tl() + bbox.br());
}

/**
 * @brief Returns bool which determines if tracked object was found in new frame
 * 
 * @return true 
 * @return false 
 */
bool TrackedObject::isFound() const
{
    return found;
}

/**
 * @brief Returns the state of the tracked object
 * 
 * @return TrackedObject::State 
 */
TrackedObject::State TrackedObject::getState() const
{
    return state;
}

/**
 * @brief Returns string representation of tracked object's state
 * 
 * @return std::string 
 */
std::string TrackedObject::getStateString() const
{
    switch (state)
    {
    case State::Unknown:
        return "Unknown";
    case State::Outside:
        return "Outside";
    case State::Inside:
        return "Inside";
    default:
        return "";
    }
}

/**
 * @brief Set state of tracked Object
 * 
 * @param state 
 */
void TrackedObject::setState(const TrackedObject::State state)
{
    this->state = state;
}
