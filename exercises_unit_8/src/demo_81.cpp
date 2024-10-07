#include <iostream>
#include <stdexcept>

using namespace std;

int Zero(int a) {
  if (a == 0)
    throw a;

  return (a);
}

int main() {
  int num = 2;
  int den = 0;
  float result;
  try {
    cout << Zero(den); // exception
    result = num / den;
  }

  catch (int e) {
    cerr << "Enter non zero denominator. " << e
         << " as denominator not accepted." << endl;
    return -1;
  }

  return 0;
}