 #ifndef EVALUATE_PREFIX_H
#define EVALUATE_PREFIX_H

#include <string>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <iostream>

/*  Klasa za izračunavanje aritmetičkog izraza danog u poljskoj notaciji.
 *  Binarne operacije su +,-,*,/ i ^.
 *  Unarne operacije ~ (negacija). Koristimo ~ umjesto - kako bismo
 *  mogli razlikovati unarnu od binarne operacije prema simbolu.
 *  Klasa radi samo s cjelobrojnim izrazima. 
 */
class Expression
{
public:
    // tip izraza
    using Value = int;

    //tiop tokena
    enum TokenType
    {
        operand,
        unaryOp,
        binaryOp
    };

    // pomoćna klasa koja predstavlja element izraza. Ako je izraz operand
    // imat će vrijednost. 
    //Ako se radi o operaciji, onda je symbol dotična operacija, a
    //vrijednost sljedeca:
    //{"~" = 0, "+" = 1; "-" = 2, "*" = 3, "/" = 4, "^" = 5}
    class Token
    {
    private:
        TokenType type;
        char symbol;
        Value value;

    public:
        //Token(){};
        //getteri
        TokenType getType() const { return type; };
        char getSymbol() const { return symbol; };
        Value getValue() const { return value; };
        //setteri
        void setType(TokenType type) {this->type = type;}
        void setSymbol(char symbol) {this->symbol = symbol;}
        void setValue(Value value) {this->value = value;}
        
    };

    // Konstrukcija izraza iz stringa.
    // text mora sadržavati aritmetički izraz u poljskoj notaciji Sprema
    // se u varijablu članicu mText.
    Expression(std::string text);

    // Izračunaj vrijednost izraza. Može uništiti izraz, odnosno
    // evaluate se ne može pozvati više puta.
    //rekurzivna metoda
    Value evaluate();

    //pomocna funkcija za debuggiranje
    //void printAllTokens();

private:
    //ne zelim implementirati iterator, stoga cu se sluziti indeksima
    //i kretati kroz vector tokena
    int currentIndex; //nisam htio koristiti Value currentIndex
    Token currentToken;
    std::vector<Token> tokens;
    std::vector<std::string> stringTokens;
    std::string mText;
    Value currentValue;

    // Daje sljedeći token sadržan u izrazu
    // (simbol operacije ili cijeli broj)
    Token getToken();
    void prepareTokens();
    //evaluira operatore
    Value evaluateOp(Value op, Value first, Value second);
};

/* Pomocna funkcija za pripremu tokenizacije izraza
zelim nakon svakog znaka imati razmake, pritom pazeci
na to da moze biti viseznamenkasti broj!*/
std::string spacedExpression(std::string expr);

/* Ukloni svako pojavljivanje znaka c iz stringa str. Vratiti 
novi string ne mijenjajući polazni string.  */
std::string remove(std::string str, char c);

/* Rutina za tokenizaciju stringa. Treba razbiti string na niz riječi 
odijeljenih zadanim tokenom (argument delimiter). Riječi mogu biti 
odvojene i sa više uzastopnih delimitera. Vratiti sve riječi kao 
vektor stringova. Ulazni string ne mijenjati. */
std::vector<std::string> tokenize(std::string const &str, char delimiter = ' ');
// NAPOMENA: Nije nužno koristiti unutarnju klasu  Expression::Token
//           ukoliko imate bolji način, no unutarnje klase su ovdje vrlo
//           prirodne.

#endif // EVALUATE_PREFIX_H
