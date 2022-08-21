#include "spch.h"
#include "Core/Application.h"

static std::unique_ptr<Application> CreateApp(const std::string& name, int width, int heigth);

int main()
{
    auto app = CreateApp("Name", 1280, 720);
    app->Run();
    return 0;
}

std::unique_ptr<Application> CreateApp(const std::string& name, int width, int heigth)
{
    return std::make_unique<Application>(name, width, heigth);
}
