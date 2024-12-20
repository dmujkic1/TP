// TP 2022/2023: Zada?a 1, Zadatak 2
#include <cmath> //oko svakog piksela prozor (2n +1)(2n +1) N JE RED FILTERA PRIRODAN BROJ
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
    double
    aritmetikaprozora(
        std::vector<std::vector<double>> p) // PREKO VEKTORA PROBATI
{
  int brel = 0;
  double suma = 0;
  for (int i = 0; i < p.size(); i++)
    brel = brel + p.at(i).size();
  for (int i = 0; i < p.size(); i++) {
    for (int j = 0; j < p.at(i).size();
         j++) // NECE RADITI ZADATAK ZA GRBAVE, PROBATI
    {
      suma = suma + p.at(i).at(j);
    }
  }
  double arsr = suma / brel;
  return arsr;
}
std::vector<std::vector<double>>
UsrednjavajuciFilter(std::vector<std::vector<double>> m, int N) {
  if (N < 0)
    throw std::domain_error("Neispravan red filtriranja");
  int brojredova = m.size();
  std::vector<std::vector<double>> novamatrica;
  novamatrica.resize(brojredova);
  for (int i = 0; i < brojredova; i++)
    novamatrica.at(i).resize(m.at(i).size());
  // od i-N do i+N, od j-N do j+N, pa na to mjesto aritmeticku sred obuhvacenih
  for (int i = 0; i < brojredova; i++) {
    for (int j = 0; j < m.at(i).size(); j++) {
      std::vector<std::vector<double>> prozor;
      prozor.resize(2 * N + 1);
      int a = 0;
      int pocetakreda = i - N;
      int krajreda = i + N;
      int pocetakkolone = j - N;
      int krajkolone = j + N;
      if (pocetakreda < 0)
        pocetakreda = 0;
      if (krajreda >= brojredova)
        krajreda = brojredova - 1;
      if (pocetakkolone < 0)
        pocetakkolone = 0;
      if (krajkolone >= m.at(i).size())
        krajkolone = m.at(i).size() - 1;
      for (int k = pocetakreda; k <= krajreda; k++) {
        for (int l = pocetakkolone; l <= krajkolone; l++) {
          prozor.at(a).push_back(m.at(k).at(l));
        }
        a++;
      }
      double arsr;
      arsr = aritmetikaprozora(prozor);
      novamatrica.at(i).at(j) = arsr;
    }
  }
  return novamatrica;
}
int main() {
  try {
    std::cout << "Unesite broj redova i kolona matrice: " << std::endl;
    int brojredova, brojkolona;
    std::cin >> brojredova >> brojkolona;
    std::cout << "Unesite elemente matrice: " << std::endl;
    std::vector<std::vector<double>> m;
    m.resize(brojredova);
    for (int i = 0; i < brojredova; i++)
      m.at(i).resize(brojkolona);
    for (int i = 0; i < brojredova; i++) {
      for (int j = 0; j < brojkolona; j++) {
        int element;
        std::cin >> element;
        m.at(i).at(j) = element;
      }
    }
    std::cout << "Unesite red filtriranja: " << std::endl;
    int N;
    std::cin >> N;
    std::vector<std::vector<double>> nova = UsrednjavajuciFilter(m, N);
    std::cout << "Matrica nakon filtriranja: " << std::endl;
    for (int i = 0; i < brojredova; i++) {
      for (int j = 0; j < brojkolona; j++) {
        std::cout << std::fixed << std::setprecision(2) << std::setw(7)
                  << nova.at(i).at(j);
      }
      std::cout << std::endl;
    }
  } catch (std::domain_error e) {
    std::cout << "GRESKA: " << e.what() << "!";
  }
  return 0;
}
