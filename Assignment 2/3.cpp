// TP 2022/2023: Zada?a 2, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
template <typename T1, typename T2, typename f1, typename f2>
auto GeneraliziraniMatricniProizvod(std::vector<std::vector<T1>> A,
                                    std::vector<std::vector<T2>> B, f1 f,
                                    f2 g) {
  if /*(A.size()==0 || B.size()==0 || A.at(0).size()!=B.size()*/
      (A.at(0).size() != B.size()) {
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }
  using tip =
      std::remove_reference_t<decltype(g(A.at(0).at(0), B.at(0).at(0)))>;
  std::vector<std::vector<tip>> C(A.size(), std::vector<tip>(0));
  // std::vector<std::vector<tip>> prazna;
  // PROBA
  // int redovi_druge=0;
  // for (int i=0;i<B.at(0).size();i++) redovi_druge++;
  // std::vector<std::vector<tip>> prazna(A.size(),
  // std::vector<tip>(redovi_druge)); PROBA
  if (A.at(0).size() == 0 /* || B.size()==0*/)
    return C;
  for (int i = 0; i < A.size(); i++)
    C.at(i).resize(B.at(0).size());
  int m = A.size();       // broj redova matrice A
  int n = A.at(0).size(); // broj kolona matrice A
  int p = B.at(0).size(); // broj kolona matrice B
  for (int i = 0; i < m; i++) {
    if (A.at(i).size() != B.size())
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
  }
  try {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < p; j++) {
        tip sum = g(A.at(i).at(0), B.at(0).at(j));
        for (int k = 1; k < n; k++)
          sum = f(sum, g(A.at(i).at(k), B.at(k).at(j)));
        C.at(i).at(j) = sum;
      }
    }
  } catch (...) {
    throw std::runtime_error("Neocekivani problemi pri racunanju");
  }
  return C;
}
int main() {
  int m;
  int n;
  int p;
  std::cout << "Unesite broj redova prve matrice: ";
  std::cin >> m;
  std::cout
      << "Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
  std::cin >> n;
  std::cout << "Unesite broj kolona druge matrice: ";
  std::cin >> p;
  std::vector<std::vector<std::string>> A(m, std::vector<std::string>(n));
  std::vector<std::vector<std::string>> B(n, std::vector<std::string>(p));
  std::cout << std::endl << "Unesite elemente prve matrice:";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      std::cin >> A.at(i).at(j);
  }
  std::cout << std::endl << "Unesite elemente druge matrice:";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++)
      std::cin >> B.at(i).at(j);
  }
  auto f = [](const std::string &a, const std::string &b) {
    return a + "+" + b;
  };
  auto g = [](const std::string &a, const std::string &b) {
    return a + "*" + b;
  };
  try {
    auto C = GeneraliziraniMatricniProizvod(A, B, f, g);
    std::cout << std::endl << "Matricni proizvod:" << std::endl;
    for (const auto &red : C) {
      for (const auto &el : red)
        std::cout << el << " ";
      std::cout << std::endl;
    }
  } catch (std::exception e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}