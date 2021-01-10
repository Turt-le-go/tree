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
int index = 0;

std::string genTree(std::string folder, int deep = 0){
	++index;
	std::string tree;
	
	std::string command1 = "ls -F '"+ folder +"' > /tmp/file" + std::to_string(index);
	std::system(command1.c_str());

	std::string command2 = "ls -l '"+ folder +"' | cut -c 1 | sed '1d' > /tmp/fileType" + std::to_string(index);
	std::system(command2.c_str());
	
	std::ifstream file("/tmp/file" + std::to_string(index));		
	std::ifstream fileType("/tmp/fileType" + std::to_string(index));		
	if (file.is_open() && fileType.is_open()){
		std::string dt = "";
		for(int i = 0; i< deep; i++){
			dt += " │   ";
		}
		int n = 256;
		char lineC[n];
		std::string type;
		std::string lineS;
		file.getline(lineC,n);
		lineS = lineC;
		while(file.getline(lineC,n)){
			getline(fileType , type);
			tree += dt + " ├── "+ lineS + '\n';
			if(type == "d"){
				tree += genTree(folder+'/'+lineS, deep + 1)+ '\n';
			}
			lineS = lineC;	
		};
		tree += dt +" └── ";
		tree += lineS;
		file.close();
		fileType.close();
	}else{
		throw;
	}
	return tree; 
};

int main(){
	std::cout<<genTree(pwd())<<std::endl;
	return 0;
}
