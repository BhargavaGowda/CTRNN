@ECHO OFF

gcc -Wall -c "src/CTRNN.c" -o "src/CTRNN.o" -I"./include/"
ar rcs "lib/libCTRNN.a" "src/CTRNN.o" 
gcc -Wall -o main main.c -I"./include/" -L"./lib/" -lraylib -lCTRNN -lopengl32 -lgdi32 -lwinmm
