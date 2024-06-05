#pragma once

#include <string>
#include <memory>

#include <raylib.h>

#include "../include/simulation.h"
#include "../include/menu.h"
#include "../include/grid.h"
#include "application-specification.h"

class Simulation;
class Menu;

class Application
{
public:
    explicit Application(const ApplicationSpecification& spec = ApplicationSpecification());
    ~Application();

public:
    void run();

private:
    ApplicationSpecification m_specification;
    Image m_icon;

    std::unique_ptr<Simulation> m_simulation;
    std::unique_ptr<Menu> m_menu;
};