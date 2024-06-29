// dsu on tree
	std::vector<int> cnt(n + 1);
	std::vector<ll> res(n);
	int mx = 0;
	ll ans = 0;

	auto add = [&](int x)
	{
		x = c[x];
		cnt[x]++;
		if (cnt[x] > mx)
		{
			mx = cnt[x];
			ans = x;
		}
		else if (cnt[x] == mx)
		{
			ans += x;
		}
	};

	auto del = [&](int x)
	{
		x = c[x];
		cnt[x]--;
	};

	function<void(int, int)> calc = [&](int x, int kepp) -> void
	{
		// 1.先走轻儿子
		for (auto y : tr.adj[x])
		{
			if (y != tr.adj[x][0])
			{
				calc(y, -1);
			}
		}
		// 2.再走重儿子
		if (!tr.adj[x].empty())
		{
			calc(tr.adj[x][0], 1);
			// 3. 加回轻儿子贡献
			for (auto y : tr.adj[x])
			{
				if (y != tr.adj[x][0])
				{
					for (int i = tr.in[y]; i < tr.out[y]; ++i)
					{
						add(tr.seq[i]);
					}
				}
			}
		}
		// 4. 添加本身
		add(x);
		res[x] = ans;
		// 5. 轻儿子，清空信息
		if (kepp == -1)
		{
			ans = mx = 0;
			for (int i = tr.in[x]; i < tr.out[x]; ++i)
			{
				del(tr.seq[i]);
			}
		}
	};
	calc(0, -1);
