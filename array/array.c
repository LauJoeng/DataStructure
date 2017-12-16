#include<stdio.h>
#include<stdlib.h>

typedef int datatype;
typedef struct
{
    datatype *base;
    int index[3];
    int c[3];
}arr;

int initarray(arr *A,int b1,int b2,int b3)
{
    int elements;
    if(b1<=0||b2<=0||b3<=0)
    {
        return 0;
    }
    A->index[0]=b1;
    A->index[1]=b2;
    A->index[3]=b3;
    elements = b1*b2*b3;
    A->base = (datatype*)malloc(elements*sizeof(datatype));
    if(!(A->base))
        return 0;
    A->c[0] = b2 * b3;
    A->c[1] = b3;
    A->c[2] = 1;
    return 1;
}

int value(arr A,int i1,int i2,int i3,datatype *x)
{
    int off;
    if(i1<0||i1>=A.index[0]||i2<0||i2>=A.index[1]||i3<0||i3>=A.index[2])
    {
        return 0;
    }
    off = i1*A.c[0] + i2.c[1] + i3*A.c[2];
    *x = *(A.base + off);
    return 1;
}
