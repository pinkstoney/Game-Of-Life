#pragma once

#include <memory>

#include "grid.h"

class Grid;

class Simulation
{
public:
    Simulation(int width, int height, int cellSize, int x, int y);

public:
    void setCellValue(int row, int column, int value);

public:
    int countAliveNeighbours(int row, int column) const;
    int calculateNewState(int row, int column) const;

    void draw() const;
    void update();
    void toggleCell(int row, int column);

    void clearGrid();
    void createRandomState();

    bool isRunning() const { return run; }
    void start() { run = true; }
    void stop() { run = false; }

private:
    std::unique_ptr<Grid> m_grid;
    std::unique_ptr<Grid> m_tempGrid;

    bool run;
};