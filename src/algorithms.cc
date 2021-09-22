#include "algorithms.h"

Pair movements[8]{
    {0, -1}, {0, 1}, {1, 0}, {-1, 0}, {-1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

void abs(int &a)
{
    a = (a < 0) ? -1 * a : a;
}
Pair sumPair(Pair a, Pair b)
{
    return Pair(a.first + b.first, a.second + b.second);
}

neighborType neighborChecker(Pair position, Grid myGrid)
{
    if (0 > position.first || 0 > position.second || position.first > myGrid.GRID_SIZE - 1 || position.second > myGrid.GRID_SIZE - 1)
        return neighborType::invalid;

    int nextcell = myGrid.grid[position.first][position.second];
    return neighborType(nextcell);
}

int computeH(Pair currentNode, Pair dest)
{
    int h = std::abs(dest.first - currentNode.first);
    h += std::abs(dest.second - currentNode.second);
    return h * 10;
}

void updateF(Queue &q, int position, int newF)
{
    Queue newQ;
    while (!q.empty())
    {
        if (q.top().second == position)
        {
            Pair tmp(newF, q.top().second);
            newQ.push(tmp);
        }
        else
        {
            newQ.push(q.top());
        }
        q.pop();
    }
    q = newQ;
}
void updateIndex(Queue &q, int position)
{
    Queue newQ;
    while (!q.empty())
    {
        if (q.top().second > position)
        {
            Pair tmp(q.top().first, q.top().second - 1);
            newQ.push(tmp);
        }
        else
        {
            newQ.push(q.top());
        }
        q.pop();
    }
    q = newQ;
}
//-------------------------------------------------aStar-------------------------------------------------
bool aStar(Pair src, Pair dest, Grid myGrid)
{
    myGrid.paintGrid(src, 1);
    myGrid.paintGrid(dest, 4);

    std::vector<Node> closedList;
    std::vector<Node> openList;

    Queue openListDetails;

    Node currentNode;
    currentNode.coords = src;
    int iterator{0};
    while (currentNode.coords != dest)
    {
        myGrid.paintGrid(currentNode.coords, 1);
        closedList.push_back(currentNode);

        for (int i = 0; i < 8; i++)
        {
            Pair nextPosition = sumPair(currentNode.coords, movements[i]);
            int movement = i >= 4 ? 14 : 10;
            if (neighborChecker(nextPosition,myGrid) == neighborType::empty || neighborChecker(nextPosition,myGrid) == neighborType::dest)
            {
                Node tmp;
                tmp.coords = nextPosition;
                tmp.parent = currentNode.coords;
                tmp.h = computeH(tmp.coords, dest);
                if (neighborChecker(nextPosition,myGrid) == neighborType::dest)
                {
                    myGrid.paintGrid(nextPosition, 1);
                    tmp.g = 0;
                    tmp.f = 0;
                }
                else
                {
                    myGrid.paintGrid(nextPosition, 2);
                    tmp.g = movement;
                    tmp.g += currentNode.g;
                    tmp.f = tmp.h + tmp.g;
                }
                openList.push_back(tmp);
                int aux = openList.size() - 1;
                openListDetails.push(Pair(tmp.f, iterator));
                iterator++;
            }
            if (neighborChecker(nextPosition,myGrid) == neighborType::neighbor)
            {
                int mov = movement;
                Node tmp;
                int j = 0;
                while (openList[j].coords != nextPosition)
                {
                    j++;
                }
                if (currentNode.g + mov < openList[j].g)
                {
                    openList[j].parent = currentNode.coords;
                    openList[j].g = mov;
                    openList[j].f = openList[j].h + openList[j].g;
                    updateF(openListDetails, j, openList[j].f);
                }
            }
        }
        if (openList.empty())
        {
            return false;
        }
        currentNode = openList[openListDetails.top().second];
        openList.erase(openList.begin() + openListDetails.top().second);
        int aux = openListDetails.top().second;
        openListDetails.pop();
        updateIndex(openListDetails, aux);
        iterator--;

    }
    myGrid.paintGrid(src, 5);
    myGrid.paintGrid(dest, 4);
    currentNode = closedList.back();
    Pair reversePath = closedList.back().coords;
    while (reversePath != src)
    {
        myGrid.paintGrid(reversePath, 6);
        reversePath = closedList.back().parent;
        closedList.pop_back();
    }
    return true;
}


using namespace std;
int dirx[8]={0,0,-1,1,1,-1,-1,1};
int diry[8]={1,-1,0,0,1,-1,1,-1};
//int mat[N][N];
#include<list>
//-------------------------------------------------bfs-------------------------------------------------

int check_dir(int x, int y, Grid mat)
{
	if(x<0 || x>mat.GRID_SIZE-1 || y<0 || y>mat.GRID_SIZE-1 || mat.grid[x][y]!=0)
		return false;
	else
		return true;
}


void bfs(int x1, int y1, int x2, int y2,Grid mat) {
	// bool visited[N][N];
    Grid visited;
    visited.GRID_SIZE = mat.GRID_SIZE;
    visited.buildGrid();
	for (int i = 0; i < mat.GRID_SIZE; i++)
		for (int j = 0; j < mat.GRID_SIZE; j++)
			visited.grid[i][j] = 0;

	list <pair<int, int>> queue;
	pair <int, int> aux;

	visited.grid[x1][y1] = 1;
	aux.first = x1;
	aux.second = y1;
	queue.push_back(aux);

	while (!queue.empty()) {
		aux = queue.front();
		mat.grid[aux.first][aux.second] = 6;
		queue.pop_front();

		x1 = aux.first;
		y1 = aux.second;

		for (int i = 0; i < 8; i++) {
			int newx = x1 + dirx[i];
			int newy = y1 + diry[i];
			if (check_dir(newx, newy,mat)) {
				if (visited.grid[newx][newy] == 0) {
					visited.grid[newx][newy] = 1;
					aux.first = newx;
					aux.second = newy;
					queue.push_back(aux);
				}	
			}
		}
	}
}
//-------------------------------------------------dfs-------------------------------------------------

void dfs(int x1, int y1, int x2, int y2,Grid mat)
{
	for(int i=0; i < 8; i++)
	{
		int newx = x1+dirx[i];
		int newy = y1+diry[i];
		if(check_dir(newx, newy, mat))
		{
			//cout<<newx<<"   "<<newy<<endl;
			mat.grid[newx][newy] = 6;
			//print_matrix();
			if(newx == x2 && newy == y2)
			{
                // mat.grid[x1,y1] = 4
				mat.grid[newx][newy] = 4;
				// print_matrix();
			}
			else
				dfs(newx,newy, x2, y2,mat);
		}
	}
	// mat.grid[x1][y1]=3;
}