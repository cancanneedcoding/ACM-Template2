/*
维护信息：最大值,最小值,总和
特点：支持三个属性的线段树上二分
是否支持修改：支持单点修改
*/
class SegmentTree
{
private:
    struct Node
    {
        ll maxVal;
        ll minVal;
        ll sum;
    };

    vector<Node> tree;
    int n;

    void buildTree(const vector<int> &nums, int treeIndex, int lo, int hi)
    {
        if (lo == hi)
        {
            tree[treeIndex] = {nums[lo], nums[lo], nums[lo]};
            return;
        }

        int mid = lo + (hi - lo) / 2;
        int leftChild = 2 * treeIndex + 1;
        int rightChild = 2 * treeIndex + 2;

        buildTree(nums, leftChild, lo, mid);
        buildTree(nums, rightChild, mid + 1, hi);

        tree[treeIndex].maxVal =
            max(tree[leftChild].maxVal, tree[rightChild].maxVal);
        tree[treeIndex].minVal =
            min(tree[leftChild].minVal, tree[rightChild].minVal);
        tree[treeIndex].sum = tree[leftChild].sum + tree[rightChild].sum;
    }

    void updateTree(int treeIndex, int lo, int hi, int arrIndex, ll val)
    {
        if (lo == hi)
        {
            tree[treeIndex] = {val, val, val};
            return;
        }

        int mid = lo + (hi - lo) / 2;
        int leftChild = 2 * treeIndex + 1;
        int rightChild = 2 * treeIndex + 2;

        if (arrIndex <= mid)
        {
            updateTree(leftChild, lo, mid, arrIndex, val);
        }
        else
        {
            updateTree(rightChild, mid + 1, hi, arrIndex, val);
        }

        tree[treeIndex].maxVal =
            max(tree[leftChild].maxVal, tree[rightChild].maxVal);
        tree[treeIndex].minVal =
            min(tree[leftChild].minVal, tree[rightChild].minVal);
        tree[treeIndex].sum = tree[leftChild].sum + tree[rightChild].sum;
    }

    Node queryTree(int treeIndex, int lo, int hi, int i, int j)
    {
        if (lo > j || hi < i)
            return {INT_MIN, INT_MAX, 0}; // Out of range
        if (i <= lo && hi <= j)
            return tree[treeIndex]; // Segment is completely within range

        int mid = lo + (hi - lo) / 2;
        int leftChild = 2 * treeIndex + 1;
        int rightChild = 2 * treeIndex + 2;

        Node leftQuery = queryTree(leftChild, lo, mid, i, j);
        Node rightQuery = queryTree(rightChild, mid + 1, hi, i, j);

        // Merge left and right query results
        return {max(leftQuery.maxVal, rightQuery.maxVal),
                min(leftQuery.minVal, rightQuery.minVal),
                leftQuery.sum + rightQuery.sum};
    }

    ll binarySearchSum(int treeIndex, int curLo, int curHi, ll target,
                       ll &acc)
    {
        if (curLo == curHi)
        {
            if (acc + tree[treeIndex].sum >= target)
                return curLo;
            acc += tree[treeIndex].sum;
            return -1;
        }

        int mid = curLo + (curHi - curLo) / 2;
        int leftChild = 2 * treeIndex + 1;
        int rightChild = 2 * treeIndex + 2;

        if (tree[leftChild].sum + acc >= target)
        {
            return binarySearchSum(leftChild, curLo, mid, target, acc);
        }
        else
        {
            acc += tree[leftChild].sum;
            return binarySearchSum(rightChild, mid + 1, curHi, target, acc);
        }
    }

    ll binarySearchMax(int treeIndex, int curLo, int curHi, int targetLo,
                       int targetHi, ll target)
    {
        if (curHi < targetLo || curLo > targetHi ||
            tree[treeIndex].maxVal < target)
        {
            // 当前区间与目标区间不重叠或者区间的最大值小于target
            return -1;
        }
        if (curLo == curHi)
        {
            // 叶节点，已经是单个元素的区间
            return tree[treeIndex].maxVal >= target ? curLo : -1;
        }

        int mid = curLo + (curHi - curLo) / 2;
        int leftChild = 2 * treeIndex + 1;
        int rightChild = 2 * treeIndex + 2;
        int res = -1;

        // 先尝试在左子树中查找
        if (mid >= targetLo)
        { // 只有当左子树可能包含目标区间时才搜索
            res = binarySearchMax(leftChild, curLo, mid, targetLo, targetHi,
                                  target);
        }

        // 如果左子树没有找到，并且右子树可能包含目标区间，才在右子树中搜索
        if (res == -1 && mid < targetHi && tree[rightChild].maxVal >= target)
        {
            res = binarySearchMax(rightChild, mid + 1, curHi, targetLo,
                                  targetHi, target);
        }

        return res;
    }

    ll binarySearchMin(int treeIndex, int curLo, int curHi, int targetLo,
                       int targetHi, ll target)
    {
        if (curHi < targetLo || curLo > targetHi ||
            tree[treeIndex].minVal > target)
        {
            // 当前区间与目标区间不重叠或者区间的最小值大于target
            return -1;
        }
        if (curLo == curHi)
        {
            // 叶节点，已经是单个元素的区间
            return tree[treeIndex].minVal <= target ? curLo : -1;
        }

        int mid = curLo + (curHi - curLo) / 2;
        int leftChild = 2 * treeIndex + 1;
        int rightChild = 2 * treeIndex + 2;
        int res = -1;

        // 先尝试在左子树中查找
        if (mid >= targetLo &&
            tree[leftChild].minVal <=
                target)
        { // 只有当左子树可能包含目标区间时才搜索
            res = binarySearchMin(leftChild, curLo, mid, targetLo, targetHi,
                                  target);
        }

        // 如果左子树没有找到，并且右子树可能包含目标区间，才在右子树中搜索
        if (res == -1 && mid < targetHi)
        {
            res = binarySearchMin(rightChild, mid + 1, curHi, targetLo,
                                  targetHi, target);
        }

        return res;
    }

public:
    SegmentTree(const vector<int> &nums)
    {
        n = nums.size();
        tree.resize(4 * n);
        buildTree(nums, 0, 0, n - 1);
    }
    SegmentTree()
    {
    }
    // 将下标 index 的值修改为 val
    void update(int index, ll val) { updateTree(0, 0, n - 1, index, val); }

    // 查询区间 [i,j] 第一个大于等于 target 的下标
    ll binarySearchMax(int i, int j, ll target)
    {
        return binarySearchMax(0, 0, n - 1, i, j, target);
    }

    // 查询区间 [i,j] 第一个小于等于 target 的下标
    ll binarySearchMin(int i, int j, ll target)
    {
        return binarySearchMin(0, 0, n - 1, i, j, target);
    }

    // 查询区间 [i,j] 的最小值
    ll queryMin(int i, int j) { return queryTree(0, 0, n - 1, i, j).minVal; }

    // 查询区间 [i,j] 的最大值
    ll queryMax(int i, int j) { return queryTree(0, 0, n - 1, i, j).maxVal; }

    // 查询区间 [i,j] 的总和
    ll querySum(int i, int j) { return queryTree(0, 0, n - 1, i, j).sum; }

    // 找到第一个下标 i,使得 [0,i] 的总和大于等于 target
    int findTargetSumIndex(ll target)
    {
        ll acc = 0;
        return binarySearchSum(0, 0, n - 1, target, acc);
    }
};
