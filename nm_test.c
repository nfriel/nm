#define NM_IMPLEMENTATION
#include "nm.h"

NM_VTYPE div_by_two(NM_VTYPE v)
{
    return v / 2.0;
}

int main(void)
{
    /* allocate memory for 2 20x3 matrices m and n */
    NM_Matrix m = nm_m(20, 3);
    NM_Matrix n = nm_m(20, 3);

    nm_mset_default(m, NM_MATRIX_ZERO);
    nm_mset_default(n, NM_MATRIX_INC_ONE);
    nm_mprint(m, NM_VARNAME(m));
    nm_mprint(n, NM_VARNAME(n));

    /* apply function to each element of matrix n and store result in matrix m */
    nm_mapply(n, m, div_by_two);
    nm_mprint(m, NM_VARNAME(m));

    /* free memory associated with m and n */
    nm_mfree(m);
    nm_mfree(n);
    return 0;
}
