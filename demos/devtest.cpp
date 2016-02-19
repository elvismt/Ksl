#include <Ksl/Array.h>
using namespace Ksl;

#include <iostream>
using namespace std;

int main()
{
    QList<double> cont;
    cont << 1 << 3 << 7;
    cont << 1 << 3 << 7;
    cont << 1 << 3 << 7;
    cont << 1 << 3 << 7;

    auto a = make2D(4, 3, cont);
    cout << a << endl;
    cout << mean(a) << endl;

    return 0;
}
