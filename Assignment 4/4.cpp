// TP 2022/2023: Zada?a 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>
class Korisnik {
private:
  int clanski_broj;
  std::string ime_i_prezime;
  std::string adresa;
  std::string broj_telefona;

public:
  Korisnik(int clanski_broj, std::string ime_i_prezime, std::string adresa,
           std::string broj_telefona)
      : clanski_broj(clanski_broj), ime_i_prezime(ime_i_prezime),
        adresa(adresa), broj_telefona(broj_telefona) {}
  int DajClanskiBroj() const { return clanski_broj; }
  std::string DajImeIPrezime() const { return ime_i_prezime; }
  std::string DajAdresu() const { return adresa; }
  std::string DajTelefon() const { return broj_telefona; }
  void Ispisi() {
    std::cout << "Clanski broj: " << clanski_broj << std::endl;
    std::cout << "Ime i prezime: " << ime_i_prezime << std::endl;
    std::cout << "Adresa: " << adresa << std::endl;
    std::cout << "Telefon: " << broj_telefona << std::endl;
  }
};
class Film {
private:
  int evidencijski_broj;
  bool traka_ili_DVD;
  std::string naziv_filma;
  std::string zanr;
  int godina_produkcije;
  Korisnik *zaduzenje;

public:
  Film(int evidencijski_broj, bool traka_ili_DVD, std::string naziv_filma,
       std::string zanr, int godina_produkcije)
      : evidencijski_broj(evidencijski_broj), traka_ili_DVD(traka_ili_DVD),
        naziv_filma(naziv_filma), zanr(zanr),
        godina_produkcije(godina_produkcije), zaduzenje(nullptr) {}
  int DajEvidencijskiBroj() const { return evidencijski_broj; }
  std::string DajNaziv() const { return naziv_filma; }
  std::string DajZanr() const { return zanr; }
  int DajGodinuProdukcije() const { return godina_produkcije; }
  bool DaLiJeDVD() const { return traka_ili_DVD; }
  void ZaduziFilm(Korisnik &k) {
    if (DaLiJeZaduzen())
      throw std::logic_error("Film vec zaduzen");
    zaduzenje = &k;
  }
  void RazduziFilm() { zaduzenje = nullptr; }
  bool DaLiJeZaduzen() const {
    if (zaduzenje != nullptr)
      return true;
    return false;
  }
  Korisnik &DajKodKogaJe() const {
    if (zaduzenje == nullptr)
      throw std::domain_error("Film nije zaduzen");
    return *zaduzenje;
  }
  Korisnik *DajPokKodKogaJe() const { return zaduzenje; }
  void Ispisi() {
    std::cout << "Evidencijski broj: " << evidencijski_broj << std::endl;
    std::cout << "Medij: ";
    if (traka_ili_DVD)
      std::cout << "DVD" << std::endl;
    else
      std::cout << "Video traka" << std::endl;
    std::cout << "Naziv filma: " << naziv_filma << std::endl;
    std::cout << "Zanr: " << zanr << std::endl;
    std::cout << "Godina produkcije: " << godina_produkcije << std::endl;
  }
};
class Videoteka {
private:
  std::map<int, std::shared_ptr<Korisnik>> mapa_korisnika;
  std::map<int, std::shared_ptr<Film>> mapa_filmova;

public:
  Videoteka() = default;
  void RegistrirajNovogKorisnika(int clanski_broj, std::string ime_i_prezime,
                                 std::string adresa,
                                 std::string broj_telefona) {
    if (mapa_korisnika.count(clanski_broj) > 0)
      throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
    std::shared_ptr<Korisnik> novi_korisnik = std::make_shared<Korisnik>(
        clanski_broj, ime_i_prezime, adresa, broj_telefona);
    mapa_korisnika[clanski_broj] = novi_korisnik;
  }
  void RegistrirajNoviFilm(int evidencijski_broj, bool na_dvd,
                           std::string naziv, std::string zanr,
                           int godina_produkcije) {
    if (mapa_filmova.count(evidencijski_broj) > 0)
      throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
    std::shared_ptr<Film> novi_film = std::make_shared<Film>(
        evidencijski_broj, na_dvd, naziv, zanr, godina_produkcije);
    mapa_filmova[evidencijski_broj] = novi_film;
  }
  Korisnik &NadjiKorisnika(int clanski_broj) const {
    auto it = mapa_korisnika.find(clanski_broj);
    if (it == mapa_korisnika.end())
      throw std::logic_error("Korisnik nije nadjen");
    return *(it->second);
  }
  Film &NadjiFilm(int evidencijski_broj) const {
    auto it = mapa_filmova.find(evidencijski_broj);
    if (it == mapa_filmova.end())
      throw std::logic_error("Film nije nadjen");
    return *(it->second);
  }
  void IzlistajKorisnike() const {
    for (const auto &par : mapa_korisnika) {
      par.second->Ispisi();
      std::cout << std::endl;
    }
  }
  void IzlistajFilmove() const {
    for (const auto &par : mapa_filmova) {
      if (par.second->DaLiJeZaduzen()) {
        par.second->Ispisi();
        std::cout << "Zaduzen kod korisnika: "
                  << par.second->DajKodKogaJe().DajImeIPrezime() << " ("
                  << par.second->DajKodKogaJe().DajClanskiBroj() << ")"
                  << std::endl;
      } else
        par.second->Ispisi();
      std::cout << std::endl;
    }
  }
  void ZaduziFilm(int evidencijski_broj, int clanski_broj) {
    Film &film = NadjiFilm(evidencijski_broj);
    Korisnik &korisnik = NadjiKorisnika(clanski_broj);
    if (film.DaLiJeZaduzen())
      throw std::logic_error("Film vec zaduzen");
    film.ZaduziFilm(korisnik);
  }
  void RazduziFilm(int evidencijski_broj) {
    Film &film = NadjiFilm(evidencijski_broj);
    if (!film.DaLiJeZaduzen())
      throw std::logic_error("Film nije zaduzen");
    film.RazduziFilm();
  }
  void PrikaziZaduzenja(int clanski_broj) const {
    auto korisnik = mapa_korisnika.find(clanski_broj);
    if (korisnik == mapa_korisnika.end())
      throw std::logic_error("Korisnik nije nadjen");
    bool duzan = false;
    for (auto i : mapa_filmova) {
      if (i.second->DaLiJeZaduzen() &&
          i.second->DajKodKogaJe().DajClanskiBroj() == clanski_broj) {
        duzan = true;
        i.second->Ispisi();
      }
    }
    if (!duzan)
      std::cout << "Korisnik nema zaduzenja" << std::endl;
  }
  Videoteka(const Videoteka &v) {
    for (auto filmovi : v.mapa_filmova) {
      mapa_filmova[filmovi.first] = std::make_shared<Film>(*filmovi.second);
    }
    for (auto korisnici : v.mapa_korisnika) {
      mapa_korisnika[korisnici.first] =
          std::make_shared<Korisnik>(*korisnici.second);
    }
  }
  Videoteka(Videoteka &&v) = default;
  Videoteka &operator=(const Videoteka &v) {
    if (this != &v) {
      mapa_korisnika.clear();
      mapa_filmova.clear();
      for (auto filmovi : v.mapa_filmova) {
        mapa_filmova[filmovi.first] = std::make_shared<Film>(*filmovi.second);
      }
      for (auto korisnici : v.mapa_korisnika) {
        mapa_korisnika[korisnici.first] =
            std::make_shared<Korisnik>(*korisnici.second);
      }
    }
    return *this;
  }
  Videoteka &operator=(Videoteka &&v) = default;
};
int main() {
  Videoteka videoteka;
  for (;;) {
    std::cout << "1. Registracija novog korisnika" << std::endl;
    std::cout << "2. Registracija novog filma" << std::endl;
    std::cout << "3. Zaduzi film" << std::endl;
    std::cout << "4. Razduzi film" << std::endl;
    std::cout << "5. Prikazi zaduzenja korisnika" << std::endl;
    std::cout << "6. IZLAZ" << std::endl;
    std::cout << "Odaberite opciju: " << std::endl;
    int opcija;
    std::cin >> opcija;
    try {
      switch (opcija) {
      case 1: {
        int clanski_broj;
        std::string ime_prezime;
        std::cout << "Unesite clanski broj korisnika: ";
        std::cin >> clanski_broj;
        std::cin.ignore();
        std::cout << "Unesite ime i prezime korisnika: ";
        std::cin.ignore();
        std::getline(std::cin, ime_prezime);
        std::cout << "Unesi adresu korisnika: ";
        std::string adresa, broj_telefona;
        std::getline(std::cin, adresa);
        std::cout << "Unesi broj telefona: ";
        std::getline(std::cin, broj_telefona);
        videoteka.RegistrirajNovogKorisnika(clanski_broj, ime_prezime, adresa,
                                            broj_telefona);
        std::cout << "Korisnik upsjesno registrovan!" << std::endl;
        break;
      }
      case 2: {
        int evidencijski_broj;
        bool na_dvd;
        std::string naziv;
        std::string zanr;
        int godina_produkcije;
        std::cout << "Unesite evidencijski broj filma: ";
        std::cin >> evidencijski_broj;
        std::cout << "Unesite fa li je film na DVD-u (1 za da, 0 za ne): ";
        std::cin >> na_dvd;
        std::cin.ignore();
        std::cout << "Unesite naziv filma: ";
        std::cin.ignore();
        std::getline(std::cin, naziv);
        std::cout << "Unesite zanr filma: ";
        std::getline(std::cin, zanr);
        std::cout << "Unesite godinu produkcije filma: ";
        std::cin >> godina_produkcije;
        videoteka.RegistrirajNoviFilm(evidencijski_broj, na_dvd, naziv, zanr,
                                      godina_produkcije);
        std::cout << "Film uspjesno registrovan!" << std::endl;
        break;
      }
      case 3: {
        int evidencijski_broj;
        int clanski_broj;
        std::cout << "Unesite evidencijski broj filma: ";
        std::cin >> evidencijski_broj;
        std::cout << "Unesite clanski broj korisnika: ";
        std::cin >> clanski_broj;
        videoteka.ZaduziFilm(evidencijski_broj, clanski_broj);
        std::cout << "Film uspjesno zaduzen!" << std::endl;
        break;
      }
      case 4: {
        int evidencijski_broj;
        std::cout << "Unesite evidencijski broj filma: ";
        std::cin >> evidencijski_broj;
        videoteka.RazduziFilm(evidencijski_broj);
        std::cout << "Film uspjesno razduzen!" << std::endl;
        break;
      }
      case 5: {
        int clanski_broj;
        std::cout << "Unesite clanski broj korisnika: ";
        std::cin >> clanski_broj;
        videoteka.PrikaziZaduzenja(clanski_broj);
        break;
      }
      case 6: {
        std::cout << "Hvala na koristenju programa!" << std::endl;
        return 0;
      }
      default:
        std::cout << "Nepoznatno ?udan odabir opcija!" << std::endl;
      }
    } catch (std::exception e) {
      std::cout << "Greska: " << e.what() << std::endl;
    }
  }
  return 0;
}
