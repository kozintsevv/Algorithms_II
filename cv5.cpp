#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

class State {
private:
	bool isValidStateVector(const vector<int> inState) const {
		if ((inState[0] == inState[1] or inState[0] == inState[2]) and (inState[0] != inState[3])) {
			return false;
		}
		return true;
	}

public:
	//Koza,Vlk,Zeli,Prevoznik
	//1: L, 0:R
	vector<int> mState;


	State() {
		mState = { 0,0,0,0 };
	}

	State(const vector<int> inState) {
		mState = inState;
	}

	bool isFinal() const {
		vector<int> finalState = { 1,1,1,1 };
		return mState == finalState;
	}

	vector<State> generateChildren() const {
		vector<State> result;
		//prevoznik jede sam
		vector<int> potentialState = mState;
		potentialState[3] = (potentialState[3] + 1) % 2;
		//potentialState ok?
		if (isValidStateVector(potentialState)) {
			State newState(potentialState);
			result.push_back(newState);
		}


		//prevoznik nekoho veze
		for (int i = 0; i < 3; i++) {
			if (potentialState[i] == potentialState[3]) {
				potentialState = mState;
				potentialState[3] = (potentialState[3] + 1) % 2;
				potentialState[i] = (potentialState[i] + 1) % 2;
			}
		}
		return result;
	}

	bool operator<(const State& other) const {
		return mState < other.mState;
	}

};

int main()
{
	queue<State> BFS_queueu;
	set<State> visited;

	State initialState;
	BFS_queueu.push(initialState);
	visited.insert(initialState);

	int counter = 0;
	bool solutionFound = false;

	while (!BFS_queueu.empty() and !solutionFound) {
		counter += 1;
		size_t lenght = BFS_queueu.size();
		for (int i = 0; i < lenght; i++) {
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

	cout << (solutionFound ? "Решение найдено!" : "Решение не найдено!") << endl;
    cout << "Количество шагов: " << counter << endl;

	return 0;
}