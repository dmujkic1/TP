// TP 2022/2023: Zada?a 3, Zadatak 3
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>
template <typename TipElemenata> struct Matrica {
  char ime_matrice; // Koristi se samo u funkciji "UnesiMatricu"
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!!!
};
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona]{};
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  return mat;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &mat1,
                                     const Matrica<TipElemenata> &mat2) {
  if (mat1.br_kolona != mat2.br_redova)
    throw std::domain_error("Matrice nisu saglasne za mnozenje");
  Matrica<TipElemenata> pomnozenamatrica =
      StvoriMatricu<TipElemenata>(mat1.br_redova, mat2.br_kolona);
  pomnozenamatrica.br_redova = mat1.br_redova;
  pomnozenamatrica.br_kolona = mat2.br_kolona;
  for (int i = 0; i < pomnozenamatrica.br_redova; i++) {
    for (int j = 0; j < pomnozenamatrica.br_kolona; j++) {
      for (int k = 0; k < mat2.br_redova; k++) {
        pomnozenamatrica.elementi[i][j] +=
            mat1.elementi[i][k] * mat2.elementi[k][j];
      }
    }
  }
  return pomnozenamatrica;
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(Matrica<TipElemenata> mat,
                                                 int n) {
  if (mat.br_redova != mat.br_kolona)
    throw std::domain_error("Matrica nije kvadratna");
  if (n < 0)
    throw std::domain_error("Pogresan parametar n");
  Matrica<TipElemenata> rezultat;
  try {
    rezultat = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
  } catch (...) {
    UnistiMatricu(rezultat);
    throw std::bad_alloc();
  }
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++) {
      rezultat.elementi[i][j] = mat.elementi[i][j];
    }
  }
  double clan;
  Matrica<TipElemenata> faktor; // 000
  Matrica<TipElemenata> o;      // 000
  Matrica<TipElemenata> temp;   // 000
  bool pocetak = true;
  for (int i = 2; i <= n; i++) {
    if (!pocetak)
      temp = o;
    else
      temp = mat; // 898
    try {
      faktor = ProduktMatrica(mat, temp); // 934 nova matrica
    } catch (...) {
      UnistiMatricu(faktor);
      UnistiMatricu(rezultat);
      throw std::bad_alloc();
    }
    clan = 1. / i;
    for (int j = 0; j < mat.br_redova; j++) {
      for (int k = 0; k < mat.br_redova; k++) {
        rezultat.elementi[j][k] += clan * faktor.elementi[j][k];
      }
    }
    if (!pocetak)
      UnistiMatricu(o);
    o = faktor;
    if (i == n)
      UnistiMatricu(o);
    pocetak = false;
  }
  return rezultat;
}
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}
template <typename TipElemenata> void UnesiMatricu(Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
    }
}
template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost = 6, bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost)
                << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if (treba_brisati) {
    Matrica<TipElemenata> temp = mat;
    UnistiMatricu(temp);
  }
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}
int main() {
  Matrica<double> A; // AUTOMATSKA INICIJALIZACIJA!!!
  Matrica<double> B;
  int dimenzija;
  std::cout << "Unesite dimenziju kvadratne matrice: ";
  std::cin >> dimenzija;
  std::cout << "Unesite elemente matrice A: \n";
  try {
    A = StvoriMatricu<double>(dimenzija, dimenzija, 'A');
    UnesiMatricu(A);
    std::cout << "Unesite red polinoma: ";
    int n;
    std::cin >> n;
    B = MatricniHarmonijskiPolinom(A, n);
  } catch (std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }
  std::cout << "Matricni harmonijski polinom:\n";
  IspisiMatricu(B, 10);
  UnistiMatricu(A);
  UnistiMatricu(B);
  return 0;
}
