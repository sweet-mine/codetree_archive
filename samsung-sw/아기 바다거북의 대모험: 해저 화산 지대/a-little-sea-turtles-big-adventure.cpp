#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct edge {
    int y;
    int x;
    int cost;
};

struct compare {
    bool operator()(const edge& a, const edge& b) const {
        return a.cost > b.cost;
    }
};

int N, M, K;
int turtleNum;

int map[20][20] = {}; 
int volcano[20][20] = {}; // 현재 마그마 압력 (분출시 초기화)
int fire[20][20] = {}; // 현재까지 쌓인 열기 (초기화 필요)
int limit[20][20] = {}; // 분출 임계치
bool isFired[20][20] = {}; // 이번턴에 분출했는지 여부 판단 (초기화 필요)
pair<int, int> turtleLocate[11] = {}; // 꼬부기 현재 위치
int turtleTurn[11] = {}; // 꼬부기 도착한 턴 저장
int dijkstraMap[20][20] = {}; // 경로값

int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

bool valid(int y, int x) {
    if(y >= 0 && y < N && x >= 0 && x < N) {
        return true;
    }
    return false;
}

void dijkstra() {
    priority_queue<edge, vector<edge>, compare> pq;
    memset(dijkstraMap, 0x3F, sizeof(dijkstraMap));
    pq.push({N-1, N-1, 0});
    dijkstraMap[N-1][N-1] = 0;

    while(!pq.empty()) {
        edge a = pq.top();
        pq.pop();

        if(a.cost > dijkstraMap[a.y][a.x]) {
            continue;
        }

        for(int i = 0; i<4;i++) {
            int sy = a.y + dy[i];
            int sx = a.x + dx[i];
            int newCost = a.cost+1;

            if(valid(sy, sx) && !map[sy][sx] && dijkstraMap[sy][sx] > newCost) {
                dijkstraMap[sy][sx] = newCost;
                pq.push({sy, sx, newCost});
            }
        }
    }
}

void shot(int y, int x, int num) { // 분출 및 분출 중 다른 화산 만나면 연계
    isFired[y][x] = true;
    volcano[y][x] = 0;

    fire[y][x] += num;
    num /= 2;
    
    for(int i = 0; i<4;i++) {
        int sy = y+dy[i];
        int sx = x+dx[i];
        int currentFire = num;
        while(valid(sy,sx) && currentFire != 0 && map[sy][sx] != -1) { // 열기가 0이거나 충돌하면 멈춤
            fire[sy][sx] += currentFire;

            if(limit[sy][sx] > 0 && !isFired[sy][sx] && fire[sy][sx] + volcano[sy][sx] >= limit[sy][sx]) { // 연쇄
                shot(sy, sx, limit[sy][sx]);
            }

            sy += dy[i];
            sx += dx[i];
            currentFire /= 2;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> K;
    turtleNum = M;
    int num;

    for(int i = 0; i<N;i++){
        for(int j =0;j<N;j++){
            cin >> num;
            map[i][j] = -num;
        }
    }

    int y, x;

    for(int i = 1;i<=M;i++){
        cin >> y >> x;
        map[y][x] = i;
        turtleLocate[i].first = y;
        turtleLocate[i].second = x;
    }

    for(int i = 0; i<K;i++) {
        cin >> y >> x >> num;
        limit[y][x] = num;
    }

    for(int t = 1; t<=100;t++){

        if(turtleNum == 0) { // 조기종료
            break;
        }

        for(int i = 1; i<=M;i++){ // 1단계
            if(turtleLocate[i].first == N-1 && turtleLocate[i].second == N-1) { // 도착했으면 스킵
                continue;
            }

            dijkstra();
            int minDist = 0x3F3F3F3F;
            int minDirec = -1;
            
            for(int j=0;j<4;j++) {
                int sy = turtleLocate[i].first + dy[j];
                int sx = turtleLocate[i].second + dx[j];

                if(valid(sy, sx) && dijkstraMap[sy][sx] < minDist) {
                    minDist = dijkstraMap[sy][sx];
                    minDirec = j;
                }
            }

            if(minDirec == -1) continue; // 이동 불가

            map[turtleLocate[i].first][turtleLocate[i].second] = 0;
            int sy = turtleLocate[i].first + dy[minDirec];
            int sx = turtleLocate[i].second + dx[minDirec];
            turtleLocate[i].first = sy;
            turtleLocate[i].second = sx;

            if(sy == N-1 && sx == N-1) { // 도착했을 경우
                turtleNum--;
                turtleTurn[i] = t;
            }
            else {
                map[sy][sx] = i;
            }
        }

        for(int i = 0;i<N;i++) { // 2단계
            for(int j = 0;j<N;j++) {
                if(limit[i][j]) {
                    volcano[i][j] += 10;
                }
            }
        }

        for(int i = 0; i<N;i++) { // 3단계
            for(int j = 0; j<N;j++) {
                if(limit[i][j] > 0 && !isFired[i][j] && fire[i][j] + volcano[i][j] >= limit[i][j]) { // 연쇄
                    shot(i, j, limit[i][j]);
                }
            }
        }

        for(int i = 1; i<=M;i++){ // 꼬부기 냉동시키기
            if(turtleLocate[i].first == N-1 && turtleLocate[i].second == N-1) { // 도착했으면 스킵
                continue;
            }

            if(fire[turtleLocate[i].first][turtleLocate[i].second] >= 20) {
                map[turtleLocate[i].first][turtleLocate[i].second] = -1;
                turtleLocate[i].first = N-1;
                turtleLocate[i].second = N-1;
                turtleNum--;
            }
        }

        // 4단계
        memset(fire, 0, sizeof(fire));
        memset(isFired, 0, sizeof(isFired));
    }

    for(int i = 1; i<=M;i++){
        if(turtleTurn[i] == 0) {
            cout << -1 << '\n';
        }
        else {
        cout << turtleTurn[i] << '\n';
        }
    }

    return 0;
}