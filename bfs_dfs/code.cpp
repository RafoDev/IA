#include <bits/stdc++.h>
#define N 20
using namespace std;
int dirx[8]={0,0,-1,1,1,-1,-1,1};
int diry[8]={1,-1,0,0,1,-1,1,-1};
//const int N =20;
int mat[N][N]={};
int mat_bfs[N][N];
//int **mat;
void print_matrix(int matx[N][N])
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
            //cout<<mat[i][j];
			if(matx[i][j] == 3)
				cout<<"o ";
			else if(matx[i][j] == 1)
				cout<<"# ";
			else
				cout<<". ";
		}
		cout<<endl;
	}
}
void llenar_mat(int mat[N][N], string filename)
{
    std::string line;
    std::ifstream file(filename+".txt");
    int i = 0;
    while (std::getline(file,line))
    {
        for(int e = 0; e<N; e++)
        {
            int num;
            std::stringstream ss;
            ss << line[e];
            ss >> num;
            mat[i][e] = num;
        }
        i++;
    }
}
void buildGridFromTxt(std::string fileName, int **grid)
{
    std::string line;
    std::ifstream file(fileName+".txt");
    int j{0}, i{0};
    grid = new int *[N];
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            j = 0;
            grid[i] = new int[N]{0};
            for (int k = 0; k < N; k++)
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

int check_dir(int x, int y)
{
	if(x<0 || x>N-1 || y<0 || y>N-1 || mat[x][y]!=0)
		return false;
	else
		return true;
}
void bfs(int x1, int y1, int x2, int y2) {
	bool visited[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			visited[i][j] = false;

	list <pair<int, int>> queue;
	pair <int, int> aux;

	visited[x1][y1] = true;
	aux.first = x1;
	aux.second = y1;
	queue.push_back(aux);

	while (!queue.empty()) {
		aux = queue.front();
		mat_bfs[aux.first][aux.second] = 3;
		queue.pop_front();

		x1 = aux.first;
		y1 = aux.second;

		for (int i = 0; i < 8; i++) {
			int newx = x1 + dirx[i];
			int newy = y1 + diry[i];
			if (check_dir(newx, newy)) {
				if (visited[newx][newy] == false) {
					visited[newx][newy] = true;
					aux.first = newx;
					aux.second = newy;
					queue.push_back(aux);
				}	
			}
		}
		
	}
	print_matrix(mat_bfs);
}
void dfs(int x1, int y1, int x2, int y2)
{
	for(int i=0; i < 8; i++)
	{
		int newx = x1+dirx[i];
		int newy = y1+diry[i];
		if(check_dir(newx, newy))
		{
			//cout<<newx<<"   "<<newy<<endl;
			mat[newx][newy] = 3;
			//print_matrix();
			if(newx == x2 && newy == y2)
			{
				mat[newx][newy] = 5;
				print_matrix(mat);
			}
			else
				dfs(newx,newy, x2, y2);
		}
	}
	//mat[x1][y1]==2;
}
void copiar_matriz(int mat[N][N])
{
    for(int i=0; i<N;i++)
    {
        for(int e=0;e<N;e++)
            mat_bfs[i][e]=mat[i][e];
    }
}
int main()
{
    llenar_mat(mat, "maze_20");
    mat[1][1] = 3;
    mat_bfs[1][1]=3;
    copiar_matriz(mat);
    cout<<"///////////////////////////////////////////////////////////////////"<<endl;
    cout<<"//                      Algoritmo BFS                            //"<<endl;
    cout<<"///////////////////////////////////////////////////////////////////"<<endl;
	cout<<"Laberinto antes:"<<endl;
    print_matrix(mat_bfs);
    cout<<endl;
    cout<<"Laberinto despues:"<<endl;
    bfs(1,1,N-1,N-1);
    cout<<endl;
    cout<<"///////////////////////////////////////////////////////////////////"<<endl;
    cout<<"//                      Algoritmo BFS                            //"<<endl;
    cout<<"///////////////////////////////////////////////////////////////////"<<endl;
    cout<<"Laberinto antes:"<<endl;
    print_matrix(mat);
    cout<<endl;
    cout<<"Laberinto despues:"<<endl;
    dfs(1,1,N-1,N-1);
	return 0;
}
