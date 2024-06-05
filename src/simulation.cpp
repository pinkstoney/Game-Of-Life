#include <vector>
#include <utility>

#include "../include/simulation.h"

Simulation::Simulation(int width, int height, int cellSize, int x, int y)
    : m_grid(std::make_unique<Grid>(width, height, cellSize, x, y)),
      m_tempGrid(std::make_unique<Grid>(width, height, cellSize, x, y)),
      run(false)
{
}

void Simulation::draw() const
{
    m_grid->draw();
}

void Simulation::setCellValue(int row, int column, int value)
{
    m_grid->setValue(row, column, value);
}

int Simulation::calculateNewState(int row, int column) const
{
    int aliveNeighbours = countAliveNeighbours(row, column);
    int cellValue = m_grid->getValue(row, column);

    bool isAlive = cellValue == 1 && (aliveNeighbours == 2 || aliveNeighbours == 3);
    bool isDeadAndReproduces = cellValue == 0 && aliveNeighbours == 3;

    return isAlive || isDeadAndReproduces ? 1 : 0;
}

int Simulation::countAliveNeighbours(int row, int column) const
{
    int aliveNeighbours = 0;

    const std::vector<std::pair<int, int>> neighbourOffsets =
            {
                    { -1, -1 }, // top-left
                    { -1, 0 },  // top
                    { -1, 1 },  // top-right
                    { 0, -1 },  // left
                    { 0, 1 },   // right
                    { 1, -1 },  // bottom-left
                    { 1, 0 },   // bottom
                    { 1, 1 }    // bottom-right
            };

    for (const auto& offset : neighbourOffsets)
    {
        int neighbourRow = (row + offset.first + m_grid->getRows()) % m_grid->getRows();
        int neighbourColumn = (column + offset.second + m_grid->getColumns()) % m_grid->getColumns();

        aliveNeighbours += m_grid->getValue(neighbourRow, neighbourColumn);
    }
    return aliveNeighbours;
}

void Simulation::update()
{
    if (isRunning())
    {
        for (int row = 0; row < m_grid->getRows(); row++)
            for (int column = 0; column < m_grid->getColumns(); column++)
                m_tempGrid->setValue(row, column, calculateNewState(row, column));
        m_grid.swap(m_tempGrid);
    }
}

void Simulation::clearGrid()
{
    if (!isRunning())
        m_grid->clear();
}

void Simulation::createRandomState()
{
    if (!isRunning())
        m_grid->fillRandom();
}

void Simulation::toggleCell(int row, int column)
{
    if (!isRunning())
        m_grid->toggleCell(row, column);
}

