/* Projeto 2 - ASA
   Pedro Gomes - 93747
   Rafael Pereira - 93749 */

#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

int N, K;

int bfs(vector<vector<int>> rGraph, int s, int t, int parent[]) {
	bool visited[N + 2];
	memset(visited, 0, sizeof(visited));

	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < N + 2; v++) {
			if (!visited[v] && rGraph[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true);
}

void dfs(vector<vector<int>> rGraph, int s, bool visited[]) {
	visited[s] = true;
	queue <int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		if (!visited[u]){
            visited[u] = true;
        }

		for (int v = 0; v < N + 2; v++) {
			if (!visited[v] && rGraph[u][v] > 0) {
				q.push(v);
				visited[v] = true;
			}
		}
	}
}

int minCut(vector<vector<int>> graph, int s, int t) {
	int u, v;
	int x = 0;

	vector<vector<int>> rGraph;
	for (u = 0; u < N + 2; u++){
		vector<int> row;
		for (v = 0; v < N + 2; v++){
			row.push_back(graph[u][v]);
		}
		rGraph.push_back(row);
	}

	int parent[N + 2];

	while (bfs(rGraph, s, t, parent)) {
		int path_flow = INT_MAX;
		for (v=t; v!=s; v=parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		for (v=t; v != s; v=parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
	}

	bool visited[N + 2];
	memset(visited, false, sizeof(visited));
	dfs(rGraph, s, visited);

	for (int i = 0; i < N + 2; i++){
		for (int j = 0; j < N + 2; j++){
			if (visited[i] && !visited[j] && graph[i][j]) {
				x += graph[i][j];
			}
		}
	}
	return x;
}

int main() {
	int x, y, c;
    vector<int> exec[2];
    vector<vector<int>> coms;
    vector<vector<int>> graph;
    
    if (scanf("%d %d", &N, &K) != 2 && N < 2 && K < 0) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
  		vector<int> row;
    	scanf("%d %d", &x, &y);
    	exec[0].push_back(x);
    	exec[1].push_back(y);
    	for(int j = 0; j < N;j ++){
    		row.push_back(0);
    	}
    	coms.push_back(row);
  	}	

  	for (int j = 0; j < K; j++) {
    	scanf("%d %d %d", &x, &y, &c);
    	coms[x-1][y-1] = c;
    	coms[y-1][x-1] = c;
  	}

  	for(int i = 0;i < N + 2;i ++){
  		vector<int> row;
  		if(!i){
  			row.push_back(0);
  			for(int j = 0;j < N;j ++){
  				row.push_back(exec[1][j]);
  			}
  			row.push_back(0);
  		}
  		else if(i == N + 1){
  			row.push_back(0);
  			for(int j = 0;j < N;j ++){
  				row.push_back(exec[0][j]);
  			}
  			row.push_back(0);
  		}
  		else{
  			row.push_back(exec[1][i - 1]);
  			for(int j = 0;j < N;j ++){
  				row.push_back(coms[i - 1][j]);
  			}
  			row.push_back(exec[0][i - 1]);
		}
		graph.push_back(row);
  	}

	int comCost = minCut(graph, 0, N + 1);
	cout << comCost << endl;
	return 0;
}
