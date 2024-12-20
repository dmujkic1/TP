// TP 2022/2023: Zada?a 2, Zadatak 4
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>
template <typename tip> bool Kriterij(std::vector<tip> a, std::vector<tip> b) {
  auto it1 = a.begin();
  auto it2 = a.end();
  auto it3 = b.begin();
  auto it4 = b.end();
  if (a.size() == 0 || b.size() == 0)
    return false;
  tip A = *a.begin();
  tip B = *b.begin();
  for (auto i = it1 + 1; i != it2; i++) {
    A = A * (*i);
  }
  for (auto i = it3 + 1; i != it4; i++) {
    B = B * (*i);
  }
  if (A != B)
    return A < B;
  return a < b;
}
template <typename tip>
void SortirajPoProizvoduRedova(std::vector<std::vector<tip>> &matrica) {
  std::sort(matrica.begin(), matrica.end(), Kriterij<tip>);
}
template <typename tip>
void IspisiMatricu(const std::vector<std::vector<tip>> &matrica) {
  for (auto &red : matrica) {
    for (auto &element : red) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }
}
int main() {
  std::vector<std::vector<int>> matrica;
  std::cout
      << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): "
      << std::endl;
  for (;;) {
    std::vector<int> red;
    int broj = 0;
    for (;;) {
      std::cin >> broj;
      if (!std::cin) {
        break;
      }
      red.push_back(broj);
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    if (red.size() == 0)
      break;
    matrica.push_back(red);
  }
  SortirajPoProizvoduRedova(matrica);
  std::cout << "Matrica nakon sortiranja: " << std::endl;
  IspisiMatricu(matrica);
  std::cout << "Unesite elemente sekvence koja se trazi (* za kraj reda): ";
  std::vector<int> sekvenca;
  for (;;) {
    int broj = 0;
    std::cin >> broj;
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      break;
    }
    sekvenca.push_back((broj));
  }
  auto it =
      std::lower_bound(matrica.begin(), matrica.end(), sekvenca, Kriterij<int>);
  if (it == matrica.end() || *it != sekvenca)
    std::cout << "Trazena sekvenca se ne nalazi u matrici";
  else
    std::cout << "Trazena sekvenca se nalazi u " << (it - matrica.begin() + 1)
              << ". redu (nakon sortiranja)";
  return 0;
}
