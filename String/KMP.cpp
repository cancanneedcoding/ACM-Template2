struct KMP
{
    string s, t;
    vector<int> next;

    KMP(const string &s, const string &t) : s(s), t(t)
    {
        init();
    }

    void init()
    {
        next.resize(t.size() + 1);
        next[0] = next[1] = 0;
        for (int i = 1, j = 0; i < t.size(); i++)
        {
            while (j > 0 && t[i] != t[j])
                j = next[j];
            if (t[i] == t[j])
                j++;
            next[i + 1] = j;
        }
    }

    // 返回 t 在 s 中出现的所有下标
    vector<int> match()
    {
        vector<int> res;
        for (int i = 0, j = 0; i < s.size(); i++)
        {
            while (j > 0 && s[i] != t[j])
                j = next[j];
            if (s[i] == t[j])
                j++;
            if (j == t.size())
            {
                res.push_back(i - j + 1);
                j = next[j];
            }
        }
        return res;
    }
};
