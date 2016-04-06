#include <Ksl/Array.h>
using namespace Ksl;


int main() {
    
    qout << "cols: \n" <<column_stack({ones(4), zeros(4), ones(4)});
    qout << "rows: \n" <<row_stack({ones(4), zeros(4), ones(4)});

    return 0;
}
