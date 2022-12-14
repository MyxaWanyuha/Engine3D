#include "spch.h"
#include "GameLayer.h"

#include "Core/Input.h"
#include "Render/Renderer.h"
#include <ImGui/ImGuiOpenGL.h>
#include <imgui.h>
#include <glm/gtx/transform.hpp>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
};
// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

GameLayer::GameLayer(const std::string& name)
    : Layer(name)
{
    float width = Application::Get().GetWindow().GetWidth();
    float heigth = Application::Get().GetWindow().GetHeigth();
    m_CameraController = std::make_unique<CameraController>(EditorCamera(45.0f, width / heigth));

    m_LightShader = std::make_shared<Shader>("assets/shaders/vertex2.vert", "assets/shaders/fragmentLight.frag");
    m_CubeShader = std::make_shared<Shader>("assets/shaders/vertex2.vert", "assets/shaders/fragmentMaterialTextures.frag");
    //m_Shader = std::make_shared<Shader>("assets/shaders/vertexTexture.vert", "assets/shaders/fragmentTexture.frag");
    m_Shader = std::make_shared<Shader>("assets/shaders/vertex2.vert", "assets/shaders/fragmentMaterialTexturesLightCaster.frag");
    m_MultipleLightsShader = std::make_shared<Shader>("assets/shaders/vertex2.vert", "assets/shaders/fragmentMultipleLights.frag");
    /*auto IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));*/
    auto VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    auto bufferLayout = BufferLayout{
        {DataType::Float, 3, "a_Pos"},
        {DataType::Float, 2, "a_TexCoord"},
        {DataType::Float, 3, "a_Normal"}, };

    m_VertexArray = std::make_unique<VertexArray>(VBO, bufferLayout);
    m_TextureContainer = std::make_unique<Texture>("assets/textures/container.jpg");
    m_TextureAwesomeface = std::make_unique<Texture>("assets/textures/awesomeface.png");
    m_TextureContainerDiffuse = std::make_unique<Texture>("assets/textures/container2.png");
    m_TextureContainerSpecular = std::make_unique<Texture>("assets/textures/container2_specular.png");
    m_TextureContainerEmission = std::make_unique<Texture>("assets/textures/matrix.jpg");

    for (int i = 0; i < NR_POINT_LIGHTS; ++i)
        m_PointLights->Position = m_PointLightPositions[i];
}

void GameLayer::Update(float dt)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Renderer::ClearColor(m_BackgroundColor);
    Renderer::Clear(ColorBufer | DepthBuffer);
    m_CameraController->Update(dt);
    {
        auto shader = m_MultipleLightsShader;
        shader->Bind();
        shader->SetFloat3("u_SpotLight.Position", m_CameraController->GetCamera().GetPosition());
        shader->SetFloat3("u_SpotLight.Direction", m_CameraController->GetCamera().GetFront());
        shader->SetFloat("u_SpotLight.CutOff", m_SpotLight.CutOff);
        shader->SetFloat("u_SpotLight.OuterCutOff", m_SpotLight.OuterCutOff);
        shader->SetFloat("u_SpotLight.Linear", m_SpotLight.Linear);
        shader->SetFloat("u_SpotLight.Quadratic", m_SpotLight.Quadratic);
        shader->SetFloat3("u_SpotLight.Ambient", m_SpotLight.Ambient);
        shader->SetFloat3("u_SpotLight.Diffuse", m_SpotLight.Diffuse);
        shader->SetFloat3("u_SpotLight.Specular", m_SpotLight.Specular);

        for (int i = 0; i < NR_POINT_LIGHTS; ++i)
        {
            char buffer[64];
            sprintf(buffer, "u_PointLights[%i].Position", i);
            shader->SetFloat3(buffer, m_PointLights[i].Position);
            sprintf(buffer, "u_PointLights[%i].Ambient", i);
            shader->SetFloat3(buffer, m_PointLights[i].Ambient);
            sprintf(buffer, "u_PointLights[%i].Diffuse", i);
            shader->SetFloat3(buffer, m_PointLights[i].Diffuse);
            sprintf(buffer, "u_PointLights[%i].Specular", i);
            shader->SetFloat3(buffer, m_PointLights[i].Specular);
            sprintf(buffer, "u_PointLights[%i].Linear", i);
            shader->SetFloat(buffer, m_PointLights[i].Linear);
            sprintf(buffer, "u_PointLights[%i].Quadratic", i);
            shader->SetFloat(buffer, m_PointLights[i].Quadratic);
        }

        shader->SetFloat3("u_DirLight.Direction", m_DirLight.Direction);
        shader->SetFloat3("u_DirLight.Ambient", m_DirLight.Ambient);
        shader->SetFloat3("u_DirLight.Diffuse", m_DirLight.Diffuse);
        shader->SetFloat3("u_DirLight.Specular", m_DirLight.Specular);

        shader->SetFloat3("u_CameraPosition", m_CameraController->GetCamera().GetPosition());

        /// Material uniforms begin ///////////////////////
        m_TextureContainerDiffuse->Bind(0);
        m_TextureContainerSpecular->Bind(1);
        m_TextureContainerEmission->Bind(2);
        shader->SetInt("u_Material.Diffuse", 0);
        shader->SetInt("u_Material.Specular", 1);
        //m_Shader->SetInt("u_Material.Emission", 2);
        shader->SetFloat("u_Material.Shininess", m_ObjectMaterial.Shininess);
        /// Material uniforms end /////////////////////////

        shader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());

        m_VertexArray->Bind();
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader->SetMat4("u_Model", model);
            Renderer::DrawArrays(0, 36);
        }
    }

    // Cube
    {
        m_CubeShader->Bind();
        m_CubeShader->SetFloat3("u_Light.Position", m_SpotLight.Position);
        m_CubeShader->SetFloat3("u_Light.Ambient", m_SpotLight.Ambient);
        m_CubeShader->SetFloat3("u_Light.Diffuse", m_SpotLight.Diffuse);
        m_CubeShader->SetFloat3("u_Light.Specular", m_SpotLight.Specular);

        m_CubeShader->SetFloat3("u_CameraPosition", m_CameraController->GetCamera().GetPosition());


        m_TextureContainerDiffuse->Bind(0);
        m_TextureContainerSpecular->Bind(1);
        m_TextureContainerEmission->Bind(2);
        m_CubeShader->SetInt("u_Material.Diffuse", 0);
        m_CubeShader->SetInt("u_Material.Specular", 1);
        m_CubeShader->SetInt("u_Material.Emission", 2);
        m_CubeShader->SetFloat("u_Material.Shininess", m_ObjectMaterial.Shininess);

        m_CubeShader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_ObjectPosition);
        m_CubeShader->SetMat4("u_Model", model);

        m_VertexArray->Bind();
        Renderer::DrawArrays(0, 36);
    }
    // Light
    {
        m_LightShader->Bind();
        m_LightShader->SetFloat3("u_LightColor", m_SpotLight.Ambient);
        m_LightShader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_SpotLight.Position);
        model = glm::scale(model, glm::vec3(0.2f));
        m_LightShader->SetMat4("u_Model", model);

        m_VertexArray->Bind();
        Renderer::DrawArrays(0, 36);
    }
}

void GameLayer::OnEvent(Event& e)
{
    m_CameraController->OnEvent(e);
}

void GameLayer::OnAttach()
{
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::DragFloat4("Background color", &m_BackgroundColor.x, 0.01f, 0.0f, 1.0f);
    ImGui::Text("Object");
    ImGui::DragFloat3("Object Position", &m_ObjectPosition.x, 0.01f, 0.0f, 100.0f);
    ImGui::DragFloat3("Object Ambient", &m_ObjectMaterial.Ambient.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Object Diffuse", &m_ObjectMaterial.Diffuse.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Object Specular", &m_ObjectMaterial.Specular.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat("Object Shininess", &m_ObjectMaterial.Shininess, 2.0f, 2.0f, 256.0f);
    ImGui::End();

    ImGui::Begin("SpotLight settings");
    ImGui::DragFloat3("Position", &m_SpotLight.Position.x, 0.01f, -100.0f, 100.0f);
    ImGui::DragFloat3("Direction", &m_SpotLight.Direction.x, 0.01f, -100.0f, 100.0f);
    ImGui::DragFloat("CutOff", &m_SpotLight.CutOff, 0.01f, 0.0f, 89.0f);
    ImGui::DragFloat("OuterCutOff", &m_SpotLight.OuterCutOff, 0.01f, 0.0f, 89.0f);
    ImGui::DragFloat("Linear", &m_SpotLight.Linear, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat("Quadratic", &m_SpotLight.Quadratic, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Ambient", &m_SpotLight.Ambient.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Diffuse", &m_SpotLight.Diffuse.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Specular", &m_SpotLight.Specular.x, 0.01f, 0.0f, 1.0f);
    ImGui::End();

    for (int i = 0; i < NR_POINT_LIGHTS; ++i)
    {
        ImGui::Begin(std::string("PointLight settings " + std::to_string(i)).c_str());
        ImGui::DragFloat3("Position", &m_PointLights[i].Position.x, 0.01f, -100.0f, 100.0f);
        ImGui::DragFloat3("Ambient", &m_PointLights[i].Ambient.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Diffuse", &m_PointLights[i].Diffuse.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Specular", &m_PointLights[i].Specular.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Linear", &m_PointLights[i].Linear, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Quadratic", &m_PointLights[i].Quadratic, 0.01f, 0.0f, 1.0f);
        ImGui::End();
    }
    ImGui::Begin("DirLight settings");
    ImGui::DragFloat3("Direction", &m_DirLight.Direction.x, 0.01f, -100.0f, 100.0f);
    ImGui::DragFloat3("Ambient", &m_DirLight.Ambient.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Diffuse", &m_DirLight.Diffuse.x, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat3("Specular", &m_DirLight.Specular.x, 0.01f, 0.0f, 1.0f);
    ImGui::End();
}
