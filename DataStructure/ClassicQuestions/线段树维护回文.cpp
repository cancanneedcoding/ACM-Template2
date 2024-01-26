#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define sz(s) ((int)s.size())
#define ms(s, x) memset(s, x, sizeof(s))
const int inf = 0x3f3f3f3f;
const int mod = 1000000007;

/*
线段树维护回文，单点修改，区间判断回文
原题链接：https://atcoder.jp/contests/abc331/tasks/abc331_f
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

template <class T>
T power(T a, ll b)
{
    T res = 1;
    for (; b; b /= 2, a *= a)
    {
        if (b % 2)
        {
            res *= a;
        }
    }
    return res;
}

template <int P>
struct MInt
{
    int x;
    MInt() : x{} {}
    MInt(ll x) : x{norm(x % P)} {}

    int norm(int x)
    {
        if (x < 0)
        {
            x += P;
        }
        if (x >= P)
        {
            x -= P;
        }
        return x;
    }
    int val() const
    {
        return x;
    }
    MInt operator-() const
    {
        MInt res;
        res.x = norm(P - x);
        return res;
    }
    MInt inv() const
    {
        assert(x != 0);
        return power(*this, P - 2);
    }
    MInt &operator*=(const MInt &rhs)
    {
        x = 1LL * x * rhs.x % P;
        return *this;
    }
    MInt &operator+=(const MInt &rhs)
    {
        x = norm(x + rhs.x);
        return *this;
    }
    MInt &operator-=(const MInt &rhs)
    {
        x = norm(x - rhs.x);
        return *this;
    }
    MInt &operator/=(const MInt &rhs)
    {
        return *this *= rhs.inv();
    }
    friend MInt operator*(const MInt &lhs, const MInt &rhs)
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend MInt operator+(const MInt &lhs, const MInt &rhs)
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend MInt operator-(const MInt &lhs, const MInt &rhs)
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend MInt operator/(const MInt &lhs, const MInt &rhs)
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, MInt &a)
    {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const MInt &a)
    {
        return os << a.val();
    }
};

constexpr int P = 1000000007;
using Z = MInt<P>;

struct Info
{
    Z pw = 1;
    Z l = 0;
    Z r = 0;

    Info() {}
    Info(Z _pw, Z _l, Z _r) : pw(_pw), l(_l), r(_r)
    {
    }
};

Info operator+(const Info &a, const Info &b)
{
    return {a.pw * b.pw, a.l * b.pw + b.l, a.r + b.r * a.pw};
}

constexpr int B = 114514;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;

    std::string S;
    std::cin >> S;

    std::vector<Info> init(N);
    for (int i = 0; i < N; i++)
    {
        init[i] = {B, S[i], S[i]};
    }

    SegmentTree<Info> seg(init);
    while (Q--)
    {
        int o;
        std::cin >> o;

        if (o == 1)
        {
            int x;
            char c;
            std::cin >> x >> c;
            x--;
            seg.modify(x, {B, c, c});
        }
        else
        {
            int l, r;
            std::cin >> l >> r;
            l--;
            auto res = seg.rangeQuery(l, r);
            std::cout << (res.l.val() == res.r.val() ? "Yes" : "No") << "\n";
        }
    }

    return 0;
}
