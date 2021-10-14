#include <iostream>

using namespace std;

struct Position {
    int x, y;
};

struct Lever {
    int position;
    char* vector;
};

const int WALL = 1;
const int EMPTY = 0;
const int START_X = 0;
const int START_Y = 0;
const int VerticalDelta[] = {1, 0, -1, 0};
const int HorizontalDelta[] = {0, 1, 0, -1};

void print_map(int** map, int mapSize) {
    for (int i = mapSize - 1; i >= 0; i--) {
        for (int j = 0; j < mapSize; j++)
            cout << map[i][j] << ' ';
        cout << endl;
    }
}

void read_input (int& mapSize, int& leverCount, Lever*& levers, int**& map, Position& finalPos) {
    cin >> mapSize >> leverCount;
    levers = new Lever[leverCount];
    map = new int*[mapSize];

    for (int i = 0; i < leverCount; i++) {
        levers[i].vector = new char[mapSize];
        cin >> levers[i].position;
        for (int j = 0; j < mapSize; j++)
            cin >> levers[i].vector[j];
    }

    for (int i = mapSize - 1; i >= 0; i--) {
        map[i] = new int[mapSize];
        for (int j = 0; j < mapSize; j++) {
            char tempChar;
            cin >> tempChar;
            map[i][j] = tempChar - '0';
        }
    }

    cin >> finalPos.x >> finalPos.y;
    finalPos.x--;
    finalPos.y--;
}

void clear_all (Lever*& levers, int leversCount, int**& map, int mapSize) {
    for (int i = 0; i < leversCount; i++)
        delete[] levers[i].vector;

    delete[] levers;

    for (int i = 0; i < mapSize; i++)
        delete[] map[i];

    delete[] map;
}

void mark_neighbours (int** map, int mapSize, Position currentPosition) {
    for (int i = 0; i < 4; i++) {
        Position newPos{};
        newPos.x = currentPosition.x + HorizontalDelta[i];
        newPos.y = currentPosition.y + VerticalDelta[i];

        if (newPos.y >= 0 && newPos.y < mapSize && newPos.x >= 0 && newPos.x < mapSize
                && map[newPos.y][newPos.x] > map[currentPosition.y][currentPosition.x] + 1) {
            map[newPos.y][newPos.x] = map[currentPosition.y][currentPosition.x] + 1;
            mark_neighbours(map, mapSize, newPos);
        }
    }
}

int find_length (int** map, int mapSize, Position finalPos) {
    if (map[START_Y][START_X] == WALL || map[finalPos.y][finalPos.x] == WALL)
        return -1;

    for (int i = mapSize - 1; i >= 0; i--)
        for (int j = 0; j < mapSize; j++) {
            if (map[i][j] == EMPTY)
                map[i][j] = INT32_MAX;
            else if (map[i][j] == WALL)
                map[i][j] = -1;
        }

    map[finalPos.y][finalPos.x] = 0;
    print_map(map, mapSize);
    mark_neighbours(map, mapSize, finalPos);

    return map[START_Y][START_X];
}

int main() {
    int mapSize, leverCount;
    Lever* levers;
    int** map;
    Position finalPos{};

    read_input(mapSize, leverCount, levers, map, finalPos);
    find_length(map, mapSize, finalPos);

    print_map(map, mapSize);

    clear_all(levers, leverCount, map, mapSize);

    return 0;
}
