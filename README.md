#HARP Architecure Emulator
This a prject for emulating harp ISA.
Currently divergence is not supported.

##Make
'make'

##How to execute
Currently the executable takes binary file and output file. The output will be saved in a file of `OUTPUT_TO_FILE` is defined in `globals.h`.

To execute:

`./harp_emulator [binary_file] [output_file]`

##Clean
Simply in root do make clean.

##To Debug
Different Debug flags at globals.h

###Debug with harptool
- git clone https://github.com/cdkersey/harptool
- uncomment the debug build flags in src/Makefile 
- run make in src/
- ./harptool -E -b -a 4w8/8/8/8 -c bubble.bin
- Alternatively you can get just the dynamic pc and instruction by printing to the console the variables at core.cpp:135

##Refrences
You can learn more about HARP in https://github.com/cdkersey/harptool
