#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <iostream>
#include <sstream>

/* 1. Funkcija pretvara mala slova u velika i vraća novi string s kapitaliziranim znakovima.
   Za kapitalizaciju koristimo funkciju toupper() i <cctype> zaglavlja.
*/
std::string to_upper(std::string str);

/* 2.  Funkcija pretvara velika slova u mala i vraća novi string s dekapitaliziranim znakovima.
   Za dekapitalizaciju koristimo funkciju tolower() i <cctype> zaglavlja.
*/
std::string to_lower(std::string str);

/* 3. Funkcija invertira string i rezultat vraća kao novi string. */
std::string reverse(std::string str);

/* 4. Ukloni znakove u stringu str s lijeve strane (na početku stringa).
   Treba ukloniti sve znakove koji se pojavljuju u varijabli znakovi. Ako 
   argument znakovi nije dan podazumijeva se da sadrži bjeline. Vratiti 
   novi string ne mijenjajući polazni string. Ako linija sadrži samo bjeline
   vratiti prazan string. */
std::string trim_left(std::string str, std::string znakovi = " \t\n\v");

/* 5. Ukloni znakove u stringu str sa desne strane (na kraju stringa).
   Treba ukloniti sve znakove koji se pojavljuju u varijabli znakovi. Ako 
   argument znakovi nije dan podazumijeva se da sadrži bjeline. Vratiti 
   novi string ne mijenjajući polazni string. Ako linija sadrži samo bjeline
   vratiti prazan string. */
std::string trim_right(std::string str, std::string znakovi = " \t\n\v");

/* 6. Ukloni znakove u stringu str sa desne i lijeve strane (na početku i kraju stringa).
   Treba ukloniti sve znakove koji se pojavljuju u varijabli znakovi. Ako 
   argument znakovi nije dan podazumijeva se da sadrži bjeline. Vratiti 
   novi string ne mijenjajući polazni string. Ako linija sadrži samo bjeline
   vratiti prazan string. */
std::string trim(std::string str, std::string znakovi = " \t\n\v");

/* 7. Ukloni svako pojavljivanje znaka c iz stringa str. Vratiti 
   novi string ne mijenjajući polazni string.  */
std::string remove(std::string str, char c);

/* 8. Rutina za tokenizaciju stringa. Treba razbiti string na niz riječi 
   odijeljenih zadanim tokenom (argument delimiter). Riječi mogu biti 
   odvojene i sa više uzastopnih delimitera. Vratiti sve riječi kao 
   vektor stringova. Ulazni string ne mijenjati. 

   Implementacija: koristiti std::getline() na std::strinstream objektu.  
*/
std::vector<std::string> tokenize(std::string const & str, char delimiter);