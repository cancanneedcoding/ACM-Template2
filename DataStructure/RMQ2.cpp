class SparseTable
{
private:
    std::vector<std::vector<int>> mx, mi;
    std::vector<int> logTable;

public:
    // 使用数组 arr 构造 ST 表
    SparseTable(const std::vector<int> &arr)
    {
        int n = arr.size();
        int maxLog = std::log2(n) + 1;
        mx.assign(n, std::vector<int>(maxLog));
        mi.assign(n, std::vector<int>(maxLog));
        logTable.assign(n + 1, 0);

        // 预处理对数表
        for (int i = 2; i <= n; i++)
        {
            logTable[i] = logTable[i / 2] + 1;
        }

        // 初始化 ST 表
        for (int i = 0; i < n; i++)
        {
            mx[i][0] = arr[i];
            mi[i][0] = arr[i];
        }

        // 动态规划填充表
        for (int j = 1; (1 << j) <= n; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
                mi[i][j] = std::min(mi[i][j - 1], mi[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // 查询区间 [l, r] 的最大值
    int querymax(int l, int r)
    {
        int j = logTable[r - l + 1];
        return std::max(mx[l][j], mx[r - (1 << j) + 1][j]);
    }

    // 查询区间 [l, r] 的最小值
    int querymin(int l, int r)
    {
        int j = logTable[r - l + 1];
        return std::min(mi[l][j], mi[r - (1 << j) + 1][j]);
    }
};
