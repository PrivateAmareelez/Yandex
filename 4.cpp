#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

struct Star {
    double x, y;

    Star(double xx, double yy) {
        x = xx;
        y = yy;
    }
};

bool comp(Star a, Star b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool clockwise(Star a, Star b, Star c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool anticlockwise(Star a, Star b, Star c) {
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

vector<Star> makeConvexHull(vector<Star> &v) {
    if (v.size() <= 1) {
        return v;
    }

    vector<Star> ans;
    sort(v.begin(), v.end(), comp);

    Star left = v[0], right = v[v.size() - 1];
    vector<Star> up, down;
    up.push_back(left);
    down.push_back(left);

    for (int i = 1; i < v.size(); i++) {
        if (i == v.size() - 1 || clockwise(left, v[i], right)) {
            while (up.size() >= 2 && !clockwise(up[up.size() - 2], up[up.size() - 1], v[i]))
                up.pop_back();
            up.push_back(v[i]);
        }
        if (i == v.size() - 1 || anticlockwise(left, v[i], right)) {
            while (down.size() >= 2 && !anticlockwise(down[down.size() - 2], down[down.size() - 1], v[i])) {
                down.pop_back();
            }
            down.push_back(v[i]);
        }
    }

    for (int i = 0; i < up.size(); i++)
        ans.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        ans.push_back(down[i]);
    return ans;
}

bool isIntersecting(vector<Star> convex1, vector<Star> convex2) {
    bool exist = false;
    for (int i = 0; i < convex1.size() - 1; i++) {
        Star a = convex1[i], b = convex1[i + 1];

        if (clockwise(a, b, convex2[0]) == anticlockwise(a, b, convex2[0])) {
            continue;
        }

        bool neededOrientation = clockwise(a, b, convex2[0]);
        bool couldSeparate = true;

        for (int j = 1; j < convex2.size(); j++) {
            if (clockwise(a, b, convex2[j]) == anticlockwise(a, b, convex2[j])) {
                couldSeparate = false;
                break;
            }

            if (neededOrientation && clockwise(a, b, convex2[j]))
                continue;
            else if (!neededOrientation && anticlockwise(a, b, convex2[j]))
                continue;
            else {
                couldSeparate = false;
                break;
            }
        }

        for (int j = 0; j < convex1.size() - 1; j++) {
            if (clockwise(a, b, convex2[j]) == anticlockwise(a, b, convex2[j])) {
                couldSeparate = false;
                break;
            }

            if (neededOrientation && clockwise(a, b, convex1[j])) {
                couldSeparate = false;
                break;
            }
            else if (!neededOrientation && anticlockwise(a, b, convex1[j])) {
                couldSeparate = false;
                break;
            }
            else {
                continue;
            }
        }

        if (couldSeparate) {
            exist = true;
            break;
        }
    }
    return exist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Star> beauty, nonBeauty;
    for (int i = 0; i < n; i++) {
        double x, y;
        int type;
        cin >> x >> y >> type;
        if (type == 1)
            beauty.push_back(Star(x, y));
        else
            nonBeauty.push_back(Star(x, y));
    }

    if (beauty.size() == 0 || nonBeauty.size() == 0) {
        cout << "Yes\n";
        return 0;
    }

    if (beauty.size() == 1 && nonBeauty.size() == 1) {
        cout << "Yes\n";
        return 0;
    }

    vector<Star> beautyConvex = makeConvexHull(beauty);
    vector<Star> nonBeautyConvex = makeConvexHull(nonBeauty);

    bool exist;
    if (beautyConvex.size() > nonBeautyConvex.size()) {
        beautyConvex.push_back(beautyConvex[0]);
        exist = isIntersecting(beautyConvex, nonBeautyConvex);
    } else {
        nonBeautyConvex.push_back(nonBeautyConvex[0]);
        exist = isIntersecting(nonBeautyConvex, beautyConvex);
    }

    if (exist)
        cout << "Yes\n";
    else
        cout << "No\n";
    return 0;
}