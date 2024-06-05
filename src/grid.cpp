#include <raylib.h>

#include "../include/grid.h"

const ApplicationSpecification appSpec;

const Color Grid::ALIVE_COLOR = {227, 227, 227, 255};
const Color Grid::DEAD_COLOR = {52, 52, 52, 255};
const int Grid::CELL_BORDER = 1;

Grid::Grid(int width, int height, int cellSize, int x, int y)
        : m_width(width), m_height(height), m_cellSize(cellSize), m_x(x), m_y(y)
{
    m_rows = height / cellSize;
    m_columns = width / cellSize;
    m_cells = std::vector<std::vector<int>>(m_rows, std::vector<int>(m_columns, 0));
}

int Grid::calculateGridPosition(int index) const
{
    return index * m_cellSize;
}

bool Grid::isWithinGrid(int row, int column) const
{
    return row >= 0 && row < m_rows && column >= 0 && column < m_columns;
}

void Grid::setValue(int row, int column, int value)
{
    if (isWithinGrid(row, column))
        m_cells[row][column] = value;
    else
        throw std::out_of_range("Row or column is out of m_grid bounds");
}

int Grid::getValue(int row, int column) const
{
    if (isWithinGrid(row, column))
        return m_cells[row][column];
    else
        throw std::out_of_range("Row or column is out of m_grid bounds");
}

void Grid::drawCell(int row, int column) const
{
    Color cellColor = getValue(row, column) ? ALIVE_COLOR : DEAD_COLOR;

    int colPos = calculateGridPosition(column) + m_x;
    int rowPos = calculateGridPosition(row) + m_y;

    DrawRectangle(colPos, rowPos, m_cellSize - CELL_BORDER, m_cellSize - CELL_BORDER, cellColor);
}

template <typename Func>
void Grid::iterateOverCells(Func func) const
{
    for (int row = 0; row < m_rows; row++)
        for (int column = 0; column < m_columns; column++)
            func(row, column);
}

void Grid::draw() const
{
    iterateOverCells([this](int row, int column)
    {
        drawCell(row, column);
    });
}

void Grid::fillRandom()
{
    iterateOverCells([this](int row, int column)
    {
        int randomValue = GetRandomValue(0, 4);
        m_cells[row][column] = (randomValue == 4) ? 1 : 0;
    });
}

void Grid::clear()
{
    iterateOverCells([this](int row, int column)
    {
        m_cells[row][column] = 0;
    });
}

void Grid::toggleCell(int row, int column)
{
    if (isWithinGrid(row, column))
        m_cells[row][column] = !m_cells[row][column];
}
