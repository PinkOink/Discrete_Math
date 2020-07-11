#include "UINT32.h"
#include "ErrorAnalysis.h"
#include "CombObjects.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

string to_string(int m){
  string buf = "";
  int l = 1;
  for ( int mbuf = m; mbuf /= 10; l *= 10 );
  while (l){
    buf += m / l + '0';
    m %= l;
    l /= 10;
  }
  return buf;
}


int main() {
  cout << "Combinatoric Project:" << endl << endl;
  cout << "Enter H for information" << endl << endl;
  CheckUINT32();

  string str;
  while (getline(cin, str)) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    int n = 0;
    int numbers = 0;
    int i = 0;
    while (str[i])
      if (isdigit(str[i])) {
        numbers++;
        while (isdigit(str[i]))
          n = n * 10 + str[i++] - '0';
        break;
      }
      else
        ++i;
    
    int m = 0;
    while (str[i]) 
      if (isdigit(str[i])) {
        numbers++;
        while (isdigit(str[i]))
          m = m * 10 + str[i++] - '0';
        break;
      }
      else
        ++i;
    
    if (numbers == 0) {
      if (str == "Q") {
        break;
      }
      if (str == "H") {
        cout << "* Число размещений U(m,n)" << endl;
        cout << "* Число размещений без повторений A(m,n)" << endl;
        cout << "* Число перестановок P(n)" << endl;
        cout << "* Число сочетаний C(m,n)" << endl;
        cout << "* Число Стирлинга второго рода S(m,n)" << endl;
        cout << "* Число Белла B(n)" << endl;
        cout << "Предусмотрены следующие команды:" << endl;
        cout << "* H - получение справки" << endl;
        cout << "* Q - завершение работы" << endl;
        cout << "* U, A, P, C, S, B - вычисление соответствующего комбинаторного числа." << endl;
      }
      else {
        cout << "You entered wrong command" << endl;
      }
    }
    if (numbers == 1) {
      str.erase(str.find(to_string(n), 0), to_string(n).size());
      if (str == "P()") {
        try {
          cout << "P(" << n << ") = " << Permutation(n) << endl;
        }
        catch (ErrorTypes err) {
          PrintErrorMessage(cout, err);
        }
      }
      else if (str == "B()") {
        try {
          cout << "B(" << n << ") = " << BellNumber(n) << endl;
        }
        catch (ErrorTypes err) {
          PrintErrorMessage(cout, err);
        }
      }
      else {
        cout << "You entered wrong command" << endl;
      }
    }
    if (numbers == 2) {
      str.erase(str.find(to_string(n), 0), to_string(n).size());
      str.erase(str.find(to_string(m), 0), to_string(m).size());
      if (str == "C(,)") {
        try {
          cout << "C(" << n  << ',' << m << ") = " << Combination(n, m) << endl;
        }
        catch (ErrorTypes err) {
          PrintErrorMessage(cout, err);
        }
      }
      else if (str == "S(,)") {
        try {
          cout << "S(" << n  << ',' << m << ") = " << StirlingNumberSecondKind(n, m) << endl;
        }
        catch (ErrorTypes err) {
          PrintErrorMessage(cout, err);
        }
      }
      else if (str == "U(,)") {
        try {
          cout << "U(" << n << ',' << m << ") = " << Placing(n, m) << endl;
        }
        catch (ErrorTypes err) {
          PrintErrorMessage(cout, err);
        }
      }
      else if (str == "A(,)") {
        try {
          cout << "A(" << n << ',' << m << ") = " << PlacingWithoutRepeat(n, m) << endl;
        }
        catch (ErrorTypes err) {
          PrintErrorMessage(cout, err);
        }
      }
      else {
        cout << "You entered wrong command" << endl;
      }
    }
  }

  return 0;
}