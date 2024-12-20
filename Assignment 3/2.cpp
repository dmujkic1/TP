// TP 2022/2023: Zada?a 3, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
typedef std::map<std::string, std::vector<std::string>> Knjiga;
// KreirajIndeksPojmova
std::map<std::string, std::set<std::tuple<std::string, int, int>>>
KreirajIndeksPojmova(const Knjiga &knjiga) {
  std::map<std::string, std::set<std::tuple<std::string, int, int>>> indeks;
  int brojacStranica = 0;
  for (const auto &poglavlje : knjiga) {
    const std::string &oznakaPoglavlja = poglavlje.first;
    const std::vector<std::string> &stranice = poglavlje.second;
    int brojacStranica = 0; // DODANO
    for (int i = 0; i < stranice.size(); i++) {
      const std::string &sadrzajStranice = stranice[i];
      std::string rijec;
      int pozicija = 0;
      for (char c : sadrzajStranice) {
        if (std::isalnum(c))
          rijec.push_back(std::tolower(c));
        else {
          if (!rijec.empty()) {
            indeks[rijec].insert(std::make_tuple(oznakaPoglavlja,
                                                 brojacStranica + 1,
                                                 pozicija - rijec.length()));
            rijec.clear();
          }
        }
        pozicija++;
      }
      if (!rijec.empty())
        indeks[rijec].insert(std::make_tuple(
            oznakaPoglavlja, brojacStranica + 1, pozicija - rijec.length()));
      brojacStranica++;
    }
  }
  return indeks;
}
// PretraziIndeksPojmova
std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(
    const std::string &rijec,
    const std::map<std::string, std::set<std::tuple<std::string, int, int>>>
        &indeks) {
  std::string lowercaseRijec = rijec;
  std::transform(lowercaseRijec.begin(), lowercaseRijec.end(),
                 lowercaseRijec.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  // pretvaranje u lowercase
  auto it = indeks.find(lowercaseRijec);
  if (it != indeks.end())
    return it->second;
  else
    throw std::logic_error("Pojam nije nadjen");
}
// IspisiIndeksPojmova
void IspisiIndeksPojmova(
    const std::map<std::string, std::set<std::tuple<std::string, int, int>>>
        &indeks) {
  for (const auto &unos : indeks) {
    std::cout << unos.first << ": ";

    // for (const auto &pozicija : unos.second)
    // std::cout<<std::get<0>(pozicija)<<"/"<<std::get<1>(pozicija)<<"/"<<std::get<2>(pozicija)<<", ";
// std::cout<<std::endl;
auto it = unos.second.begin();
if (it != unos.second.end()) {
  std::cout << std::get<0>(*it) << "/" << std::get<1>(*it) << "/"
            << std::get<2>(*it);
  it++;
}
while (it != unos.second.end()) {
  std::cout << ", " << std::get<0>(*it) << "/" << std::get<1>(*it) << "/"
            << std::get<2>(*it);
  it++;
}
std::cout << std::endl;
  }
}
int main() {
  Knjiga knjiga;
  std::string oznakaPoglavlja;
  std::string sadrzajStranice;
  int brojStranice = 1;
  for (;;) {
    std::cout << "Unesite naziv poglavlja: \n";
    std::getline(std::cin, oznakaPoglavlja);
    if (oznakaPoglavlja == ".")
      break;
    brojStranice = 1; // resetuje ga
    for (;;) {
      std::cout << "Unesite sadrzaj stranice " << brojStranice << ": \n";
      std::getline(std::cin, sadrzajStranice);
      if (sadrzajStranice == ".")
        break;
      knjiga[oznakaPoglavlja].push_back(sadrzajStranice);
      brojStranice++;
    }
  }
  std::map<std::string, std::set<std::tuple<std::string, int, int>>> indeks =
      KreirajIndeksPojmova(knjiga);
  std::cout << "Kreirani indeks pojmova: \n";
  IspisiIndeksPojmova(indeks);
  std::string rijec;
  for (;;) {
    std::cout << "Unesite rijec: \n";
    std::cin >> rijec;
    if (rijec == ".")
      break;
    try {
      std::set<std::tuple<std::string, int, int>> rezultati =
          PretraziIndeksPojmova(rijec, indeks);
      for (const auto &pozicija : rezultati)
        std::cout << std::get<0>(pozicija) << "/" << std::get<1>(pozicija)
                  << "/" << std::get<2>(pozicija) << " ";
    } catch (const std::logic_error e) {
      std::cout << "Unesena rijec nije nadjena!" << std::endl;
    }
  }
  return 0;
}
