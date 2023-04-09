//
// Created by shepherd on 8.3.23.
//

#ifndef GLCORE_MOUSE_EVENT_HPP
#define GLCORE_MOUSE_EVENT_HPP

#include <glcore/events/event.hpp>

namespace glcore {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(double xpos, double ypos);

    double GetXpos() const;

    double GetYpos() const;

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    double xpos;
    double ypos;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(double xoffset, double yoffset);

    double GetXoffset() const;

    double GetYoffset() const;

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseScrolled)

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    double xoffset_;
    double yoffset_;
};

class MouseButtonEvent : public Event {
public:
    int GetMouseButton() const;

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

protected:
    explicit MouseButtonEvent(int button);

    int button_;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(int button);

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(int button);

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseButtonReleased);
};

} // glcore

#endif //GLCORE_MOUSE_EVENT_HPP
