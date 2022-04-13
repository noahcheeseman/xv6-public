#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"


// note about git, I was commiting originally to Kell repo and had to port files to this
// that explains the lack of commits
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
        printf(1, "\n- protecting -\nvalue = %d\n",*start);
        munprotect(start, 1) ;
        *start=5;
        printf(1, "\n- un-protecting -\nvalue = %d\n",*start);
        exit();
    }

    else if(child>0){
        wait();
        printf(1, "\n- trap assurance test start -\n");
        *start=5;
        printf(1, "\nassurance failure\n");
        exit();
    }
    exit();
}