int LIS(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> tails; // 存储当前长度的 LIS 的末尾元素
        tails.push_back(nums[0]);

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > tails.back())
            {
                tails.push_back(nums[i]);
            }
            else
            {
                // 找到 nums[i] 可以插入的位置，并替换该位置的元素
                int left = 0, right = tails.size() - 1;
                while (left < right)
                {
                    int mid = (left + right) / 2;
                    if (tails[mid] < nums[i])
                        left = mid + 1;
                    else
                        right = mid;
                }
                tails[left] = nums[i];
            }
        }

        return tails.size();
    }
