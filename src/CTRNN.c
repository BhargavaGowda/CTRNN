#include "CTRNN.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXBIAS 5.0
#define MINTAU 1e-2
#define MAXWEIGHT 10.0
#define DELT 17e-3
#define MAXFILESTRLEN 100
#define WEIGHTMUTATE 0.1

void init_net_fc(net_t *my_net){

    srand(time(NULL));

    for(int i=0;i<my_net->num_neurons;i++){
        my_net->neurons[i].potential = 0.0;
        my_net->neurons[i].buffer=0.0;
        my_net->neurons[i].bias = ((double)rand()/RAND_MAX) *MAXBIAS*2 - MAXBIAS ;
        my_net->neurons[i].tau = ((double)rand()/RAND_MAX);
        if(my_net->neurons[i].tau<MINTAU){my_net->neurons[i].tau = MINTAU;}
    }

    for(int i=0;i<my_net->num_conns;i++){
        my_net->conns[i].from_id = i/my_net->num_neurons;
        my_net->conns[i].to_id = i%my_net->num_neurons;
        my_net->conns[i].conn_weight = ((double)rand()/RAND_MAX)*MAXWEIGHT*2 - MAXWEIGHT;
    }
    
    // printf("Initialized fully connected net with %d neurons and %d connections.\n",my_net->num_neurons,my_net->num_conns);
}

void step(net_t *network){
    for(int i=0;i<network->num_conns;i++){
        network->neurons[network->conns[i].to_id].buffer+= network->neurons[network->conns[i].from_id].potential * network->conns[i].conn_weight;
    }

    for(int i=0;i<network->num_neurons;i++){
        network->neurons[i].potential += DELT * network->neurons[i].tau * (ReLU(network->neurons[i].buffer+network->neurons[i].bias)-network->neurons[i].potential);
        network->neurons[i].buffer = 0.0;
    }

}

void free_net(net_t *my_net){
    free(my_net->neurons);
    free(my_net->conns);
    return;
}

double ReLU(double inp){
    if (inp<0.0){
        return 0.0;
    }else if(inp>1.0){
        return 1.0;
    }else{
        return inp;
    }
}

int write_to_file(net_t *my_net, char *filename){
    FILE *fptr;
    if(strlen(filename)>MAXFILESTRLEN){
        printf("filename too long.");
        return 1;
    }

    char infoStr[MAXFILESTRLEN+5+1];
    char neuronStr[MAXFILESTRLEN+8+1];
    char connsStr[MAXFILESTRLEN+12+1];

    strcpy(infoStr,filename);
    strcpy(neuronStr,filename);
    strcpy(connsStr,filename);
    
    strcat(infoStr,"_info");
    strcat(neuronStr,"_neurons");
    strcat(connsStr,"_connections");

    fptr = fopen(infoStr,"w");
    fprintf(fptr,"%d %d\n", my_net->num_neurons,my_net->num_conns);
    fclose(fptr);

    fptr = fopen(neuronStr,"w");
    for (int i=0;i<my_net->num_neurons;i++){
        fprintf(fptr,"%f %f %f\n",
            my_net->neurons[i].potential,
            my_net->neurons[i].bias,
            my_net->neurons[i].tau);
    }
    fclose(fptr);

    fptr = fopen(connsStr,"w");
    for (int i=0;i<my_net->num_conns;i++){
        fprintf(fptr,"%u %u %f\n",
            my_net->conns[i].from_id,
            my_net->conns[i].to_id,
            my_net->conns[i].conn_weight);
    }
    fclose(fptr);

    return 0;

}

void mutate(net_t *my_net){

    for (int i =0;i<my_net->num_conns;i++){
        my_net->conns[i].conn_weight += ((double)rand()/RAND_MAX)*WEIGHTMUTATE*2 - WEIGHTMUTATE;
    }
    for (int i =0;i<my_net->num_neurons;i++){
        my_net->neurons[i].bias += ((double)rand()/RAND_MAX)*WEIGHTMUTATE*2 - WEIGHTMUTATE;
    }
}

net_t read_from_file(char *net_name){
    FILE *fptr;
    if(strlen(net_name)>MAXFILESTRLEN){
        printf("filename too long.");
    }

    char infoStr[MAXFILESTRLEN+5+1];
    char neuronStr[MAXFILESTRLEN+8+1];
    char connsStr[MAXFILESTRLEN+12+1];

    strcpy(infoStr,net_name);
    strcpy(neuronStr,net_name);
    strcpy(connsStr,net_name);
    
    strcat(infoStr,"_info");
    strcat(neuronStr,"_neurons");
    strcat(connsStr,"_connections");

    fptr = fopen(infoStr,"r");
    int net_size;
    int net_conns_num;
    fscanf(fptr,"%d %d\n",&net_size,&net_conns_num);
    fclose(fptr);
    net_t my_net = {malloc(net_size*sizeof(neuron_t)),
        net_size,
        malloc(net_conns_num*sizeof(connection_t)),
        net_conns_num};

    fptr = fopen(neuronStr,"r");
    for(int i =0;i<net_size;i++){
        fscanf(fptr,"%lf %lf %lf\n",
            &my_net.neurons[i].potential,
            &my_net.neurons[i].bias,
            &my_net.neurons[i].tau);
    }
    fclose(fptr);

    fptr = fopen(connsStr,"r");
    for(int i =0;i<net_conns_num;i++){
        fscanf(fptr,"%d %d %lf\n",
            &my_net.conns[i].from_id,
            &my_net.conns[i].to_id,
            &my_net.conns[i].conn_weight);
    }
    fclose(fptr);
    
    return my_net;
    
}