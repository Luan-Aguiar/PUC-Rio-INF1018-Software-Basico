####################################
# CS:APP Buffer Lab
# Makefile that builds a buffer bomb
####################################

####################################### 
# No need to change anything below here
#######################################
CC = gcc
CFLAGS = -Wall -O0

# The buffer bomb is always a 32-bit binary
# We give it an address where it should locate the runtime stack

all: bufbomb hex2raw bufbomb.diss

# Build the buffer bomb
bufbomb: bufbomb.c buf.c 
	$(CC) $(CFLAGS) -fno-stack-protector -m32 -o bufbomb bufbomb.c buf.c 

# Build hex2raw utility
hex2raw: hex2raw.c
	$(CC) $(CFLAGS) -o hex2raw hex2raw.c

# Handy file for examining machine code
bufbomb.diss: bufbomb
	objdump -d bufbomb > bufbomb.32d

# Use this when you want to recompile
clean:
	-rm -f *.o bufbomb hex2raw *~

