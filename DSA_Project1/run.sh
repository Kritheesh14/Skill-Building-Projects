echo "Compiling...";
gcc -o calculator main.c eval.c stack.c gui.c `pkg-config --cflags --libs gtk+-3.0` -lm ;
echo "Done, compiling, running executable...";
./calculator