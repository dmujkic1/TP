// TP 2022/2023: Zada?a 2, Zadatak 5
#include <array>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <type_traits>
#include <vector>
template <typename iterator1, typename iterator2>
auto KreirajTablicuSabiranja(iterator1 pocetak1, iterator1 kraj1,
                             iterator2 pocetak2 /*, T** &matrica*/) {
  typename std::remove_reference<decltype(*pocetak1 + *pocetak2)>::type *
      *matrica;
  int n = std::distance(pocetak1, kraj1);
  // auto matrica = new typename
  // std::remove_reference<decltype(*pocetak1+*pocetak2)>::type *[n]{};
  try {
    matrica = new
        typename std::remove_reference<decltype(*pocetak1 + *pocetak2)>::type
            *[n] {}; // alociranje memorije za matricu
  } catch (...) {
    throw std::range_error("Nema dovoljno memorije!");
  }
  try {
    matrica[0] = new typename std::remove_reference<decltype(
        *pocetak1 + *pocetak2)>::type[(n * (n + 1)) / 2]{};
  } catch (...) {
    delete[] matrica;
    throw std::range_error("Nema dovoljno memorije!");
  }
  for (iterator1 it1 = pocetak1; it1 != kraj1;
       it1++) // provjera komutativnosti sabiranja
  {
    for (iterator2 it2 = pocetak2;
         it2 != pocetak2 + std::distance(pocetak1, it1); it2++) {
      if (*it2 + *it1 != *it1 + *it2) {
        delete[] matrica[0];
        delete[] matrica;
        throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
      }
    }
  }
  int k = 1;
  for (int i = 1; i < n; i++) {
    matrica[i] = matrica[i - 1] + k;
    k++; // zavrseno alociranje
  }
  iterator2 temp = pocetak2;
  for (int i = 0; i < n; i++) {
    pocetak2 = temp;
    for (int j = 0; j <= i; j++) {
      matrica[i][j] = *pocetak1 + *pocetak2;
      if (j != i)
        pocetak2++;
    }
    if (i != n - 1)
      pocetak1++;
  }
  return matrica;
}
int main() {
  try {
    int duzina;
    std::cout << "Duzina sekvenci: " << std::endl;
    std::cin >> duzina;
    std::cout << "Elementi prve sekvence: " << std::endl;
    std::vector<double> el1(duzina);
    for (int i = 0; i < duzina; i++)
      std::cin >> el1.at(i);
    std::cout << "Elementi druge sekvence: " << std::endl;
    std::deque<double> el2(duzina);
    for (int i = 0; i < duzina; i++)
      std::cin >> el2.at(i);
    double **matrica(
        KreirajTablicuSabiranja(el1.begin(), el1.end(), el2.begin()));
    std::cout << "Tablica sabiranja: " << std::endl;
    for (int i = 0; i < el1.size(); i++) {
      for (int j = 0; j <= i; j++) {
        std::cout << matrica[i][j] << " ";
      }
      std::cout << std::endl;
    }
    delete[] matrica[0];
    delete[] matrica;
  } catch (std::logic_error &e) {
    std::cout << e.what() << std::endl;
    // return 1;
  } catch (std::range_error &e) {
    std::cout << e.what() << std::endl;
    // return 1;
  }
  /*for (int i = 0; i < a.size(); i++) {
  for (int j = 0; j <= i; j++) {
  std::cout << matrica[i][j] << " ";
  }
  std::cout << std::endl;
  }*/
  // for (int i = 0; i < a.size(); i++) // oslobadjanje memorije
  //{
  // delete[] matrica[0];
  //}
  // delete[] matrica;
  return 0;
}
