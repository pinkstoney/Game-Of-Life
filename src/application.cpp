#include "../include/application.h"

Application::Application(const ApplicationSpecification& spec)
        : m_specification(spec),
          m_simulation(std::make_unique<Simulation>(gridSpec.gridWidth, gridSpec.gridHeight, gridSpec.cellSize, gridSpec.gridX, gridSpec.gridY)),
          m_menu(std::make_unique<Menu>(*m_simulation))
{
    InitWindow(m_specification.width, m_specification.height, m_specification.title.c_str());
    m_icon = LoadImage("../res/icon.png");
    SetWindowIcon(m_icon);
    SetTargetFPS(60);
}

Application::~Application()
{
    CloseWindow();
}

void Application::run()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        m_menu->onUpdate();

        m_simulation->update();
        m_simulation->draw();

        EndDrawing();
    }
}


