#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<double> > dp(k + 1, vector<double>(k, 0));
    dp[1][0] = 1;
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < i; j++) {
            dp[i + 1][j] += dp[i][j] * (1. * n * m - i + j) / (n * m);
            dp[i + 1][j + 1] += dp[i][j] * (1. * i - j) / (n * m);
        }
    }

    double ans = 0;
    for (int i = 0; i <= k; i++)
        ans += 1. * (k - i) * dp[k][i];
    cout << fixed << setprecision(12) << ans << "\n";
    return 0;
}