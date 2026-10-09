#include "CTRNN.h"
#define NETSIZE 3

int main(){
    // net_t my_net = {malloc(NETSIZE*sizeof(neuron_t)),
    //     NETSIZE,
    //     malloc(NETSIZE*NETSIZE*sizeof(connection_t)),
    //     NETSIZE*NETSIZE};
    // init_net_fc(&my_net);

    net_t my_net = read_from_file("model1");

    

    for (int i=0;i<10000;i++){
        for(int n=0;n<NETSIZE;n++){
            printf(" %f",my_net.neurons[n].potential);
        }
        printf("\n");
        for(int s=0;s<10;s++){
            step(&my_net);
        }
        
    }
    write_to_file(&my_net,"model1");
}