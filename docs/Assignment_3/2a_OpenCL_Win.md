# OpenCL in Windows

Make sure your graphics drivers are up to date.

Use pathnames without special characters, spaces for all paths.

Install MSYS2 from https://github.com/msys2/msys2-installer/releases/download/2025-08-30/msys2-x86_64-20250830.exe

Run MSYS2. It takes a few seconds to open.

In the Msys command line, insert the following.

pacman -Syu
and then
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-gcd

By default, the toolchain is installed to C:\msys64\ucrt64. 

which g++ to confirm the source.

Add the toolchain to PATH:
Open Start → Environment Variables → Edit system environment variables → Environment Variables → Path → Edit.
Add the bin folder of your UCRT64 installation, e.g.:

C:\msys64\ucrt64\bin and C:\msys64\ucrt64\include. Click OK to save changes.

Verify Installation:

Open Command Prompt (in start menu, type cmd) and run:

gcc --version
g++ --version
If installed correctly, it should display version information. Only new command windows can see the updated path, so if it was already open, close and reopen.


Download and Unzip OpenCLSDK.

https://github.com/KhronosGroup/OpenCL-SDK/releases/download/v2025.07.23/OpenCL-SDK-v2025.07.23-Win-x64.zip

C:\OpenCLSDK such that C:\OpenCLSDK\bin, etc. If you choose another path, edit the VS Code config files accordingly.

C:\OpenCLSDK
├── include   (contains CL/cl.h etc.)
├── lib       (contains OpenCL.lib)
└── bin       (contains OpenCL.dll if you built it, but Intel’s driver already provides one)


Install Visual Studio Code.

Install the following extensions
C/C++
C/C++ Extension Pack
CMake Tools (optional)
OpenCL

Open a workspace. 
Create a .vscode folder and put the following files inside. Make appropriate changes to the paths in the .json files as necessary.

Include the files (not inside the .vscode folder).
main.c and kernel.cl

Ctrl+Shift+B to build it
F5 to run it with debugging
To run normally, go to the terminal of visual studio, ensure that you are in the folder with the main.exe (cd to there if need be), and execute .\main.exe.