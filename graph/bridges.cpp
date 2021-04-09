/* ref : https://codeforces.com/blog/entry/68138
usage : https://codeforces.com/contest/118/submission/86184466
https://pastebin.com/ATwq4mJa
low implementation : https://pastebin.com/7MWuxdLQ
*/
int lvl[N+1];
int dp[N+1];
vector<pii> ans ;
// idea :  dp[u] is the number of back-edges passing over the edge between u and its parent
// dp[u]=(# of back-edges going up from u)−(# of back-edges going down from u)+∑dp[v]v is a child of u.
void dfs(int u , int par =1){
	// bridge iff dp[u] = 0 ;
	lvl[u] = lvl[par] + 1 ;
	trav(v,adj[u]){
		if(lvl[v]!=0){ // not parent
			if(v==par) continue;
			if(lvl[v] > lvl[u]){
				dp[u]--;
				ans.pb({v,u}) ; 
			}
			else if(lvl[u] > lvl[v]) dp[u]++;
		}
		else {
			dfs(v,u);
			ans.pb({u,v}) ; // add desc.
			dp[u]+=dp[v];
		}
	}
	//trace(dp[u]);
	if(dp[u] ==0 and u!=par){ 
		cout << 0 << endl; 
		exit(0) ;
	}
}
