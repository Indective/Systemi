#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    for(int i = 0; i < (sizeof(argv) / sizeof(argv[0])); i++)
    {
        printf("\n %s", argv[i]);
    }

    return 0;
}
