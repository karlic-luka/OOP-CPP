// Ovdje dolazi vaš kod za Expression klasu dolazi ovdje.
using namespace std;
#include "evaluate_prefix.h"
#include <algorithm>
#include <math.h>

string remove(string str, char c)
{
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
    return str;
}

vector<string> tokenize(string const &str, char delimiter)
{
    vector<string> tokeni;
    stringstream ss(str);
    string current;

    while (getline(ss, current, delimiter))
    {
        current = remove(current, delimiter);
        if (current != "")
            tokeni.push_back(current);
    }
    return tokeni;
}
string spacedExpression(string expr)
{
    string spacedExpr;
    for (int i = 0; i < expr.size(); i++)
    {
        if (!isdigit(expr[i]))
            spacedExpr.push_back(expr[i]);
        else
        {
            while (isdigit(expr[i]) && i < expr.size())
            {
                spacedExpr.push_back(expr[i++]);
            }
            //moram vratiti jedan i ako sam izasao iz petlje radi prvog uvjeta
            i--;
        }
        spacedExpr.push_back(' ');
    }
    return spacedExpr;
}
Expression::Expression(string text) : mText(text), currentIndex(0)
{
    stringTokens = tokenize(spacedExpression(mText));
    prepareTokens();
}

void Expression::prepareTokens()
{
    for (string token : stringTokens)
    {
        Token currToken;
        //leksiram tako da prvo provjeravam koji je simbol
        if (token == "~")
        {
            currToken.setType(TokenType::unaryOp);
            currToken.setValue(0);
            currToken.setSymbol('~');
        }
        else if (token == "+")
        {
            currToken.setType(TokenType::binaryOp);
            currToken.setValue(1);
            currToken.setSymbol('+');
        }
        else if (token == "-")
        {
            currToken.setType(TokenType::binaryOp);
            currToken.setValue(2);
            currToken.setSymbol('-');
        }
        else if (token == "*")
        {
            currToken.setType(TokenType::binaryOp);
            currToken.setValue(3);
            currToken.setSymbol('*');
        }
        else if (token == "/")
        {
            currToken.setType(TokenType::binaryOp);
            currToken.setValue(4);
            currToken.setSymbol('/');
        }
        else if (token == "^")
        {
            currToken.setType(TokenType::binaryOp);
            currToken.setValue(5);
            currToken.setSymbol('^');
        }
        //inace je broj (moze biti i viseznamenkasti)
        else
        {
            currToken.setType(TokenType::operand);
            currToken.setValue(stoi(token));
            currToken.setSymbol('N');
        }
        tokens.push_back(currToken);
    }
}
Expression::Value Expression::evaluateOp(Value op, Value first, Value second)
{
    switch (op)
    {
    case 0:
        return -first;
    case 1:
        return first + second;
    case 2:
        return first - second;
    case 3:
        return first * second;
    case 4:
        if (second == 0)
            throw runtime_error("Dijeljenje s nulom nije dozvoljeno!");
        else
            return first / second;
    case 5:
        return pow(first, second);
    }
}

Expression::Value Expression::evaluate()
{
    Token t = this->getToken();

    if (t.getType() == unaryOp)
    {
        Value operand = evaluate();
        return evaluateOp(t.getValue(), operand, 1); //treci parametar je irelevantan u ovom slucaju
    }
    else if (t.getType() == binaryOp)
    {
        Value firstOperand = evaluate();
        Value secondOperand = evaluate();
        return evaluateOp(t.getValue(), firstOperand, secondOperand);
    }

    else if (t.getType() == operand)
    {
        return t.getValue();
    }
}

Expression::Token Expression::getToken()
{
    if (currentIndex >= tokens.size())
        throw runtime_error("Nepravilan prefix oblik!");
    currentToken = tokens.at(currentIndex++);
    return currentToken;
}

/*void Expression::printAllTokens()
{
    cout << "Broj elemenata: " << stringTokens.size() << endl;
    for_each(stringTokens.begin(), stringTokens.end(),
             [](const std::string &str) { cout << str << " "; });
    cout << endl;
    for (int i = 0; i < tokens.size(); i++)
    {
        cout << "(" << tokens.at(i).getType() << ", " << tokens.at(i).getSymbol() << ", "
             << tokens.at(i).getValue() << "), ";
    }
    cout << endl;
}*/
