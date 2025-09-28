# OpenCL Configuration

It is generally easier to run OpenCL in a Linux distribution. Instructions for Windows are also provided, but expect some rough edges.

Make sure your graphics drivers are up-to-date.

Use path names without special characters or spaces for all paths.

## Installing Build Tools and OpenCL

=== "Windows"
  *Install MSYS2*: Install MSYS2 from https://github.com/msys2/msys2-installer/releases/download/2025-08-30/msys2-x86_64-20250830.exe. This provides a minimal Linux-like setup for Windows.

  Run MSYS2. It takes a few seconds to open.

  *Install the compiler toolchaing*: Via the MSYS2 command line, run the following.

  `pacman -Syu` to update the package manager.
  and then
  `pacman -S mingw-w64-ucrt-x86_64-gcc` to install the GCC compiler
  `pacman -S mingw-w64-ucrt-x86_64-gcd` to install the GNU debugger.

  By default, the toolchain is installed to C:\msys64\ucrt64. If you want to know the location, you can find out by typing `which g++`.

  *Add the toolchain to Windows PATH*: Win+S → Environment Variables → Edit system environment variables → Environment Variables → Path → Edit.
  Add the bin folder of your UCRT64 installation, e.g.: `C:\msys64\ucrt64\bin and C:\msys64\ucrt64\include`. Click OK to save changes.

  *Verify Installation*: Open Command Prompt (in start menu, type cmd) and run: g++ --version
  If installed correctly, it should display version information. Only new command windows can see the updated path, so if it was already open, close and reopen.

  *Install OpenCL SDK*: Download and Unzip OpenCL SDK from https://github.com/KhronosGroup/OpenCL-SDK/releases/download/v2025.07.23/OpenCL-SDK-v2025.07.23-Win-x64.zip (a newer release, if available, should be fine too).

  Unzip to C:\OpenCLSDK such that C:\OpenCLSDK\bin, etc. If you choose another path, modify command line build options and/or edit the VS Code config files accordingly.

  `C:\OpenCLSDK\\
  ├── include   (contains CL/cl.h etc.)\\
  ├── lib       (contains OpenCL.lib)\\
  └── bin       (contains OpenCL.dll`\\ if you built it, but Intel’s driver already provides one)


=== "Linux"
  `sudo apt update` (refresh package list). You will be prompted for your Ubuntu password.

  `sudo apt upgrade` (update packages). If it prompts you, enter y.

  `sudo apt install build-essential clinfo intel-opencl-icd ocl-icd-opencl-dev gdb` (assuming Intel GPU. For Nvidia / AMD, appropriate drivers may need to be installed). 
  
  Depending on the system configuration, other dependencies may also need to be installed. `sudo apt -f install` can sometimes help install these additional dependencies.

  Run `clinfo` from the terminal and see if lists platforms and devices. If it lists platforms and devices, you are close!

  Before building your program for the first time, it may be a good idea to refresh the linker cache via `sudo ldconfig`.


## Comiling and Running from Command Line

Create a .c file with the example program covered in the lecture (which can also be found here). You can use any text editor for this purpose.

Assuming your filename is main.c, build the program via `gcc main.c -o main.out -lOpenCL -lm`, after doing a `cd` to the folder/directory with the source file.

You can now run it by entering the command `/main.out` and it should print the result 2-10 later. If it works, you are good to go!

Running in Windows is less stable, there is a higher likelihood of the runtime compilation of the kernel failing. Just run again if that happens.

// To do: do the above for Windows.

## Using Visual Studio Code IDE

Install Visual Studio Code. This can be done in multiple different ways depending on the OS and package manager.

Install the following extensions

* C/C++
* C/C++ Extension Pack
* CMake Tools (optional)
* OpenCL (optional, allows syntax highlighting of .cl files, has a built-in clinfo tool, etc.)

You can use the following workspace depending on your OS.

Make appropriate changes to the paths in the .json files as necessary.

Ctrl+Shift+B to build the project.

F5 to run it with debugging.

To run normally, go to the terminal of VS Code, ensure that you are in the folder with the main.exe / main.out (`cd` to there if need be), and execute `.\main.exe` or `./main.out`.
