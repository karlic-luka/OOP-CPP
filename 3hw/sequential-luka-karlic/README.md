# Sekvencijalni spremnici

**Zadatak 1**. Spremnik `std::map<Key,Val>` predstavlja asocijativno polje u kojem se 
vrijednosti (tipa `Val`) dohvaćaju prema ključu (tipa `Key`). Obično se implementira kao binarno stablo
traženja što znači da su elementi u njemu _sortirani_ radi efikasnog pristupa.

S druge strane uobičajena implementacija binarnog stabla pomoću pokazivača je
memorijski vrlo neefikasna (za nalaženje sljedećeg elementa treba slijediti pokazivač).
Stoga se ponekad kao alternativa koristi sortirani `std::vector<std::pair<Key Val>>`.

Zadatak je implementirati klasu `Map` koja implementira asocijativno polje s ključem 
`Key = std::string` i vrijednostima `Val=int`. Potrebno je implementirati samo metode
`size`, `find`, `insert` i `erase`. Signature i opis metoda su dani u datoteci 
`sequential.h`. 

Bitna stvar je da dohvat elementa ima maksimalno složenost od log(n), što znači da 
spremnik treba držati SORTIRANIM pri insertiranju i brisanju elemenata kako bi se nalaženje
elementa moglo vršiti algoritmima na sortirani kolekcijama 
(`std::lower_bound`, `std::upper_bound`, `std::binary_search`, `std::equal_range`), 
koji garantiraju log(n) složenost. Radi vašeg vlastitog testiranja koda treba implementirati i `print()`
metodu koja ispisuje kolekciju na ekranu.

**Napomene**: Klasa `Map`  je zadana u datoteci `sequential.h` i ne treba ju mijenjati, niti 
išta dodavati ili oduzimati. Kako klasa nije parametrizirana implementacija metoda članica ide u 
datoteku `sequential.cpp`. Metoda `find()` vraća `std::optional` objekt koji je uveden u
C++17 te stoga morate imati noviji prevodilac. `std::optional` omogućava da vratimo vrijednost ili 
"ništa" ako element nije u spremniku. Na žalost, `std::optional` ne uzima referencu na objekt
pa stoga `find()` ne može mijenjati vrijednost elementa u spremniku `Map`. Ona samo vraća kopiju
vrijednosti.




**Zadatak 2**. U ovom zadatku treba implementirati još jednu verziju asocijativnog polja
koje čuva parove ključ (`Key`), vrijednost (`Val`).
Klasa koju treba implementirati naziva se `LUCache` i ima statičku dimenziju te ne koristi 
dinamički alociranu memoriju. Implementacija će stoga ponovo biti pomoću sortiranog polja parova
ključ/vrijednost, ali će spremnik koji interno koristimo biti `std::array<>`. To znači da će 
klasa `LUCache` biti parametrizirana brojem elemenata u kolekciji. 

`LUCache` je asocijativno polje što znači da se elementi dohvaćaju prema ključu. 
Elementi se sortiraju prema ključu i ostaju sortirani pri svim operacijama 
tako da dohvat elementa ima složenost log(N).

Specifičnost ove strukture podataka, koja ima fiksni broj elemenata,  je sljedeća: kada nema mjesta za novi element
u spremniku on se ubacuje na mjesto **najmanje korištenog elementa**. Najmanje korišteni element izlazi iz kolekcije odnosno
jednostavno je prebrisan novim elementom. 
Pri tome nije bitno koji će od najmanje korištenih elementa biti izbačen (može ih biti više). Odatle i ime kolekciji
(LU - `least used`).

Zadatak je implementirati predložak klase `LUCache<N>` koji implementira asocijativno polje s ključem 
`Key = std::string` i vrijednostima `Val=int`, dok je `N` broj elemenata u kolekciji. Potrebno je implementirati samo metode
 `size`, `find`, `insert` i `erase`. Signature i opis metoda su dani u datoteci 
`sequential.h`. Implementacija tih metoda također dolazi u datoteku `sequential.h` jer se radi o 
predlošku klase! Treba još implementirati i `print()`
metodu koja ispisuje kolekciju na ekranu radi vaših testova te `getKey(i)` metodu koja vraća ključ na i-toj 
poziciji radi testova u `test` direktoriju.

