// TP 2022/2023: Zada?a 4, Zadatak 3
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
class Polazak {
private:
  std::string odrediste;
  std::string oznaka_voznje;
  int broj_perona;
  int sat_polaska;
  int minute_polaska;
  int trajanje_voznje;
  int kasnjenje;

public:
  Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona,
          int sat_polaska, int minute_polaska, int trajanje_voznje)
      : odrediste(odrediste), oznaka_voznje(oznaka_voznje),
        broj_perona(broj_perona), sat_polaska(sat_polaska),
        minute_polaska(minute_polaska), trajanje_voznje(trajanje_voznje),
        kasnjenje(0) {
    if (broj_perona < 1 || broj_perona > 15)
      throw std::domain_error("Besmislena vrijednost za broj perona");
    if (sat_polaska < 0 || sat_polaska > 23 || minute_polaska < 0 ||
        minute_polaska > 59)
      throw std::domain_error("Besmislena vrijednost za vrijeme polaska");
    if (trajanje_voznje < 0)
      throw std::domain_error(
          "Nisi Flash druže moj, teleportaciju nismo još izmislili!");
  }
  void PostaviKasnjenje(int kasnjenje) {
    if (kasnjenje < 0)
      throw std::logic_error("Neregularna vrijednost kasnjenja.");
    this->kasnjenje = kasnjenje; // Polazak::kasnjenje=kasnjenje;
  }
  bool DaLiKasni() const { return kasnjenje > 0; }
  int DajTrajanje() const { return trajanje_voznje; }
  int DajKasnjenje() const { return kasnjenje; }
  void OcekivanoVrijemePolaska(int &sati, int &minute) const {
    sati = sat_polaska;
    minute = minute_polaska + kasnjenje;
    while (minute > 59) {
      minute = minute - 60;
      sati++;
    }
    while (sati > 23)
      sati = sati - 24;
  }
  void OcekivanoVrijemeDolaska(int &sati, int &minute) const {
    int ukupno_minuta = minute_polaska + trajanje_voznje + kasnjenje;
    int dodatni_sati = ukupno_minuta / 60;
    sati = (sat_polaska + dodatni_sati) % 24;
    minute = ukupno_minuta % 60;
  }
  void Ispisi() const {
    std::cout << std::setw(10) << std::left << oznaka_voznje << " "
              << std::setw(30) << odrediste << " " << std::right;
    if (DaLiKasni()) // BELAAAAAAJ STD LEFT ODE SVE U
    {
      int sat, min;
      OcekivanoVrijemePolaska(sat, min);
      std::cout << std::setw(7) << sat << ":";
      if (min < 10)
        std::cout << "0" << min << " (Planirano " << sat << ":";
      else if (min > 9)
        std::cout << min << " (Planirano " << sat << ":";
      if (minute_polaska < 10)
        std::cout << "0" << minute_polaska << ", Kasni " << kasnjenje
                  << " min)\n";
      else if (minute_polaska > 9)
        std::cout << minute_polaska << ", Kasni " << kasnjenje << " min)\n";
    } else {
      int sat, min;
      OcekivanoVrijemePolaska(sat, min);
      std::cout << std::setw(7) << sat << ":";
      if (min < 10)
        std::cout << "0" << min << " ";
      else if (min > 9)
        std::cout << min << " ";
      int sati_dolaska, minute_dolaska;
      OcekivanoVrijemeDolaska(sati_dolaska, minute_dolaska);
      std::cout << std::setw(7) << sati_dolaska << ":";
      if (minute_dolaska < 10)
        std::cout << "0" << minute_dolaska << " " << std::right << std::setw(8)
                  << broj_perona << std::endl;
      else if (minute_dolaska > 9)
        std::cout << minute_dolaska << " " << std::right << std::setw(8)
                  << broj_perona << std::endl;
    }
  }
};
class Polasci {
private:
  int maksimalan_broj_polazaka;
  Polazak **polasci;
  int broj_registrovanih_polazaka;

public:
  explicit Polasci(int maksimalan_broj_polazaka)
      : maksimalan_broj_polazaka(maksimalan_broj_polazaka),
        polasci(new Polazak *[maksimalan_broj_polazaka] {}),
        broj_registrovanih_polazaka(0) {}
  Polasci(std::initializer_list<Polazak> lista_polazaka)
      : maksimalan_broj_polazaka(lista_polazaka.size()),
        polasci(new Polazak *[lista_polazaka.size()] {}),
        broj_registrovanih_polazaka(0) {
    for (auto i = lista_polazaka.begin(); i != lista_polazaka.end(); i++) {
      Polazak *p = new Polazak(*i);
      RegistrirajPolazak(p);
    }
  }
  ~Polasci() {
    IsprazniKolekciju();
    delete[] polasci;
  }
  Polasci(const Polasci &polasci)
      : maksimalan_broj_polazaka(polasci.maksimalan_broj_polazaka),
        polasci(new Polazak *[polasci.maksimalan_broj_polazaka] {}),
        broj_registrovanih_polazaka(polasci.broj_registrovanih_polazaka) {
    for (int i = 0; i < broj_registrovanih_polazaka; i++)
      this->polasci[i] = new Polazak(*polasci.polasci[i]);
  }
  Polasci(Polasci &&polasci)
      : maksimalan_broj_polazaka(polasci.maksimalan_broj_polazaka),
        polasci(polasci.polasci),
        broj_registrovanih_polazaka(polasci.broj_registrovanih_polazaka) {
    polasci.polasci = nullptr;
    polasci.broj_registrovanih_polazaka = 0;
  }
  Polasci &operator=(const Polasci &polasci) {
    if (this == &polasci)
      return *this;
    IsprazniKolekciju();
    delete[] this->polasci;
    this->maksimalan_broj_polazaka = polasci.maksimalan_broj_polazaka;
    this->polasci = new Polazak *[polasci.maksimalan_broj_polazaka];
    this->broj_registrovanih_polazaka = polasci.broj_registrovanih_polazaka;
    for (int i = 0; i < broj_registrovanih_polazaka; i++)
      this->polasci[i] = new Polazak(*polasci.polasci[i]);
    return *this;
  }
  Polasci &operator=(Polasci &&polasci) {
    if (this == &polasci)
      return *this;
    IsprazniKolekciju();
    delete[] this->polasci;
    this->maksimalan_broj_polazaka = polasci.maksimalan_broj_polazaka;
    this->polasci = polasci.polasci;
    this->broj_registrovanih_polazaka = polasci.broj_registrovanih_polazaka;
    polasci.polasci = nullptr;
    polasci.broj_registrovanih_polazaka = 0;
    return *this;
  }
  void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje,
                          int broj_perona, int sat_polaska, int minute_polaska,
                          int trajanje_voznje) {
    if (broj_registrovanih_polazaka >= maksimalan_broj_polazaka)
      throw std::range_error("Dostignut maksimalni broj polazaka");
    polasci[broj_registrovanih_polazaka] =
        new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska,
                    minute_polaska, trajanje_voznje);
    broj_registrovanih_polazaka++;
  }
  void RegistrirajPolazak(Polazak *polazak) {
    if (broj_registrovanih_polazaka >= maksimalan_broj_polazaka)
      throw std::range_error("Dostignut maksimalni broj polazaka");
    polasci[broj_registrovanih_polazaka] = polazak;
    broj_registrovanih_polazaka++;
  }
  int DajBrojPolazaka() const { return broj_registrovanih_polazaka; }
  int DajBrojPolazakaKojiKasne() const {
    int broj_kasnih_polazaka =
        std::count_if(polasci, polasci + broj_registrovanih_polazaka,
                      [](const Polazak *p) { return p->DajKasnjenje() > 0; });
    return broj_kasnih_polazaka;
  }
  Polazak &DajPrviPolazak() {
    auto it = std::min_element(polasci, polasci + broj_registrovanih_polazaka,
                               [](const Polazak *p1, const Polazak *p2) {
                                 int sati1, minute1, sati2, minute2;
                                 p1->OcekivanoVrijemeDolaska(sati1, minute1);
                                 p2->OcekivanoVrijemeDolaska(sati2, minute2);
                                 if (sati1 != sati2)
                                   return sati1 < sati2;
                                 return minute1 < minute2;
                               });
    return **it;
  }
  Polazak DajPrviPolazak() const {
    auto it = std::min_element(polasci, polasci + broj_registrovanih_polazaka,
                               [](const Polazak *p1, const Polazak *p2) {
                                 int sati1, minute1, sati2, minute2;
                                 p1->OcekivanoVrijemeDolaska(sati1, minute1);
                                 p2->OcekivanoVrijemeDolaska(sati2, minute2);
                                 if (sati1 != sati2)
                                   return sati1 < sati2;
                                 return minute1 < minute2;
                               });
    return **it;
  }
  Polazak &DajPosljednjiPolazak() {
    auto it = std::max_element(polasci, polasci + broj_registrovanih_polazaka,
                               [](const Polazak *p1, const Polazak *p2) {
                                 int sati1, minute1, sati2, minute2;
                                 p1->OcekivanoVrijemeDolaska(sati1, minute1);
                                 p2->OcekivanoVrijemeDolaska(sati2, minute2);
                                 if (sati1 != sati2)
                                   return sati1 < sati2;
                                 return minute1 < minute2;
                               });
    return **it;
  }
  Polazak DajPosljednjiPolazak() const {
    auto it = std::max_element(polasci, polasci + broj_registrovanih_polazaka,
                               [](const Polazak *p1, const Polazak *p2) {
                                 int sati1, sati2, minute1, minute2;
                                 p1->OcekivanoVrijemeDolaska(sati1, minute1);
                                 p2->OcekivanoVrijemeDolaska(sati2, minute2);
                                 if (sati1 != sati2)
                                   return sati1 < sati2;
                                 return minute1 < minute2;
                               });
    return **it;
  }
  void Ispisi() const {
    std::vector<Polazak *> polasci_vec(polasci,
                                       polasci + broj_registrovanih_polazaka);
    std::sort(polasci_vec.begin(), polasci_vec.end(),
              [](Polazak *p1, Polazak *p2) {
                int sati1, sati2, minute1, minute2;
                p1->OcekivanoVrijemePolaska(sati1, minute1);
                p2->OcekivanoVrijemePolaska(sati2, minute2);
                if (sati1 == sati2)
                  return minute1 < minute2;
                return sati1 < sati2;
              });
    std::cout << std::setw(10) << "Voznja" << std::setw(30) << std::right
              << "Odrediste" << std::setw(10) << "Polazak" << std::setw(10)
              << "Dolazak" << std::setw(8) << "Peron" << std::endl;
    std::cout << std::setw(70) << std::setfill('-') << "" << std::setfill(' ')
              << std::endl;
    for (const auto &polazak : polasci_vec) {
      polazak->Ispisi();
      std::cout << std::endl;
    }
  }
  void IsprazniKolekciju() {
    for (int i = 0; i < broj_registrovanih_polazaka; i++)
      delete polasci[i];
    broj_registrovanih_polazaka = 0;
  }
};
int main() {
  Polasci p(1000);
  std::string oznaka_voznje("A");
  for (int i = 1; i <= 3; i++) {
    oznaka_voznje[0]++;
    p.RegistrirajPolazak("A", oznaka_voznje, 1, 20 - i, 1, i);
  }
  for (int i = 1; i <= 3; i++) {
    oznaka_voznje[0]++;
    Polazak *po = new Polazak("C", oznaka_voznje, 1, 10 - i, 1, i);
    po->PostaviKasnjenje(1);
    p.RegistrirajPolazak(po);
  }
  const Polasci &p2(p);
  p2.Ispisi();
  return 0;
}
