/*
 * Paréntesis balanceados
 */

#include <iostream>
#include <string>
#include "stack_array.h"

using namespace std;

bool tratar_caso() {
  string str;
  StackArray<char> pila;

  getline(cin, str);
  if (cin.eof()) return false;

  int i = 0;
  bool equilibrado = true;

  while (i < str.length() && equilibrado) {
    switch (str[i]) {
      case '[':
      case '(':
      case '{':
        pila.push(str[i]);
        break;

      case ']':
        if (pila.empty() || pila.top() != '[') equilibrado = false;
        else pila.pop();
        break;

      case ')':
        if (pila.empty() || pila.top() != '(') equilibrado = false;
        else pila.pop();
        break;

      case '}':
        if (pila.empty() || pila.top() != '{') equilibrado = false;
        else pila.pop();
        break;

    }
    i++;
  }

  if (equilibrado && !pila.empty()) equilibrado = false;

  cout << (equilibrado ? "YES" : "NO") << endl;
  return true;
}

int main() {
  while (tratar_caso()) {}
  return 0;
}
