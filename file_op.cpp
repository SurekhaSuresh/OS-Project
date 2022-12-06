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
	if(argc<2){
		cout << "Insufficient arguments. Check usage \n";
		// ./file_op <filename to read from / write to> <-r|-w> <block_size>
	}
	string path = argv[1]; // first argument - file to write into / read from
	char op = argv[2][1]; // second argument - read / write flag ( -r | -w)


	if(!op || (op!='r' || op!='w')) op = 'r';

	if(op == 'r') {
		// reading from file
		int block_size = argv[3];
		if(!block_size || block_size < 0) block_size = 512;

		fstream my_file;
		my_file.open(path, ios::in);
		if (!my_file) {
			cout << "No such file";
		}
		else {
			cout<< "File opened!! \n";
			char ch;
			while (1) {
				my_file >> ch;
				if (my_file.eof())
					break;
				cout << ch;
			}
			cout << "\n";
		}
		my_file.close();
	}

return 0;
}
// int main(int argc,char* argv[]) {
// 	fstream my_file;
// 	my_file.open("my_file", ios::out);
// 	if (!my_file) {
// 		cout << "File not created!";
// 	}
// 	else {
// 		cout << "File created successfully!\n";
// 		my_file.close(); 
// 	}
// 	return 0;
// 	/* 
// 	// writing
// 	fstream my_file;
// 	my_file.open("my_file.txt", ios::out);
// 	if (!my_file) {
// 		cout << "File not created!";
// 	}
// 	else {
// 		cout << "File created successfully!";
// 		my_file << "Guru99";
// 		my_file.close();
// 	}
// 	return 0;

// 	// reading from file
// 	fstream my_file;
// 	my_file.open("my_file.txt", ios::in);
// 	if (!my_file) {
// 		cout << "No such file";
// 	}
// 	else {
// 		char ch;

// 		while (1) {
// 			my_file >> ch;
// 			if (my_file.eof())
// 				break;

// 			cout << ch;
// 		}

// 	}
// 	my_file.close();
// 	return 0;
// 	*/
// }