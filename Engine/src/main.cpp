#include "spch.h"
#include "Core/Application.h"

int main()
{
    auto app = CreateApp("Name", 1280, 720);
    app->Run();
    return 0;
}
