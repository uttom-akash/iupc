// C * 3^N + (E log N) * (2^N)

#include <bits/stdc++.h>
#define ll long long

using namespace std;

vector<vector<ll>> dp;

vector<vector<pair<ll, int>>> adjacancyList;

unordered_map<int, ll> subsetCost;

ll applyPrimMst(int subset, int city) // (V+E)logV
{
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    vector<bool> marked(city, false);

    ll minimumCost = 0;
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

        for (int i = 0; i < adjacancyList[u].size(); i++)
        {
            int v = adjacancyList[u][i].second;

            if (marked[v] == false and (subset >> v & 1))
                pq.push(adjacancyList[u][i]);
        }
    }

    for (int i = 0; i < city; i++)
    {
        if ((subset >> i & 1) and !marked[i])
            return LONG_LONG_MAX;
    }

    return minimumCost;
}

ll minimizeMaxCostDp(int numberOfCity, int numberOfCountry, int currentCountry, int mask)
{
    if (mask == (1 << numberOfCity) - 1)
        return 0;

    if (currentCountry >= numberOfCountry)
        return LONG_LONG_MAX;

    if (dp[currentCountry][mask] != -1)
        return dp[currentCountry][mask];

    dp[currentCountry][mask] = LONG_LONG_MAX;

    int reverseMask = ((1 << numberOfCity) - 1) ^ mask;

    for (int sset = reverseMask;; sset = (sset - 1) & reverseMask)
    {
        auto currSetCost = subsetCost[sset];

        auto followingMinCost = minimizeMaxCostDp(numberOfCity, numberOfCountry, currentCountry + 1, mask | sset);

        dp[currentCountry][mask] = min(dp[currentCountry][mask], max(currSetCost, followingMinCost));

        if (sset == 0)
            break;
    }

    return dp[currentCountry][mask];
}

ll minimizeConstructionCost()
{
    int numberOfCity, numberOfCountry, numberOfRoad;

    cin >> numberOfCity >> numberOfCountry >> numberOfRoad;

    if(numberOfCity <= numberOfCountry)
		return 0;

    adjacancyList = vector<vector<pair<ll, int>>>(numberOfCity);

    dp = vector<vector<ll>>(numberOfCountry, vector<ll>(1 << numberOfCity, -1));

    for (int i = 0; i < numberOfRoad; i++)
    {
        int u, v, weight;
        cin >> u >> v >> weight;

        adjacancyList[u].push_back({weight, v});
        adjacancyList[v].push_back({weight, u});
    }

    for (int sset = 1; sset < (1 << numberOfCity); sset++)
    {
        auto minimumCost = applyPrimMst(sset, numberOfCity);
        subsetCost[sset] = minimumCost;
    }

    auto ans = minimizeMaxCostDp(numberOfCity, numberOfCountry, 0, 0);

    return ans == LONG_LONG_MAX ? -1 : ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    auto ans = minimizeConstructionCost();

    cout<<ans<<"\n";

    return 0;
}