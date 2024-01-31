std::vector<int> discretize(const std::vector<int> &vec)
{
    std::vector<int> sorted_vec(vec);

    std::sort(sorted_vec.begin(), sorted_vec.end());

    sorted_vec.erase(unique(sorted_vec.begin(), sorted_vec.end()), sorted_vec.end());

    std::vector<int> result;
    result.reserve(vec.size());
    for (int v : vec)
    {
        int discrete_value = lower_bound(sorted_vec.begin(), sorted_vec.end(), v) - sorted_vec.begin();
        result.push_back(discrete_value);
    }

    return result;
}
