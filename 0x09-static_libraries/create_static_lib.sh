#!/bin/bash

# Compile all .c files.
gcc -Wall -pedantic -Werror -Wextra -c *.c

# Create the static library.
ar -rc liball.a *.o

# Index the library.
ranlib liball.a

