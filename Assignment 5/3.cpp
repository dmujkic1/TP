// TP 2022/2023: Zada?a 5, Zadatak 3
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
class ApstraktnoVozilo {
protected:
  int tezina;

public:
  ApstraktnoVozilo(int _tezina) : tezina(_tezina) {}
  virtual ~ApstraktnoVozilo() {}
  int DajTezinu() const { return tezina; }
  virtual int DajUkupnuTezinu() const = 0;
  virtual ApstraktnoVozilo *DajKopiju() const = 0;
  virtual void IspisiPodatke() const = 0;
};
class Automobil : public ApstraktnoVozilo {
private:
  std::vector<int> tezinePutnika;

public:
  Automobil(int _tezina, const std::vector<int> &_tezinePutnika)
      : ApstraktnoVozilo(_tezina), tezinePutnika(_tezinePutnika) {}
  int DajUkupnuTezinu() const override {
    int ukupnaTezina = tezina;
    for (const auto &tezinaPutnika : tezinePutnika)
      ukupnaTezina += tezinaPutnika;
    return ukupnaTezina;
  }
  Automobil *DajKopiju() const override { return new Automobil(*this); }
  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Automobil" << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
    std::cout << "Tezine putnika: ";

    // for (const auto &tezinaPutnika : tezinePutnika)
    // std::cout<<tezinaPutnika<<" kg, ";
    for (auto it = tezinePutnika.begin(); it != tezinePutnika.end(); it++) {
      std::cout << *it << " kg";
      if (it != tezinePutnika.end() - 1)
        std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
  }
};
class Kamion : public ApstraktnoVozilo {
private:
  int tezinaTereta;

public:
  Kamion(int _tezina, int _tezinaTereta)
      : ApstraktnoVozilo(_tezina), tezinaTereta(_tezinaTereta) {}
  int DajUkupnuTezinu() const override { return tezina + tezinaTereta; }
  Kamion *DajKopiju() const override { return new Kamion(*this); }
  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Kamion" << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
    std::cout << "Tezina tereta: " << tezinaTereta << " kg" << std::endl;
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
  }
};
class Autobus : public ApstraktnoVozilo {
private:
  int brojPutnika;
  int prosjecnaTezinaPutnika;

public:
  Autobus(int _tezina, int _brojPutnika, int _prosjecnaTezinaPutnika)
      : ApstraktnoVozilo(_tezina), brojPutnika(_brojPutnika),
        prosjecnaTezinaPutnika(_prosjecnaTezinaPutnika) {}
  int DajUkupnuTezinu() const override {
    return tezina + brojPutnika * prosjecnaTezinaPutnika;
  }
  Autobus *DajKopiju() const override { return new Autobus(*this); }
  void IspisiPodatke() const override {
    std::cout << "Vrsta vozila: Autobus" << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " kg" << std::endl;
    std::cout << "Broj putnika: " << brojPutnika << std::endl;
    std::cout << "Prosjecna tezina putnika: " << prosjecnaTezinaPutnika << " kg"
              << std::endl;
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
  }
};
/*class Vozilo : public ApstraktnoVozilo{ //BELAJ KOPIRAJUCI KONSTRUKTOR NEGDJE
private:
 ApstraktnoVozilo* vozilo;
 //const ApstraktnoVozilo &vozilo;
public:
 Vozilo(ApstraktnoVozilo* _vozilo) : ApstraktnoVozilo(_vozilo->DajTezinu()),
vozilo
(_vozilo) {}
 int DajUkupnuTezinu() const override {return vozilo->DajUkupnuTezinu();}
 Vozilo* DajKopiju() const override {return new Vozilo(*this);}
 void IspisiPodatke() const override {vozilo->IspisiPodatke();}
 //Vozilo(const ApstraktnoVozilo &_vozilo) :
ApstraktnoVozilo(_vozilo.DajTezinu()), vozilo(_vozilo) {}
 //void IspisiPodatke() const override {vozilo.IspisiPodatke();}
};*/
class Vozilo {
private:
  ApstraktnoVozilo *vozilo;

public:
  Vozilo() : vozilo(nullptr) {}
  ~Vozilo() { delete vozilo; }
  Vozilo(const ApstraktnoVozilo &v) : vozilo(v.DajKopiju()) {}
  Vozilo(const Vozilo &v) {
    if (!v.vozilo)
      vozilo = nullptr;
    else
      vozilo = v.vozilo->DajKopiju();
  }
  Vozilo(Vozilo &&v) {
    vozilo = v.vozilo;
    v.vozilo = nullptr;
  }
  Vozilo &operator=(const Vozilo &v) {
    ApstraktnoVozilo *novi = nullptr;
    if (v.vozilo != nullptr)
      novi = v.vozilo->DajKopiju();
    delete vozilo;
    vozilo = novi;
    return *this;
  }
  int DajUkupnuTezinu() const { return vozilo->DajUkupnuTezinu(); }
  Vozilo *DajKopiju() const { return new Vozilo(*this); }
  void IspisiPodatke() const { vozilo->IspisiPodatke(); }
};
int main() {
  std::vector<ApstraktnoVozilo *> vozila;
  std::ifstream datoteka("VOZILA.TXT");
  if (!datoteka) {
    std::cout << "Greska pri otvaranju datoteke: VOZILA.TXT" << std::endl;
    return 1;
  }
  char vrstaVozila;
  while (datoteka >> vrstaVozila) {
    int tezinaVozila;
    datoteka >> tezinaVozila;
    if (vrstaVozila == 'A') {
      int brojPutnika;
      datoteka >> brojPutnika;
      std::vector<int> tezinePutnika(brojPutnika);
      for (auto &tezina : tezinePutnika)
        datoteka >> tezina;
      vozila.push_back(new Automobil(tezinaVozila, tezinePutnika));
    } else if (vrstaVozila == 'K') {
      int tezinaTereta;
      datoteka >> tezinaTereta;
      vozila.push_back(new Kamion(tezinaVozila, tezinaTereta));
    } else if (vrstaVozila == 'B') {
      int brojPutnika;
      datoteka >> brojPutnika;
      int prosjecnaTezinaPutnika;
      datoteka >> prosjecnaTezinaPutnika;
      vozila.push_back(
          new Autobus(tezinaVozila, brojPutnika, prosjecnaTezinaPutnika));
    } else
      std::cout << "Neispravan format podataka: " << vrstaVozila << tezinaVozila
                << std::endl;
  }
  datoteka.close();
  // Sortiranje po ukupnoj tezini
  std::sort(vozila.begin(), vozila.end(),
            [](const ApstraktnoVozilo *v1, const ApstraktnoVozilo *v2) {
              return v1->DajUkupnuTezinu() < v2->DajUkupnuTezinu();
            });
  // Ispis ukupnih tezina nakon sortiranja
  // std::cout<<"Ukupne tezine vozila nakon sortiranja: "<<std::endl;
  for (const auto &vozilo : vozila) {
    // vozilo->IspisiPodatke();
    // std::cout<<std::endl;
    std::cout << vozilo->DajUkupnuTezinu() << std::endl;
  }
  for (const auto &vozilo : vozila)
    delete vozilo;
  return 0;
}