#pragma once

#include "simulation.h"
#include "grid.h"
#include "raygui.h"
#include "application.h"

class Simulation;

struct GridSpecification;
const extern GridSpecification gridSpec;

class Menu
{
public:
    explicit Menu (Simulation& simulation);

public:
    void onUpdate();

private:
    Simulation& m_simulation;

private:
    void m_handleButtonPresses();
    void m_handleMouseClick();

    void m_startSimulation();
    void m_stopSimulation();
    void m_randomizeSimulation();
    void m_clearSimulation();
};

