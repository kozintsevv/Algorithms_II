#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>
#include <sstream> 

using namespace std;

template <typename T>
string to_string_custom(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

struct State {
    vector<int> leftBank;
    bool boatLeft;
    int transports;

    State(vector<int> lb, bool bl, int tr) : leftBank(lb), boatLeft(bl), transports(tr) {}

    string getKey() const {
        string key = boatLeft ? "L" : "R";
        for (int x : leftBank) key += to_string_custom(x); 
        return key;
    }
};

bool isValid(const vector<int>& bank) {
    int n = bank.size() / 2;
    for (int i = 0; i < n; ++i) {
        if (bank[i] == bank[i + n]) continue;
        for (int j = 0; j < n; ++j) {
            if (i != j && bank[j + n] == bank[i] && bank[j] != bank[i]) return false;
        }
    }
    return true;
}

int bfs(int pairs) {
    int n = pairs;
    vector<int> initialLeftBank(2 * n, 1);
    queue<State> q;
    set<std::string> visited;
    q.push(State(initialLeftBank, true, 0));
    visited.insert(State(initialLeftBank, true, 0).getKey());

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        bool goalReached = true;
        for (int x : current.leftBank) if (x == 1) goalReached = false;
        if (goalReached) return current.transports;

        for (int i = 0; i < 2 * n; ++i) {
            if (current.leftBank[i] != current.boatLeft) continue;
            for (int j = i; j < 2 * n; ++j) {
                if (current.leftBank[j] != current.boatLeft) continue;

                vector<int> newLeftBank = current.leftBank;
                newLeftBank[i] = 1 - newLeftBank[i];
                if (i != j) newLeftBank[j] = 1 - newLeftBank[j];

                State newState(newLeftBank, !current.boatLeft, current.transports + 1);
                if (isValid(newState.leftBank) && visited.find(newState.getKey()) == visited.end()) {
                    q.push(newState);
                    visited.insert(newState.getKey());
                }
            }
        }
    }
    return -1;
}

int main() {
    for (int pairs = 2; pairs <= 4; ++pairs) {
        int transports = bfs(pairs);
        cout << pairs << " pairs - " << transports << " transports" << endl;
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << endl;
    cout << " aLLLLLLLLLLLLLLL~~~~~~~~~~~~~~~~~~~~~GOOOOOOOOOOYYYYYYYYYYYYYYYYYYY";
    return 0;
}
