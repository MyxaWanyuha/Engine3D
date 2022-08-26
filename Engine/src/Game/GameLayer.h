#pragma once
#include "Core/Layer.h"
#include "Core/Application.h"

class GameLayer : public Layer
{
public:
    GameLayer(const std::string& name = "GameLayer");

    virtual ~GameLayer() override = default;
    virtual void Update(float dt) override;
    virtual void OnEvent(Event& e) override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

private:
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Shader> m_CubeShader;
    std::shared_ptr<Shader> m_LightShader;
    std::shared_ptr<Shader> m_MultipleLightsShader;
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<Texture> m_TextureContainer;
    std::unique_ptr<Texture> m_TextureAwesomeface;
    std::unique_ptr<Texture> m_TextureContainerDiffuse;
    std::unique_ptr<Texture> m_TextureContainerSpecular;
    std::unique_ptr<Texture> m_TextureContainerEmission;

    glm::vec4 m_BackgroundColor = glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f };

    SpotLight m_SpotLight;
    PointLight m_PointLights[NR_POINT_LIGHTS];
    glm::vec3 m_PointLightPositions[NR_POINT_LIGHTS] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    DirLight m_DirLight;

    glm::vec3 m_ObjectPosition = glm::vec3(0, 0, 0);
    Material m_ObjectMaterial = { { 0.0f, 0.0f, 0.37f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, 256.0f };

    std::unique_ptr<CameraController> m_CameraController;
};
