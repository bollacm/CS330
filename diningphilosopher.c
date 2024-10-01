#include <stdio.h>

main()
{
    
    int philos[5][4];
    int fork[5][3];
    int i = 0;
    while(i<5) {
        philos[i][0] = i;
        philos[i][1] = 100; //random number
        philos[i][2] = 0;
        philos[i][3] = 0;
        fork[i][0]=i;
        if (i!=4) 
            fork[i][1]= i;
        
        else 
            fork[i][1] = 1;

        fork[i][2] = 0;
        i++;
    }
    // Print all elements of philos array
    printf("philos array:\n");
    for (i = 0; i < 5; i++) {
        printf("philos[%d]: %d %d %d %d\n", i, philos[i][0], philos[i][1], philos[i][2], philos[i][3]);
    }

    // Print all elements of fork array
    printf("fork array:\n");
    for (i = 0; i < 5; i++) {
        printf("fork[%d]: %d %d %d\n", i, fork[i][0], fork[i][1], fork[i][2]);
    }
    printf("hello, world\n");
    
}