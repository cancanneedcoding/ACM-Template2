// 对顶堆：动态维护区间中位数
class MedianFinder
{
private:
    multiset<int> minSet, maxSet;

    // 调整两个 multiset，保持平衡
    void balanceSets()
    {
        // 如果最大堆比最小堆多了两个元素，将最大堆的最大元素移动到最小堆
        if (maxSet.size() > minSet.size() + 1)
        {
            auto it = prev(maxSet.end());
            minSet.insert(*it);
            maxSet.erase(it);
        }
        // 如果最小堆比最大堆多了一个元素，将最小堆的最小元素移动到最大堆
        else if (minSet.size() > maxSet.size())
        {
            auto it = minSet.begin();
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
    }

    void add(int num)
    {
        if (maxSet.empty() || num <= *maxSet.rbegin())
        {
            maxSet.insert(num);
        }
        else
        {
            minSet.insert(num);
        }

        balanceSets();
    }

    double findMedian()
    {
        if (maxSet.size() == minSet.size())
        {
            return (*maxSet.rbegin() + *minSet.begin()) / 2.0; // 偶数个元素，取平均值
        }
        else
        {
            return *maxSet.rbegin(); // 奇数个元素，取最大堆的最大值
        }
    }

    void removeNum(int num)
    {
        if (!maxSet.empty() && num <= *maxSet.rbegin())
        {
            auto it = maxSet.find(num);
            if (it != maxSet.end())
            {
                maxSet.erase(it);
            }
        }
        else
        {
            auto it = minSet.find(num);
            if (it != minSet.end())
            {
                minSet.erase(it);
            }
        }

        balanceSets();
    }
};
