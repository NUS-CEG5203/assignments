# Pynq and OpenCL on Kria

!!! warning "Follow the Spirit"
    The instructions should be treated as a guideline rather than a very comprehensive manual. Figure out on your own how to solve issues, if any.

## Booting Linux

For this part, we will boot Ubuntu Linux on Kria board. AMD/Xilinx does not provide a ready-to-use image for Kria board yet. 
A zipped SD card image is provided [here - version 16_10_2025](https://www.dropbox.com/scl/fi/th7kynsmgxojzxmkh0fav/Ubuntu_Pynq_Kria_CEG5203_16_10_2025.img.zip?rlkey=q3ioj6el6vzrxj9gzw1d70p9x&st=pr2fa0ml&dl=0). The download password is mentioned in the Canvas announcements. Download and unzip the image (.img).

<span style="color: brown;">
The following changes were made to the image:

* Version 12_10_2025 : OpenCV downgraded to 4.10.0.84. 
* Version 16_10_2025 : Size of image shrunk to less than 14 GB, which should fit into all 16 GB SD cards.
</span>

It is the default Ubuntu 22.04 image modified with the following:

* Pynq installed. That requires numpy to be downgraded to 1.26.4. <span style="color: brown;">OpenCV should be downgraded to 4.10.0.84 for it to work with this version of numpy (not sure if it breaks any other package).</span>
* PoCL installed.
* Example programmes for [OpenCL](https://nus-ceg5203.github.io/assignments/Assignment_3/code_templates/OpenCLExample) and [Pynq](https://nus-ceg5203.github.io/assignments/Assignment_3/code_templates/PynqDMAExample) loaded.

Some familiarity with Linux commandline is handy from now on. Some useful commands are
`ls`, `pwd`, `clear`, `nano` (commandline text editor), `cp`, `mv`, `rm`, `cat`, `mkdir`, pressing tab will help with for autocomplete. Read up more about these.

Use the .img image and flash it to an SD card after plugging the SD card into your laptop’s card reader. The SD card should be at least 16 GB capacity. Do not just copy over; use an image writer application such as [Win32 Disk Imager](https://win32diskimager.org/) or [balena Etcher](https://etcher.balena.io/) or the ones bundled with Linux distributions (e.g., Disk Image Writer in Ubuntu - just right-click on the .img file in file explorer). The contents of the SD card will entirely be erased.

Put the SD card into the micro SD card slot.

Turn it on, and it will boot from SD Card to Ubuntu 22.04. There is a small chance it may not boot due to potential incompatibility between the board firmware and OS version. If this happens, perhaps it is a good idea to change the board to another one with a newer firmware.

If using serial port (minimal connections to the board, but less flexible):
Use a terminal program and connect to the appropriate COM/tty/serial port as you did in assignment 1, baud rate of 115200. You will see the various boot messages.

If using Windows on your laptop/PC, RealTerm can be used for this purpose, but it is not great to be used like a conventional high-level terminal, though it is great for low-level debugging. RealTerm shows all characters by default, including non-printable ones, which makes it look messy. In the display tab, change it to ANSI to make it operate like a normal terminal. Even then, it is not great for the purpose. It is suggested to use another terminal program such as [MobaXterm Home Editon](https://mobaxterm.mobatek.net/download.html).

Eventually, it will throw up a login prompt. Username is _ubuntu_ and password is the same as the one used for downloading the archive.

If you had not connected to the serial port before the boot is complete, press enter, and it will show the login prompt. 

An alternative to serial port if you have network connectivity. - SSH (MobaXterm on Windows and [Muon SSH](https://github.com/devlinx9/muon-ssh) / bash terminal in Linux) or terminal within Jupyter Lab at <your_ip_address\>:9090/lab - password to enter the web interface itself is _xilinx_. This has the advantage of not needing USB drive to copy programs/bitstream over.

Another alternative: If you have an HDMI/DisplayPort monitor, keyboard and mouse: You can connect and operate like a normal computer.

Every time before you power off, shut down the OS properly using `sudo shutdown -h now`. Wait until the LEDs next to the fan turns off before removing power.

First, try running the example programs following the sessions below.

## OpenCL on Kria

Let us start with an OpenCL on CPU (Cortex A53). The main.cpp file is the same as the one we used with OpenCL on PC/Laptop. Just ensure that the correct platform id and device type are used in the .cpp file. Execute the following.

`cd /home/ubuntu/OpenCLExample` to change to the folder with OpenCL example.

`g++ main.cpp -lOpenCL -o main.out` to compile main.cpp

`./main.out` to run it.

If you want to make minor edits to the .cpp file, you can do so using nano editor via the command `nano main.cpp`.

Make sure that the line containing `#define XCLBIN` is commented out, as uncommenting it will cause the system to crash. It was an attempt to use OpenCL host code with the FPGA (PL) accelerator, which is not working, likely due to version-related issues.

## Pynq on Kria

Pynq framework allows python code to interact with your custom coprocessor connected via AXI DMA (not AXI Stream FIFO).

The example program adds 4 numbers, invoking the coprocessor and prints the sum, sum+1, sum+2, sum+3 (the coprocessor created using the example HLS code from Assignment 2).  

Have a look at the .py code and understand the functionality. It is more or less the same as the C program used with AXI DMA, except that the bitstream is downloaded by the host python code, rather than before the host code is run (which was the case with Assignment 2). This also means a few seconds delay before the computation is started and results are printed.

Pynq requires the .hwh file with the same name as the .bit file, and in the same folder. This is already done for the example in the PynqDMAExample folder.

`sudo -s`

`source /etc/profile.d/pynq_venv.sh`

`cd /home/ubuntu/PynqDMAExample/`

`python3 PynqDMAExample.py`

To have a new .bit and .hwh, first have the .xsa ready. The .xsa can be unzipped using any tool that can deal with .zip (rename it to .zip if necessary). You will then find the .bit and the .hwh (<span style="color: brown;">Hthe one we need is the top level .hwh, usually named design_1.hwh; not those named design_1_axi_smc_*.hwh</span>) file. Rename the .hwh file to be the same as the .bit file.

If you have SSH /Jupyter lab access, you can copy these files via MobaXterm/Muon SSH/Jupyter lab UI conveniently.

If not, you will need to do it via a USB drive. Copy it to a USB drive (not BitLocker-encrypted) from your laptop. Plug it into one of the USB ports.
You can then copy the file (say, mybitstream.bit) from `/media/ubuntu/<label>` to your working folder (say, `/home/ubuntu/PynqDMAExample`) via the command

`cp  /media/ubuntu/<label>/mybitstream.bit /home/ubuntu/PynqDMAExample`.

You can find the `<label>` corresponding to your USB drive by pressing tab and looking at autocomplete options.

If you wish to make substantial changes to the .cpp file for OpenCL, you can also edit on the laptop and copy it using one of the methods mentioned above.