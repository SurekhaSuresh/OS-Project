/*
ios:: app 	The Append mode. The output sent to the file is appended to it.
ios::ate 	It opens the file for the output then moves the read and write control to file’s end.
ios::in 	It opens the file for a read.
ios::out 	It opens the file for a write.
ios::trunc 	If a file exists, the file elements should be truncated prior to its opening.
*/


#include <iostream>
#include <fstream>
#include <sys/time.h>

using namespace std;
int main(int argc,char* argv[]) {
	if(argc<2){
		cout << "\n <filename> <block_size>";
		cout << "\n Insufficient arguments. Check usage \n";
		return 0;
		// ./file_op <filename to read from > <block_size>
	}

	string fname = argv[1]; // first argument - file to write into / read from

	// reading from file
	int block_size = atoi(argv[2]); // third argument - block_size
	int block_count_counter = 0;
	
	fstream my_file;
	my_file.open(fname, ios::in);

	// // file size read 
	// const auto begin = my_file.tellg();
	// my_file.seekg (0, ios::end);
	// const auto end = my_file.tellg();
	// const auto fsize = (end-begin);

	
	char memblock[block_size];
	memblock[block_size-1] =  '\0';

	// Start measuring time
	struct timeval c_begin, c_end;
    gettimeofday(&c_begin, 0);
	    
	if (!my_file) {
		cout << " No such file";
	}		
	else {			
		cout << " File opened!! \n";
		my_file.seekg(0);
		while(1){
			// ISSUE: Some junk character at the end HACK : that's why block_size-1 to prevent print junk character
			my_file.read(memblock, block_size-1); 
			block_count_counter += 1;

			if(my_file.eof()){
				break;
			}
			// cout << memblock;
		}
		// cout << "\n";
	}
		
	// Stop measuring time and calculate the elapsed time
    gettimeofday(&c_end, 0);
    long seconds = c_end.tv_sec - c_begin.tv_sec;
    long microseconds = c_end.tv_usec - c_begin.tv_usec;
   	double c_elapsed = seconds + microseconds*1e-6;

   	int fsize = block_count_counter * block_size;

    cout << "\n Time measured: "<< c_elapsed << " seconds.\n";
	cout << "\n File size (Bytes) "<< fsize << "\n";
    cout << "\n Performance in B/s : "<< fsize/c_elapsed << "\n";
	my_file.close();

	return 0;
}