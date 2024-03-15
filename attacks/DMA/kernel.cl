__kernel void copy(__global unsigned char* input, __global unsigned char* output, int n) {
	unsigned int i;

	for(i = 0; i < n; i++)
	    output[i] = input[i];
}