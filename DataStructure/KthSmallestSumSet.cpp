
// 对顶堆：动态维护区间内前 k 小元素之和
template <typename T>
class   
{
public:
    multiset<ll> low, high;
    ll sum = 0;
    ll k;
    KThMinMax<T>(ll k) : k(k), sum(0)
    {
        low.clear();
        high.clear();
    }
    void insert(ll x)
    {
        low.insert(x);
        sum += x;
        if (low.size() > k)
        {
            ll d = *low.rbegin();
            sum -= d;
            high.insert(d);
            low.erase(low.find(d));
        }
    }
    void erase(ll x)
    {
        if (low.find(x) != low.end())
        {
            sum -= x;
            low.erase(low.find(x));
            if (low.size() < k and high.size() > 0)
            {
                ll x = *high.begin();
                high.erase(high.find(x));
                low.insert(x);
                sum += x;
            }
        }
        else if (high.find(x) != high.end())
        {
            high.erase(high.find(x));
        }
    }
};
