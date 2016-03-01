#include "simplex.h"
bool Simplex::function_is_undefined()
{
    int i;
    for (i = 0; i < num_l; i++)
        if (bv[i][1] < 0) {
            return false;
        }
    return true;
}





