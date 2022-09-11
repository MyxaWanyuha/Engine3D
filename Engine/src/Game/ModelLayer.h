#pragma once
#include "Core/Layer.h"
#include "Core/Application.h"
#include "Render/Model.h"

class ModelLayer : public Layer
{
public:
    ModelLayer(const std::string& name = "ModelLayer");

    virtual ~ModelLayer() override = default;
    virtual void Update(float dt) override;
    virtual void OnEvent(Event& e) override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

private:
    Shader m_ModelShader;
    Shader m_StencilShader;
    Model m_Backpack;
    std::shared_ptr<CameraController> m_CameraController;
};

