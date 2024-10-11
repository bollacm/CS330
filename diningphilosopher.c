#include <stdio.h>



void eat(int philosopher[5][4], int forks[5][3]){
    for (int i = 0; i < 5; i++){
        if ((philosopher[i][1] <= 20) &&
            (forks[i][0] == 0) && (forks[i+1][0] == 0)){
            philosopher[i][1] += 10;
            printf("Philosopher %d is eating\n", i);
        }
        else if (philosopher[5][1] && 
            forks[4] == 0 && forks[1] == 0){
            philosopher[5][1] += 10;
            printf("Philosopher 5 is eating\n");
        }
        else {
            printf("Philosopher %d is thinking\n", i);
        }
    }
}

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