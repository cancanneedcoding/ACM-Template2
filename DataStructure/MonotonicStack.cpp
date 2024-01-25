/*
单调栈：寻找下一个大于等于自己的元素
*/
std::vector<int> nextmaxstack(const std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> result(n, n);
    std::stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] < nums[i])
        {
            st.pop();
        }
        if (!st.empty())
            result[i] = st.top();
        st.push(i);
    }

    return result;
}

/*
单调栈：寻找下一个小于等于自己的元素
*/
std::vector<int> nextminstack(const std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> result(n, n);
    std::stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] > nums[i])
        {
            st.pop();
        }
        if (!st.empty())
            result[i] = st.top();
        st.push(i);
    }

    return result;
}

/*
单调栈：寻找上一个大于等于自己的元素
*/
std::vector<int> premaxstack(const std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> result(n, -1);
    std::stack<int> st;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && nums[st.top()] < nums[i])
        {
            st.pop();
        }
        if (!st.empty())
            result[i] = st.top();
        st.push(i);
    }

    return result;
}

/*
单调栈：寻找上一个小于等于自己的元素
*/
std::vector<int> preminstack(const std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> result(n, -1);
    std::stack<int> st;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && nums[st.top()] > nums[i])
        {
            st.pop();
        }
        if (!st.empty())
            result[i] = st.top();
        st.push(i);
    }

    return result;
}
