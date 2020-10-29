#include "../include/strutils.h"

// Vaš kod dolazi ovdje.
using namespace std;

//1.funkcija
string to_upper(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

//2.funkcija
string to_lower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

//3.funkcija
string reverse(string str)
{
    reverse(str.begin(), str.end());
    return str;
}

//4.funkcija
string trim_left(string str, string znakovi)
{
    str.erase(0, str.find_first_not_of(znakovi));
    return str;
}

//5.funkcija
string trim_right(string str, string znakovi)
{
    str.erase(str.find_last_not_of(znakovi) + 1);
    return str;
}

//6.funkcija
string trim(string str, string znakovi)
{
    return trim_left(trim_right(str, znakovi), znakovi);
}

//7.funckija
string remove(string str, char c)
{
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
    return str;
}
//8.funkcija
vector<string> tokenize(string const &str, char delimiter)
{
    vector<string> tokeni;
    stringstream ss(str);
    string current;

    while(getline(ss, current, delimiter)) {
        current = remove(current, delimiter);
        if(current != "") tokeni.push_back(current);
    }
    return tokeni;
}