/*
 * Tortitas
 */

#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

bool tratar_caso() {
  stack<int> st;
  queue<int> q;

  int tam_tortita;
  cin >> tam_tortita;
  while (tam_tortita != -1) {
    st.push(tam_tortita);
    cin >> tam_tortita;
  }

  if (st.empty()) return false;

  int num_volteos;
  cin >> num_volteos;
  for (int i = 0; i < num_volteos; i++) {
    int num_tortitas;
    cin >> num_tortitas;

    for (int i = 0; i < num_tortitas; i++) {
      q.push(st.top());
      st.pop();
    }

    while(!q.empty()) {
      st.push(q.front());
      q.pop();
    }
  }

  cout << st.top() << endl;

  return true;
}

int main() {
  while (tratar_caso()) {}
  return 0;
}
