#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct StringHash
{
    int P;
    std::vector<int> h, p;

    StringHash(const std::string &s, int mod) : P(mod)
    {
        int n = s.length();
        h.resize(n + 1);
        p.resize(n + 1);
        p[0] = 1;
        for (int i = 0; i < n; i++)
        {
            h[i + 1] = (10LL * h[i] + s[i] - '0') % P;
            p[i + 1] = 10LL * p[i] % P;
        }
    }

    int getHash(int l, int r)
    {
        return (h[r] + 1LL * (P - h[l]) * p[r - l]) % P;
    }
};

bool isprime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int findPrime(int n)
{
    while (!isprime(n))
    {
        n++;
    }
    return n;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    const int P = findPrime(rng() % 900000000 + 100000000);

    int n, m;
    cin >> n >> m;

    std::string s;
    std::cin >> s;

    StringHash hashS(s, P);

    for (int i = 0; i < m; ++i)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (hashS.getHash(l1 - 1, r1) == hashS.getHash(l2 - 1, r2))
        {
            cout << "Yes" << '\n';
        }
        else
        {
            cout << "No" << '\n';
        }
    }

    return 0;
}
