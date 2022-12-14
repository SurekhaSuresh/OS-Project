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
	if(argc<5){
		printf("\n<filename> [-r|-w] <block_size> <block_count>");
		printf("\nInsufficient arguments. Check usage \n");
		return 0;
		// ./file_op <filename to read from > -r <block_size> <block_count>
		// ./file_op <filename to write to> -w <block_size> <block_count> 		
	}

	char* fname = argv[1]; // first argument - file to write into / read from
	char op = argv[2][1]; // second argument - read / write flag ( -r | -w)
	int block_size = atoi(argv[3]); // third argument - block_size
	int block_count = atoi(argv[4]); // fourth argument - block_count
	int block_count_counter = 0;

	// printf("%d block size is", block_size);

	if(!op || (op!='r' && op!='w')) op = 'r';
	
	if(op == 'r') {

		// struct stat st;
		// stat(fname, &st);
		// unsigned int size = st.st_size;

		// printf("\n File size is %u \n",size);

		// int num_of_char = block_size/sizeof(unsigned int);

		// int fd = open(fname,O_RDONLY, 0);
		// if (fd < 0)
		// {
		// 	printf("\nCannot open file \n");
		// 	return 0;
		// }
		// unsigned int resxor = 0;
		// char *memblock = (char *) calloc(block_size, sizeof(char));
		// // memblock[block_size] = '\0';
		// int rd;
		// while(1){
		// 	rd = read(fd,memblock,block_size);	
		// 	block_count_counter += 1;
		// 	if(rd<block_size) {
		// 		if(rd==0) break;
		// 		char* substr = (char *)malloc(rd);
		// 		strncpy(substr, memblock, rd);
		// 		// printf("%d %s \n ",rd , substr);
		// 		// printf("%s \n ",substr);
		// 		resxor ^= xorbuf((unsigned int *)substr,rd);
		// 		continue;
		// 	}
		// 	// printf("%s",memblock);
		// 	resxor ^= xorbuf((unsigned int *)memblock,block_size);
		// }

		// // printf("%d\n",rd);
		// printf("\n %08x\n", resxor);
		// free(memblock);

		// close(fd);



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

		while(block_count_counter < block_count){
		// while(1){
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
	}

	if(op == 'w') {

		srand((unsigned)time(NULL) * getpid()); 

		int fd = open(fname, O_WRONLY | O_CREAT, 0777);
		if (fd < 0)
		{
			printf("\nCannot open file \n");
			return 0;
		}
		
		char  *memblock = (char *) calloc(block_size, sizeof(char *));
		int wd;
		long int fsize = 0;
		double start = now();

		while(block_count_counter < block_count){
		// while(1){
			char* randstring = gen_random(block_size);	
			wd = write(fd,randstring,block_size);
			fsize += wd;
			block_count_counter += 1;
		}

		double end = now();	
		double perf = fsize/(end-start);
		double perf_mb = fsize/(1024*1024*(end-start));


		printf("\n[size read] %ld \n", fsize);
		printf("\n[time] %f\n", end-start);
		printf("\n[B/s] %f\n", perf);
		printf("\n[MiB/s] %f\n", perf_mb);

		free(memblock);

		close(fd);

	}

return 0;
}

