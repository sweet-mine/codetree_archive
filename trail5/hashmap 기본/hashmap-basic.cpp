#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int n;
string cmd[100000];
int k[100000];
int v[100000];

int main() {
    cin >> n;

    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++) {
        cin >> cmd[i];
        cin >> k[i];
        if (cmd[i] == "add") {
            cin >> v[i];
            mp[k[i]] = v[i];
        }
        else if (cmd[i] == "remove") {
            mp.erase(k[i]);
        }
        else if (cmd[i] == "find") {
            auto it = mp.find(k[i]);
            if(it == mp.end()) {
                cout << "None" << '\n';
            }
            else {
                cout << it->second << '\n';
            }
        }
    }

    // Please write your code here.

    return 0;
}
