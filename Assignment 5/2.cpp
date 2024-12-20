// TP 2022/2023: Zada?a 5, Zadatak 2
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>
class Padavine {
private:
  std::vector<int> kolicine;
  int maksimalnaKolicina;

public:
  Padavine(int maksimalnaKolicina) : maksimalnaKolicina(maksimalnaKolicina) {
    if (maksimalnaKolicina <= 0)
      throw std::range_error("Ilegalna maksimalna kolicina");
  }
  void RegistrirajPadavine(int kolicina) {
    if (kolicina < 0 || kolicina > maksimalnaKolicina)
      throw std::range_error("Ilegalna kolicina padavina");
    kolicine.push_back(kolicina);
  }
  int DajBrojRegistriranihPadavina() const { return kolicine.size(); }
  void BrisiSve() { kolicine.clear(); }
  int DajMinimalnuKolicinuPadavina() const {
    if (kolicine.empty())
      throw std::range_error("Nema registriranih padavina");
    return *std::min_element(kolicine.begin(), kolicine.end());
  }
  int DajMaksimalnuKolicinuPadavina() const {
    if (kolicine.empty())
      throw std::range_error("Nema registriranih padavina");
    return *std::max_element(kolicine.begin(), kolicine.end());
  }
  int DajBrojDanaSaPadavinamaVecimOd(int vrijednost) const {
    if (kolicine.empty())
      throw std::range_error("Nema registriranih padavina");
    return std::count_if(
        kolicine.begin(), kolicine.end(),
        std::bind(std::greater<int>(), std::placeholders::_1, vrijednost));
  }
  void Ispisi() const {
    if (kolicine.empty())
      throw std::range_error("Nema registriranih padavina");
    std::vector<int> sortiraneKolicine = kolicine;
    std::sort(sortiraneKolicine.begin(), sortiraneKolicine.end(),
              std::greater<int>());
    for (int kolicina : sortiraneKolicine)
      std::cout << kolicina << std::endl;
  }
  int operator[](int index) const {
    if (index < 1 || index > kolicine.size())
      throw std::range_error("Neispravan indeks");
    return kolicine[index - 1];
  }
  // MOZE LI OVAKO != i == PROVJERITI
  friend bool operator==(const Padavine &p1, const Padavine &p2) {
    if (p1.DajBrojRegistriranihPadavina() != p2.DajBrojRegistriranihPadavina())
      return false;
    if (std::equal(p1.kolicine.begin(), p1.kolicine.end(), p2.kolicine.begin()))
      return true;
  }
  friend bool operator!=(const Padavine &p1, const Padavine &p2) {
    if (!(p1 == p2))
      return true;
    return false;
  }
  Padavine &operator++() {
    std::transform(kolicine.begin(), kolicine.end(), kolicine.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, 1));
    maksimalnaKolicina++;
    return *this;
  }
  Padavine operator++(int) {
    Padavine kopija(*this);
    ++(*this);
    return kopija;
  }
  Padavine &operator+=(int broj) {
    if (!kolicine.empty())
      std::transform(kolicine.begin(), kolicine.end(), kolicine.begin(),
                     std::bind(std::plus<int>(), std::placeholders::_1, broj));
    return *this;
  }
  Padavine &operator+=(const Padavine &p) {
    if (kolicine.size() == p.kolicine.size())
      std::transform(kolicine.begin(), kolicine.end(), p.kolicine.begin(),
                     kolicine.begin(), std::plus<int>());
    return *this;
  }
  Padavine &operator-=(int broj) {
    if (!kolicine.empty())
      std::transform(kolicine.begin(), kolicine.end(), kolicine.begin(),
                     std::bind(std::minus<int>(), std::placeholders::_1, broj));
    if (std::count_if(kolicine.begin(), kolicine.end(),
                      std::bind(std::less<int>(), std::placeholders::_1, 0)))
      throw std::domain_error("Nekorektan rezultat operacije");
    return *this;
  }
  Padavine &operator-=(const Padavine &p) {
    if (kolicine.size() == p.kolicine.size())
      std::transform(kolicine.begin(), kolicine.end(), p.kolicine.begin(),
                     kolicine.begin(), std::minus<int>());
    return *this;
  }
  Padavine &operator-() {
    std::vector<int> temp(kolicine.size());
    std::transform(kolicine.begin(), kolicine.end(), temp.begin(),
                   std::bind(std::minus<int>(), maksimalnaKolicina,
                             std::placeholders::_1));
    kolicine = temp;
    if (std::count_if(kolicine.begin(), kolicine.end(),
                      std::bind(std::less<int>(), std::placeholders::_1, 0)))
      throw std::domain_error("Nekorektan rezultat operacije");
    return *this;
  }
  friend std::ostream &operator<<(std::ostream &os, const Padavine &padavine) {
    if (padavine.kolicine.empty())
      os << "Nema registriranih padavina";
    else
      for (int kolicina : padavine.kolicine)
        os << kolicina << " ";
    return os;
  }
  friend Padavine operator+(const Padavine &p1, const Padavine &p2) {
    Padavine temp = p1;
    temp += p2;
    return temp;
  }
  friend Padavine operator-(const Padavine &p1, const Padavine &p2) {
    Padavine temp = p1;
    temp -= p2;
    return temp;
  }
};
int main() {
  try {
    Padavine t(10);
    t.RegistrirajPadavine(5);
    t.RegistrirajPadavine(7);
    t.RegistrirajPadavine(10);
    std::cout << "Broj registriranih padavina: "
              << t.DajBrojRegistriranihPadavina();
    std::cout << "Minimalna kolicina padavina: "
              << t.DajMinimalnuKolicinuPadavina();
    std::cout << "Broj dana sa padavinama vecim od 6: "
              << t.DajBrojDanaSaPadavinamaVecimOd(6);
    t.Ispisi();
    std::cout << "Druge padavine: " << t[2] << std::endl;
    Padavine T(12);
    T.RegistrirajPadavine(1);
    T.RegistrirajPadavine(11);
    std::cout << "Maksimalna kolicina padavina: "
              << T.DajMaksimalnuKolicinuPadavina() << std::endl;
  } catch (std::exception e) {
    std::cout << "BELAJ MOJ BEŽE!!! " << e.what() << std::endl;
  }
  return 0;
}