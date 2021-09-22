#include "algorithms.h"
int main()
{
    int option{0};
    while(option!=4)
    {
        std::cout<<"-----------------------------------\n";
        std::cout<<"Algoritmos de Busqueda Disponibles\n";
        std::cout<<"(1) A-star\n";
        std::cout<<"(2) BFS\n";
        std::cout<<"(3) DFS\n";
        std::cout<<"(4) Salir\n";
        std::cin>>option;
        if(option>=4) return 0;
        Grid test;
        std::cout<<"Tamaño del plano: ";
        std::cin>>test.GRID_SIZE;
        test.buildGrid();
        // test.buildGridFromTxt("maze2");
        test.buildmaze();
        Pair src(0, 0);
        Pair dest(test.GRID_SIZE-1,test.GRID_SIZE-1);
        test.printMaze();
        std::cout<<"\n";
        switch (option)
        {
        case 1:
            aStar(src,dest,test);
            std::cout<<"Se utilizó A-star\n";
            break;    
        case 2:
            std::cout<<"Se utilizó BFS\n";
            bfs(src.first,src.second,dest.first,dest.second,test);
            break;
        case 3:
            std::cout<<"Se utilizó DFS\n";
            dfs(src.first,src.second,dest.first,dest.second,test);
            break;
        }
        test.printMaze();
    }
}