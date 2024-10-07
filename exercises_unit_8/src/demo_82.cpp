#include <iostream>
using namespace std;

void multiple(int x) {
  try {
    if (x > 0)
      throw x;
    else
      throw 'x';
  } catch (int x) {
    cout << "Catch a integer and that integer is:" << x << endl;
  } catch (char x) {
    cout << "Catch a character and that character is:" << x << endl;
  } catch (...) {
    cout << "Just in case something unexpected comes up" << endl;
  }
}

int main() {
  cout << "Testing multiple catches:\n";
  multiple(10);
  multiple(0);
  multiple('a');
  return 0;
}