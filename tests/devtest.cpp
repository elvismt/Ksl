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

    return 0;
}
