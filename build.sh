echo "Building"
gcc src/Pong.c -o build/Pong -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g 

