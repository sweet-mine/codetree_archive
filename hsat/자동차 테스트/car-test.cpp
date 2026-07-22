#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;

    cin >> n >> q;

    vector<int> vect(n);
    
    for(int i = 0; i<n;i++){
        cin >> vect[i];
    }

    sort(vect.begin(), vect.end());
    int num;

    for(int i = 0; i<q;i++){
        cin >> num;
        auto it = lower_bound(vect.begin(), vect.end(), num);
        if(*it == num) {
            int idx = it - vect.begin();
            cout << (idx) * (n-idx-1) << '\n';
        }
        else {
            cout << 0 << '\n';
        }
    }
    return 0;
}
