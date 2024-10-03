#include <stdio.h>

int thinking(int health){ 
    return health -1;

}
int eating(int health){ 
    return health+1;
}
main()
{
    
    int philos[5][4];
    int fork[5][3];
    int i = 0;
    while(i<5) {
        philos[i][0] = i; //name
        philos[i][1] = 100; //random number health
        philos[i][2] = 0; //acces to fork 1
        philos[i][3] = 0; //access to fork 2
        fork[i][0]=i; //fork name
        if (i!=4) 
            fork[i][1]= i+1; //who can acces ffork 1
        
        else 
            fork[i][1] = 0;

        fork[i][2] = 0; //who can access fork two
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
    
    //run loop while all philosphers are alive
    while(philos[0][1]>=0) {
        //if both forks that philosopher can access are available and health less than 20 then access fork 
        if(philos[0][1]<=20 && fork[0][2]==0 && fork[1][2]==0) {
            fork[0][2] = 1;
            fork[1][2] = 1;
            philos[0][2] = 1;
            philos[0][3] = 1;
        }
        //if philospher is in possesion of both forks, eat
        while ((philos[0][2]== 1 && philos[0][3]==1) ) {   
            int h =  philos[0][1];
            philos[0][1] = eating(h);
        }
        //if philsopher isnt in possesion of both forks, and health is > tgab 0
        while ((philos[0][2]== 0 || philos[0][3] == 0) && philos[0][1]>=0){
            int h =  philos[0][1];
            philos[0][1] = thinking(h);
        
        }
    }
    printf("Philosopher Number %d died! \n", philos[0][0]);
    return 0;
}
