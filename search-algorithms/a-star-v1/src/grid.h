#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>
#include <stdlib.h>

typedef std::pair<int, int> Pair;

struct Grid
{
    size_t GRID_SIZE;
    int **grid;
    void paintGrid(Pair coords, int newCellValue);
    void buildGrid();
    void buildGridFromTxt(std::string);
    const char* characters = "...#FIo";
    void printMaze();
    void printGrid();
    void printTxt();
    void buildmaze();
};
