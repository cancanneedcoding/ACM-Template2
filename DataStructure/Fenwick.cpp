/*
树状数组
*/
template <typename T>
struct Fenwick
{
    int n;
    std::vector<T> a;

    Fenwick(int n = 0)
    {
        init(n);
    }

    void init(int n)
    {
        this->n = n;
        a.assign(n + 1, T());
    }

    void add(int x, T v)
    {
        for (; x <= n; x += x & (-x))
        {
            a[x] += v;
        }
    }

    T sum(int x)
    {
        auto ans = T();
        for (; x; x -= x & (-x))
        {
            ans += a[x];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }
    // 求小于等于 s 的最小下标
    int kth(T s)
    {
        int pos = 0;
        for (int j = 18; j >= 0; j--)
        {
            if (pos + (1 << j) <= n && a[pos + (1 << j)] <= s)
            {
                pos += (1 << j);
                s -= a[pos];
            }
        }
        return pos;
    }
};
