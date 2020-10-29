**Zadatak**. 
Treba napisati 8 funkcija za manipulaciju sa stringovima. 


1. Funkcija pretvara mala slova u velika i vraća novi string s kapitaliziranim znakovima.
   Za kapitalizaciju koristimo funkciju `toupper()` i `<cctype>` zaglavlja.

2. Funkcija pretvara velika slova u mala i vraća novi string s dekapitaliziranim znakovima.
   Za dekapitalizaciju koristimo funkciju `tolower()` i `<cctype>` zaglavlja.

3. Funkcija invertira string i rezultat vraća kao novi string. 

4. Ukloni znakove u stringu str s lijeve strane (na početku stringa).
   Treba ukloniti sve znakove koji se pojavljuju u varijabli znakovi. Ako 
   argument znakovi nije dan podazumijeva se da sadrži bjeline. Vratiti 
   novi string ne mijenjajući polazni string. Ako linija sadrži samo bjeline
   vratiti prazan string. 

5. Ukloni znakove u stringu str sa desne strane (na kraju stringa).
   Treba ukloniti sve znakove koji se pojavljuju u varijabli znakovi. Ako 
   argument znakovi nije dan podazumijeva se da sadrži bjeline. Vratiti 
   novi string ne mijenjajući polazni string. Ako linija sadrži samo bjeline
   vratiti prazan string.

6.  Ukloni znakove u stringu str sa desne i lijeve strane (na početku i kraju stringa).
   Treba ukloniti sve znakove koji se pojavljuju u varijabli znakovi. Ako 
   argument znakovi nije dan podazumijeva se da sadrži bjeline. Vratiti 
   novi string ne mijenjajući polazni string. Ako linija sadrži samo bjeline
   vratiti prazan string. 

7.  Ukloni svako pojavljivanje znaka c iz stringa str. Vratiti 
   novi string ne mijenjajući polazni string. 

8. Rutina za tokenizaciju stringa. Treba razbiti string na niz riječi 
   odijeljenih zadanim tokenom (argument delimiter). Riječi mogu biti 
   odvojene i sa više uzastopnih delimitera. Vratiti sve riječi kao 
   vektor stringova. Ulazni string ne mijenjati. 
   Implementacija: koristiti `std::getline()` na `std::strinstream` objektu.  


Samo u osmoj funkciji se smije koristiti (jedna) petlja. U svim  ostalim funkcijama 
ne smije biti  petlji. Svu funkcionalnost treba implementirati pomoću metoda članica klase
`std::string` i algoritmima (iz zaglavlja `<algorithm>`).

Signature funkcija koje treba napisati dane su u datoteci `include/strutils.h`. Implementacija 
ide u `src/strutils.cpp`. U datoteci `src/main.cpp` testira se vlastiti kod. 

