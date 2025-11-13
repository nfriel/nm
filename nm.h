/*
 * NM matrix/vector header-only math library
 * Written in C89
 *
 * When using in your project, make sure to define NM_IMPLEMENTATION
 * for example:
 * #define NM_IMPLEMENTATION
 * #include "nm.h"
 *
 * To use doubles instead of floats, define NM_VTYPE_DOUBLE
 * To use a different memory allocation function, define NM_MALLOC (your chosen function)
*/

#ifndef NM_H_
#define NM_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NM_VTYPE_DOUBLE
#define NM_VTYPE float
#define NM_SQRT sqrtf
#else
#define NM_VTYPE double
#define NM_SQRT sqrt
#endif

#ifndef NM_MALLOC
#define NM_MALLOC malloc
#endif

#define NM_VSIZE sizeof(NM_VTYPE)
#define NM_MATAT(m, row, col) m.data[row * m.cols + col]

#define NM_VARNAME(v) #v

typedef struct {
    NM_VTYPE x;
    NM_VTYPE y;
} NM_Vector2;

typedef struct {
    unsigned int rows;
    unsigned int cols;
    NM_VTYPE *data;
} NM_Matrix;

typedef enum {
    NM_MATRIX_ZERO,
    NM_MATRIX_INC_ONE,
} NM_MATRIX_SET_TYPE;

/* Vector operations */
void nm_v2print(NM_Vector2 a);
NM_VTYPE nm_v2mag(NM_Vector2 a);
NM_Vector2 nm_v2scale(NM_Vector2 a, NM_VTYPE scale);
NM_Vector2 nm_v2norm(NM_Vector2 a);
NM_Vector2 nm_v2add(NM_Vector2 a, NM_Vector2 b);
NM_Vector2 nm_v2sub(NM_Vector2 a, NM_Vector2 b);

/* Matrix operations */
void nm_mprint(NM_Matrix a, const char *name);
NM_Matrix nm_m(unsigned int rows, unsigned int cols);
void nm_mfree(NM_Matrix a);
void nm_mset(NM_Matrix a, unsigned int row, unsigned int col, NM_VTYPE v);
void nm_mset_default(NM_Matrix a, NM_MATRIX_SET_TYPE t);
void nm_mscale(NM_Matrix a, NM_Matrix b, NM_VTYPE scale);
void nm_apply(NM_Matrix a, NM_Matrix b, NM_VTYPE (*func)(NM_VTYPE));

#endif /* NM_H_ */

#ifdef NM_IMPLEMENTATION

/* Vector operations */
void nm_v2print(NM_Vector2 a)
{
    printf("[%.3f, %.3f]\n", a.x, a.y);
}

NM_VTYPE nm_v2mag(NM_Vector2 a)
{
    return NM_SQRT(a.x * a.x + a.y * a.y); 
}

NM_Vector2 nm_v2norm(NM_Vector2 a)
{
    NM_VTYPE mag = nm_v2mag(a);
    NM_Vector2 v = {
        a.x / mag,
        a.y / mag,
    };
    return v;
}

NM_Vector2 nm_v2scale(NM_Vector2 a, NM_VTYPE scale)
{
    NM_Vector2 v = {
        a.x * scale,
        a.y * scale,
    };
    return v;
}

NM_Vector2 nm_v2add(NM_Vector2 a, NM_Vector2 b)
{
    NM_Vector2 v = {
        a.x + b.x,
        a.y + b.y,
    };
    return v;
}

NM_Vector2 nm_v2sub(NM_Vector2 a, NM_Vector2 b)
{
    NM_Vector2 v = {
        a.x - b.x,
        a.y - b.y,
    };
    return v;
}

/* Matrix operations */
void nm_mprint(NM_Matrix a, const char *name)
{
    printf("NM_Matrix %ix%i %s:\n", a.rows, a.cols, name);
    for (int i = 0; i < (int) a.rows; i++) {
        printf("| ");
        for (int j = 0; j < (int) a.cols; j++) {
            printf("%06.2f ", NM_MATAT(a, i, j));
        }
        printf("|\n");
    }
    putchar('\n');

}

NM_Matrix nm_m(unsigned int rows, unsigned int cols)
{
    /* Create new matrix and allocate memory */
    NM_Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = (NM_VTYPE*) NM_MALLOC(NM_VSIZE * rows * cols);
    return m;
}

void nm_mfree(NM_Matrix a)
{
    free(a.data);
}

void nm_mset(NM_Matrix a, unsigned int row, unsigned int col, NM_VTYPE v)
{
    NM_MATAT(a, row, col) = v;
}

void nm_mset_default(NM_Matrix a, NM_MATRIX_SET_TYPE t)
{
    switch (t) {
    case NM_MATRIX_INC_ONE:
        for (int i = 0; i < (int) (a.cols * a.rows); i++) {
            a.data[i] = (NM_VTYPE) i;
        }
        break;
    case NM_MATRIX_ZERO:
        for (int i = 0; i < (int) (a.cols * a.rows); i++) {
            a.data[i] = (NM_VTYPE) 0;
        }
        break;
    default:
        break;
    }
}

void nm_mscale(NM_Matrix a, NM_Matrix b, NM_VTYPE scale)
{
    for (int i = 0; i < (int) (a.rows * a.cols); i++) {
        b.data[i] = a.data[i] * scale;
    }
}

void nm_mapply(NM_Matrix a, NM_Matrix b, NM_VTYPE (*func)(NM_VTYPE))
{
    /* Apply func to each element of matrix a and store result in matrix b */
    for (int i = 0; i < (int) (a.rows * a.cols); i++) {
        b.data[i] = func(a.data[i]);
    }
}

#endif /* NM_IMPLEMENTATION */
