// Vaša implementacija dolazi ovdje.
#include <memory>
#include <math.h>
#include <algorithm>
#include <functional>
#include <numeric>

template <typename T>
Vect<T>::Vect(size_t n, T v)
{
    mdata = alloc.allocate(n);
    if (n == 0)
        mdata = mfirst_free = mend = nullptr;
    mend = mfirst_free = mdata + n;
    std::fill_n(mdata, n, v);
    //std::cout << "Konstruktor" << std::endl;
}

template <typename T>
Vect<T>::Vect(Vect const &rhs) : mdata(alloc.allocate(rhs.capacity()))
{
    //mdata = alloc.allocate(rhs.capacity());
    std::uninitialized_copy(rhs.mdata, rhs.mfirst_free, mdata);
    mfirst_free = mdata + rhs.size();
    mend = mdata + rhs.capacity();
    //std::cout << "Copy Konstruktor" << std::endl;
}

template <typename T>
Vect<T>::Vect(Vect &&rhs) noexcept : mdata(rhs.mdata), mfirst_free(rhs.mfirst_free), mend(rhs.mend)
{
    //rhs mora biti spreman za prolaz destruktora
    rhs.mdata = rhs.mfirst_free = rhs.mend = nullptr;
    //std::cout << "Move copy Konstruktor" << std::endl;
}
template <typename T>
void Vect<T>::free()
{
    //alloc.destroy(mdata);
    for (size_t i = 0; i < size(); i++)
        alloc.destroy(mdata + i);
    alloc.deallocate(mdata, capacity());
}
template <typename T>
Vect<T> &Vect<T>::operator=(Vect const &rhs)
{
    if (mdata != rhs.mdata)
    {
        free();
        mdata = alloc.allocate(rhs.capacity());
        std::uninitialized_copy(rhs.mdata, rhs.mfirst_free, mdata);
        mfirst_free = mdata + rhs.size();
        mend = mdata + rhs.capacity();
    }
    //std::cout << "OP" << std::endl;
    return *this;
}
template <typename T>
Vect<T> &Vect<T>::operator=(Vect &&rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        mdata = rhs.mdata;
        mfirst_free = rhs.mfirst_free;
        mend = rhs.mend;
        //rhs mora biti spreman za prolazak destruktora
        rhs.mdata = rhs.mfirst_free = rhs.mend = nullptr;
    }
    //std::cout << "MOP" << std::endl;
    return *this;
}

template <typename T>
size_t Vect<T>::capacity() const
{
    return mend - mdata;
}

template <typename T>
size_t Vect<T>::size() const
{
    return mfirst_free - mdata;
}

template <typename T>
double Vect<T>::two_norm() const
{
    if (size() == 0)
        return 0.0;
    else
        return std::sqrt(std::inner_product(mdata, mfirst_free, mdata, 0.0));
}

template <typename T>
void Vect<T>::reallocate()
{
    size_t newCap = (capacity() == 0) ? 1 : capacity() * 2;
    T *newData = alloc.allocate(newCap);
    //std::uninitialized_copy(mdata, mfirst_free, newData); --> ispod je bolje rjesenje???
    for (size_t i = 0; i < size(); i++)
        newData[i] = std::move(mdata[i]);
    //sada sam prebacio stare elemente
    free();
    mdata = newData;
    mfirst_free = mdata + (newCap / 2);
    mend = mdata + newCap;
}

template <typename T>
void Vect<T>::push_back(T const &value)
{
    //prvo provjeri treba li realocirati
    if (!(size() < capacity()))
        reallocate();

    *mfirst_free++ = value;
}

template <typename T>
Vect<T> &Vect<T>::operator+=(Vect const &rhs)
{
    if (size() != rhs.size())
        throw std::runtime_error("Ne možeš zbrajati vektore različite duljine!");
    for (size_t i = 0; i < size(); i++)
    {
        mdata[i] += *(rhs.mdata);
    }
    return *this;
}

template <typename T>
Vect<T> &Vect<T>::operator-=(Vect const &rhs)
{
    if (size() != rhs.size())
        throw std::runtime_error("Ne možeš oduzimati vektore različite duljine!");
    for (size_t i = 0; i < size(); i++)
    {
        mdata[i] -= *(rhs.mdata);
    }
    return *this;
}

template <typename T>
Vect<T> &Vect<T>::operator*=(T const &scalar)
{
    for (size_t i = 0; i < size(); i++)
    {
        mdata[i] *= scalar;
    }
    return *this;
}

template <typename T>
T Vect<T>::operator[](unsigned int i) const
{
    if (!(i < size()))
        throw std::runtime_error("Hej! Index out of range");
    return mdata[i];
}

template <typename T>
T &Vect<T>::operator[](unsigned int i)
{
    if (!(i < size()))
        throw std::runtime_error("Hej! Index out of range");
    return mdata[i];
}

template <typename T>
Vect<T> operator+(Vect<T> const &first, Vect<T> const &second)
{
    if (first.size() != second.size())
        throw std::runtime_error("Nisu jednako veliki");
    Vect<T> temp(first.capacity());
    for (size_t i = 0; i < first.size(); i++)
    {
        temp[i] = first[i] + second[i];
    }
    return temp;
}

template <typename T>
Vect<T> operator-(Vect<T> const &first, Vect<T> const &second)
{
    if (first.size() != second.size())
        throw std::runtime_error("Nisu jednako veliki");
    Vect<T> temp(first.capacity());
    for (size_t i = 0; i < first.size(); i++)
    {
        temp[i] = first[i] - second[i];
    }
    return temp;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Vect<T> const &vec)
{
    if (vec.size() == 0)
        out << "[]";
    else
    {
        out << "[";
        std::for_each(vec.mdata, vec.mdata + vec.size() - 1, [&out](T const x) { out << x << ","; });
        out << vec[vec.size() - 1] << "]";
    }

    return out;
}

template <typename T>
Vect<T>::~Vect()
{
    free();
    //std::cout << "Dtor" << std::endl;
}