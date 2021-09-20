#include "grid.h"

void Grid::paintGrid(Pair coords, int newCellValue)
{
    grid[coords.first][coords.second] = newCellValue;
}
void Grid::buildGrid()
{
    grid = new int *[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++)
        grid[i] = new int[GRID_SIZE]{0};
}
void Grid::buildGridFromTxt(std::string fileName)
{
    std::string line;
    std::ifstream file(fileName+".txt");
    int j{0}, i{0};
    grid = new int *[GRID_SIZE];
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            j = 0;
            grid[i] = new int[GRID_SIZE]{0};
            for (int k = 0; k < GRID_SIZE; k++)
            {
                int num;
                std::stringstream ss;
                ss << line[k];
                ss >> num;
                grid[i][j] = num;
                j++;
            }
            i++;
        }
    }
    else{
        std::cout<<"Error abriendo el archivo\n";
    }
}
void Grid::printMaze()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
            std::cout << characters[grid[i][j]] << " ";
        std::cout << '\n';
    }
}
void Grid::printGrid()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
            std::cout << grid[i][j] << " ";
        std::cout << '\n';
    }
}
void Grid::printTxt()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
            std::cout << grid[i][j];
        std::cout << '\n';
    }
}

void Grid::buildmaze()
{
    Grid::buildGrid();
    std::srand(time(NULL));
    int k, l;
    for (int i = 0; i < GRID_SIZE * (GRID_SIZE/3); i++)
    {
        k = rand() % GRID_SIZE;
        l = rand() % GRID_SIZE;
        grid[k][l] = 3;
    }
}


