#pragma once

#include <string>

struct ApplicationSpecification
{
    int height = 720;
    int width = 1280;
    int cellSize = 20;
    std::string title = "Conway's Game of Life";
};