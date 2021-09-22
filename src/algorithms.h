#include "Node.h"
#include "grid.h"
#include <queue>
#include <stdlib.h>
#include <time.h>
typedef std::tuple<int, int, int> Tuple;
typedef std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> Queue;


void abs(int &a);

Pair sumPair(Pair a, Pair b);

enum class neighborType
{
    empty,
    visited,
    neighbor,
    invalid,
    dest,
    src
};

neighborType neighborChecker(Pair position, Grid myGrid);

int computeH(Pair currentNode, Pair dest);

void updateF(Queue &q, int position, int newF);

void updateIndex(Queue &q, int position);

bool aStar(Pair src, Pair dest, Grid myGrid);

int check_dir(int x, int y, Grid mat);
void bfs(int x1, int y1, int x2, int y2,Grid mat);
void dfs(int x1, int y1, int x2, int y2,Grid mat);