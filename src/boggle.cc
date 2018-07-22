#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

#define ROWS 5
#define COLS 5

using namespace std;
struct Boggle {
    char matrix[ROWS][COLS];
    vector<string> not_found;
    vector<string> found;
};

void InitMatrix(char matrix[ROWS][COLS])
{
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            scanf("%c ", &matrix[row][col]);
        }
    }
}

void GetTestCase(Boggle &boggle) {
    InitMatrix(boggle.matrix);
    int num_words;
    scanf("%d ", &num_words);
    char buf[128];
    for (int i = 0; i < num_words; i++) {
        scanf("%s ", buf);
        boggle.not_found.push_back(buf);
    }
}

bool ValidPoint(int row, int col)
{
    return row >= 0 && col >= 0 && row < ROWS && col < COLS;
}

int LookAround(int row, int col, string word, Boggle &boggle) {
    int length = word.length();
    if (ValidPoint(row, col)) {
        printf("%c %s\n", boggle.matrix[row][col], word.c_str());
    }
    if (ValidPoint(row, col) && boggle.matrix[row][col] == word.at(0)) {
        if (length == 1) {
            return 0;
        }
        // 3x3 adjacent places
        for (int row_dt = -1; row_dt <= 1; row_dt++) {
            for (int col_dt = -1; col_dt <= 1; col_dt++) {
                if (row_dt || col_dt) {
                    int after_search = LookAround(row + row_dt, col + col_dt, word.substr(1), boggle);
                    length = after_search < length ? after_search : length;
                    if (length == 0) {
                        return length;
                    }
                }
            }
        }
    }
    return length;
}

void Play(Boggle &boggle)
{
    vector<string> original = boggle.not_found;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            vector<string>::iterator it = boggle.not_found.begin();
            while (it != boggle.not_found.end()) {
                string word = *it;
                if (LookAround(row, col, word, boggle) == 0) {
                    boggle.found.push_back(word);
                    boggle.not_found.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    for (auto word : original) {
        if (find(boggle.found.begin(), boggle.found.end(), word) 
                != boggle.found.end()) {
            printf("%s %s\n", word.c_str(), "YES");
        } else {
            printf("%s %s\n", word.c_str(), "NO");
        }
    }
}

int main(int argc, const char *argv[])
{
    int num_testcases;
    scanf("%d ", &num_testcases);
    for (int i = 0; i < num_testcases; i++) {
        Boggle boggle;
        GetTestCase(boggle);
        Play(boggle);
    }
}
