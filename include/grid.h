#pragma once

#include <vector>
#include <functional>

#include <raylib.h>

#include "../include/grid.h"
#include "../include/application.h"
#include "application-specification.h"

const extern ApplicationSpecification appSpec;

struct GridSpecification
{
    int gridWidth = appSpec.width;
    int gridHeight = (appSpec.height / 2) + 300;
    int gridX = (appSpec.width - gridWidth);
    int gridY = (appSpec.height - gridHeight);
    int cellSize = 20;
};

class Grid
{
public:
    Grid(int width, int height, int cellSize, int x, int y);

public:
    void setValue(int row, int column, int value);

    int getValue(int row, int column) const;
    int getRows() const { return m_rows; }
    int getColumns() const { return m_columns; }

public:
    int calculateGridPosition(int index) const;
    bool isWithinGrid(int row, int column) const;

    template <typename Func>
    void iterateOverCells(Func func) const;

    void drawCell(int row, int column) const;
    void toggleCell(int row, int column);
    void draw() const;
    void fillRandom();

    void clear();

private:
    static const Color ALIVE_COLOR;
    static const Color DEAD_COLOR;
    static const int CELL_BORDER;

private:
    int m_width;
    int m_height;
    int m_x;
    int m_y;

    int m_rows;
    int m_columns;
    int m_cellSize;
    std::vector<std::vector<int>> m_cells;
};