// TP 2022/2023: Zada?a 1, Zadatak 1
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };
typedef std::array<std::vector<long long int>, 10> matrica;
long long int MultiplikativniDigitalniKorijen(long long int broj, int B) {
  long long int MDK = 1;
  if (broj == std::numeric_limits<long long int>::min()) {
    while (broj != 0) {
      MDK = MDK * (broj % B);
      broj = broj / B;
    }
    broj = std::abs(MDK);
  }
  if (broj == 0)
    return 0;
  if (broj < 0)
    broj = std::abs(broj);
  if (B < 2)
    throw std::domain_error("Neispravna baza");
  for (;;) // 679 u bazi 10 je 6
  {
    while (broj != 0) {
      MDK = MDK * (broj % B); // 9 // 9*7 // 9*7*6=378
      broj = broj / B;        // 67 // 6 // 0
    }
    if (MDK >= B) {
      broj = MDK;
      MDK = 1;
    } else if (MDK < B)
      return MDK;
  }
}
matrica RazvrstajBrojeve(std::vector<long long int> v, TretmanNegativnih IOP) {
  matrica m;
  for (int i = 0; i < v.size(); i++) {
    if (IOP == TretmanNegativnih::IgnorirajZnak) {
      if (v.at(i) < 0)
        v.at(i) = std::abs(v.at(i));
    }
    if (IOP == TretmanNegativnih::Odbaci) {
      if (v.at(i) < 0)
        i++;
    }
    if (IOP == TretmanNegativnih::PrijaviGresku) {
      if (v.at(i) < 0)
        throw std::domain_error(
            "Nije predvidjeno razvrstavanje negativnih brojeva");
    }
    long long int MDK = MultiplikativniDigitalniKorijen(v.at(i), 10); // baza 10
    for (int j = 0; j < 10; j++) {
      if (MDK == j) {
        m.at(j).push_back(v.at(i));
      }
    }
  }
  return m;
}
int main() {
  try {
    TretmanNegativnih IOP = TretmanNegativnih::IgnorirajZnak;
    std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
    std::vector<long long int> vec;
    for (;;) {
      long long int element;
      std::cin >> element;
      if (std::cin)
        vec.push_back(element);
      if (element < 0)
        throw std::domain_error(
            "Nije podrzano razvrstavanje negativnih brojeva!");
      if (!std::cin) {
        std::cin.clear();             // Clear, IGnore, CIG, CIGARA
        std::cin.ignore(10000, '\n'); // izvinjavanje toku CIGARA metoda
        break;
      }
    }
    matrica m = RazvrstajBrojeve(vec, IOP);
    std::cout
        << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu:"
        << std::endl;
    for (int i = 0; i < 10; i++) {
      if (m.at(i).size() != 0) {
        std::cout << i << ": ";
        for (int j = 0; j < m.at(i).size(); j++) {
          std::cout << m.at(i).at(j) << " ";
        }
        std::cout << std::endl;
      } else
        continue;
    }
  } catch (std::domain_error e) {
    std::cout << e.what();
  }
  return 0;
}