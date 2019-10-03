#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

ifstream infile("textfile.txt");

int main(){
    char ch[30];

    while(infile){
        
        char output[50] = "./iupac.obj \"";
        infile >> ch;
        strcat(output, ch);
        strcat(output, "\"");
        
        system(output);
	cout<<ch<<endl<<endl;
    }
    return 0;
}
