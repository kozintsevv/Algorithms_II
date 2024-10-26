#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

class State {
private:
    bool isValidStateVector(const vector<int> inState) const {
        // Проверяем, что коза и волк не остаются без перевозчика
        if ((inState[0] == inState[1] && inState[0] != inState[3]) ||
            (inState[0] == inState[2] && inState[0] != inState[3])) {
            return false;
        }
        return true;
    }

public:
    // 0 - левая сторона, 1 - правая сторона
    // Koza, Vlk, Zeli, Prevoznik
    vector<int> mState;

    State() {
        mState = {0, 0, 0, 0}; // Все на левой стороне
    }

    State(const vector<int> inState) {
        mState = inState;
    }

    bool isFinal() const {
        vector<int> finalState = {1, 1, 1, 1}; // Все на правой стороне
        return mState == finalState;
    }

    vector<State> generateChildren() const {
        vector<State> result;

        // Перевозчик едет сам
        vector<int> potentialState = mState;
        potentialState[3] = (potentialState[3] + 1) % 2; // Перемещение перевозчика
        if (isValidStateVector(potentialState)) {
            result.push_back(State(potentialState));
        }

        // Перевозчик берет кого-то
        for (int i = 0; i < 3; i++) {
            if (potentialState[i] == mState[3]) { // Проверяем, что перевозчик и объект на одной стороне
                potentialState[3] = (mState[3] + 1) % 2; // Перемещение перевозчика
                potentialState[i] = (potentialState[i] + 1) % 2; // Перемещение объекта
                for(int state:potentialState){
                cout<<state<<' ';
                }
                // Проверяем валидность
                if (isValidStateVector(potentialState)) {
                    result.push_back(State(potentialState));
                }
                potentialState = mState;
            }
            cout << endl;
        }
        return result;
    }

    bool operator<(const State& other) const {
        return mState < other.mState;
    }
};

int main() {
    queue<State> BFS_queueu;
    set<State> visited;

    State initialState;
    BFS_queueu.push(initialState);
    visited.insert(initialState);

    int counter = 0;
    bool solutionFound = false;

    while (!BFS_queueu.empty() && !solutionFound) {
        counter += 1;
        size_t length = BFS_queueu.size();
        for (int i = 0; i < length; i++) {
            State currentState = BFS_queueu.front();
            BFS_queueu.pop();
            auto children = currentState.generateChildren();
            for (const auto& child : children) {
                if (child.isFinal()) {
                    solutionFound = true;
                    break;
                }
                if (visited.find(child) == visited.end()) {
                    BFS_queueu.push(child);
                    visited.insert(child);
                }
            }
        }
    }

    cout << (solutionFound ? "Solution found!" : "No solution") << endl;
    cout << "Amount of steps: " << counter << endl;

    return 0;
}
