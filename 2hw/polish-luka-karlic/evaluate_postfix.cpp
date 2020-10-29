// Ovdje dolazi vaš kod za IPExpression klasu dolazi ovdje.
// Ovdje dolazi vaš kod za Expression klasu dolazi ovdje.
using namespace std;
#include "evaluate_postfix.h"
#include "evaluate_prefix.h"

IPExpression::IPExpression(string text) : mText(text), currentIndex(0)
{
    stringTokens = tokenize(spacedExpression(mText));
    prepareTokens();
}

void IPExpression::prepareTokens()
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
    Token endToken;
    endToken.setType(TokenType::endToken);
    endToken.setValue(-100);
    endToken.setSymbol('E');
    tokens.push_back(endToken);
}
IPExpression::Value IPExpression::evaluateOp(Value op, Value first, Value second)
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
//ovo bi trebalo stimati
IPExpression::Value IPExpression::evaluate()
{
    while (true)
    {
        Token t = getToken();
        if (t.getType() == unaryOp)
        {
            if (valueStack.empty())
                throw runtime_error("Stog je prazan, a ne bi trebao biti. Krivi unos!");
            Value operand = valueStack.top();
            valueStack.pop();
            valueStack.push(evaluateOp(t.getValue(), operand, 0));
        }
        else if (t.getType() == binaryOp)
        {
            if (valueStack.size() < 2)
                throw runtime_error("Na stogu moraju biti barem 2 elementa! Pogresan unos");
            Value second = valueStack.top();
            valueStack.pop();
            Value first = valueStack.top();
            valueStack.pop();
            valueStack.push(evaluateOp(t.getValue(), first, second));
        }
        else if (t.getType() == operand)
            valueStack.push(t.getValue());
        else
        {
            if (valueStack.size() != 1)
                throw runtime_error("Nije ispravan postfix oblik jer na stogu ima vise elemenata!");
            else
                return valueStack.top();
        }
    }
}
IPExpression::Token IPExpression::getToken()
{
    currentToken = tokens.at(currentIndex++);
    return currentToken;
}

/*void IPExpression::printAllTokens()
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
}
*/