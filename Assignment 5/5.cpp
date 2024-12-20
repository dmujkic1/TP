// TP 2022/2023: Zada?a 5, Zadatak 5
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
template <typename TipElemenata> class DatotecniKontejner {
private:
  std::fstream tok;

public:
  DatotecniKontejner(const std::string &ime_datoteke);
  void DodajNoviElement(const TipElemenata &element);
  int DajBrojElemenata();
  TipElemenata DajElement(int pozicija);
  void IzmijeniElement(int pozicija, const TipElemenata &element);
  void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)>
                    kriterij = std::less<TipElemenata>());
};
template <typename TipElemenata>
DatotecniKontejner<TipElemenata>::DatotecniKontejner(
    const std::string &ime_datoteke) {
  tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
  if (!tok) {
    std::ofstream tmp(ime_datoteke);
    tmp.close();
    tok.open(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
    if (!tok)
      throw std::logic_error(
          "Problemi prilikom otvaranja ili kreiranja datoteke");
  }
}
template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::DodajNoviElement(
    const TipElemenata &element) {
  tok.seekp(0, std::ios::end);
  tok.write(reinterpret_cast<const char *>(&element), sizeof(TipElemenata));
  tok.flush();
  tok.seekp(0, std::ios::beg); // pokazivac na pocetak (begin)
}
template <typename TipElemenata>
int DatotecniKontejner<TipElemenata>::DajBrojElemenata() {
  tok.seekg(0, std::ios::end);
  int velicina = tok.tellg();
  tok.seekg(0, std::ios::beg); // pokazivac na pocetak fajla opet
  // tok.flush();
  return velicina / sizeof(TipElemenata);
}
template <typename TipElemenata>
TipElemenata DatotecniKontejner<TipElemenata>::DajElement(int pozicija) {
  int broj_elemenata = DajBrojElemenata();
  if (pozicija < 0 || pozicija >= broj_elemenata)
    throw std::range_error("Neispravna pozicija");
  TipElemenata element;
  tok.seekg(pozicija * sizeof(TipElemenata), std::ios::beg);
  tok.read(reinterpret_cast<char *>(&element), sizeof(TipElemenata));
  return element;
}
template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::IzmijeniElement(
    int pozicija, const TipElemenata &element) {
  int broj_elemenata = DajBrojElemenata();
  if (pozicija < 0 || pozicija >= broj_elemenata)
    throw std::range_error("Neispravna pozicija");
  tok.seekp(pozicija * sizeof(TipElemenata), std::ios::beg);
  tok.write(reinterpret_cast<const char *>(&element), sizeof(TipElemenata));
  tok.flush();
}
template <typename TipElemenata>
void DatotecniKontejner<TipElemenata>::Sortiraj(
    std::function<bool(const TipElemenata &, const TipElemenata &)> kriterij) {
  int broj_elemenata = DajBrojElemenata();
  if (broj_elemenata <= 1)
    return;
  std::vector<TipElemenata> elementi(broj_elemenata);
  // ucitavanje el. iz dat. u vector
  for (int i = 0; i < broj_elemenata; i++) {
    tok.seekg(i * sizeof(TipElemenata), std::ios::beg);
    tok.read(reinterpret_cast<char *>(&elementi[i]), sizeof(TipElemenata));
  }
  std::sort(elementi.begin(), elementi.end(), kriterij); // sortiranje vektora
  tok.seekp(0, std::ios::beg);
  for (int i = 0; i < broj_elemenata; i++)
    tok.write(reinterpret_cast<const char *>(&elementi[i]),
              sizeof(TipElemenata));
}
int main() {
  DatotecniKontejner<double> dk("ocjene.bin");
  dk.DodajNoviElement(6);
  dk.DodajNoviElement(10);
  dk.DodajNoviElement(6);
  dk.DodajNoviElement(6);
  dk.DodajNoviElement(7);
  std::cout << "Broj ocjena: " << dk.DajBrojElemenata() << std::endl;
  std::cout << "Ocjene: ";
  for (int i = 0; i < dk.DajBrojElemenata(); i++)
    std::cout << dk.DajElement(i) << " ";
  dk.Sortiraj();
  std::cout << "\nSortirane ocjene: ";
  for (int i = 0; i < dk.DajBrojElemenata(); i++)
    std::cout << dk.DajElement(i) << " ";
  return 0;
}
