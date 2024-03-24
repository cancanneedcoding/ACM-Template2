struct Trie {
    static constexpr int N = 3000010, M = 65;
    int tot;
    int tr[N][M];
    int ends[N], prefix[N];
    void clear() {
        for (int i = 0; i <= tot; i++)
            memset(tr[i], 0, sizeof(tr[i]));
        for (int i = 0; i <= tot; i++)
            ends[i] = prefix[i] = 0;
        tot = 0;
        ends[0] = 0;
    }
    Trie() { tot = 0; }

    // 获取下标
    int getIndex(char x) {
        if (x >= 'a' && x <= 'z')
            return x - 'a';
        else if (x >= 'A' && x <= 'Z')
            return x - 'A' + 26;
        else
            return x - '0' + 52;
    }

    // 插入一个字符串
    void insert(string &s) {
        int p = 0;
        for (auto &ch : s) {
            int c = getIndex(ch);
            if (tr[p][c] == 0)
                tr[p][c] = ++tot;
            p = tr[p][c];
            prefix[p]++;
        }
        ends[p]++;
    }

    // 统计某个字符串出现次数
    int countWord(string &s) {
        int p = 0;
        for (auto &ch : s) {
            int c = getIndex(ch);
            if (tr[p][c] == 0)
                return 0;
            p = tr[p][c];
        }
        return ends[p];
    }

    // 统计某个字符串作为前缀出现的次数
    int countPrefix(string &s) {
        int p = 0;
        for (auto &ch : s) {
            int c = getIndex(ch);
            if (tr[p][c] == 0)
                return 0;
            p = tr[p][c];
        }
        return prefix[p];
    }
}
