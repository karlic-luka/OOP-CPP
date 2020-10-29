#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "entities.h"
#include <vector>
#include <list>


/**
 * Klasa u kojoj je implementirana igra Asteroids.
 */ 
class Game{
public:
    /**
     * Konstruktor klase.
     */ 
    Game();
    /**
     * Pokreće igru.
     */ 
    void run();
private:
    /**
     * Procesuira vanjske događaje poput pritiska na tipkovnici i slično.
     */ 
    void processEvents();
    /**
     * Ažurira sve elemente koji će biti prikazani na zaslonu.
     * @param dt Promjena vremena.
     */ 
    void update(sf::Time dt);
    /**
     * Slika sve elemente na zaslon.
     * @param dt Promjena vremena.
     */ 
    void render();

    /**
     * Stvara asteroide i priprema ih za igru.
     * Nasumično im dodjeljuje smjer kretnje, orijentaciju te brzinu rotacije.
     * @param numberOfAsteroids Broj asteroida koje zelimo stvoriti
     */ 
    void prepareAsteroids(int numberOfAsteroids);
    /**
     * Odrađuje posao stvaranja metka i pripemanja za ispaljivanje.
     */
    void handleBullet();
    /**
     * Metoda koja pazi da se entitet kreće po torusu.
     * Npr. kada izaže iz prozora, vrati se na suprotnoj strani.
     */ 
    void entityTorus(Entity &entity);
    /**
     * Provjerava jesu li entiteti u koliziji po principu kružnice.
     * Npr. u koliziji su ako je udaljenost središta pripadnih kružnica manja
     * od zbroja pripadajućih radijusa.
     * @param first  entitet za koji se vrši provjera
     * @param second entitet za koji se vrši provjera
     * @return True ako su u koliziji, False inače
     */ 
    bool entitiesAreInCollision(const Entity &first, const Entity &second);
    /**
     * Vraća euklidsku normu.
     * @param first
     * @param second
     */
    double norm2(sf::Vector2f first, sf::Vector2f second);    
    /**
     * Obavlja posao nakon što je asteroid pogodio igrača.
     * Smješta ga ponovno u centar ekrana te mu smanjuje broj preostalih života za 1.
     */ 
    void playerGotHit();
    /**
     * Obavlja posao nakon što je došlo do kolizije asteorida i metka.
     * Oba nestaju s ekrana te se na mjestu sudara dogodi animacija eksplozije.
     * Ukoliko je pogođen veliki asteroid, stvara 2 manja na malo razmaknutim pozicijama
     * sa suprotnim orijentacijama.
     * @param asteroid Asteorid koji je uništen.
     * @param bullet Metak koji je uništio asteroid.
     */ 
    void asteroidGotHit(Asteroid &asteroid, Bullet &bullet);
    /**
     * Priprema tekst koji se ispisuje na zaslonu. U lijevom gornjem kutu stoji broj života,
     * a u desnom gornjem trenutni score.
     */ 
    void textSetup();
    /**
     * Ažurira tekst koji se ispisuje na prozoru. Npr. povećao se score ili je igrač izgubio život.
     */ 
    void updateText();
    /**
     * Provjerava je li igra završila. Igra završava u slučaju gubitka sva 3 života ili tako što
     * je igrač uništio sve asteoride.
     * @return True ako je igra gotova, False inače
     */ 
    bool gameIsOver();
    /**
     * Ponovno pokreće igru. Igrač se stvara ponovno u sredini prozora, ima 3 života te mu je trenutni score
     * jednak 0.
     */ 
    void restartGame();
    /**
     * Priprema animaciju (eksploziju) koja se treba prikazati radi kolizije entiteta.
     * @param position Pozicija na ekranu gdje će se prikazati.
     */ 
    void handleAnimation(const sf::Vector2f &position);
    /**
     * Provjerava sve moguće kolizije koje se mogu dogoditi te postupa u skladu
     * s događajima.
     */ 
    void handleAllCollisions();
    
    /**
     * Prozor na kojem se sve odražava.
     */ 
    sf::RenderWindow mWindow;
    /**
     * Broj asteroida kojim počinje igra.
     */ 
    int mNumberOfAsteroids;
    /**
     * Vraća istinu ako je igra u fazi igranja.
     * U slučaju da je False, to znači da čekamo igrača da se izjasni želi li ponovno igrati.
     */ 
    bool mGameIsRunning;
    /**
     * Vraća istinu ako smo prilikom kolizije već oduzeli život igraču.
     * U suprotnom bismo prilikom svake kolizije oduzeli npr 60 puta život.
     */ 
    bool alreadySubtractedLife;
    /**
     * Čuva sve slike.
     */ 
    TextureHolder mTextureHolder;
    /**
     * Pozadinska slika
     */ 
    sf::Sprite mBackgroundSprite;
    /**
     * Poametni pokazivač na igrača
     */   
    std::unique_ptr<Player> mPlayer;
    /**
     * Spremnik svih aktivnih asteorida.
     * Koristi se lista jer ima dosta brisanja i umetanja.
     */ 
    std::list<std::unique_ptr<Asteroid>> mAsteroids;
    /**
     * Spremnik svih aktivnih metaka.
     * Koristi se lista jer ima dosta brisanja i umetanja.
     */ 
    std::list<std::unique_ptr<Bullet>> mBullets;
    /**
     * Spremnik svih aktivnih eksplozija.
     * Koristi se lista jer ima dosta brisanja i umetanja. 
     */ 
    std::list<std::unique_ptr<Animation>> mExplosions;
    /**
     * Broj preostalih života. Po defaultu su 3.
     */ 
    int mNumberOfLives = 3;
    /**
     * Trenutni score. Razbijanje "malog" asteroida nosi 40 bodova,
     * "srednjeg" 20, a "velikog" 10. Pritom se "veliki" raspada na 2 manja prilikom pogotka.
     */ 
    int mScore = 0;
    /**
     * Font za ispis teksta.
     */ 
    sf::Font mFont;
    /**
     * Tekst koji se prikazuje u gornjem lijevom kutu.
     */ 
    sf::Text mUpperLeftText;
    /**
     * Tekst koji se prikazuje u gornjem desnom kutu.
     */ 
    sf::Text mUpperRightText;
    /**
     * Fiksno vrijeme promjene.
     */ 
    sf::Time mDtFixed;
};
