#include "../include/strutils.h"
#include <iostream>

using namespace std;
void testiraj(string ulaz, string izlaz, int broj)
{
    if (ulaz == izlaz)
    {
        cout << broj << ". RUN : OK" << endl;
    }
    else
    {
        cout << broj << ". RUN : FAIL"
             << " Pisalo je: " << ulaz
             << ", a treba: " << izlaz << endl;
    }
}
int main(int argc, char **argv)
{

    string str("tEst");
    string output;
    string expected;

    //to_upper
    output = to_upper(str);
    expected = "TEST";
    testiraj(output, expected, 1);
    expected = "tEst";
    testiraj(str, expected, 2);

    //to_lower
    output = to_lower(str);
    expected = "test";
    testiraj(output, expected, 3);
    expected = "tEst";
    testiraj(str, expected, 4);

    //reverse
    output = reverse(str);
    expected = "tsEt";
    testiraj(output, expected, 5);
    expected = "tEst";
    testiraj(str, expected, 6);

    //trim_left
    str = "     abc";
    output = trim_left(str);
    expected = "abc";
    testiraj(output, expected, 7);

    str = "abba   abc";
    string znakovi("ab");
    output = trim_left(str, znakovi);
    expected = "   abc";
    testiraj(output, expected, 8);

    str = "       ";
    output = trim_left(str);
    expected = "";
    testiraj(output, expected, 9);

    //trim right
    str = "abc    ";
    output = trim_right(str);
    expected = "abc";
    testiraj(output, expected, 10);

    str = "abc   abba";
    znakovi = "ab";
    output = trim_right(str, znakovi);
    expected = "abc   ";
    testiraj(output, expected, 11);

    str = "       ";
    output = trim_left(str);
    expected = "";
    testiraj(output, expected, 12);

    //nije mi se dalo pisati primjere za trim jer sam ju
    //implementirao kao kompoziciju trim_left i right
    //stoga je ekvivalentno samo provjeriti left i rigt

    //remove
    str = "ovo je recenica";
    char c = 'o';
    output = remove(str, c);
    expected = "v je recenica";
    testiraj(output, expected, 13);
    expected = "ovo je recenica";
    testiraj(str, expected, 14);

    str = "aaa";
    c = 'a';
    output = remove(str, c);
    expected = "";
    testiraj(output, expected, 15);

    //tokenize
    str = "   prvo testiram     samo     na    razmacima   ";
    char delimiter = ' ';
    vector<string> tokeni = tokenize(str, delimiter);
    vector<string> out = {"prvo", "testiram", "samo", "na", "razmacima"};
    expected = "   prvo testiram     samo     na    razmacima   ";
    testiraj(str, expected, 16);

    if (tokeni == out)
        cout << "RUN : OK" << endl;
    else
        cout << "FAIL tokenizacija1" << endl;

    str = "dodao sssam novi delimiter s";
    delimiter = 's';
    tokeni = tokenize(str, delimiter);
    out.clear();
    out = {"dodao ", "am novi delimiter "};
    if (tokeni == out)
        cout << "RUN : OK" << endl;
    else
        cout << "FAIL tokenizacija2" << endl;

    //for_each(tokeni.begin(), tokeni.end(), [](const string &str) { cout << str << endl; });
    return 0;
}