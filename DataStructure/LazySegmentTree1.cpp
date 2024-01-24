template <class Info, class Tag>
struct LazySegmentTree
{
    const int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 << (int)std::log2(n)), tag(4 << (int)std::log2(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size())
    {
        std::function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (r - l == 1)
            {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v)
    {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p)
    {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1)
        {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m)
        {
            modify(2 * p, l, m, x, v);
        }
        else
        {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x)
        {
            return Info();
        }
        if (l >= x && r <= y)
        {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l >= y || r <= x)
        {
            return;
        }
        if (l >= x && r <= y)
        {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 0, n, l, r, v);
    }
    void half(int p, int l, int r)
    {
        if (info[p].act == 0)
        {
            return;
        }
        if ((info[p].min + 1) / 2 == (info[p].max + 1) / 2)
        {
            apply(p, {-(info[p].min + 1) / 2});
            return;
        }
        int m = (l + r) / 2;
        push(p);
        half(2 * p, l, m);
        half(2 * p + 1, m, r);
        pull(p);
    }
    void half()
    {
        half(1, 0, n);
    }
};

constexpr ll inf = 1E18;

// 标记
struct Tag
{
    ll add;
    Tag(int _rev = 0) : add{_rev} {}
    // 标记更新
    void apply(const Tag &t)
    {
        add += t.add;
    }
};
// 节点信息
struct Info
{
    int len;       // 区间长度
    long long sum; // 区间和

    // 默认构造函数
    Info() : len(1), sum(0) {}

    // 两参数构造函数，用于设置区间和和区间长度
    Info(long long v, int x) : len(x), sum(v) {}

    // 信息更新函数，根据标记t来更新当前信息
    void apply(const Tag &t)
    {
        sum += t.add * len; // 更新区间和，将标记的增加值乘以区间长度
    }
};
Info operator+(const Info &a, const Info &b)
{
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    return c;
}
