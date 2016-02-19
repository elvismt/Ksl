#include <iostream>
using namespace std;

#include <Ksl/Array.h>
using namespace Ksl;

#include <QHash>
#include <QVariant>


int main()
{
    QTextStream out(stdout);
    
    QHash<QString,QVariant> dict;
    dict["name"] = "Elvis";
    dict["age"] = 27;
    dict["height"] = 1.86;
    
    out << dict["name"].toString() << endl;
    out << dict["age"].toInt() << endl;
    out << dict["height"].toDouble() << endl;
    return 0;
}
