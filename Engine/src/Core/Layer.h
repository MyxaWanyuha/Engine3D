#pragma once
#include <string>
#include "Event.h"

class Layer
{
public:
    Layer(const std::string& name = "Layer") : m_DebugName(name) {}
    virtual ~Layer() = default;
    virtual void Update(float dt) {}
    virtual void OnEvent(Event& e) {}

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnImGuiRender() {}

protected:
    std::string m_DebugName;
};