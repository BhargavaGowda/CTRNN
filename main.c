#include "CTRNN.h"
#include "raylib.h"
#define NETSIZE 100
#define TRAJLEN 10000

int main(){
    // net_t my_net = {malloc(NETSIZE*sizeof(neuron_t)),
    //     NETSIZE,
    //     malloc(NETSIZE*NETSIZE*sizeof(connection_t)),
    //     NETSIZE*NETSIZE};
    // init_net_fc(&my_net);

    net_t my_net = read_from_file("model");
    

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(800,800,"appWindow");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        if (IsKeyDown(KEY_RIGHT)){
            my_net.neurons[2].potential+=0.01;

        }else if (IsKeyDown(KEY_LEFT))
        {
            my_net.neurons[2].potential+=-0.01;
        }

        if (IsKeyDown(KEY_UP)){
            my_net.neurons[4].potential+=0.01;

        }else if (IsKeyDown(KEY_DOWN))
        {
            my_net.neurons[4].potential+=-0.01;
        }
        if (IsKeyPressed(KEY_SPACE)){
            free_net(&my_net);
            my_net = read_from_file("model");
            mutate(&my_net);
            printf("Mutated");
        }
        if (IsKeyPressed(KEY_LEFT_CONTROL)){
            write_to_file(&my_net,"model");
            printf("Saved");
        }
        
        step(&my_net);

        BeginDrawing();
        ClearBackground(BLACK);
        for(int i = 0;i<NETSIZE-1;i+=2){
            DrawCircle(600*my_net.neurons[i].potential+100, 600*my_net.neurons[i+1].potential+100,5.0,RED);

        }
        EndDrawing();
    }

    

    CloseWindow();
    free_net(&my_net);
    return 0;
}