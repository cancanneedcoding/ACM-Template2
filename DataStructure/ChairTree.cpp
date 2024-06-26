struct ChairTree
{
    int tot, n, inf; // tot 是节点总数计数器，n 是版本数，inf 是数组中可能的最大值
    vector<int> rs, ls, sum, root;
    vector<ll> sv; // rs 和 ls 分别表示右孩子和左孩子的索引，sum 表示节点的区间和，root 表示每个版本的根节点

    ChairTree() {}
    ChairTree(int _n, int _inf)
    { // 构造函数
        init(_n, _inf);
    }

    void init(int _n, int _inf)
    { // 初始化函数
        n = _n;
        inf = _inf;
        tot = 0;
        rs.resize(1, 0);
        ls.resize(1, 0);
        sum.resize(1, 0);
        sv.resize(1, 0);
        root.resize(n + 1, 0);
    }

    // 应用一个更新，构建一个新版本的线段树
    void apply(int v, int &u, int l, int r, int p)
    {
        u = ++tot;
        rs.emplace_back(); // 为新节点分配空间
        ls.emplace_back();
        sum.emplace_back();
        sv.emplace_back();
        ls.back() = ls[v],
        rs.back() = rs[v], sum.back() = sum[v] + 1, sv.back() = sv[v] + p;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (p <= mid)
            apply(ls[v], ls.back(), l, mid, p);
        else
            apply(rs[v], rs.back(), mid + 1, r, p);
    }

    void apply(int v1, int v2, int p)
    {
        apply(root[v1], root[v2], 1, inf, p);
    }

    int querymin(int u, int v, int l, int r, int k)
    {
        if (l == r)
            return l;
        int s = sum[ls[u]] - sum[ls[v]];
        int mid = (l + r) >> 1;
        if (s >= k)
            return querymin(ls[u], ls[v], l, mid, k);
        else
            return querymin(rs[u], rs[v], mid + 1, r, k - s);
    }

    // 查询区间 [l,r] 第 k 小值
    int querymin(int l, int r, int k)
    {
        return querymin(root[r], root[l], 1, inf, k);
    }

    // 查询区间 [l,r] 第 k 大值
    int querymax(int l, int r, int k)
    {
        return querymin(root[r], root[l], 1, inf, r - l + 1 - k);
    }

    ll querysv(int u, int v, int l, int r, int ql, int qr)
    {
        if (ql > qr || l > r)
        {
            return 0;
        }

        if (ql <= l && r <= qr)
        {
            return sv[u] - sv[v];
        }
        int mid = (l + r) >> 1;
        ll ans = 0;

        if (ql <= mid)
            ans += querysv(ls[u], ls[v], l, mid, ql, qr);
        if (mid < qr)
            ans += querysv(rs[u], rs[v], mid + 1, r, ql, qr);
        return ans;
    }

    // 查询区间 [l,r] 中值域 [ql,qr] 的出现总和
    ll querysv(int l, int r, int ql, int qr)
    {
        return querysv(root[r], root[l], 1, inf, ql, qr);
    }

    int querysum(int u, int v, int l, int r, int ql, int qr)
    {
        if (ql > qr || l > r)
        {
            return 0;
        }
        if (ql <= l && r <= qr)
        {
            return sum[u] - sum[v];
        }
        int mid = (l + r) >> 1;
        int ans = 0;

        if (ql <= mid)
            ans += querysum(ls[u], ls[v], l, mid, ql, qr);
        if (mid < qr)
            ans += querysum(rs[u], rs[v], mid + 1, r, ql, qr);
        return ans;
    }

    // 查询区间 [l,r] 中值域 [ql,qr] 的出现个数之和
    int querysum(int l, int r, int ql, int qr)
    {
        return querysum(root[r], root[l], 1, inf, ql, qr);
    }

    int query(int u, int v, int lca, int lca_f, int l, int r, int k)
    {
        if (l == r)
        {
            return l;
        }
        int s = sum[ls[u]] + sum[ls[v]] - sum[ls[lca]] - sum[ls[lca_f]];
        int mid = l + r >> 1;
        if (s >= k)
        {
            return query(ls[u], ls[v], ls[lca], ls[lca_f], l, mid, k);
        }
        else
        {
            return query(rs[u], rs[v], rs[lca], rs[lca_f], mid + 1, r, k - s);
        }
    }

    // 在树上点 u,v 之间查询第 k 小值
    int query(int u, int v, int lca, int lca_f, int k)
    {
        return query(root[u], root[v], root[lca], root[lca_f], 1, inf, k);
    }
};
