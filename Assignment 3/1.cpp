// TP 2022/2023: Zada?a 3, Zadatak 1
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
const double eps = 0.0000001;
std::function<double(double)>
LagrangeovaInterpolacija(std::vector<std::pair<double, double>> cvorovi) {
  for (int i = 0; i < cvorovi.size(); i++) {
    for (int j = i + 1; j < cvorovi.size(); j++) {
      if (std::fabs(cvorovi[i].first - cvorovi[j].first) < eps)
        throw std::domain_error("Neispravni cvorovi");
    }
  }
  return [cvorovi](double x) {
    double rezultat = 0;
    for (int i = 0; i < cvorovi.size(); i++) {
      double brojnik = 1, nazivnik = 1;
      for (int j = 0; j < cvorovi.size(); j++) {
        if (j != i) {
          brojnik = brojnik * (x - cvorovi[j].first);
          nazivnik = nazivnik * (cvorovi[i].first - cvorovi[j].first);
        }
      }
      rezultat = rezultat + (cvorovi[i].second * brojnik / nazivnik);
    }
    return rezultat;
  };
}
double f(double x) { return x * x + std::sin(x) + std::log(x + 1); }
std::function<double(double)>
LagrangeovaInterpolacija(std::function<double(double)> f, double Xmin,
                         double Xmax, double deltaX) {
  if (Xmin > Xmax || deltaX <= 0)
    throw std::domain_error("Nekorektni parametri");
  int brojclanova = 0;
  double rezultat = (Xmax - Xmin) / deltaX;
  if (rezultat == int(rezultat)) // djeljivi su
  {
    double izraz = Xmin;
    int i = 0;
    while (izraz <= Xmax) {
      izraz = Xmin + i * deltaX;
      brojclanova++;
      i++;
    }
  } else {
    double izraz = Xmin;
    int i = 0;
    while (izraz < Xmax) {
      izraz = Xmin + i * deltaX;
      brojclanova++;
      i++;
    }
  }
  std::vector<std::pair<double, double>> vektor;
  double prvi = Xmin;
  double drugi = 0;
  for (int i = 0; i < brojclanova - 1; i++) {
    prvi = Xmin + i * deltaX;
    drugi = f(prvi);
    vektor.push_back(std::make_pair(prvi, drugi));
  }
  auto RJESENJE = LagrangeovaInterpolacija(vektor);
  return RJESENJE;
}
int main() {
  try {
    std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): "
              << std::endl;
    int opcija;
    std::cin >> opcija;
    if (opcija == 1) {
      std::cout << "Unesite broj cvorova: " << std::endl;
      int brcvorova;
      std::cin >> brcvorova;
      std::cout << "Unesite cvorove kao parove x y: " << std::endl;
      std::vector<std::pair<double, double>> cvor;
      for (int i = 0; i < brcvorova; i++) {
        double x, y;
        std::cin >> x >> y;
        cvor.push_back(std::make_pair(x, y)); // probati emplace_back
      }
      double min = cvor[0].first;
      double max = cvor[0].first;
      for (int i = 0; i < cvor.size(); i++) {
        if (cvor[i].first > max)
          max = cvor[i].first;
        else if (cvor[i].first < min)
          min = cvor[i].first;
      }
      auto p = LagrangeovaInterpolacija(cvor);
      double argument;
      std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
      while (std::cin >> argument) {
        if (argument < min || argument > max)
          std::cout << "f(" << argument << ") = " << p(argument)
                    << " [ekstrapolacija]";
        else
          std::cout << "f(" << argument << ") = " << p(argument);
        std::cout << "\nUnesite argument (ili \"kraj\" za kraj): ";
      }
      return 0;
    } else if (opcija == 2) {
      std::cout << "Unesite krajeve intervala i korak: ";
      double kraj1, kraj2, korak;
      std::cin >> kraj1 >> kraj2 >> korak;
      auto p = LagrangeovaInterpolacija(f, kraj1, kraj2, korak);
      std::cout << "Unesite argument (ili \"kraj\" za kraj): ";
      double argument;
      while (std::cin >> argument) {
        if (argument < kraj1 || argument > kraj2)
          std::cout << "f(" << argument << ") = " << f(argument) << " P("
                    << argument << ") = " << p(argument) << " [ekstrapolacija]";
        else
          std::cout << "f(" << argument << ") = " << f(argument) << " P("
                    << argument << ") = " << p(argument);
        std::cout << "\nUnesite argument (ili \"kraj\" za kraj): ";
      }
      return 0;
    }
  } catch (std::domain_error izuzetak) {
    std::cout << izuzetak.what();
    return 0;
  }
  return 0;
}
