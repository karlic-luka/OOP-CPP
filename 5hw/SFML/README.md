# Uvod u SFML

U ovom repozitoriju se nalazi polazni kod za uvod u SFML. Na stranici kolegija 
nalaze se video datoteke u kojima polazeći od ovdje prisutnog koda uvodimo neke elemente
biblioteke SFML. 

 
U direktoriju `src/` se nalazi jedan jednostavan SFML program.
U njemu koristimo sljedeće objekte:

*   [sf::RenderWindow](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1RenderWindow.php)
*   [sf::VideoMode](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1VideoMode.php)
*   [sf::Texture](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Texture.php)
*   [sf::Sprite](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Sprite.php)
*   [sf::Event](http://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Event.php)

U prvm koraku je potrebno reorganizirati program tako da se sav kod
smjesti u jednu klasu koju ćemo zvati `Game`. Program se izvršava pozivom
metode `Game::run()`.

U drugom koraku treba implementirati pomicanje objekta pomoću tipkovnice.

U trećem koraku treba kontrolirati brzinu pomicanja pomoću dodatne varijable.

Konačno treba primijeniti `fiksan vremenski korak`.

Više detalja nalazi se u dokumentu [doc/SFMLintro.html](doc/SFMLintro.html).


Nakon potpune transformacije koda potrebno je napraviti sljedeći **zadatak**.
Potrebno je kodu dodati funkcionalnost pomicanja _sprite_-a pomoću miša. 
Kada se miš pozicionira na  _sprite_ i pritisne se tipka miša (na primjer lijeva)
_sprite_ se mora pomicati za mišem sve dok se tipka miša ne otpusti.

 
