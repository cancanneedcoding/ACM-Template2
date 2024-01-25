/*
线段树模版来源：jiangly
支持单点修改，维护最大值最小值总和
特点：findFirst 和 findLast 函数
*/
template <class Info>
struct SegmentTree
{
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }
    template <class T>
    SegmentTree(std::vector<T> init_)
    {
        init(init_);
    }
    void init(int n_, Info v_ = Info())
    {
        init(std::vector<Info>(n_, v_));
    }
    template <class T>
    void init(std::vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << (int)std::log2(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (r - l == 1)
            {
                info[p] = init_[l];
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
    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1)
        {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
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
    // 修改下标为 p 的值为 v
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
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    // 查询区间 [l,r)
    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F pred)
    {
        if (l >= y || r <= x || !pred(info[p]))
        {
            return -1;
        }
        if (r - l == 1)
        {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1)
        {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    // 从区间 [l,r) 找到第一个符合条件 pred 的下标，没找到返回 -1
    template <class F>
    int findFirst(int l, int r, F pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F>
    int findLast(int p, int l, int r, int x, int y, F pred)
    {
        if (l >= y || r <= x || !pred(info[p]))
        {
            return -1;
        }
        if (r - l == 1)
        {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1)
        {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    // 从区间 [l,r) 找到最后一个符合条件 pred 的下标，没找到返回 -1
    template <class F>
    int findLast(int l, int r, F pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }
};

const ll inf = 1e18;
// 维护区间总和，最大值，最小值
struct Info
{
    ll mi = inf;
    ll mx = -inf;
    ll sum = 0;
    Info()
    {
    }
    // 用于初始化线段树的构造函数
    Info(ll value) : mx(value), mi(value), sum(value) {}
};
Info operator+(Info a, Info b)
{
    Info c;
    c.mx = std::max(a.mx, b.mx); // 选取两个区间最大值中的较大者
    c.mi = std::min(a.mi, b.mi); // 选取两个区间最小值中的较小者
    c.sum = a.sum + b.sum;       // 两个区间的总和相加
    return c;
}

/*
例如，如果你想要找到线段树中最后一个 sum 字段值大于 5 的节点，你可以写一个如下的 pred 函数：
*/
auto pred = [](const Info &node)
{
    return node.sum > 5;
};
