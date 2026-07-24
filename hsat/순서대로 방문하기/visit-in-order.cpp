#include <iostream>
using namespace std;

int visited[4][4] = {};
int map[4][4] = {};
int n, m, answer = 0;
pair<int, int> point[16];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0,1,0,-1};

bool valid(int y, int x) {
    if(y < n && y >=0 && x < n && x >= 0) {
        return true;
    }
    return false;
}

void dfs(int count, int y, int x) {
    if(y == point[count].first && x == point[count].second) {
        count++;
    }

    if(count == m) {
        answer++;
        return;
    }

    for(int i = 0; i<4;i++) {
        int sy = y + dy[i];
        int sx = x + dx[i];
        if(valid(sy, sx) && !map[sy][sx] &&!visited[sy][sx]) {
            visited[sy][sx] = true;
            dfs(count, sy, sx);
            visited[sy][sx] = false;
        }
    }
}

int main() {
    cin >> n >> m;

    for(int i = 0; i<n;i++){
        for(int j = 0; j<n;j++){
            cin >> map[i][j];
        }
    }

    for(int i = 0; i<m;i++) {
        cin >> point[i].first >> point[i].second;
        point[i].first--;
        point[i].second--;
    }

    visited[point[0].first][point[0].second] = true;
    dfs(0, point[0].first, point[0].second);

    cout << answer;
    
    return 0;
}