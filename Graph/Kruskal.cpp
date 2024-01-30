
// 并查集模版：https://github.com/cancanneedcoding/ACM-Template2/blob/main/DataStructure/DSU.cpp
long long kruskal(int n, std::vector<std::array<int, 3>> &edges)
{
    // 初始化并查集
    DSU dsu(n);

    // 将边按照权重从小到大排序
    std::sort(edges.begin(), edges.end(), [](const std::array<int, 3> &a, const std::array<int, 3> &b)
              {
                  return a[0] < b[0]; // 按照权重排序
              });

    long long mst_cost = 0; // 最小生成树的权重和
    int edges_used = 0;     // 已使用的边的数量

    // 遍历所有边
    for (const auto &edge : edges)
    {
        int w = edge[0], u = edge[1], v = edge[2];

        // 如果 u 和 v 不在同一个集合中，即这条边不会构成环
        if (dsu.merge(u, v))
        {
            mst_cost += w; // 累加权重
            edges_used++;  // 已使用边的数量增加

            // 如果已经使用了 n-1 条边，则提前结束循环
            if (edges_used == n - 1)
            {
                break;
            }
        }
    }

    // 如果使用的边数不足以构成树，则不存在最小生成树
    if (edges_used != n - 1)
    {
        return -1;
    }

    return mst_cost; // 返回最小生成树的权重和
}
