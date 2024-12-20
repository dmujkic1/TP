// TP 2022/2023: Zada?a 4, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>
const double PI = 4 * std::atan(1);
double EPSILON = 0.0000000001;
class NepreklapajuciKrug {
private:
  std::pair<double, double> centar;
  double poluprecnik; //|x-y|<=EPSILON*(|x|+|y|)
  NepreklapajuciKrug *prethodni;
  static NepreklapajuciKrug *posljednji;
  bool DaLiSePreklapa(const NepreklapajuciKrug &krug) {
    NepreklapajuciKrug *k = posljednji;
    bool postoji = false;
    while (k != nullptr) {
      double udaljenost =
          std::sqrt(std::pow(krug.centar.first - k->centar.first, 2) +
                    std::pow(krug.centar.second - k->centar.second, 2));
      if (udaljenost < krug.poluprecnik + k->poluprecnik + EPSILON) {
        postoji = true;
        break;
      }
      k = k->prethodni;
    }
    return postoji;
  }
  bool DaLiSePreklapa2(std::pair<double, double> centar, double r) {
    NepreklapajuciKrug *k = posljednji;
    bool postoji = false;
    while (k != nullptr) {
      if ((std::fabs(k->centar.first - this->centar.first) <=
           EPSILON *
               (std::fabs(k->centar.first) + std::fabs(this->centar.first))) &&
          (std::fabs(k->centar.second - this->centar.second) <=
           EPSILON * (std::fabs(k->centar.second) +
                      std::fabs(this->centar.second))) &&
          (std::fabs(k->poluprecnik - this->poluprecnik) <=
           EPSILON *
               (std::fabs(k->poluprecnik) + std::fabs(this->poluprecnik)))) {
        k = k->prethodni;
        continue;
      }
      double udaljenost =
          std::sqrt(std::pow(centar.first - k->centar.first, 2) +
                    std::pow(centar.second - k->centar.second, 2));
      if (udaljenost < r + k->poluprecnik + EPSILON) {
        postoji = true;
        break;
      }
      k = k->prethodni;
    }
    return postoji;
  }

public:
  // KONSTRUKTORI
  explicit NepreklapajuciKrug(double poluprecnik = 0)
      : poluprecnik(poluprecnik) {
    if (posljednji == nullptr) {
      prethodni = nullptr;
      posljednji = this;
    } else if (posljednji != nullptr) {
      if (DaLiSePreklapa(*this))
        throw std::logic_error("Nedozvoljeno preklapanje");
      prethodni = posljednji;
      posljednji = this;
    }
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    centar.first = 0;
    centar.second = 0;
  }
  explicit NepreklapajuciKrug(const std::pair<double, double> &centar,
                              double poluprecnik = 0)
      : centar(centar), poluprecnik(poluprecnik), prethodni(nullptr) {
    if (posljednji == nullptr) {
      prethodni = nullptr;
      posljednji = this;
    } else if (posljednji != nullptr) {
      if (DaLiSePreklapa(*this))
        throw std::logic_error("Nedozvoljeno preklapanje");
      prethodni = posljednji;
      posljednji = this;
    }
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
  }
  ~NepreklapajuciKrug() {
    if (prethodni != nullptr)
      prethodni->posljednji = posljednji;
    else
      posljednji = nullptr;
  }
  NepreklapajuciKrug(const NepreklapajuciKrug &k) = delete;
  NepreklapajuciKrug(NepreklapajuciKrug &&k) = delete;
  NepreklapajuciKrug &operator=(const NepreklapajuciKrug &k) = delete;
  NepreklapajuciKrug &operator=(NepreklapajuciKrug &&k) = delete;
  // METODE
  std::pair<double, double> DajCentar() const { return centar; }
  double DajPoluprecnik() const { return poluprecnik; }
  double DajObim() const { return 2 * PI * poluprecnik; }
  double DajPovrsinu() const { return PI * poluprecnik * poluprecnik; }
  NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar) {
    if (DaLiSePreklapa2(centar, poluprecnik))
      throw std::logic_error("Nedozvoljeno preklapanje");
    this->centar = centar;
    return *this;
  }
  NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik) {
    if (DaLiSePreklapa2(centar, poluprecnik))
      throw std::logic_error("Nedozvoljeno preklapanje");
    if (poluprecnik < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    this->poluprecnik = poluprecnik;
    return *this;
  }
  NepreklapajuciKrug &Transliraj(double delta_x, double delta_y) {
    if (DaLiSePreklapa2({centar.first + delta_x, centar.second + delta_y},
                        poluprecnik))
      throw std::logic_error("Nedozvoljeno preklapanje");
    centar.first += delta_x;
    centar.second += delta_y;
    return *this;
  }
  NepreklapajuciKrug &Rotiraj(double alpha) {
    while (alpha > 360)
      alpha = alpha - 360;
    while (alpha < 0)
      alpha = alpha + 360;
    alpha = alpha * PI / 180.;
    double x = centar.first;
    double y = centar.second;
    double x1 = x * std::cos(alpha) - y * std::sin(alpha);
    double y1 = x * std::sin(alpha) + y * std::cos(alpha);
    if (DaLiSePreklapa2({x1, y1}, poluprecnik))
      throw std::logic_error("Nedozvoljeno preklapanje");
    centar.first = x * std::cos(alpha) - y * std::sin(alpha);
    centar.second = x * std::sin(alpha) + y * std::cos(alpha);
    return *this;
  }
  NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                              double alpha) {
    while (alpha > 360)
      alpha = alpha - 360;
    while (alpha < 0)
      alpha = alpha + 360;
    alpha = alpha * PI / 180.;
    double x = centar.first - centar_rotacije.first;
    double y = centar.second - centar_rotacije.second;
    double x1 =
        centar_rotacije.first + x * std::cos(alpha) - y * std::sin(alpha);
    double y1 =
        centar_rotacije.second + x * std::sin(alpha) + y * std::cos(alpha);
    if (DaLiSePreklapa2({x1, y1}, poluprecnik))
      throw std::logic_error("Nedozvoljeno preklapanje");
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
  static double RastojanjeCentara(const NepreklapajuciKrug &k1,
                                  const NepreklapajuciKrug &k2) {
    double dx = k2.centar.first - k1.centar.first;
    double dy = k2.centar.second - k1.centar.second;
    return std::sqrt(dx * dx + dy * dy);
  }
};
NepreklapajuciKrug *NepreklapajuciKrug::posljednji = nullptr;
int main() {
  int broj_krugova;
  std::cout << "Unesite broj krugova: ";
  for (;;) {
    if (!(std::cin >> broj_krugova) || broj_krugova <= 0) {
      std::cout << "Neispravan broj krugova, unesite ponovo!" << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n'); // CIGARA METODA
      continue;
    }
    break;
  }
  std::vector<std::shared_ptr<NepreklapajuciKrug>> krugovi;
  for (int i = 0; i < broj_krugova; i++) {
    std::pair<double, double> centar;
    double poluprecnik;
    std::cout << "Unesite centar za " << i + 1 << ". krug: ";
    for (;;) {
      if (!(std::cin >> centar.first >> centar.second)) {
        std::cout << "Neispravan centar!" << std::endl;
        std::cout << "Unesite ponovo centar za " << i + 1 << ". krug: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n'); // CIGARA METODA
        continue;
      }
      break;
    }
    std::cout << "Unesite poluprecnik: ";
    for (;;) {
      if (!(std::cin >> poluprecnik) || poluprecnik < 0) {
        std::cout << "Neispravan poluprecnik!" << std::endl;
        std::cout << "Unesite ponovo poluprecnik za " << i + 1 << ". krug: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n'); // CIGARA METODA
        continue;
      }
      break;
    }
    if (poluprecnik >= 0) {
      try {
        std::shared_ptr<NepreklapajuciKrug> krug =
            std::make_shared<NepreklapajuciKrug>(centar, poluprecnik);
        krugovi.push_back(krug);
      } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
        i--;
      }
    }
  }
  std::sort(krugovi.begin(), krugovi.end(),
            [](const std::shared_ptr<NepreklapajuciKrug> &krug1,
               const std::shared_ptr<NepreklapajuciKrug> &krug2) {
              double povrsina1 = PI * std::pow(krug1->DajPoluprecnik(), 2);
              double povrsina2 = PI * std::pow(krug2->DajPoluprecnik(), 2);
              return povrsina1 >= povrsina2;
            });
  std::cout << "Krugovi nakon obavljenog sortiranja: " << std::endl;
  for (const auto &krug : krugovi)
    std::cout << "{(" << krug->DajCentar().first << ","
              << krug->DajCentar().second << ")," << krug->DajPoluprecnik()
              << "}" << std::endl;
  return 0;
}
