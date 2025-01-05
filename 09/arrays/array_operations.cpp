#include "array_operations.hh"

int greatest_v1(int *itemptr, int size) {

    int the_greatest = *itemptr;
    int counter = 1;

    while(counter != size){
        ++ itemptr;
        int current = *itemptr;

        if (the_greatest < current) {
            the_greatest = current;
        }
        ++ counter;

    }
    return the_greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int the_greatest = *itemptr;

    for(int* position = itemptr; position < endptr; ++position){
        int current = *position;
        if (the_greatest < current) {
            the_greatest = current;
        }

    }
    return the_greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr != endptr) {
        *targetptr = *itemptr;
        ++itemptr;
        ++targetptr;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    while (leftptr < rightptr) {
        --rightptr;
        int current = *leftptr;
        *leftptr = *rightptr;
        *rightptr = current;
        ++ leftptr;
    }
}
