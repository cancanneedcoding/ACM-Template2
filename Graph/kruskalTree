// 克鲁斯卡尔重构树
    HLD tr(2 * n);
    DSU dsu(n), dsu2(n * 2);
    int tot = n;
    // 每个点的权值
    vector<int> t(2 * n);
    for (auto [w, u, v] : adj) {
        if (dsu.merge(u, v)) {
            tr.addEdge(dsu2.find(u), tot);
            tr.addEdge(dsu2.find(v), tot);
            dsu2.merge(tot, u);
            dsu2.merge(tot, v);
            t[tot] = -w;
            tot++;
        }
    }
    t[tot] = -1;
    for (int i = 0; i < tot; ++i) {
        if (dsu2.find(i) == i) {
            tr.addEdge(i, tot);
        }
    }
