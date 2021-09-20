#include<tuple>
#include<iostream>
typedef std::pair<int,int> Pair;

struct Node
{
    Pair coords; 
    Pair parent;
    int g,f,h;
    Node();
    void showDetails();
};

bool operator < (const Node &a, const Node &b);

bool operator > (const Node &a, const Node &b);

bool operator == (const Node &a, const Node &b);

bool operator != (const Node &a, const Node &b);
