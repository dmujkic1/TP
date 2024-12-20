// TP 2022/2023: Zada?a 1, Zadatak 3
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
typedef std::vector<std::vector<int>> matrica;
bool DaLiJeSpiralnaMatrica(matrica m) {
  int brojac = 1;
  for (int i = 0; i < m.size() - 1; i++) {
    if (m.at(i).size() != m.at(i + 1).size())
      return false;
    brojac++;
  }
  if (brojac == m.size())
    return true;
  int brojredova;
  brojredova = m.size();
  int brojkolona;
  brojkolona = m.at(0).size();
  int k;
  k = m.at(0).at(0);
  bool smjer;
  if ((m.at(0).at(1)) + 1 == m.at(0).at(0))
    smjer = true;
  if ((m.at(0).at(0)) + 1 == m.at(0).at(0))
    smjer = false;
  if (smjer == true) // desna
  {
    int gornjagr = 0;
    int donjagr = brojredova - 1;
    int desnagr = brojkolona - 1;
    int lijevagr = 0;
    int i = 0;
    int j = 0;
    while (gornjagr <= donjagr && lijevagr <= desnagr) {
      while (j < desnagr - 1) {
        m.at(gornjagr).at(j) = k;
        if (m.at(gornjagr).at(j + 1) != (m.at(gornjagr).at(j)) + 1)
          return false;
        k++;
        j++;
      }
      gornjagr++;
      while (i < donjagr - 1) {
        m.at(i).at(desnagr) = k;
        if (m.at(i + 1).at(desnagr) != (m.at(i).at(desnagr)) + 1)
          return false;
        k++;
        i++;
      }
      desnagr--;
      // donjagr--;
      // gornjagr++;
      while (j > lijevagr - 1) {
        m.at(donjagr).at(j) = k;
        if (m.at(donjagr).at(j - 1) != (m.at(donjagr).at(j)) + 1)
          return false;
        k++;
        j--;
      }
      donjagr--;
      // desnagr--;
      // lijevagr++;
      while (i > gornjagr - 1) {
        m.at(i).at(lijevagr) = k;
        if (m.at(i - 1).at(lijevagr) != (m.at(i).at(lijevagr)) + 1)
          return false;
        k++;
        i--;
      }
      lijevagr++;
    }
    m.at(i).at(j) = k;
    if (m.at(i).at(j) < m.at(0).at(0))
      return false;
    return true;
  } else if (smjer == false) // lijeva
  {
    int gornjagr = 0;
    int donjagr = brojredova - 1;
    int desnagr = brojkolona - 1;
    int lijevagr = 0;
    int i = 0;
    int j = 0;
    while (gornjagr <= donjagr && lijevagr <= desnagr) {
      while (i < donjagr - 1) {
        m.at(i).at(lijevagr) = k;
        if (m.at(i + 1).at(lijevagr) != (m.at(i).at(lijevagr)) + 1)
          return false;
        k++;
        i++;
      }
      lijevagr++;
      while (j < desnagr - 1) {
        m.at(donjagr).at(j) = k;
        if (m.at(donjagr).at(j + 1) != (m.at(donjagr).at(j)) + 1)
          return false;
        k++;
        j++;
      }
      donjagr--;
      while (i > gornjagr - 1) {
        m.at(i).at(desnagr) = k;
        if (m.at(i - 1).at(desnagr) != (m.at(i).at(desnagr)) + 1)
          return false;
        k++;
        i--;
      }
      desnagr--;
      while (j > lijevagr - 1) {
        m.at(gornjagr).at(j) = k;
        if (m.at(gornjagr).at(j - 1) != (m.at(gornjagr).at(j)) + 1)
          return false;
        k++;
        j--;
      }
      gornjagr++;
    }
    m.at(i).at(j) = k;
    if (m.at(i).at(j) < m.at(0).at(0))
      return false;
    return true;
  }
}
matrica KreirajSpiralnuMatricu(int brojredova, int brojkolona, int k,
                               bool smjer) {
  matrica prazna;
  if (brojredova <= 0 || brojkolona <= 0)
    return prazna; // 0x0 matrica
  matrica m;
  m.resize(brojredova);
  for (int i = 0; i < brojredova; i++)
    m.at(i).resize(brojkolona);
  if (smjer == true) // desna
  {
    int gornjagr = 0;
    int donjagr = brojredova - 1;
    int desnagr = brojkolona - 1;
    int lijevagr = 0;
    int i = 0;
    int j = 0;
    while (gornjagr <= donjagr && lijevagr <= desnagr) {
      while (j < desnagr) {
        m.at(gornjagr).at(j) = k;
        k++;
        j++;
      }
      gornjagr++;
      while (i < donjagr) {
        m.at(i).at(desnagr) = k;
        k++;
        i++;
      }
      desnagr--;
      // donjagr--;
      // gornjagr++;
      while (j > lijevagr) {
        m.at(donjagr).at(j) = k;
        k++;
        j--;
      }
      donjagr--;
      // desnagr--;
      // lijevagr++;
      while (i > gornjagr) {
        m.at(i).at(lijevagr) = k;
        k++;
        i--;
      }
      lijevagr++;
    }
    m.at(i).at(j) = k;
  } else if (smjer == false) // lijeva
  {
    int gornjagr = 0;
    int donjagr = brojredova - 1;
    int desnagr = brojkolona - 1;
    int lijevagr = 0;
    int i = 0;
    int j = 0;
    while (gornjagr <= donjagr && lijevagr <= desnagr) {
      while (i < donjagr) {
        m.at(i).at(lijevagr) = k;
        k++;
        i++;
      }
      lijevagr++;
      while (j < desnagr) {
        m.at(donjagr).at(j) = k;
        k++;
        j++;
      }
      donjagr--;
      while (i > gornjagr) {
        m.at(i).at(desnagr) = k;
        k++;
        i--;
      }
      desnagr--;
      while (j > lijevagr) {
        m.at(gornjagr).at(j) = k;
        k++;
        j--;
      }
      gornjagr++;
    }
    m.at(i).at(j) = k;
  }
  return m;
}
int main() {
  std::cout << "Unesite broj redova i kolona matrice: " << std::endl;
  int brojredova;
  int brojkolona;
  std::cin >> brojredova >> brojkolona;
  std::cout << "Unesite pocetnu vrijednost: " << std::endl;
  int k;
  std::cin >> k;
  std::cout << "Unesite L za lijevu, a D za desnu spiralnu matricu: "
            << std::endl;
  char smjer;
  std::cin >> smjer;
  if (smjer == 'D') {
    bool pravac = true;
    matrica m = KreirajSpiralnuMatricu(brojredova, brojkolona, k, pravac);
    std::cout << "Kreirana desna spiralna matrica: " << std::endl;
    for (int i = 0; i < brojredova; i++) {
      for (int j = 0; j < brojkolona; j++) {
        std::cout << m.at(i).at(j) << " ";
      }
      std::cout << std::endl;
    }
  } else if (smjer == 'L') {
    bool pravac = false;
    matrica m = KreirajSpiralnuMatricu(brojredova, brojkolona, k, pravac);
    std::cout << "Kreirana lijeva spiralna matrica: " << std::endl;
    for (int i = 0; i < brojredova; i++) {
      for (int j = 0; j < brojkolona; j++) {
        std::cout << m.at(i).at(j) << " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
