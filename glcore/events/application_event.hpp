//
// Created by shepherd on 8.3.23.
//

#ifndef GLCORE_APPLICATION_EVENT_HPP
#define GLCORE_APPLICATION_EVENT_HPP

#include <glcore/events/event.hpp>

namespace glcore {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(int width, int height);

    int GetWidth() const;

    int GetHeight() const;

    std::string ToString() const override;

    EVENT_CLASS_TYPE(WindowResize);

    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    int width_, height_;
};

class WindowCloseEvent : public Event {
public:
    EVENT_CLASS_TYPE(WindowClose);

    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

} // glcore

#endif //GLCORE_APPLICATION_EVENT_HPP
