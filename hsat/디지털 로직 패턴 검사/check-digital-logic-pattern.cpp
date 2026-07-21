#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    int K, M;

    if (!(cin >> str >> K >> M)) return 0;

    int n = str.size();
    if (n < K) {
        cout << 0 << "\n";
        return 0;
    }
    string_view sv = str;

    unordered_map<string_view, short> pattern_map;

    pattern_map.reserve(n - K + 1);

    for (int i = 0; i <= n - K; ++i) {
        string_view sub = sv.substr(i, K);
        
        pattern_map[sub]++;
        if (pattern_map[sub] >= M) {
            cout << 1 << "\n";
            return 0;
        }
    }

    cout << 0 << "\n";
    return 0;
}