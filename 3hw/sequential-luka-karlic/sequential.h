#pragma once

#include <string>
#include <vector>
#include <array>
#include <optional> // C++17

#include <iostream>
#include <algorithm>
#include <cassert>
#include <tuple>

class MapTest; // Klasa porebna za testiranje privatnog dijela klase .

// Sortirani vektor kao std::map. Klasa koju trebate implementirati
class Map
{
    friend class MapTest;

public:
    //  Eksportirani tipovi.
    using value_type = std::pair<std::string, int>;
    using Key = std::string;
    using Val = int;

    // Konstruktor. Kreira prazan spremnik.
    Map(std::size_t n = 0);

    // Nalaženje elementa u kolekcji. Mora biti O(log n).
    // Vraća vrijednost ako je ključ nađen ili prazan optional ako nije.
    std::optional<Val> find(const Key &key) const;

    // Ubacivanje elementa u kolekciju. Vraća true ako je element ubačen.
    // Ako element već postoji u kolekciji ne ubacuje ga i vraća false.
    bool insert(value_type elem);

    // Brisanje elementa iz kolekcije. Vraća true ako je elemnt izbrisan,
    // false ako ga nema u kolekciji.
    bool erase(const Key &key);

    // Broj elemenata u kolekciji.
    std::size_t size() const;

    // Ispis kolekcije. Samo za razvoj programa. Ne testira se.
    void print(const char *message = nullptr) const;

private:
    // Sortirani vektor kao zamjena za std::map.
    std::vector<value_type> mData;
};

//2.ZADATAK
// LUCache = least used cache. Klasa koju trebate implementirati
template <std::size_t N>
class LUCache
{
public:
    using Key = std::string;
    using Val = int;
    using value_type = std::pair<Key, Val>;
    // Možete eksportirati i druge tipove, ali zadržite ove!

    // Konstruktor.
    LUCache();

    // Nalaženje elementa u kolekcji. Mora biti O(log n).
    // Vraća vrijednost ako je ključ nađen ili prazan optional ako nije.
    std::optional<Val> find(const Key &key);

    // Ubacivanje elementa u kolekciju.Vraća true ako je element ubačen.
    // Ako element već postoji u kolekciji ne ubacuje ga i vraća false.
    bool insert(value_type elem);

    // Brisanje elementa iz kolekcije.  Vraća true ako je elemnt izbrisan,
    // false ako ga nema u kolekciji.
    bool erase(const Key &key);

    // Broj elemenata u kolekciji. Uvijek <= N.
    std::size_t size() const { return mSize; }

    // Ispis kolekcije. Samo za razvoj programa. Ne testira se.
    void print(const char *message = nullptr) const;

    // Ključ i-tog elementa u kolekciji. Metoda služi samo za testiranje.
    // Ako elemet nije prisutan ponašanje je nedefinirano.
    Key getKey(std::size_t i) const;

private:
    //data
    std::array<value_type, N> mData;
    
    //trenutna "stvarna" velicina arraya
    std::size_t mSize;
    
    //varijabla koja će čuvati sve TRENUTNE elemente naseg spremnika
    //na ISTIM indeksima kako ih cuva i mData
    //bitno mi je samo kakav je key(a ne mogu biti 2 s istim kljucem istovremeno)
    //stoga cu koristiti value_type::second kao BROJ POZIVA FUNKCIJE find!
    std::array<value_type, N> mAll;
    
    //pomocna funckija koja vraca indeks na kojem se nalazi najrjedi
    //(ako su jednako rijetki, onda zadnji prema implementaciji)
    int indexRare() const;
};

// Implementacija predloška klase dolazi u datoteku zaglavlja.
// Napomena. typename se stavlja tamo gdje u parametriziranoj klasi LUCache<N>
//           dohvaća eksportirani tip (Key, Val). To je nužno jer ista sintaksa služi
//           za dohvat statičke varijable.

template <std::size_t N>
LUCache<N>::LUCache() : mSize(0){};

template <std::size_t N>
std::optional<typename LUCache<N>::Val> LUCache<N>::find(const Key &key)
{
    //implementirao sam svoj binary search, a nisam koristio <algorithm>
    //zato sto preko <algorithm> ne mogu zapamtiti INDEX koji mi treba
    //za updejtanje mAll varijable (trebam inkrementirati vrijednost za second)
    //u protivnom bih pokvario slozenost

    //binary search
    int indLeft = 0;
    int indRight = mSize - 1;

    while (indLeft <= indRight)
    {
        int indMiddle = indLeft + (indRight - 1) / 2;
        value_type middle = mData.at(indMiddle);

        if (middle.first == key)
        {
            mAll.at(indMiddle).second++;
            return {middle.second};
        }
        else if (middle.first < key)
            indLeft = indMiddle + 1;
        else
            indRight = indMiddle - 1;
    }
    //ako sam ovdje, ne postoji
    return {};
}

template <std::size_t N>
int LUCache<N>::indexRare() const
{
    int indSmallest;
    Val smallest;
    //kad se ova funkcija poziva, onda je sigurno mSize = mData.size()
    for (int i = 0; i < mSize; i++)
    {
        if (i == 0 || mAll.at(i).second <= smallest)
        {
            indSmallest = i;
            smallest = mAll.at(i).second;
        }
    }
    return indSmallest;
}
template <std::size_t N>
bool LUCache<N>::insert(value_type elem)
{
    if (mSize == 0)
    {
        mData[0] = elem;
        mAll[mSize++] = std::make_pair(elem.first, 0);
        return true;
    }
    //moram provjeriti postoji li mozda vec
    if (std::any_of(mData.begin(), mData.end(), [elem](const value_type &x) { return x.first == elem.first; }))
        return false;
    //zelim ubaciti tako da bude sortirano
    if (mSize < mData.size())
    {
        int i;
        for (i = mSize - 1; (i >= 0 && mData.at(i).first > elem.first); i--)
        {
            mData.at(i + 1) = mData.at(i);
            mAll.at(i + 1) = mAll.at(i);
        }
        mData.at(i + 1) = elem;
        mAll.at(i + 1) = std::make_pair(elem.first, 0);
        mSize++;
    }
    else
    {
        //moram izbaciti najrjedi element
        int index = indexRare();
        mData.at(index) = elem;
        mAll.at(index) = std::make_pair(elem.first, 0);
        //sada trebam opet sortirati!
        //ali to nije problem jer je polje pune velicine
        auto compKey = [](const value_type &lhs, const value_type &rhs) { return lhs.first < rhs.first; };
        sort(mData.begin(), mData.end(), compKey);
        sort(mAll.begin(), mAll.end(), compKey);
    }
    return true;
}

template <std::size_t N>
bool LUCache<N>::erase(const Key &key)
{
    int index = 0;
    for (value_type x : mData)
    {
        if (x.first == key)
        {
            //obrisati valjda znaci staviti prazan string
            mData.at(index) = std::make_pair("", 0);
            //updejt mAll varijable trenutnih vrijednosti
            mAll.at(index) = std::make_pair("", 0);
            mSize--;
            //moram opet sortirati, ali "problem" je prazan string - mora biti veci od svih, tj zelim ga skroz desno!
            //zato sam lambdu napisao kao 3 if-a
            auto compKey = [](const value_type &lhs, const value_type &rhs) { if(lhs.first == "" && rhs.first != "") return false; 
            else if(lhs.first != "" && rhs.first == "") return true; else return lhs.first < rhs.first; };

            std::sort(mData.begin(), mData.end(), compKey);
            std::sort(mAll.begin(), mAll.end(), compKey);
            return true;
        }
        index++;
    }
    return false;
}

template <std::size_t N>
void LUCache<N>::print(const char *message) const
{
    //message nema smisla, a ako je nullptr, onda mi blokira ostatak ispisa
    std::cout << "Trenutno stanje: " << std::endl;
    std::for_each(mData.begin(), mData.end(),
                  [](const value_type &elem) { std::cout << "(" << elem.first << ", " << elem.second << ") "; });

    std::cout << std::endl;
}

template <std::size_t N>
typename LUCache<N>::Key LUCache<N>::getKey(std::size_t i) const
{
    return mData.at(i).first;
}
