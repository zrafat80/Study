#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<bool> accepting(n);
    for (int i = 0; i < n; ++i) {
        int acc;
        cin >> acc;
        accepting[i] = acc;
    }

    vector<vector<int>> transitions(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> transitions[i][j];
        }
    }

    // Initial partition into accepting and non-accepting states
    vector<vector<int>> partition;
    vector<int> acc_group, non_acc_group;
    for (int i = 0; i < n; ++i) {
        if (accepting[i])
            acc_group.push_back(i);
        else
            non_acc_group.push_back(i);
    }
    if (!acc_group.empty()) partition.push_back(acc_group);
    if (!non_acc_group.empty()) partition.push_back(non_acc_group);

    bool changed = true;
    while (changed) {
        changed = false;

        // Create state to group mapping for current partition
        vector<int> state_to_group(n);
        for (int i = 0; i < partition.size(); ++i) {
            for (int state : partition[i]) {
                state_to_group[state] = i;
            }
        }

        vector<vector<int>> new_partition;
        for (auto &group : partition) {
            if (group.empty()) continue;

            map<vector<int>, vector<int>> signature_map;
            for (int state : group) {
                vector<int> signature;
                for (int sym = 0; sym < m; ++sym) {
                    int next_state = transitions[state][sym];
                    signature.push_back(state_to_group[next_state]);
                }
                signature_map[signature].push_back(state);
            }

            if (signature_map.size() > 1) {
                changed = true;
                for (auto &entry : signature_map) {
                    new_partition.push_back(entry.second);
                }
            } else {
                new_partition.push_back(group);
            }
        }

        if (changed) {
            partition = new_partition;
        }
    }

    // Build minimal DFA components
    vector<int> state_to_group_final(n);
    for (int i = 0; i < partition.size(); ++i) {
        for (int state : partition[i]) {
            state_to_group_final[state] = i;
        }
    }

    vector<vector<int>> minimal_transitions(partition.size(), vector<int>(m));
    for (int i = 0; i < partition.size(); ++i) {
        int rep = partition[i][0];
        for (int sym = 0; sym < m; ++sym) {
            int next_state = transitions[rep][sym];
            minimal_transitions[i][sym] = state_to_group_final[next_state];
        }
    }

    vector<bool> minimal_accepting(partition.size(), false);
    for (int i = 0; i < partition.size(); ++i) {
        for (int state : partition[i]) {
            if (accepting[state]) {
                minimal_accepting[i] = true;
                break;
            }
        }
    }

    // Output the minimized DFA
    cout << "Minimized DFA States: " << partition.size() << endl;
    cout << "Transitions:" << endl;
    for (int i = 0; i < partition.size(); ++i) {
        cout << "State " << i << ":";
        for (int sym = 0; sym < m; ++sym) {
            cout << " " << minimal_transitions[i][sym];
        }
        cout << endl;
    }
    cout << "Accepting States:";
    for (int i = 0; i < minimal_accepting.size(); ++i) {
        if (minimal_accepting[i]) {
            cout << " " << i;
        }
    }
    cout << endl;

    return 0;
}
