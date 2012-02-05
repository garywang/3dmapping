#include <iostream>
using namespace std;

#include "image.h";

int main()
{
	image* On=LoadImage("on.image");
	image* Off=LoadImage("off.image");
	for(int t=30; t<=310; t+=10)
	{
		image* onframe=new image(320,240,BLACK);
		for(int y=30; y<=120; y++)
			onframe->set(t,y,WHITE);
		cout<<"got here!";
		for(int y=120; y<230; y++)
			onframe->set(200+t-y,y,WHITE);
		cout<<"got here!";
		char* name=new char[11];
		name[0]='o';
		name[1]='n';
		name[2]=(t/100+48);
		name[3]=((t%100)/10+48);
		name[4]='.';
		name[5]='i';
		name[6]='m';
		name[7]='a';
		name[8]='g';
		name[9]='e';
		name[10]='\0';
		SaveImage(onframe,name);
	};
	On->print();
	cout<<endl;
	Off->print();
	cout<<endl;
	SUBTRACT(On,Off)->print();
	return (0);
};