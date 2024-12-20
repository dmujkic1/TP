// TP 2022/2023: Zada?a 2, Zadatak 2
#include <cmath>
#include <iostream>
#include <limits>
void RastavaBroja(int n, int &p, int &q) {
  long long int temp = n;
  n = std::abs(n);
  p = 1;
  q = 1;
  int i = 2;
  while (i <= std::sqrt(n)) // brojac broji koliko puta se neko broj ponavlja
  {                         // ponovi >1 = nije slobodan od kvadrata i nije u p
    int brojac = 0;
    while (n % i == 0) {
      n = n / i;
      brojac++;
    }
    if (brojac > 1) {
      q = q * std::pow(i, brojac / 2);
      p = p * std::pow(i, brojac % 2);
    } else if (brojac == 1)
      p = p * i;
    i++;
  }
  if (n > 1)
    p = p * n;
  // if (temp==std::numeric_limits<int>::min())
  // p=std::numeric_limits<int>::min();
  if (temp < 0)
    p = p * -1;
  if (temp == 0)
    p = 0;
}
int main() {
  std::cout << "Unesi broj: ";
  int n;
  std::cin >> n;
  if (n == 0) {
    std::cout << n << " = " << n << "*" << "1^2";
  }
  int p, q;
  RastavaBroja(n, p, q);
  if (n < 0) {
    std::cout << n << " = -" << std::abs(p) << "*" << q << "^2";
  }
  if (n > 0) {
    std::cout << n << " = " << std::abs(p) << "*" << q << "^2";
  }
  return 0;
}