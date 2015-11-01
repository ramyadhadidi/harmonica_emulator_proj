#HARP Architecure Emulator
This a prject for emulating harp ISA.
Currently divergence is not supported.

##Make
Simply in root do make.

##How to execute
Currently the executable takes binary file and output file. The output will be saved in a file of `OUTPUT_TO_FILE` is defined in `globals.h`.

To execute:

`./harp_emulator [binary_file] [output_file]`

##Clean
Simply in root do make clean.

##To Debug
Define Debug flag. Also harptool can be used with `harptool -E -a 4w8/8/1/1 -c ../../harp-programs/bin/bubble.bin -b`

##Refrences
You can learn more about HARP in https://github.com/cdkersey/harptool
