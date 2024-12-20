// TP 2022/2023: Zada?a 5, Zadatak 1
#include <cmath>
#include <complex>
#include <iostream>
#include <stdexcept>
#include <tuple>
const double PI = 4 * std::atan(1);
class Sinusoida {
private:
  double amplituda;
  double frekvencija;
  double faza;

public:
  Sinusoida(double A, double omega, double fi)
      : amplituda(A), frekvencija(omega), faza(fi) {
    Normiraj();
  }
  void Normiraj() {
    if (amplituda < 0) {
      amplituda = -amplituda;
      faza += PI;
    }
    if (frekvencija < 0) {
      frekvencija = -frekvencija;
      faza = -faza + PI;
    }
    while (faza > PI)
      faza -= 2 * PI;
    while (faza < -PI)
      faza += 2 * PI;
  }
  double DajAmplitudu() const { return amplituda; }
  double DajFrekvenciju() const { return frekvencija; }
  double DajFazu() const { return faza; }
  std::tuple<double, double, double> DajParametre() const {
    return std::make_tuple(amplituda, frekvencija, faza);
  }
  Sinusoida &PostaviAmplitudu(double A) {
    amplituda = A;
    Normiraj();
    return *this;
  }
  Sinusoida &PostaviFrekvenciju(double omega) {
    frekvencija = omega;
    Normiraj();
    return *this;
  }
  Sinusoida &PostaviFazu(double fi) {
    faza = fi;
    Normiraj();
    return *this;
  }
  Sinusoida &
  PostaviParametre(const std::tuple<double, double, double> &parametri) {
    std::tie(amplituda, frekvencija, faza) = parametri;
    Normiraj();
    return *this;
  }
  Sinusoida &operator-() {
    amplituda = -amplituda;
    Normiraj();
    return *this;
  }
  Sinusoida &operator+=(const Sinusoida &tmp) {
    if (frekvencija != tmp.frekvencija)
      throw std::domain_error("Razlicite frekvencije");
    // double novaAmplituda=amplituda+tmp.amplituda;
    double re1 = amplituda * std::cos(faza);
    double im1 = amplituda * std::sin(faza);
    double re2 = tmp.amplituda * std::cos(tmp.faza);
    double im2 = tmp.amplituda * std::sin(tmp.faza);
    double re = re1 + re2;
    double im = im1 + im2;
    double novaFaza = std::atan(im / re);
    double novaAmplituda = std::sqrt(re * re + im * im);
    amplituda = novaAmplituda;
    faza = novaFaza;
    Normiraj();
    return *this;
  }
  Sinusoida &operator-=(const Sinusoida &tmp) {
    if (frekvencija != tmp.frekvencija)
      throw std::domain_error("Razlicite frekvencije");
    // double novaAmplituda=amplituda-tmp.amplituda;
    double re1 = amplituda * std::cos(faza);
    double im1 = amplituda * std::sin(faza);
    double re2 = tmp.amplituda * std::cos(tmp.faza);
    double im2 = tmp.amplituda * std::sin(tmp.faza);
    double re = re1 - re2;
    double im = im1 - im2;
    double novaFaza = std::atan(im / re);
    double novaAmplituda = std::sqrt(re * re + im * im);
    amplituda = novaAmplituda;
    faza = novaFaza;
    Normiraj();
    return *this;
  }
  Sinusoida operator*(double skalar) const {
    double novaAmplituda = amplituda * skalar;
    return Sinusoida(novaAmplituda, frekvencija, faza);
  }
  Sinusoida operator*(const Sinusoida &tmp) const {
    double novaAmplituda = amplituda * tmp.amplituda;
    // double novaFaza=faza+tmp.faza;
    return Sinusoida(novaAmplituda, frekvencija, faza);
  }
  Sinusoida operator/(double skalar) const {
    double novaAmplituda = amplituda / skalar;
    return Sinusoida(novaAmplituda, frekvencija, faza);
  }
  Sinusoida operator/(const Sinusoida &tmp) const {
    double novaAmplituda = amplituda / tmp.amplituda;
    double novaFaza = faza - tmp.faza;
    return Sinusoida(novaAmplituda, frekvencija, novaFaza);
  }
  Sinusoida &operator*=(double skalar) {
    *this = *this * skalar;
    return *this;
  }
  Sinusoida &operator*=(const Sinusoida &tmp) {
    *this = *this * tmp;
    return *this;
  }
  Sinusoida &operator/=(double skalar) {
    *this = *this / skalar;
    return *this;
  }
  Sinusoida &operator/=(const Sinusoida &tmp) {
    *this = *this / tmp;
    return *this;
  }
  double operator()(double t) const {
    return amplituda * std::sin(frekvencija * t + faza);
  }
  double &operator[](const std::string &parametar) {
    if (parametar == "A")
      return amplituda;
    else if (parametar == "omega" || parametar == "w")
      return frekvencija;
    else if (parametar == "phi" || parametar == "fi")
      return faza;
    else
      throw std::domain_error("Neispravan naziv parametra");
  }
  double operator[](const std::string &parametar) const {
    if (parametar == "A")
      return amplituda;
    else if (parametar == "omega" || parametar == "w")
      return frekvencija;
    else if (parametar == "phi" || parametar == "fi")
      return faza;
    else
      throw std::domain_error("Neispravan naziv parametra");
  }
  friend Sinusoida operator+(const Sinusoida &s1, const Sinusoida &s2);
  friend Sinusoida operator*(const Sinusoida &s1, int broj);
  friend Sinusoida operator-(const Sinusoida &s1, const Sinusoida &s2);
};
Sinusoida operator+(const Sinusoida &s1, const Sinusoida &s2) {
  Sinusoida temp(s1.DajAmplitudu(), s1.DajFrekvenciju(), s1.DajFazu());
  // pokusao da fixam sesti AT ovako
  temp += s2;
  temp.Normiraj();
  return temp;
}
Sinusoida operator*(const Sinusoida &s1, int broj) {
  Sinusoida temp = s1;
  temp *= broj;
  temp.Normiraj();
  return temp;
}
Sinusoida operator-(const Sinusoida &s1, const Sinusoida &s2) {
  Sinusoida temp = s1;
  temp -= s2;
  temp.Normiraj();
  return temp;
}
int main() {
  Sinusoida s(2.5, 1.0, 7.2);
  std::cout << "Amplituda: " << s.DajAmplitudu() << std::endl;
  std::cout << "Frekvencija: " << s.DajFrekvenciju() << std::endl;
  std::cout << "Faza: " << s.DajFazu() << std::endl;
  s.PostaviAmplitudu(3.0);
  s.PostaviFrekvenciju(2.0);
  s.PostaviFazu(PI / 6);
  std::cout << "Novi parametri: " << std::endl;
  std::cout << "Amplituda: " << s.DajAmplitudu() << std::endl;
  std::cout << "Frekvencija: " << s.DajFrekvenciju() << std::endl;
  std::cout << "Faza: " << s.DajFazu();
  return 0;
  // operatori su mi malo kriticni
}
