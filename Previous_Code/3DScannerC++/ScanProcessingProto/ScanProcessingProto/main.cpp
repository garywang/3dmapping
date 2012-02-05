#include <iostream>
using namespace std;

#include "scan.h"

int main()
{
	/*cout<<"Provide .scan filename to process.\n";
	char* filename=new char[256];
	cin.getline (filename,256);

	cout<<"\n";
*/
	scan* s=new scan("Blank_Test/scan.scan");//filename);

	/*cout<<"\n";

	cout<<"Provide .obj filename to save to.\n";
	cin.getline (filename,256);

	cout<<"\n";
*/
	s->process("Blank_Test/test.obj");//filename);

	//cout<<"\n";
	return 0;
};