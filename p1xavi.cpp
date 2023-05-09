/* Projeto 1 - ASA
   Pedro Gomes - 93747
   Rafael Pereira - 93749 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int node, vector<int> adj[], int dp[], bool vis[]){
    stack<int> stack;
    unsigned int i;
    int visitAll = 0;
    stack.push(node);
    while(!stack.empty()){
        node = stack.top();
        if(vis[node])
            break;
        
        if(adj[node].size() > 0){
            visitAll = 1;
            for (i = 0; i < adj[node].size(); i++) {
                if (!vis[adj[node][i]]){
                    stack.push(adj[node][i]);
                    visitAll = 0;
                }
                else{
                    dp[node] = max(dp[node], 1 + dp[adj[node][i]]);
                }
            }
            if(visitAll){
                stack.pop();
                vis[node] = true;
            }
        }
        else{
            vis[node] = true;
            stack.pop();
        }
    }
}
  
void addEdge(vector<int> adj[], vector<int> adjINV[],int u, int v){
    adj[u].push_back(v);
    adjINV[v].push_back(u);
}

int findLongestPath(vector<int> adj[], int n){
    int dp[n + 1];
    bool vis[n + 1];

    for(int i = 1;i < n + 1;i ++){
        dp[i] = 1;
        vis[i] = false;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]){
            dfs(i, adj, dp, vis);
        }
    }
  
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    return ans;
}

int minimumMoves(vector<int> adjINV[], int n) {
    int min = 0;
    for (int i = 1; i < n + 1; i++) {
        if (adjINV[i].empty()) {
            min++;
        }
    }
    return min;
}

int main(){
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) {
        return 1;
    }
    vector<int> adj[N + 1];
    vector<int> adjINV[N + 1];
    for (int i = 0; i < M; i++) {
        int x, y;
        if (scanf("%d %d", &x, &y) != 2 || x > N || y > N) {
            return 1;
        }
        addEdge(adj, adjINV, x, y);
    }
    cout << minimumMoves(adjINV, N) << " " << findLongestPath(adj, N) << endl;
    return 0;
}