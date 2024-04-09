// 二维树状数组
template <typename T>
struct Fenwick {
	int n, m;
	vector<vector<T>> a;

	Fenwick(int n = 0, int m = 0) {
		init(n, m);
	}

	void init(int n, int m) {
		this->n = n;
		this->m = m;
		a.assign(n + 1, vector<T>(m + 1, T()));
	}

	void add(int x, int y, T v) {
		for (int i = x; i <= n; i += i & (-i))
			for (int j = y; j <= m; j += j & (-j))
				a[i][j] += v;
	}

	T sum(int x, int y) {
		auto ans = T();
		for (int i = x; i; i -= i & (-i))
			for (int j = y; j; j -= j & (-j))
				ans += a[i][j];
		return ans;
	}

	T rangeSum(int x1, int y1, int x2, int y2) {
		return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
	}
};
