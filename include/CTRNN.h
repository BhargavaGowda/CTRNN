#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    double potential;
    double buffer;
    double bias;
    double tau;
} neuron_t;

typedef struct
{
    uint32_t from_id;
    uint32_t to_id;
    double conn_weight;
} connection_t;

typedef struct
{
    neuron_t *neurons;
    uint32_t num_neurons;
    connection_t *conns;
    uint32_t num_conns;
} net_t;

void init_net_fc(net_t *my_net);
void step(net_t *network);
void free_net(net_t *my_net);
double ReLU(double inp);
int write_to_file(net_t *my_net, char *filename);
net_t read_from_file(char *net_name);
void mutate(net_t *my_net);
