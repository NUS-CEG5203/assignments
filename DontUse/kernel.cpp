#include <hls_stream.h>
#include <ap_int.h>

// Vector addition kernel
// Each pointer is mapped to AXI4 memory (global memory)
extern "C" {
void vadd(const int *A, const int *B, int *C, int size) {
#pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=B offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=C offset=slave bundle=gmem

#pragma HLS INTERFACE s_axilite port=A bundle=control
#pragma HLS INTERFACE s_axilite port=B bundle=control
#pragma HLS INTERFACE s_axilite port=C bundle=control
#pragma HLS INTERFACE s_axilite port=size bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

  // Main loop
  for (int i = 0; i < size; i++) {
  #pragma HLS PIPELINE II=1
    C[i] = A[i] + B[i];
  }
}
}
