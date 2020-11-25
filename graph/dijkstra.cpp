const int MAXN = 100, INF = 0x3f3f3f3f;
std::vector<std::pair<int, int> > adj[MAXN];
int dist[MAXN], pred[MAXN];

void dijkstra(int nodes, int start) {
  std::vector<bool> visit(nodes, false);
  for (int i = 0; i < nodes; i++) {
    dist[i] = INF;
    pred[i] = -1;
  }
  dist[start] = 0;
  std::priority_queue<std::pair<int, int> > pq;
  pq.push(std::make_pair(0, start));
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    visit[u] = true;
    for (int j = 0; j < (int)adj[u].size(); j++) {
      int v = adj[u][j].first;
      if (visit[v]) {
        continue;
      }
      if (dist[v] > dist[u] + adj[u][j].second) {
        dist[v] = dist[u] + adj[u][j].second;
        pred[v] = u;
        pq.push(std::make_pair(-dist[v], v));
      }
    }
  }
}

/*** Example Usage and Output:
The shortest distance from 0 to 3 is 5.
Take the path: 0->1->2->3.
***/

void print_path(int dest) {
  vector<int> path;
  for (int j = dest; pred[j] != -1; j = pred[j]) {
    path.push_back(pred[j]);
  }
  cout << "Take the path: ";
  while (!path.empty()) {
    cout << path.back() << "->";
    path.pop_back();
  }
  cout << dest << "." << endl;
}
