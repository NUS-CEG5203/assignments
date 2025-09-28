# OpenCL in Linux

It is generally easier to run OpenCL in a Linux distribution. A rough list of steps is as follows (there could be minor changes/omissions).

Installing OpenCL and Build Tools

sudo apt update (refresh package list). You will be prompted for your Ubuntu password.

sudo apt upgrade (update packages). If it prompts you, enter y.

sudo apt install build-essential clinfo intel-opencl-icd ocl-icd-opencl-dev gdb (assuming Intel GPU. For Nvidia / AMD, appropriate drivers may need to be installed.). Depending on the system configuration, other dependencies may also need to be installed. sudo apt -f install can sometimes help install these additional dependencies.

See if clinfo lists the platforms and devices. If it lists the devices, you are close!

Before building your program for the first time, it may be a good idea to refresh the linker cache via sudo ldconfig.

Create a .c file with the example program covered in the lecture. You can use any text editor for this purpose.

Assuming your filename is vadd.c, build the program via gcc vadd.c -o vadd -lOpenCL -lm. 

You can now run it by entering the command ./vadd and it should print 1.0 a second or two later. If it works, you are good to go!

Basic instructions for VS Code over eclipse is given below, detailed instructions are not provided.

Select gcc (not v9)

In tasks.json, add the following (note: add a , before "-lOpenCL", but not after "-lm" ).

          ,
"-lOpenCL",
"-lm"
],

