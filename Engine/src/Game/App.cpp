#include "spch.h"
#include "Core/Application.h"
#include "Game/GameLayer.h"
#include "Game/ModelLayer.h"

class App : public Application
{
public:
    App(const std::string& name, int width, int heigth) : Application(name, width, heigth)
    {
        //GetLayerArray().AddAndAttachLayer(new GameLayer());
        GetLayerArray().AddAndAttachLayer(new ModelLayer());
    }

    virtual ~App() override = default;

    virtual void OnEvent(Event& e) override
    {
        Application::OnEvent(e);
    }

    virtual void Update(float dt) override
    {
        Application::Update(dt);
    }
};

std::unique_ptr<Application> CreateApp(const std::string& name, int width, int heigth)
{
    return std::make_unique<App>(name, width, heigth);
}