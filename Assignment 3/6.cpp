// TP 2022/2023: Zada?a 3, Zadatak 6
#include <cmath>
#include <iostream>
#include <memory>
/*struct Clan{
 int redni_broj;
 std::shared_ptr<Clan> sljedeci;
};*/
struct Cvor {
  int redni_broj;
  std::shared_ptr<Cvor> sljedeci;
};
int Poglavica(int N, int M, bool ispis = false) {
  if (N <= 0 || M <= 0)
    return 0;
  std::shared_ptr<Cvor> prvi = std::make_shared<Cvor>();
  prvi->redni_broj = 1;
  std::shared_ptr<Cvor> trenutni = prvi;
  for (int i = 2; i <= N; i++) {
    trenutni->sljedeci = std::make_shared<Cvor>();
    trenutni = trenutni->sljedeci;
    trenutni->redni_broj = i;
  }
  trenutni->sljedeci = prvi;
  while (N > 1) {
    for (int i = 1; i < M; i++)
      trenutni = trenutni->sljedeci;
    if (ispis)
      std::cout << trenutni->sljedeci->redni_broj << ", ";
    std::shared_ptr<Cvor> izbaceni = trenutni->sljedeci;
    trenutni->sljedeci = izbaceni->sljedeci;
    N--;
  }
  int poglavica = trenutni->redni_broj;
  trenutni->sljedeci = nullptr;
  // prekid veze na posljednjem cvoru, oslobadjanje pametnog
  return poglavica;
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