#include "../include/menu.h"

const GridSpecification gridSpec;

Menu::Menu(Simulation &simulation)
    : m_simulation(simulation) {}

void Menu::m_handleButtonPresses()
{
    bool startButtonPressed = GuiButton((Rectangle){10, 10, 120, 30}, "Start");
    bool stopButtonPressed = GuiButton((Rectangle){140, 10, 120, 30}, "Stop");
    bool randomizeButtonPressed = GuiButton((Rectangle){static_cast<float>(appSpec.width) - 130.0f, 10, 120, 30}, "Randomize");
    bool clearButtonPressed = GuiButton((Rectangle){static_cast<float>(appSpec.width) - 260.0f, 10, 120, 30}, "Clear");

    if (startButtonPressed) m_startSimulation();
    if (stopButtonPressed) m_stopSimulation();
    if (randomizeButtonPressed) m_randomizeSimulation();
    if (clearButtonPressed) m_clearSimulation();
}

void Menu::m_handleMouseClick()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition = GetMousePosition();
        auto row = static_cast<int>((mousePosition.y - gridSpec.gridY) / gridSpec.cellSize);
        auto column = static_cast<int>((mousePosition.x - gridSpec.gridX) / gridSpec.cellSize);
        m_simulation.toggleCell(row, column);
    }
}

void Menu::m_startSimulation()
{
    SetTargetFPS(15);
    m_simulation.start();
}

void Menu::m_stopSimulation()
{
    SetTargetFPS(60);
    m_simulation.stop();
}

void Menu::m_randomizeSimulation()
{
    m_simulation.createRandomState();
}

void Menu::m_clearSimulation()
{
    m_simulation.clearGrid();
}

void Menu::onUpdate()
{
    DrawLine(0, gridSpec.gridY - 10, gridSpec.gridWidth, gridSpec.gridY - 10, LIGHTGRAY);

    if (m_simulation.isRunning())
        DrawText("Simulation is running", (appSpec.width / 2) - 100, 15, 20, LIGHTGRAY);

    m_handleButtonPresses();
    m_handleMouseClick();
}


