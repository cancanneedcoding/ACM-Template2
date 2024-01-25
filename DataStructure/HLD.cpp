
/*
模版来源：jiangly
树链剖分
*/
struct HLD
{
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;

    HLD() {}
    HLD(int n)
    {
        init(n);
    }
    void init(int n)
    {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }

    // 在节点 u 和 v 之间添加一条无向边。
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 对外的接口函数，开始执行重链剖分。
    void work(int root = 0)
    {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }

    // 第一遍深度优先搜索，计算每个节点的大小、深度、父节点，并对子节点按大小排序，保证重儿子在第一位。
    void dfs1(int u)
    {
        if (parent[u] != -1)
        {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for (auto &v : adj[u])
        {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]])
            {
                std::swap(v, adj[u][0]);
            }
        }
    }

    // 第二遍深度优先搜索，分配每个节点的进时间戳 in[u]，建立重链，并计算每个节点的出时间戳 out[u]。
    void dfs2(int u)
    {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u])
        {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }

    // 计算节点 u 和 v 的最近公共祖先（LCA）
    int lca(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[top[u]] > dep[top[v]])
            {
                u = parent[top[u]];
            }
            else
            {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }

    // 计算节点 u 和 v 之间的距离。
    int dist(int u, int v)
    {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    // 在树中从节点 u 向上跳 k 步，返回目标节点索引，如果不可能则返回 -1。
    int jump(int u, int k)
    {
        if (dep[u] < k)
        {
            return -1;
        }

        int d = dep[u] - k;

        while (dep[top[u]] > d)
        {
            u = parent[top[u]];
        }

        return seq[in[u] - dep[u] + d];
    }

    // 判断节点 u 是否是节点 v 的祖先
    bool isAncester(int u, int v)
    {
        return in[u] <= in[v] && in[v] < out[u];
    }

    // 在以 u 为根的树中，找到 v 的父节点
    int rootedParent(int u, int v)
    {
        std::swap(u, v);
        if (u == v)
        {
            return u;
        }
        if (!isAncester(u, v))
        {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y)
                                   { return in[x] < in[y]; }) -
                  1;
        return *it;
    }

    // 在以 u 为根的树上，计算以 v 为根的子树大小。
    int rootedSize(int u, int v)
    {
        if (u == v)
        {
            return n;
        }
        if (!isAncester(v, u))
        {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }

    // 在根变为 a 的情况下，求 b 与 c 的 LCA
    int rootedLca(int a, int b, int c)
    {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
