#include <iostream>
using namespace std;

class case_1 {};

class case_2 {};

int main() {
  for (int i = 1; i <= 2; i++) {
    try {
      if (i == 1)
        throw case_1();

      else if (i == 2)
        throw case_2();
    }

    catch (case_1 c1) {
      cout << "Caught case_1 class exception \n";
    }

    catch (case_2 c2) {
      cout << "Caught case_2 class exception \n";
    }
  }
}