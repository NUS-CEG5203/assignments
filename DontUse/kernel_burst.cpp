#include <ap_int.h>
#include <hls_stream.h>

#define MAX_SIZE 1024
#define BURST_LEN 64

// Optimized vector addition kernel
void vadd(volatile int* A, volatile int* B, volatile int* C, int N) {
#pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem0 depth=1024
#pragma HLS INTERFACE m_axi port=B offset=slave bundle=gmem1 depth=1024
#pragma HLS INTERFACE m_axi port=C offset=slave bundle=gmem2 depth=1024
#pragma HLS INTERFACE s_axilite port=N
#pragma HLS INTERFACE s_axilite port=return

    // Local buffers for burst transfers
    int buffer_A[BURST_LEN];
    int buffer_B[BURST_LEN];
    int buffer_C[BURST_LEN];
    
#pragma HLS ARRAY_PARTITION variable=buffer_A complete
#pragma HLS ARRAY_PARTITION variable=buffer_B complete
#pragma HLS ARRAY_PARTITION variable=buffer_C complete

    // Process data in bursts
    burst_loop: for (int base = 0; base < N; base += BURST_LEN) {
        int chunk_size = (base + BURST_LEN > N) ? N - base : BURST_LEN;
        
        // Burst read from A and B
        read_loop: for (int i = 0; i < chunk_size; i++) {
#pragma HLS PIPELINE II=1
            buffer_A[i] = A[base + i];
            buffer_B[i] = B[base + i];
        }
        
        // Compute vector addition
        compute_loop: for (int i = 0; i < chunk_size; i++) {
#pragma HLS PIPELINE II=1
            buffer_C[i] = buffer_A[i] + buffer_B[i];
        }
        
        // Burst write to C
        write_loop: for (int i = 0; i < chunk_size; i++) {
#pragma HLS PIPELINE II=1
            C[base + i] = buffer_C[i];
        }
    }
}