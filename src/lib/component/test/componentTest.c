
#include <stdio.h>
#include "../component.h"

int main(int argc, char *argv[])
{
    int result = 0;
    printf( "Hello World\n");
    result = e_resistance(5.0, NULL);
    printf("%d", result);
    return 0;
}
