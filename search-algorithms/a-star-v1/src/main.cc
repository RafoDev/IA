#include "aStar.h"

int main()
{
    Grid test;
    // test.GRID_SIZE = 20;
    std::cin>>test.GRID_SIZE;
    Pair src(0, 0);
    Pair dest(test.GRID_SIZE-1,test.GRID_SIZE-1);
    // test.printGrid();
    // test.buildGridFromTxt("maze");
    test.buildGrid();
    test.buildmaze();
    if(aStar(src,dest,test))
    {
        test.printMaze();
    }
    else{
        std::cout<<"No tiene solución\n";
    }
    // test.printGrid();
    // test.printMaze();
    // // std::cin>>GRID_SIZE;
    // grid::GRID_SIZE = 100;
    // 

    // // buildGrid();
    // // buildmaze();
    // grid::buildGridFromTxt();
    // aStar(src, dest);
    // // printGrid();
    // grid::printMaze();
}