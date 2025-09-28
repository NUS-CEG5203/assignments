# OpenCL

!!! danger "Work in Progress"
    This assignment description is being updated. Information can change substantially.

!!! warning "Follow the Spirit"
    The instructions should be taken as a rough guideline rather than a very comprehensive manual.
    

This assignment involves

1) Configuring your computer (PC) and IDE to run OpenCL code. Instructions for Intel GPUs in Windows and Linux are provided.

2) The computational problem is the same as what you did in the previous 2 assignments - to be able to multiply two matrices A and B and to produce the result RES = A*B/256.

3) You must also report the time taken for multiplication in pure software (run without hardware acceleration / OpenCL) as well as via OpenCL code. If you have both onboard graphics (e.g. Intel) as well as a discrete GPU, it would be interesting to compare the performance of the two vs pure software. Note: Since the size of the problem you are dealing with is small, the acceleration you obtain won't be indicative. Also, operating system context switches make performance evaluation hard to do deterministically. It is also affected by caching, and generally, it is faster the second time you run it.

4) Implement OpenCL-based acceleration on Kria board? >> May or may not be an eventual requirement. Still a WIP.

You can make use of this file as a starting point - vadd.c , which is slightly enhanced from the one explained in lecture notes. This file has enhanced debugging options, as well as time measurement-related functions. Note that the time functions are Linux-specific, but Windows equivalents exist.

## Submission Info

Assignment 3 (10 marks)

Upload a .zip file containing the

the .c host code
the .cl kernel code if it is not embedded into the host code
A text file containing the information printed on the console.

to Canvas by 11:59 PM, 14 Oct 2025.

It should be as a .zip archive, with the filename  <Team number>_<Team Member 1 Name>_<Team Member 1 Name>_3.zip.

Please DO NOT upload the whole project!

You will also need to do a demonstration to a teaching assistant (arrangements will be made known in due course) - arrangements will be made known in due course.

## Tips

### Multiple Platforms

If you have multiple GPUs (for example, integrated/onboard and discrete), the idea below could be useful. The idea could be extended for cases where there are multiple devices per platform.

cl_platform_id cpPlatform[2]; // If you have 2 platforms

// Get IDs of both platforms
err = clGetPlatformIDs(2, cpPlatform, NULL);

// Discrete GPU is likely cpPlatform[0] - you can find this info using clinfo. Change this to cpPlatform[1] to change to onboard graphics.
err = clGetDeviceIDs(cpPlatform[0], CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

### Time Measurement

You can use some form of a time library for time measurement. For Linux, it will look similar to the one below (won't work as such on Windows, but similar functions exist).

### Printing Kernel Program Build Log

If you experience issues related to your device OpenCL code compilation failure, you should inspect the kernel build log.

The most likely reason is that the .cl isn't accessible by the main program at runtime.

Another reason is the use of `double` - OpenCL extension `cl_khr_fp64` - is not supported by Intel integrated GPUs. You can see the supported extensions via clinfo - if you have only one GPU, see if clinfo | grep cl_khr_fp64 gives some output. Such issues can be debugged by inspecting the kernel program build log.

### Setting OpenCL Version

You may need to have #define CL_TARGET_OPENCL_VERSION 120 at the beginning of the example code covered in the lecture, else you will get warnings such as clCreateCommandQueue being deprecated. clCreateCommandQueue usage is discouraged in versions >=2.0, and the OpenCL version will default to the highest supported (likely 3.0 on Intel GPUs). This is just a warning though, not an error.
