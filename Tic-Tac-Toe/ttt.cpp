#include <iostream>
#include <vector>
using namespace std;

void DrawBoard(const vector<int> &v) {
    vector<char> v1(v.size());
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 1) {
            v1[i] = 'x';
        } else if (v[i] == 2) {
            v1[i] = 'o';
        } else {
            v1[i] = ' '; // Empty space
        }
    }
    cout << v1[0] << " | " << v1[1] << " | " << v1[2] << endl;
    cout << "----------\n";
    cout << v1[3] << " | " << v1[4] << " | " << v1[5] << endl;
    cout << "----------\n";
    cout << v1[6] << " | " << v1[7] << " | " << v1[8] << endl;
}

int DecideTurn(const vector<int> &t) {
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == 1) 
            count1++;
        if (t[i] == 2) 
            count2++;
    }
    return count1 <= count2 ? 1 : 2; // Player 1 starts first
}

void PlayerChoice(vector<int> &v) {
    int turn = DecideTurn(v);
    cout << "Player " << turn << "'s turn:\n";
    cout << "Which space would you like to choose (0-8): ";
    int choice;
    cin >> choice;
    if (choice >= 0 && choice < v.size() && v[choice] == 0) {
        v[choice] = turn;
    } else {
        cout << "Invalid choice. Try again.\n";
        PlayerChoice(v); // Recur until a valid choice is made
    }
}

bool CheckWinner(const vector<int> &v) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (v[i] != 0 && v[i] == v[i + 1] && v[i] == v[i + 2]) {
            cout << (v[i] == 1 ? "X wins!\n" : "O wins!\n");
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (v[i] != 0 && v[i] == v[i + 3] && v[i] == v[i + 6]) {
            cout << (v[i] == 1 ? "X wins!\n" : "O wins!\n");
            return true;
        }
    }
    // Check diagonals
    if (v[0] != 0 && v[0] == v[4] && v[0] == v[8]) {
        cout << (v[0] == 1 ? "X wins!\n" : "O wins!\n");
        return true;
    }
    if (v[2] != 0 && v[2] == v[4] && v[2] == v[6]) {
        cout << (v[2] == 1 ? "X wins!\n" : "O wins!\n");
        return true;
    }
    // If all spaces are filled, but no winner is chosen, return true, and say no one won
    int noWin = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] != 0){
            noWin++;
        } 
        if(noWin == v.size()){
            cout << "No winner!\n";
            return true;
        }
    }
    return false;
}

void Run(vector<int> &v){
    DrawBoard(v);
    PlayerChoice(v);
}

int main() {
    vector<int> pChoices(9, 0); // Initialize with 0 (empty) and size 9
    while (!CheckWinner(pChoices)) {
        Run(pChoices);
    }
    cout << "Final board:\n";
    DrawBoard(pChoices);
    return 0;
}