// TP 2022/2023: Zada?a 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <vector>
const double PI = 4 * std::atan(1);
double EPSILON = 0.0000000001;
class Krug {
private:
  std::pair<double, double> centar;
  double poluprecnik;

public:
  // KONSTRUKTORI
  explicit Krug(double poluprecnik = 0)
      : centar({0, 0}), poluprecnik(poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
  }
  explicit Krug(const std::pair<double, double> &centar, double poluprecnik = 0)
      : centar(centar), poluprecnik(poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
  }
  // METODE
  std::pair<double, double> DajCentar() { return centar; }
  double DajPoluprecnik() const { return poluprecnik; }
  double DajObim() const { return 2 * PI * poluprecnik; }
  double DajPovrsinu() const { return PI * poluprecnik * poluprecnik; }
  Krug &PostaviCentar(const std::pair<double, double> &centar) {
    this->centar = centar;
    return *this;
  }
  Krug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    this->poluprecnik = poluprecnik;
    return *this;
  }
  Krug &Transliraj(double delta_x, double delta_y) {
    centar.first += delta_x;
    centar.second += delta_y;
    return *this;
  }
  Krug &Rotiraj(double alpha) {
    double x = centar.first;
    double y = centar.second;
    centar.first = x * std::cos(alpha) - y * std::sin(alpha);
    centar.second = x * std::sin(alpha) + y * std::cos(alpha);
    return *this;
  }
  Krug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                double alpha) {
    double x = centar.first - centar_rotacije.first;
    double y = centar.second - centar_rotacije.second;
    centar.first =
        centar_rotacije.first + x * std::cos(alpha) - y * std::sin(alpha);
    centar.second =
        centar_rotacije.second + x * std::sin(alpha) + y * std::cos(alpha);
    return *this;
  }
  void Ispisi() const {
    std::cout << "{(" << centar.first << "," << centar.second << "),"
              << poluprecnik << "}" << std::endl;
  }
  static double RastojanjeCentara(const Krug &k1, const Krug &k2) {
    double dx = k2.centar.first - k1.centar.first;
    double dy = k2.centar.second - k1.centar.second;
    return std::sqrt(dx * dx + dy * dy);
  }
  static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2) {
    if ((std::fabs(k1.poluprecnik - k2.poluprecnik) <=
         EPSILON * (std::fabs(k1.poluprecnik) + std::fabs(k2.poluprecnik))) &&
        (std::fabs(k1.centar.first - k2.centar.first) <=
         EPSILON * (std::fabs(k1.centar.first) + std::fabs(k2.centar.first))) &&
        (std::fabs(k1.centar.second - k2.centar.second) <=
         EPSILON * (std::fabs(k1.centar.second) + std::fabs(k2.centar.second))))
      return true;
    return false;
  }
  static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2) {
    return std::fabs(k1.poluprecnik - k2.poluprecnik) <=
           EPSILON * (std::fabs(k1.poluprecnik) + std::fabs(k2.poluprecnik));
  }
  static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2) {
    if ((std::fabs(k1.centar.first - k2.centar.first) <=
         EPSILON * (std::fabs(k1.centar.first) + std::fabs(k2.centar.first))) &&
        (std::fabs(k1.centar.second - k2.centar.second) <=
         EPSILON * (std::fabs(k1.centar.second) + std::fabs(k2.centar.second))))
      return true;
    return false;
  }
  static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2) {
    double rastojanje = RastojanjeCentara(k1, k2);
    double zbirpoluprecnika = k1.poluprecnik + k2.poluprecnik;
    return std::fabs(rastojanje - zbirpoluprecnika) <=
           EPSILON * (std::fabs(rastojanje) + std::fabs(zbirpoluprecnika));
  }
  static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2) {
    double rastojanje = RastojanjeCentara(k1, k2);
    double razlikapoluprecnika = std::fabs(k1.poluprecnik - k2.poluprecnik);
    return std::fabs(rastojanje - razlikapoluprecnika) <=
           EPSILON * (std::fabs(rastojanje) + std::fabs(razlikapoluprecnika));
  }
  static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2) {
    double rastojanje = RastojanjeCentara(k1, k2);
    return rastojanje < k1.poluprecnik + k2.poluprecnik;
  }
  static bool DaLiSeSijeku(const Krug &k1, const Krug &k2) {
    double rastojanje = RastojanjeCentara(k1, k2);
    return rastojanje < k1.poluprecnik + k2.poluprecnik &&
           rastojanje > std::fabs(k1.poluprecnik - k2.poluprecnik);
  }
  bool DaLiSadrzi(const Krug &k) const {
    double rastojanje = RastojanjeCentara(*this, k);
    return rastojanje + k.poluprecnik < poluprecnik;
  }
  friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y) {
    Krug novi = k;
    novi.Transliraj(delta_x, delta_y);
    return novi;
  }
  friend Krug RotiraniKrug(const Krug &k, double alpha) {
    Krug novi = k;
    novi.Rotiraj(alpha);
    return novi;
  }
  friend Krug RotiraniKrug(const Krug &k,
                           const std::pair<double, double> &centar_rotacije,
                           double alpha) {
    Krug novi = k;
    novi.Rotiraj(centar_rotacije, alpha);
    return novi;
  }
  bool operator==(const Krug &drugi) const {
    return centar == drugi.centar && poluprecnik == drugi.poluprecnik;
  }
};
int main() {
  int brojkrugova;
  std::cout << "Unesite broj krugova: ";
  try {
    std::cin >> brojkrugova;
    if (brojkrugova <= 0)
      throw std::logic_error("Uneseni broj nije prirodan!");
  } catch (std::logic_error e) {
    std::cout << e.what();
    return 0;
  }
  Krug **krugovi = nullptr;
  try {
    krugovi = new Krug *[brojkrugova] {};
  } catch (...) {
    std::cout << "Problemi sa alokacijom memorije!";
    delete[] krugovi;
    return 0;
  }
  for (int i = 0; i < brojkrugova; i++) {
    std::pair<double, double> centar;
    double poluprecnik;
    bool POGRESANUNOS = false;
    for (;;) {
      std::cout << "Unesite centar " << i + 1 << ". kruga: ";
      std::cin >> centar.first >> centar.second;
      if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n'); // C(IGARA) METODA
        std::cout << "Neispravne koordinate centra! Pokusajte ponovo: \n"
                  << std::endl;
        continue;
      }
      std::cout << "Unesite poluprecnik " << i + 1 << ". kruga: ";
      std::cin >> poluprecnik;
      if (!std::cin || poluprecnik < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n'); // C(IGARA) METODA
        std::cout << "Neispravan poluprecnik! Pokusajte ponovo: \n"
                  << std::endl;
        continue;
      }
      break;
    }
    try {
      krugovi[i] = new Krug(centar, poluprecnik);
    } catch (std::domain_error e) {
      std::cout << e.what();
      delete krugovi[i];
      i--;
    }
  }
  /*Ispis krugova
  std::cout<<"Krugovi nakon unosa: "<<std::endl;
  std::for_each(krugovi, krugovi+brojkrugova, [](Krug *k){k->Ispisi();});*/
  // Sortiranje krugova po povrsinama u rastuci poredak
  std::sort(krugovi, krugovi + brojkrugova, [](Krug *k1, Krug *k2) {
    return k1->DajPovrsinu() < k2->DajPovrsinu();
  });
  // Transformacija krugova
  double delta_x, delta_y, ugao;
  std::cout << "Unesite parametre translacije (delta_x,delta_y): ";
  std::cin >> delta_x >> delta_y;
  std::cout << "Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
  std::cin >> ugao;
  while (ugao < 0)
    ugao = ugao + 360;
  while (ugao > 360)
    ugao = ugao - 360;
  ugao = ugao * PI / 180.;
  std::transform(krugovi, krugovi + brojkrugova, krugovi,
                 [&](Krug *k) -> Krug * {
                   k->Transliraj(delta_x, delta_y);
                   k->Rotiraj(ugao);
                   return k;
                 });
  // Ispis transformersa hehe
  std::cout << "Parametri krugova nakon obavljene transformacije su: "
            << std::endl;
  std::for_each(krugovi, krugovi + brojkrugova, [](Krug *k) { k->Ispisi(); });
  // Najveci obim
  auto najveciObim =
      std::max_element(krugovi, krugovi + brojkrugova, [](Krug *k1, Krug *k2) {
        return k1->DajObim() < k2->DajObim();
      });
  if (najveciObim != krugovi + brojkrugova) {
    std::cout << "Krug sa najvecim obimom je: ";
    (*najveciObim)->Ispisi();
  }
  // PRESIJECANJE
  std::vector<std::pair<Krug, Krug>> presijecajuciKrugovi;
  std::for_each(krugovi, krugovi + brojkrugova, [&](Krug *k1) {
    std::for_each(krugovi, krugovi + brojkrugova, [&](Krug *k2) {
      bool vecpostojipar = false;
      if (Krug::DaLiSeSijeku(*k1,*k2)
/*&& (Krug::DaLiSePreklapaju(*k1,*k2)) && !(Krug::DaLiSeDodirujuIznutri(*k1,*k2)) && !
(Krug::DaLiSeDodirujuIzvani(*k1,*k2))*/)
 {
        for (int i = 0; i < presijecajuciKrugovi.size(); i++) {
          if ((*k1 == presijecajuciKrugovi.at(i).first &&
               *k2 == presijecajuciKrugovi.at(i).second) ||
              (*k1 == presijecajuciKrugovi.at(i).second &&
               *k2 == presijecajuciKrugovi.at(i).first)) {
            vecpostojipar = true;
            break;
          }
        }
        if (!vecpostojipar)
          presijecajuciKrugovi.push_back({*k1, *k2});
      }
    });
  });
  if (!presijecajuciKrugovi.empty()) {
    std::for_each(presijecajuciKrugovi.begin(), presijecajuciKrugovi.end(),
                  [](const auto &par) {
                    std::cout << "Presjecaju se krugovi:" << std::endl;
                    par.first.Ispisi();
                    std::cout << " i ";
                    par.second.Ispisi();
                    std::cout << std::endl;
                  });
  } else {
    std::cout << "Ne postoje krugovi koji se presjecaju!" << std::endl;
  }
  for (int i = 0; i < brojkrugova; i++)
    delete krugovi[i];
  delete[] krugovi;
  return 0;
}
