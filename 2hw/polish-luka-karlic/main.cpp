#include <iostream>
#include "evaluate_postfix.h"
#include "evaluate_prefix.h"

using namespace std;

void testiraj(int ulaz, int izlaz, int broj)
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

int main()
{
    // VAŠI testovi dolaze ovdje. Barem 3 test za prefix i postfix formu.
    //Expression expr(" 3 12 11 - ^ ~ 4 1 + 7 * - 9 3 2 1 - ^ * +  ");
    //expr.printAllTokens();
    string expr = "5 2*4+2 4^-";
    IPExpression exprIP(expr);
    //expr3.printAllTokens();
    testiraj(exprIP.evaluate(), -2, 1);

    expr = "2 5^  4 /8 -4     250 * 8/+";
    exprIP = IPExpression(expr);
    //exprIP.printAllTokens();
    testiraj(exprIP.evaluate(), 125, 2);

    expr = "     1 4  7 8 2/ 4*+++";
    exprIP = IPExpression(expr);
    //exprIP.printAllTokens();
    testiraj(exprIP.evaluate(), 28, 3);

    expr = "-+/*1 12 4 5 8"; //0
    Expression exp(expr);
    //exp.printAllTokens();
    testiraj(exp.evaluate(), 0, 4);

    expr = "+/-*5 5 4 7 3"; //6
    exp = Expression(expr);
    //exp.printAllTokens();
    testiraj(exp.evaluate(), 6, 5);

    expr = "+++1  4 7*/8 2 4"; //
    exp = Expression(expr);
    //exp.printAllTokens();
    testiraj(exp.evaluate(), 28, 6);

    expr = "+5";
    exprIP = IPExpression(expr);
    exp = Expression(expr);
    //exprIP.printAllTokens();
    //exp.evaluate(); //treba biti run time error
    //exprIP.evaluate(); //treba biti run time error

    return 0;
}