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
	char op = argv[2][1]; // second argument - read / write flag ( -r | -w)


	if(!op || (op!='r' || op!='w')) op = 'r';

	if(op == 'r') {
		// reading from file
		int block_size = atoi(argv[3]); // mandatory param while reading
		if(!block_size || block_size < 0) block_size = 512;
		int block_count = 1;
		if(argv[4]) block_count = atoi(argv[4]);

		fstream my_file;
		my_file.open(path, ios::in);

	
		if(argv[4]) {
			const auto begin = my_file.tellg();
			my_file.seekg (0, ios::end);
			const auto end = my_file.tellg();
			const auto fsize = (end-begin);
			if(fsize < block_size*block_count){
				cout << "\n File not big enough \n";
				return 0;
			}
		}

		cout << "\n File size "<< fsize << "\n";

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
				
				if(my_file.eof()){
					string s(memblock, my_file.gcount());
					cout << s << "\n";
					break;
				}

				cout << memblock;
			}
			cout << "\n";
		}
		my_file.close();
	}

return 0;
}
