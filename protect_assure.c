#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
int
main(int argc, char *argv[])
{
    char *start = sbrk(0);
    sbrk(PGSIZE);
    *start=100;
    mprotect(start, 1) ;
    int child=fork();
    if(child==0){
        printf(1, "protected the value = %d\n",*start);
        munprotect(start, 1) ;
        *start=5;
        printf(1, "now unprotecting. the value is = %d\n",*start);
        exit();
    }
    else if(child>0){
        wait();
        printf(1, "\nbeginning trap\n");
        *start=5;
        printf(1, "\nif printed - failure\n");
        exit();
    }
    exit();
}