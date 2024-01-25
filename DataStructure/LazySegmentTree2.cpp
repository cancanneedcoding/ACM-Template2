/*
懒标记线段树
模版来源：jiangly
支持区间赋值区间修改
*/
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

    void rangeAssign(int p, int l, int r, int x, int y, ll value)
    {
        if (l >= y || r <= x)
        {
            return;
        }
        if (l >= x && r <= y)
        {
            apply(p, Tag{value, true});
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeAssign(2 * p, l, m, x, y, value);
        rangeAssign(2 * p + 1, m, r, x, y, value);
        pull(p);
    }

    void rangeAssign(int l, int r, ll value)
    {
        rangeAssign(1, 0, n, l, r, value);
    }
};

ll inf = 1e18;

struct Tag
{
    ll add = 0;          // 区间加法标记
    bool assign = false; // 标记是否进行区间赋值
    ll value;            // 区间赋值的值

    // 默认构造函数
    Tag()
    {
    }

    // 区间赋值操作的构造函数
    Tag(ll v, bool a) : value(v), assign(a)
    {
        if (assign)
        {
            add = 0; // 当进行区间赋值时，重置加法标记
        }
    }

    Tag(ll v) : add(v)
    {
    }
    // 更新标记
    void apply(const Tag &t)
    {
        // 如果有区间赋值的标记，更新当前标记为赋值
        if (t.assign)
        {
            assign = true;
            value = t.value;
            add = 0; // 区间赋值时忽略加法标记
        }
        // 如果在被赋值后出现增加情况，则直接增加赋值的值
        else if (assign)
        {
            value += t.add;
        }
        // 否则累加加法标记
        else
        {
            add += t.add;
        }
    }
};

struct Info
{
    int len;       // 区间长度
    long long sum; // 区间和
    long long mx;  // 区间最大值
    long long mi;  // 区间最小值

    Info() : len(1), sum(0), mx(-inf), mi(inf) {}
    Info(ll value) : len(1), sum(value), mx(value), mi(value)
    {
    }
    // 信息更新函数，根据标记t来更新当前信息
    void apply(const Tag &t)
    {
        if (t.assign)
        {
            // 如果有区间赋值的标记，更新信息
            sum = t.value * len;
            mx = mi = t.value;
        }

        // 覆盖和区间加并不冲突，先覆盖再看看是否需要添加
        if (t.add)
        {
            // 累加区间和，并更新最大最小值
            sum += t.add * len;
            mx += t.add;
            mi += t.add;
        }
    }
};
Info operator+(const Info &a, const Info &b)
{
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.mx = std::max(a.mx, b.mx);
    c.mi = std::min(a.mi, b.mi);
    return c;
}


