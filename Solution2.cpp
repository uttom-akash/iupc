// C * 3^N + (N^2) * 2^N

#include <bits/stdc++.h>

using namespace std;

class PrimMST // V*V
{
private:
    int nextMinCostCity(int numberOfCity, vector<int> &cost, vector<bool> &mstSet)
    {
        int min = INT_MAX, min_index = -1;

        for (int v = 0; v < numberOfCity; v++)
            if (mstSet[v] == false && cost[v] < min)
                min = cost[v], min_index = v;

        return min_index;
    }

public:
    int getMstCost(int subset, int city, vector<vector<int>> &graph)
    {
        vector<int> parent(city, -1), cost(city, INT_MAX);
        vector<bool> mstSet(city, false);

        int cityInSubset = 0;

        for (int i = 0; i < city; i++)
            cityInSubset += ((subset >> i) & 1);

        int startCity = log2(subset & -subset);

        cost[startCity] = 0;

        for (int count = 0; count < cityInSubset - 1; count++)
        {
            int u = nextMinCostCity(city, cost, mstSet);

            if (u == -1)
                break;

            mstSet[u] = true;

            for (int v = 0; v < city; v++)
                if ((subset >> v & 1) and mstSet[v] == false && graph[u][v] <= cost[v])
                    parent[v] = u, cost[v] = graph[u][v];
        }

        int totalCost = 0;
        for (int i = 0; i < city; i++)
        {
            if (i == startCity || !(subset >> i & 1))
                continue;

            totalCost = min(1LL * INT_MAX, 1LL * totalCost + graph[i][parent[i]]);
        }

        return totalCost;
    }
};

class Solution
{
public:
    vector<vector<int>> dp;

    unordered_map<int, int> subsetCost;

    int minimizeConstructionCost()
    {
        int numberOfCity, numberOfCountry, numberOfRoad;

        cin >> numberOfCity >> numberOfCountry >> numberOfRoad;

        auto graph = vector<vector<int>>(numberOfCity, vector<int>(numberOfCity, INT_MAX));

        dp = vector<vector<int>>(numberOfCountry, vector<int>(1 << numberOfCity, -1));

        for (int i = 0; i < numberOfRoad; i++)
        {
            int u, v, weight;
            cin >> u >> v >> weight;

            graph[u][v] = weight;
            graph[v][u] = weight;
        }

        auto prim = PrimMST();

        for (int sset = 1; sset < (1 << numberOfCity); sset++)
        {
            int minimumCost = prim.getMstCost(sset, numberOfCity, graph);
            subsetCost[sset] = minimumCost;
        }

        int ans = minimizeMaxCostDp(numberOfCity, numberOfCountry, 0, 0);

        return ans == INT_MAX ? -1 : ans;
    }

    int minimizeMaxCostDp(int numberOfCity, int numberOfCountry, int currentCountry, int mask)
    {
        if (mask == (1 << numberOfCity) - 1)
            return 0;

        if (currentCountry >= numberOfCountry)
            return INT_MAX;

        if (dp[currentCountry][mask] != -1)
            return dp[currentCountry][mask];

        dp[currentCountry][mask] = INT_MAX;

        int reverseMask = ((1 << numberOfCity) - 1) ^ mask;

        for (int sset = reverseMask;; sset = (sset - 1) & reverseMask)
        {
            int currSetCost = subsetCost[sset];

            int followingMinCost = minimizeMaxCostDp(numberOfCity, numberOfCountry, currentCountry + 1, mask | sset);

            dp[currentCountry][mask] = min(dp[currentCountry][mask], max(currSetCost, followingMinCost));

            if (sset == 0)
                break;
        }

        return dp[currentCountry][mask];
    }
};

int main()
{
    freopen("input.txt", "r", stdin);

    auto sol = Solution();

    auto ans = sol.minimizeConstructionCost();
    
    cout<<"Ans :"<<ans<<"\n";

    return 0;
}