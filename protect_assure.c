#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"


// assurance test to try mprotect and munprotect
// guidance from MIT documentation used

int
main(int argc, char *argv[])
{
    printf(1, "-- assurance test start --");
    char *start = sbrk(0);
    sbrk(PGSIZE);
    *start=100;
    mprotect(start, 1);
    int child=fork();

    if(child==0){
        printf(1, "protecting - the value is = %d\n",*start);
        munprotect(start, 1) ;
        *start=5;
        printf(1, "un-protecting - the value is = %d\n",*start);
        exit();
    }

    else if(child>0){
        wait();
        printf(1, "\nbeginning trap assurance test\n");
        *start=5;
        printf(1, "\nassurance failure\n");
        exit();
    }
    exit();
}