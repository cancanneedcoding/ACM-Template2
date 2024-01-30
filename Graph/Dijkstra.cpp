std::vector<long long> dijkstra(const std::vector<std::vector<std::pair<int, long long>>> &adj, int start)
{
    int n = adj.size();
    std::vector<long long> dist(n, LLONG_MAX);
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
        {
            continue;
        }

        for (const auto &edge : adj[u])
        {
            int v = edge.first;
            long long weight = edge.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
