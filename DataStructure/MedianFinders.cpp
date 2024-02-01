// 对顶堆：动态维护区间中位数
class MedianFinder
{
private:
    multiset<int> minSet, maxSet;
    ll sumMinSet = 0, sumMaxSet = 0;

    // 调整两个 multiset，保持平衡
    void balanceSets()
    {
        while (maxSet.size() > minSet.size() + 1)
        {
            auto it = prev(maxSet.end());
            sumMaxSet -= *it;
            sumMinSet += *it;
            minSet.insert(*it);
            maxSet.erase(it);
        }
        while (minSet.size() > maxSet.size())
        {
            auto it = minSet.begin();
            sumMinSet -= *it;
            sumMaxSet += *it;
            maxSet.insert(*it);
            minSet.erase(it);
        }
    }

public:
    MedianFinder() {}

    void clear()
    {
        minSet.clear();
        maxSet.clear();
        sumMinSet = 0;
        sumMaxSet = 0;
    }

    void add(int num)
    {
        if (maxSet.empty() || num <= *maxSet.rbegin())
        {
            maxSet.insert(num);
            sumMaxSet += num;
        }
        else
        {
            minSet.insert(num);
            sumMinSet += num;
        }

        balanceSets();
    }

    int findMedian()
    {

        return *maxSet.rbegin();
    }

    void removeNum(int num)
    {
        auto itMax = maxSet.find(num);
        if (itMax != maxSet.end())
        {
            sumMaxSet -= num;
            maxSet.erase(itMax);
        }
        else
        {
            auto itMin = minSet.find(num);
            if (itMin != minSet.end())
            {
                sumMinSet -= num;
                minSet.erase(itMin);
            }
        }

        balanceSets();
    }

    // 获取最小堆的总和
    ll getSumMinSet() const
    {
        return sumMinSet;
    }

    // 获取最大堆的总和
    ll getSumMaxSet() const
    {
        return sumMaxSet;
    }
};
