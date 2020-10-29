#ifndef EVALUATE_POSTFIX_H
#define EVALUATE_POSTFIX_H

#include <string>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <math.h>

/*  Klasa za izračunavanje aritmetičkog izraza danog u inverznoj poljskoj notaciji.
 *  Binarne operacije su +,-,*,/ i ^.
 *  Unarne operacije ~ (negacija). Koristimo ~ umjesto - kako bismo
 *  mogli razlikovati unarnu od binarne operacije prema simbolu.
 */
class IPExpression
{
public:
    // tip izraza
    using Value = int;

    enum TokenType
    {
        operand,
        unaryOp,
        binaryOp,
        endToken
    };

    // pomoćna klasa koja predstavlja element izraza
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
        void setType(TokenType type) { this->type = type; }
        void setSymbol(char symbol) { this->symbol = symbol; }
        void setValue(Value value) { this->value = value; }
    };

    // Konstrukcija izraza iz stringa.
    // text mora sadržavati aritmetički izraz u poljskoj notaciji
    IPExpression(std::string text);
    // Izračunaj vrijednost izraza. Uništava izraz
    Value evaluate();

    //void printAllTokens();
private:
    //ne zelim implementirati iterator, stoga cu se sluziti indeksima
    //i kretati kroz vector tokena
    int currentIndex; //nisam htio koristiti Value currentIndex
    Token currentToken;
    std::vector<Token> tokens;
    std::vector<std::string> stringTokens;
    std::string mText;
    std::stack<Value> valueStack;

    // Daje sljedeći token sadržan u izrazu
    // (simbol operacije ili cijeli broj)
    Token getToken();
    void prepareTokens();
    //evaluira operatore
    Value evaluateOp(Value op, Value first, Value second);
};

// NAPOMENA: Nije nužno koristiti unutarnju klasu  Expression::Token
//           ukoliko imate bolji način, no unutarnje klase su ovdje vrlo
//           prirodne.

#endif // EVALUATE_POSTFIX_H
