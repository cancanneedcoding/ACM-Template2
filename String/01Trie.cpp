class Node {
public:
    array<Node *, 2> children{};
    int cnt = 0;    // 子树大小
};

class Trie {
    static const int HIGH_BIT = 31;

public:
    Node *root = new Node();

    // 添加 val
    void insert(ll val) {
        Node *cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            if (cur->children[bit] == nullptr) {
                cur->children[bit] = new Node();
            }
            cur = cur->children[bit];
            cur->cnt++;    // 维护子树大小
        }
    }

    // 删除 val，但不删除节点
    // 要求 val 必须在 trie 中
    void remove(ll val) {
        Node *cur = root;
        for (int i = HIGH_BIT; i >= 0; i--) {
            cur = cur->children[(val >> i) & 1];
            cur->cnt--;    // 维护子树大小
        }
    }

    // 返回 val 与 trie 中一个元素的最大异或和
    // 要求 trie 不能为空
    int max_xor(ll val) {
        Node *cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            // 如果 cur.children[bit^1].cnt == 0，视作空节点
            if (cur->children[bit ^ 1] && cur->children[bit ^ 1]->cnt) {
                ans |= 1 << i;
                bit ^= 1;
            }
            cur = cur->children[bit];
        }
        return ans;
    }

    // 返回 val 与 trie 中一个元素的最小异或和
    // 要求 trie 不能为空
    int min_xor(ll val) {
        Node *cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int bit = (val >> i) & 1;
            // 优先选择与当前位相同的位，如果不存在或者计数为0，则选择相反的位
            if (cur->children[bit] && cur->children[bit]->cnt) {
                cur = cur->children[bit];
            } else {
                ans |= 1 << i;
                cur = cur->children[bit ^ 1];
            }
        }
        return ans;
    }
};
