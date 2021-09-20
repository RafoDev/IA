#include "aStar.h"

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
