gcc sobel_all_host.c -o sobel_all_host -lOpenCL -O2 -lm

./sobel_all_host 2048 2048 16
