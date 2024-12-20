// TP 2022/2023: Zada?a 3, Zadatak 4
#include <cmath>
#include <iostream>
#include <list>
int Poglavica(int N, int M, bool ispis = false) {
  if (N <= 0 || M <= 0)
    return 0;
  std::list<int> clanovi;
  for (int i = 1; i <= N; i++)
    clanovi.push_back(i);
  auto it = clanovi.begin();
  while (clanovi.size() > 1) {
    for (int i = 0; i < M - 1; i++) {
      it++;
      if (it == clanovi.end())
        it = clanovi.begin();
    }
    if (ispis)
      std::cout << *it << ", ";
    it = clanovi.erase(it);
    if (it == clanovi.end())
      it = clanovi.begin();
  }
  return *clanovi.begin();
}
int SigurnoMjesto(int M, int N1, int N2) {
  if (M <= 0 || N1 <= 0 || N2 <= 0)
    return 0;
  for (int mjesto = N1; mjesto <= N2; mjesto++) {
    bool jeSigurnoMjesto = true;
    for (int N = N1; N <= N2; N++) {
      if (Poglavica(N, M) == mjesto) {
        jeSigurnoMjesto = false;
        break;
      }
    }
    if (jeSigurnoMjesto)
      return mjesto;
  }
  return 0;
}
int main() {
  int N, M, N1, N2;
  std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena "
               "Wabambe: ";
  std::cin >> N;
  std::cout << "Unesite korak razbrajanja: ";
  std::cin >> M;
  std::cout << "Unesite raspon za odabir (N1 i N2): ";
  std::cin >> N1 >> N2;
  int poglavica = Poglavica(N, M);
  std::cout << "\nRedni broj osobe koja postaje poglavica: " << poglavica
            << std::endl;
  int sigurnoMjesto = SigurnoMjesto(M, N1, N2);
  if (sigurnoMjesto == 0)
    std::cout << "Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta."
              << std::endl;
  else
    std::cout << "Mbebe Mgogo, stani na sigurno mjesto " << sigurnoMjesto
              << " da ne bi bio poglavica!" << std::endl;
  return 0;
}