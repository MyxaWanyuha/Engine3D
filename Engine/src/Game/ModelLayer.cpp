#include "spch.h"
#include "ModelLayer.h"
#include "Render/Renderer.h"
#include "Core/KeyCodes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ModelLayer::ModelLayer(const std::string& name)
{
    m_StencilShader.Init("assets/shaders/model.vert", "assets/shaders/shaperSingleColor.frag");
    m_ModelShader.Init("assets/shaders/model.vert", "assets/shaders/model.frag");
    m_Backpack.LoadModel("assets/backpack/backpack.obj");
    // m_Backpack.LoadModel("assets/volga/model.obj");

    float width = Application::Get().GetWindow().GetWidth();
    float heigth = Application::Get().GetWindow().GetHeigth();
    m_CameraController = std::make_unique<CameraController>(EditorCamera(45.0f, width / heigth));
    Renderer::Enable(DepthTest);
}

void ModelLayer::Update(float dt)
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    Renderer::ClearColor(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });
    Renderer::Clear(ColorBufer | DepthBuffer);
    m_CameraController->Update(dt);

    m_ModelShader.Bind();
    m_ModelShader.SetMat4("viewprojection", m_CameraController->GetCamera().GetViewProjectionMatrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
    model = glm::scale(model, glm::vec3(1.0f));
    m_ModelShader.SetMat4("model", model);
    m_Backpack.Draw(m_ModelShader);
}

void ModelLayer::OnEvent(Event& e)
{
    m_CameraController->OnEvent(e);
}

void ModelLayer::OnAttach()
{
}

void ModelLayer::OnDetach()
{
}

void ModelLayer::OnImGuiRender()
{
}
