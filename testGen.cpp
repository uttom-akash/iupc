#include <bits/stdc++.h>
#include "graphTest.h"

using namespace std;

int main()
{
    
    freopen("input.txt", "w", stdout);
    
    int city = 14, country = 14, roads = 91;

    auto g = Graph::random(city, roads).connected().g().shuffled();
    

    g.setEdgeWeights(Array::random(g.m(), (long long)10e10, (long long)10e16).shuffled());


    cout<<city<<" "<<country<<" "<<roads<<"\n"; 
    cout<<g<<"\n";
    
    return 0;
}