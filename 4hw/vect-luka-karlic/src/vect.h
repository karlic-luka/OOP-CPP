#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>

// deklaracija potrebna za testiranje
template <typename>
class VectTest;

template <typename T>
class Vect
{
  friend class VectTest<T>; // da testovi mogu dohvatiti privatne varijable
  friend class VectTestPair;

public:
  explicit Vect(size_t n = 0, T v = {});
  // Ctor
  // Kontrola kopiranja dolazi ovdje
  // CCtor
  Vect(Vect const &rhs);
  // MCtor
  Vect(Vect &&rhs) noexcept;
  // OP
  Vect &operator=(Vect const &rhs);
  // MOP
  Vect &operator=(Vect &&rhs) noexcept;
  // DTOR
  ~Vect();
  // dohvat elemenata (operator [])
  T operator[](unsigned int i) const;
  T &operator[](unsigned int i);
  // push_back metoda
  void push_back(T const &value);
  // info rutine size() i capacity()
  size_t size() const;
  size_t capacity() const;

  //privremene funkcija za testiranje
  T *getMdata() const { return mdata; }
  T *getMfirst() const { return mfirst_free; }
  T *getMend() const { return mend; }

  // operatori +=, -=, *=
  Vect &operator+=(Vect const &rhs);
  Vect &operator-=(Vect const &rhs);
  Vect &operator*=(T const &scalar);
  // euklidska norma vraća double !
  double two_norm() const;
  template <typename U>
  friend std::ostream &operator<<(std::ostream &out, Vect<U> const &vec);

private:
  T *mdata;       // pokazivač na prvi element
  T *mfirst_free; // pokazivač na prvo slobodno mjesto
  T *mend;        // pokazivač na kraj alociranog prostora
                  // (jedno mjesto iza posljednjeg)

  // Oslobodi zauzeti prostor (pomoću alokatora)
  void free();

  // realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
  // vektor prazan alociraj jedan element.
  void reallocate();

  // dodati vlastite privatne metode.

  // alokator ne mora imati pristup varijablama članicama klase pa ga činimo
  // statičkim. Ne zaboraviti definirati ga.
  static std::allocator<T> alloc;
};

//inicijalizacija staticke varijable
template <typename T>
std::allocator<T> Vect<T>::alloc;
// Deklaracija operator +, - i <<
template <typename T>
Vect<T> operator+(Vect<T> const &first, Vect<T> const &second);

template <typename T>
Vect<T> operator-(Vect<T> const &first, Vect<T> const &second);

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
