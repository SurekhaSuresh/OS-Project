/*
ios:: app 	The Append mode. The output sent to the file is appended to it.
ios::ate 	It opens the file for the output then moves the read and write control to file’s end.
ios::in 	It opens the file for a read.
ios::out 	It opens the file for a write.
ios::trunc 	If a file exists, the file elements should be truncated prior to its opening.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

#include <unistd.h> // getpid used in initializing rand

double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

unsigned int xorbuf(unsigned int *buffer, unsigned  int size) {
	unsigned  int result = 0;
	for (unsigned  int i = 0; i < size; i++) {
		// printf("\n ---- y u do is %lu",i);
		result ^= buffer[i];
	}
	return result;
}

char* gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    char* tmp_s = (char*) malloc(len);
    int alphanum_size = sizeof(alphanum);
    for (int i = 0; i < len; ++i) {
        tmp_s[i] = alphanum[rand() % (alphanum_size - 1)];
    }
    return tmp_s;
}


int main(int argc,char* argv[]) {
	if(argc<3){
		printf("\n<filename> <block_size>");
		printf("\nInsufficient arguments. Check usage \n");
		return 0;
		// ./file_op <filename to read from > <block_size>
	}

	char* fname = argv[1]; // first argument - file to write into / read from
	unsigned long int block_size = atoi(argv[2]); // second argument - block_size
	unsigned long int block_count = 0;
	unsigned long int block_count_counter = 0;

	int fd = open(fname,O_RDONLY, 0);
	if (fd < 0)
	{
		printf("\nCannot open file \n");
		return 0;
	}
	unsigned long  num_of_char = block_size/sizeof(unsigned int);
	unsigned long int resxor = 0;
	unsigned int *memblock = (unsigned int  *) calloc(num_of_char, sizeof(unsigned int ));
	unsigned long int rd;
	unsigned long int fsize = 0;
	double start = now();

	// while(block_count_counter < block_count){
	while(1){
		rd = read(fd,memblock,block_size);			
		fsize += rd;
		block_count_counter += 1;
		if(rd<num_of_char) {
			if(rd==0) break;
			unsigned int* substr = (unsigned int *)calloc(rd,sizeof(unsigned int));
			for(int i=0;i<rd;i++){
				substr[i] = memblock[i];
			}
			// resxor ^= xorbuf(substr,rd);
			continue;
		}
		// printf("%s",memblock);
		// resxor ^= xorbuf(memblock,rd);
		// if(now()-start > 7.0){
		// 	block_count = fsize / block_size;
		// 	break;
		// } 
	}
	double end = now();	
	double perf = fsize/(end-start);
	double perf_mb = fsize/(1024*1024*(end-start));


	// printf("\n[xor] %lu\n", resxor);
	// printf("\n[size read] %ld\n", fsize);
	// printf("\n[time] %f\n", end-start);
	// printf("\n[B/s] %f\n", perf);
	// printf("\n[MiB/s] %f\n", perf_mb);
	// printf("\n[block_size] %lu\n", block_size);
	printf("%lu,%f,%f,%f\n",block_size,end-start,perf,perf_mb);
	free(memblock);
	close(fd);

return 0;
}


/*



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

#include <unistd.h> // getpid used in initializing rand

double now() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec / 1000000.0;
}

unsigned int xorbuf(int *buffer, int size) {
	unsigned int result = 0;
	for (int i = 0; i < size; i++) {
		result ^= buffer[i];
	}
	return result;
}

char* gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    char* tmp_s = (char*) malloc(len);
    int alphanum_size = sizeof(alphanum);
    for (int i = 0; i < len; ++i) {
        tmp_s[i] = alphanum[rand() % (alphanum_size - 1)];
    }
    return tmp_s;
}


int main(int argc,char* argv[]) {
	if(argc<3){
		printf("\n<filename> <block_size>");
		printf("\nInsufficient arguments. Check usage \n");
		return 0;
		// ./file_op <filename to read from > <block_size>
	}

	char* fname = argv[1]; // first argument - file to write into / read from
	int block_size = atoi(argv[2]); // second argument - block_size
	int block_count = 0;
	int block_count_counter = 0;

	int fd = open(fname,O_RDONLY, 0);
	if (fd < 0)
	{
		printf("\nCannot open file \n");
		return 0;
	}
	int num_of_char = block_size/sizeof(unsigned int);
	unsigned int resxor = 0;
	unsigned int  *memblock = (unsigned int  *) calloc(num_of_char, sizeof(unsigned int ));
	int rd;
	long int fsize = 0;
	double start = now();

	// while(block_count_counter < block_count){
	while(1){
		rd = read(fd,memblock,block_size);	
		fsize += rd;
		block_count_counter += 1;
		if(rd<num_of_char) {
			if(rd==0) break;
			unsigned int* substr = (unsigned int *)calloc(rd,sizeof(unsigned int));
			for(int i=0;i<rd;i++){
				substr[i] = memblock[i];
			}
			resxor ^= xorbuf(substr,rd);
			continue;
		}
		// printf("%s",memblock);
		resxor ^= xorbuf(memblock,rd);
		if(now()-start > 7.0){
			block_count = fsize / block_size;
			break;
		} 
	}
	double end = now();	
	double perf = fsize/(end-start);
	double perf_mb = fsize/(1024*1024*(end-start));

	printf("\n[xor] %08x\n", resxor);
	printf("\n[size read] %ld\n", fsize);
	printf("\n[time] %f\n", end-start);
	printf("\n[B/s] %f\n", perf);
	printf("\n[MiB/s] %f\n", perf_mb);
	free(memblock);
	close(fd);

return 0;
}



*/