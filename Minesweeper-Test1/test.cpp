#include "pch.h"
#include"../16_SFML_Games/minesweeper.cpp"
// Test for counting mines around a given tile
TEST(GridTest, CountMinesAround_NoMines) {
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };  // Initialize an empty grid with no mines

    int result = countMinesAround(grid, 5, 5);  // Test the center tile (no mines around it)

    EXPECT_EQ(result, 0);  // No mines should be adjacent, so result should be 0
}

TEST(GridTest, CountMinesAround_OneAdjacentMine) {
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };  // Initialize an empty grid
    grid[4][5] = MINE;  // Place a mine next to the tile being tested

    int result = countMinesAround(grid, 5, 5);  // Test tile at (5, 5)

    EXPECT_EQ(result, 1);  // There should be one adjacent mine
}

TEST(GridTest, CountMinesAround_CornerCase) {
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };  // Initialize an empty grid
    grid[0][1] = MINE;  // Place a mine next to the top-left corner tile

    int result = countMinesAround(grid, 0, 0);  // Test the top-left corner (0, 0)

    EXPECT_EQ(result, 1);  // There should be one adjacent mine
}

TEST(GridTest, CountMinesAround_MultipleAdjacentMines) {
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };  // Initialize an empty grid
    grid[4][5] = MINE;  // Place a mine
    grid[5][5] = MINE;  // Place another mine
    grid[6][5] = MINE;  // Place another mine

    int result = countMinesAround(grid, 5, 4);  // Test tile at (5, 4) adjacent to 3 mines

    EXPECT_EQ(result, 3);  // The result should be 3 as there are 3 adjacent mines
}