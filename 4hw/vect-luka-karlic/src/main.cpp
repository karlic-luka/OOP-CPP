#include "vect.h"
#include <assert.h>

using namespace std;

int main()
{
    
    cout << "hello" << endl;
    Vect<double> vec;
    assert(vec.capacity() == 0);
    assert(vec.size() == 0);
    assert(vec.getMdata() == nullptr);
    assert(vec.getMfirst() == nullptr);
    assert(vec.getMend() == nullptr);

    Vect<int> vec1(10, 5);
    assert(vec1.capacity() == 10);
    assert(vec1.size() == 10);
    assert(*(vec1.getMdata()) == 5);
    assert(vec1[9] == 5);

    Vect<pair<int, char>> par;
    assert(par.capacity() == 0);
    assert(par.size() == 0);
    assert(par.getMdata() == nullptr);
    assert(par.getMfirst() == nullptr);
    assert(par.getMend() == nullptr);

    Vect<pair<int, char>> par2(5);
    assert(par2.size() == 5);
    assert(par2.capacity() == 5);
    assert(par2[0].first == 0);
    assert(par2[4].first == 0);

    //CCtor
    Vect<int> cctor(10, 3);
    Vect<int> cctor2(cctor);
    assert(cctor.size() == cctor2.size());
    assert(cctor.capacity() == cctor2.capacity());
    for (size_t i = 0; i < cctor.size(); ++i)
    {
        assert(cctor[i] == cctor2[i]);
    }
    assert(cctor.getMdata() != cctor2.getMdata());
    //cout << cctor.getMdata() << endl;

    //COP
    Vect<int> cop;
    Vect<int> cop2(10, 3);
    cop = cop2;
    assert(cop.size() == cop2.size());
    assert(cop.capacity() == cop2.capacity());
    for (size_t i = 0; i < cctor.size(); ++i)
        assert(cop[i] == cop2[i]);

    //MCtor
    Vect<int> mctor(10, 5);
    int *data = mctor.getMdata();
    Vect<int> mctor2(std::move(mctor));
    assert(mctor.size() == 0);
    assert(mctor.getMdata() == nullptr);
    assert(mctor.getMend() == nullptr);
    assert(mctor.getMfirst() == nullptr);
    assert(mctor2.getMdata() == data);

    //MOP
    Vect<int> mop(2, 2);
    int *dataMop = mop.getMdata();
    Vect<int> mop2;
    mop2 = std::move(mop);
    assert(mop.size() == 0);
    assert(mop.getMdata() == nullptr);
    assert(mop.getMend() == nullptr);
    assert(mop.getMfirst() == nullptr);
    assert(mop2.getMdata() == dataMop);

    //self assign
    Vect<int> sa(2, 2);
    int *saData = sa.getMdata();
    sa = std::move(sa);
    assert(sa.getMdata() == saData);
    
    Vect<int> pushanje(2, 5);
    pushanje.push_back(4);
    assert(pushanje.size() == 3);
    assert(pushanje.capacity() == 4);
    assert(pushanje[0] == 5 && pushanje[1] == 5 && pushanje[2] == 4);

    cout << pushanje << endl;
    
    Vect<int> prazan;
    assert(prazan.capacity() == 0);
    prazan.push_back(1);
    assert(prazan.capacity() == 1);

    Vect<int> prvi(2, 5);
    Vect<int> drugi(2, 10);
    Vect<int> treci = prvi + drugi;
    assert(treci[0] == 15);
    assert(treci[1] == 15);
    prvi += drugi;
    assert(prvi[0] == 15);
    assert(prvi[1] == 15);

    prvi -= drugi;
    assert(prvi[0] == 5);
    assert(prvi[1] == 5);

    prvi *= 2;
    assert(prvi[0] == 10);
    assert(prvi[1] == 10);

    treci = drugi - prvi;
    assert(treci[0] == 0);
    assert(treci[1] == 0);

    assert(abs((prvi.two_norm() - (2 * sqrt(50))) < 1e-5));
    cout << "Uspjeh!" << endl;
    
    return 0;
}
