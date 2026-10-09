@ECHO OFF

gcc -Wall -c "src/CTRNN.c" -o "src/CTRNN.o" -I"./include/"
ar rcs "lib/libCTRNN.a" "src/CTRNN.o" 
gcc -Wall -o runner runner.c -I"./include/" -L"./lib/" -lCTRNN 