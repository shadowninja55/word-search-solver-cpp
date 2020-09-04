#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

vector<string> grid;
vector<string> words;

int directions[8][2] = {
    {1, 1},
    {-1, -1},
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
    {1, -1},
    {-1, 1}
};

vector<pair<int, int>> answer;

void readGrid() {
    ifstream file;
    string row;
    string word;

    ifstream pfile("puzzle.txt");
    ifstream wfile("words.txt");

    while (pfile >> row)
        grid.push_back(row);

    while (wfile >> word)
        words.push_back(word);

    pfile.close(); wfile.close();
}

void check(int row, int col, int d[2], string word) {
    const int size = word.size();

    vector<pair<int, int>> possible;
    possible.reserve(size);

    for (int i = 0; i < size; i++) {
        int y = row + i * d[1];
        int x = col + i * d[0];

        if (y >= grid.size() || x >= grid[0].size() || grid[y][x] != word[i])
            return;

        possible.push_back(make_pair(y, x));
    }

    answer.reserve(answer.size() + size);
    answer.insert(answer.end(), possible.begin(), possible.end());
}

void find(string word) {
    for (int row = 0; row < grid.size(); row++)
        for (int col = 0; col < grid[0].size(); col++)
            if (grid[row][col] == word[0])
                for (auto d : directions)
                    check(row, col, d, word);
}

void display() {
    stringstream canvas;
    canvas << endl;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            if (find(answer.begin(), answer.end(), make_pair(y, x)) != answer.end()) {
                canvas << "\033[92m" << grid[y][x] << "\033[0m ";
            } else {
                canvas << "\033[90m" << grid[y][x] << "\033[0m ";
            }
        }
        canvas << endl;
    }

    canvas << endl;
    cout << canvas.str();
}

int main() {
    readGrid();
    for (auto word : words)
        find(word);

    system("");
    display();
}
