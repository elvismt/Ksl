#include <Ksl/Array.h>
using namespace Ksl;

#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    auto A = column_stack({ zeros(5), ones(5), randspace(5)});
    qDebug() << A;

    return 0;
}
