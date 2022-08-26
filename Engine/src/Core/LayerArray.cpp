#include "spch.h"
#include "LayerArray.h"

LayerArray::~LayerArray()
{
    for (auto e : m_Layers)
        delete e;
}

void LayerArray::AddLayer(Layer* layer)
{
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    ++m_LayerInsertIndex;
}

void LayerArray::AddAndAttachLayer(Layer* layer)
{
    layer->OnAttach();
    AddLayer(layer);
}

void LayerArray::RemoveLayer(Layer* layer)
{
    auto end = m_Layers.begin() + m_LayerInsertIndex;
    auto it = std::find(m_Layers.begin(), end, layer);
    if (it != end)
    {
        layer->OnDetach();
        m_Layers.erase(it);
        --m_LayerInsertIndex;
    }
}

void LayerArray::AddOverlay(Layer* overlay)
{
    m_Layers.emplace_back(overlay);
}

void LayerArray::AddAndAttachOverlay(Layer* overlay)
{
    overlay->OnAttach();
    AddOverlay(overlay);
}

void LayerArray::RemoveOverlay(Layer* overlay)
{
    auto begin = m_Layers.begin() + m_LayerInsertIndex;
    auto it = std::find(begin, m_Layers.end(), overlay);
    if (it != m_Layers.end())
    {
        overlay->OnDetach();
        m_Layers.erase(it);
    }
}