#include <Ksl/Array.h>
using namespace Ksl;

#include <iostream>
using namespace std;


int main()
{
    auto A = randmat(4, 4);
    auto v = col(A, 1);

    cout << A << endl;
    cout << v << endl;

    return 0;
}
