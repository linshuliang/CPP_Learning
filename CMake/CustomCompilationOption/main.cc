#include <iostream>
#include "config.h"
using namespace std;

#ifdef USE_MYMATH
  #include "math/MathFunctions.h"
#else
  #include <cmath>
#endif

int main()
{
  double base;
  int component;
  cout << "Input the base and component." << endl;
  cin >> base >> component;

  double ret;
#ifdef USE_MYMATH
  cout << "Use our own Library" << endl;
  ret = power(base, component);
#else
  cout << "Use standard Library." << endl;
  ret = pow(base, component);
#endif

  cout << "pow(" << base << ", " << component << ") = " << ret << endl;
  return 0;
}
