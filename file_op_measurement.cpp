/*
ios:: app 	The Append mode. The output sent to the file is appended to it.
ios::ate 	It opens the file for the output then moves the read and write control to file’s end.
ios::in 	It opens the file for a read.
ios::out 	It opens the file for a write.
ios::trunc 	If a file exists, the file elements should be truncated prior to its opening.
*/


#include <iostream>
#include <fstream>
using namespace std;
int main(int argc,char* argv[]) {
	if(argc<3){
		cout << "Insufficient arguments. Check usage \n";
		// ./file_op <filename to read from > -r <block_size>
		// ./file_op <filename to read from > -r <block_size> <block_count>
		// ./file_op <filename to write to> -w <block_size> <block_count> <filename to copy/read from> // check with TA
	}
	string path = argv[1]; // first argument - file to write into / read from
	int block_size = atoi(argv[2]);  // second argument - read / write flag ( -r | -w)
	if(!block_size || block_size < 0) block_size = 4;
	int block_count_counter = 0;
	fstream my_file;
	my_file.open(path, ios::in);
	cout << "\n Block size is " << block_size << "\n";

    char memblock[block_size];
    memblock[block_size-1] =  '\0';

    int p = 0;
    
	if (!my_file) {
		cout << "No such file";
	}
	
	else {
		
		cout << " File opened!! \n";
		my_file.seekg(p);

		while(1){

			// ISSUE: Some junk character at the end HACK : that's why block_size-1 to prevent print junk character
			my_file.read(memblock, block_size-1); 
			block_count_counter += 1;

			if(my_file.eof()){
				break;
			}

		}
		cout << block_count_counter;
	}
	my_file.close();

return 0;
}
