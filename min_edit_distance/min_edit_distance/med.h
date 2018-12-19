#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int min_edit_distance(const string& s1, const string& s2) {
	int sz1 = s1.size();
	int sz2 = s2.size();
	vector<vector<int>> dp(sz1+1, vector<int>(sz2+1, 0));
	for (int i = 1; i <= sz1; ++i)
		dp[i][0] = i;
	for (int j = 1; j <= sz2; ++j)
		dp[0][j] = j;
	for (int i = 1; i <= sz1; ++i) {
		for (int j = 1; j <= sz2; ++j) {
			dp[i][j] = min(min(dp[i - 1][j]+1, dp[i][j - 1]+1), s1[i-1] == s2[j-1] ? dp[i-1][j-1] : dp[i-1][j-1]+2);
		}
	}
	return dp[sz1][sz2];
}