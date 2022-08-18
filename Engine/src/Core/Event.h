#pragma once
#include <functional>
#include <list>

enum class EventType
{
    None = 0,

    WindowClose, WindowResize,

    KeyPressed, KeyReleased, KeyTyped,

    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

#define BODY(EventType_) static EventType GetStaticEventType() { return EventType::EventType_; } \
                         virtual EventType GetEventType() const override { return GetStaticEventType(); }

struct Event
{
    virtual EventType GetEventType() const = 0;
    bool bHandled = false;
};

/// Begin Key Events //////////////////////////////////////////
struct EventKey : Event
{
    EventKey(int key)
        : Key(key)
    {
    }
    const int Key;
};

struct EventKeyPressed : EventKey
{
    BODY(KeyPressed)

    EventKeyPressed(int key, int repeatCount)
        : EventKey(key), RepeatCount(repeatCount)
    {
    }
    const int RepeatCount;
};

struct EventKeyReleased : EventKey
{
    BODY(KeyReleased)

    EventKeyReleased(int key)
        : EventKey(key)
    {
    }
};

struct EventKeyTyped : EventKey
{
    BODY(KeyTyped)

    EventKeyTyped(int key)
        : EventKey(key)
    {
    }
};
/// End Key Events ////////////////////////////////////////////

/// Begin Window Events ///////////////////////////////////////
struct EventWindowClose : Event
{
    BODY(WindowClose)
};

struct EventWindowResize : Event
{
    BODY(WindowResize)

    EventWindowResize(uint32_t width, uint32_t height)
        : Width(width), Height(height)
    {
    }
    const uint32_t Width, Height;
};
/// End Window Events /////////////////////////////////////////

/// Begin Mouse Events ////////////////////////////////////////
struct EventMouseButtonPressed : Event
{
    BODY(MouseButtonPressed)
    EventMouseButtonPressed(int button)
        : Button(button)
    {
    }
    const int Button;
};

struct EventMouseButtonReleased : Event
{
    BODY(MouseButtonReleased)
    EventMouseButtonReleased(int button)
        : Button(button)
    {
    }
    const int Button;
};

struct EventMouseMoved : Event
{
    BODY(MouseMoved)
    EventMouseMoved(float x, float y)
        : X(x), Y(y)
    {
    }
    const float X, Y;
};

struct EventMouseScrolled : Event
{
    BODY(MouseScrolled)
    EventMouseScrolled(float xOffset, float yOffset)
        : XOffset(xOffset), YOffset(yOffset)
    {
    }
    const float XOffset, YOffset;
};
/// End Mouse Events //////////////////////////////////////////
#undef BODY(EventType_)

class EventDispatcher
{
public:
    EventDispatcher(Event& event)
        : m_Event(event)
    {
    }

    template<typename T, typename F>
    bool Dispatch(const F& func)
    {
        if (m_Event.GetEventType() == T::GetStaticEventType())
        {
            m_Event.bHandled = func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }
private:
    Event& m_Event;
};
