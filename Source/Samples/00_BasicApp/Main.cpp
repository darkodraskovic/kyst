#include "Application.h"

int main()
{
    // Application init
    // ---------------------------------------------------------------------------    
    Application app = Application::Instance();
    if (app.Init() < 0)
    {
        std::cout << "Failed to create an OpenGL app" << std::endl;
        return -1;
    };

    // Application CONTENT
    // ---------------------------------------------------------------------------
    
    // Application loop
    // ---------------------------------------------------------------------------
    while (!app.ShouldClose())
    {
        app.Update();
    }

    
    // Application termination
    // ---------------------------------------------------------------------------
    app.Terminate();

    return 0;
}
