#include <Ksl/Array.h>
using namespace Ksl;

#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    Array<1> v;

    for (double x=1.0; x<60.0; x+=3.0)
        v.append(x);

    cout << v << endl;

    auto A = column_stack({ zeros(5), ones(5), randspace(5)});

    cout << A << endl;

    return 0;
}
