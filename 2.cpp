#include <vector>
#include <fstream>
#include <string>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

vector<string> splitIntoSentences(string s) {
    vector<string> ans;

    int prev = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') {
            ans.push_back(s.substr(prev + 1, i - prev));
            prev = i;
        }
    }

    return ans;
}

void formatSentence(string &s) {
    int start = 0, finish = s.length() - 1;
    while (start + 1 < s.length() && s[start] == ' ' && !isalpha(s[start + 1]))
        start++;
    while (finish >= 0 && s[finish] == ' ')
        finish--;

    s = s.substr(start, finish - start + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    getline(cin, s);

    vector<string> sentences = splitIntoSentences(s);

    if (sentences.size() == 0) {
        cout << -1 << "\n";
        return 0;
    }

    for (int i = 0; i < sentences.size(); i++) {
        formatSentence(sentences[i]);

        vector<string> words
    }
    return 0;
}
