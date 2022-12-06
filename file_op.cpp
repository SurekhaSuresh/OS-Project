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
		cout << "\n Insufficient arguments. Check usage \n";
	}
	string s = argv[1]; // first argument - file to write into / read from
	char op = argv[2][1]; // second argument - read / write flag ( -r | -w)


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