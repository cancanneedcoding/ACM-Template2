struct TreeDiameterFinder
{
    int n;
    std::vector<std::vector<int>> edges;
    std::vector<int> dp;
    int diameter;

    TreeDiameterFinder(int size, const std::vector<std::vector<int>> &edges) : n(size), edges(edges), dp(size), diameter(0) {}

    int dfs(int u, int parent)
    {
        int maxDepth1 = 0;
        int maxDepth2 = 0;

        for (int v : edges[u])
        {
            if (v == parent)
                continue;
            int depth = dfs(v, u) + 1;
            if (depth > maxDepth1)
            {
                maxDepth2 = maxDepth1;
                maxDepth1 = depth;
            }
            else if (depth > maxDepth2)
            {
                maxDepth2 = depth;
            }
        }

        diameter = std::max(diameter, maxDepth1 + maxDepth2);

        return dp[u] = maxDepth1;
    }

    // 求点 v 所在树的直径
    int work(int v)
    {
        diameter = 0;
        dfs(v, -1);
        return diameter;
    }
};
