// TP 2022/2023: Zada?a 1, Zadatak 4
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
bool isti_su(std::string rijec, std::string zabranjena) {
  for (int i = 0; i < rijec.length(); i++) {
    // if (std::tolower(rijec.at(i))==std::tolower(zabranjena.at(i))) isti =
    // true;
    if (std::tolower(rijec.at(i)) != std::tolower(zabranjena.at(i)))
      return false;
  }
  return true;
}
std::string Cenzura(std::string recenica,
                    std::vector<std::string> spisakrijeci) {
  for (int i = 0; i < spisakrijeci.size(); i++) {
    for (int j = 0; j < spisakrijeci.at(i).length(); j++) {
      // if (!((spisakrijeci.at(i).at(j)>='a' && spisakrijeci.at(i).at(j)<='z')
      //|| (spisakrijeci.at(i).at(j)>='A' && spisakrijeci.at(i).at(j)<='Z')
      //|| (spisakrijeci.at(i).at(j)>='0' && spisakrijeci.at(i).at(j)<='9')))
      if (!(isalnum(spisakrijeci.at(i).at(j))))
        throw std::logic_error("Neispravna rije?");
    }
  }
  std::string rijec;
  for (int i = 0; i < recenica.length();
       i++) // DODATI EXCEPTIO ZA NEISPRAVNA RIJEC
  {
    if (isalnum(recenica.at(i))) {
      int pocetakrijeci = i;

      // while (i<recenica.length() && recenica.at(i)!=' ' &&
      // recenica.at(i)!=',' && recenica.at(i)!='!' && recenica.at(i)!='.' && recenica.at(i)!='?' && recenica.at(i)!='"')
 while (i<recenica.length() && isalnum(recenica.at(i)))
 {
  rijec = rijec + recenica.at(i);
  i++;
}
for (int j = 0; j < spisakrijeci.size(); j++) {
  if (rijec.length() == spisakrijeci.at(j).length())
  // TOLOWER MOZE AKO JE at.i at.j ali onda kako porediti slovo i rijec cijelu
  {
    if (isti_su(rijec, spisakrijeci.at(j))) {
      for (int k = pocetakrijeci; k < i; k++) {
        recenica.at(k) = '*';
      }
    }
    /*for (int x=pocetakrijeci;x<pocetakrijeci+rijec.length();x++)
    {
    if (std::tolower(rijec.at(x)) == std::tolower(spisakrijeci.at(
   j).at(x)))
    recenica.at(x)='*';
    }*/
    // for (int k=pocetakrijeci;k<i;k++)
    //{
    // recenica.at(k)='*';
    //}
  }
}
rijec = "";
    }
  }
  return recenica;
}
int main() {
  try {
    std::cout << "Unesite recenicu: " << std::endl;
    std::string recenica;
    std::getline(std::cin, recenica);
    std::cout << "Unesite zabranjene rijeci (. za kraj): " << std::endl;
    std::vector<std::string> spisak;
    std::string zabranjene;
    int i = 0;
    std::getline(std::cin, zabranjene);
    while (zabranjene.at(i) != '.') {
      std::string rijec;
      while (zabranjene.at(i) != ' ') {
        rijec = rijec + zabranjene.at(i);
        i++;
      }
      spisak.push_back(rijec);
      i++;
    }
    std::string cenzurisanarecenica = Cenzura(recenica, spisak);
    std::cout << "Cenzurisana recenica: " << cenzurisanarecenica;
  } catch (std::logic_error e) {
    // std::cout<<e.what()<<std::endl;
    std::cout << "GRESKA: Nelegalne zabranjene rijeci!";
    return 0;
  }
  return 0;
}