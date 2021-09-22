#include "Node.h"

Node::Node() : parent(0, 0), coords(0, 0), g(0), f(0), h(0){};
void Node::showDetails()
{
    std::cout << "coords: " << coords.first << "," << coords.second << " parent: " << parent.first << "," << parent.second << " f: " << f << " g: " << g << " h: " << h << '\n';
}
bool operator<(const Node &a, const Node &b)
{
    return a.f < b.f;
}

bool operator>(const Node &a, const Node &b)
{
    return !(a < b);
}

bool operator==(const Node &a, const Node &b)
{
    return a.coords == b.coords;
}

bool operator!=(const Node &a, const Node &b)
{
    return !(a == b);
}