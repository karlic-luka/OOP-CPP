#include "sequential.h"

// Ovdje dolazi vaša implementacija metoda klase Map
using namespace std;

Map::Map(size_t n)
{
    mData.reserve(n);
}

optional<Map::Val> Map::find(const Key &key) const
{
    if (mData.empty())
        return {};
    value_type help(key, 0); //samo da ga mogu ubaciti kao target, izbjegavam cast error
    auto compKey = [](const value_type &lhs, const value_type &rhs) { return lhs.first < rhs.first; };
    auto iter = lower_bound(mData.begin(), mData.end(), help, compKey);
    if (iter->first == key)
        return iter->second;
    else
        return {};
}

bool Map::insert(Map::value_type elem)
{
    if (mData.empty())
    {
        mData.push_back(elem);
        return true;
    }
    auto compKey = [](const value_type &lhs, const value_type &rhs) { return lhs.first < rhs.first; };
    auto iter = lower_bound(mData.begin(), mData.end(), elem, compKey);
    if (iter->first == elem.first)
        return false;
    else
    {
        mData.insert(iter, elem);
        return true;
    }
}

bool Map::erase(const Key &key)
{
    if (mData.empty())
        return false;
    value_type help(key, 0); //samo da ga mogu ubaciti kao target, izbjegavam cast error
    auto compKey = [](const value_type &lhs, const value_type &rhs) { return lhs.first < rhs.first; };
    auto iter = lower_bound(mData.begin(), mData.end(), help, compKey);
    if (iter->first != key)
        return false;
    else
    {
        mData.erase(iter);
        return true;
    }
}

size_t Map::size() const
{
    return mData.size();
}

void Map::print(const char *message) const
{
    for (auto elem : mData)
        cout << "(" << elem.first << ", " << elem.second << ") ";
    cout << endl;
    cout << message << endl;
}
