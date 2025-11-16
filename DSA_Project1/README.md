# Install GTK (if not already installed)
brew install gtk+3

# Compile with GUI support
gcc -o calculator main.c eval.c stack.c gui.c `pkg-config --cflags --libs gtk+-3.0` -lm

# Run the program
./calculator