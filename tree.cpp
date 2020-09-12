#include <iostream>
#include <fstream>
#include <string>
//#include <thread>
//#include <mutex>

std::string pwd(){
	std::system("pwd > /tmp/pwd");
	std::ifstream file("/tmp/pwd");
	char pwd[256];
	if(file.is_open()){
		file.getline(pwd,256);
		file.close();
	};
	return pwd;
};

std::string genTree(std::string folder){
	std::string tree;
	
	std::string command = "ls -F "+ folder +" > /tmp/file";
	std::system(command.c_str());
		
	std::ifstream file("/tmp/file");		
	if (file.is_open()){
		int n = 256;
		char lineC[n];
		std::string lineS;
		file.getline(lineC , n);
		lineS = lineC;
		while(file.getline(lineC,n)){
			tree += " ├── "+ lineS + '\n';
			lineS = lineC;	
		};
		tree += " └── ";
		tree += lineS;
		file.close();
	}else{
		throw;
	};
	return tree; 
};

int main(){
	std::cout<<genTree(pwd())<<std::endl;
	return 0;
}
