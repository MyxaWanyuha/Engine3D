#include <vector>
#include "Core/Layer.h"

class LayerArray
{
public:
    LayerArray() = default;
    ~LayerArray();

    void AddLayer(Layer* layer);
    void AddAndAttachLayer(Layer* layer);
    void RemoveLayer(Layer* layer);
    void AddOverlay(Layer* overlay);
    void AddAndAttachOverlay(Layer* overlay);
    void RemoveOverlay(Layer* overlay);

    std::vector<Layer*>::iterator               begin()  { return m_Layers.begin(); }
    std::vector<Layer*>::iterator               end()    { return m_Layers.end(); }
    std::vector<Layer*>::reverse_iterator       rbegin() { return m_Layers.rbegin(); }
    std::vector<Layer*>::reverse_iterator       rend()   { return m_Layers.rend(); }

    std::vector<Layer*>::const_iterator         begin()  const { return m_Layers.begin(); }
    std::vector<Layer*>::const_iterator         end()    const { return m_Layers.end(); }
    std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
    std::vector<Layer*>::const_reverse_iterator rend()   const { return m_Layers.rend(); }

private:
    std::vector<Layer*> m_Layers;
    uint32_t m_LayerInsertIndex = 0;
};