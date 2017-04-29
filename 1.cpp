#include <vector>
#include <fstream>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

bool isActive(int x) {
    return x == 2 || x == 3;
}

bool isStable(int x) {
    return x == 2;
}

bool isUnstable(int x) {
    return x == 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int> > v(n, vector<int>(m, 0));
    vector<vector<int> > changes(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];

    while (k--) {
        vector<vector<int> > lazyChanges = v;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {

                int stableNear = 0, activeNear = 0;
                for (int dx = -1; dx <= 1; dx++)
                    for (int dy = -1; dy <= 1; dy++) {
                        if ((dx * dy == 0 && dx + dy != 0) && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m) {
                            if (isStable(v[i + dx][j + dy]))
                                stableNear++;
                            if (isActive(v[i + dx][j + dy]))
                                activeNear++;
                        }
                    }

                if (stableNear > 1) {
                    if (!isStable(v[i][j]))
                        changes[i][j]++;
                    lazyChanges[i][j] = 2;
                    continue;
                } else if (activeNear >= 1) {
                    if (!isUnstable(v[i][j]))
                        changes[i][j]++;
                    lazyChanges[i][j] = 3;
                    continue;
                } else {
                    if (isActive(v[i][j]))
                        changes[i][j]++;
                    lazyChanges[i][j] = 1;
                }
            }

        v = lazyChanges;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << changes[i][j] << " ";
        cout << "\n";
    }
    return 0;
}