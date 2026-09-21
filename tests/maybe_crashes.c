#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

int main() {
    
    srand(time(NULL));
    
    int min = 1;
    int max = 10;
    int random = (rand() % (max - min + 1)) + min;

    printf("%d", random);

    if(random = 5)
    {
        abort();
    }

    return 0;
}