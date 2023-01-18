// C * 3^N + (E log N) * (2^N)

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> dp;

vector<vector<int>> graph; 

unordered_map<int, int> subsetCost;

int applyPrimMst(int subset, int city) // (V+E)logV
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> marked(city, false);

    int minimumCost = 0;
    int startCity = log2(subset & -subset);
    pq.push({0, startCity});

    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();

        auto u = p.second;

        if (marked[u] == true)
            continue;

        minimumCost += p.first;

        marked[u] = true;

        for (int v = 0; v < city; v++)
        {
            if(u==v)
                continue;
                
            if (marked[v] == false and (subset >> v & 1))
                pq.push({graph[u][v],v});
        }
    }

    for (int i = 0; i < city; i++)
    {
        if ((subset >> i & 1) and !marked[i])
            return INT_MAX;
    }

    return minimumCost;
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

int minimizeConstructionCost()
{
    int numberOfCity, numberOfCountry, numberOfRoad;

    cin >> numberOfCity >> numberOfCountry >> numberOfRoad;

    graph = vector<vector<int>>(numberOfCity, vector<int>(numberOfCity, INT_MAX));

    dp = vector<vector<int>>(numberOfCountry, vector<int>(1 << numberOfCity, -1));

    for (int i = 0; i < numberOfRoad; i++)
    {
        int u, v, weight;
        cin >> u >> v >> weight;

        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    for (int sset = 1; sset < (1 << numberOfCity); sset++)
    {
        int minimumCost = applyPrimMst(sset, numberOfCity);
        subsetCost[sset] = minimumCost;
    }

    int ans = minimizeMaxCostDp(numberOfCity, numberOfCountry, 0, 0);

    return ans == INT_MAX ? -1 : ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

	auto ans = minimizeConstructionCost();

    cout<<ans<<"\n";

    return 0;
}