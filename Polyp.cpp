#include <iostream>
#include <fstream>
#include <string>
#include "Polyp.h"

using namespace std;

Polyp::Polyp(void)
{
}


Polyp::~Polyp(void)
{
}
int CountLines(char *filename)
{
	ifstream ReadFile;
	int n=0;
	string tmp;
	ReadFile.open(filename,ios::in);//ios::in :readonly
	if(ReadFile.fail())// open fails
	{
		return 0;
	}
	else//if exit
	{
		while(getline(ReadFile,tmp,'\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}
vector<Seed> readSeedFromTXT(char *txtfilepath)
{
		ifstream file;
		int LINES;
		char filename[512]="inFile.txt";
		file.open(filename,ios::in);
		if(file.fail())
		{
			cout<<"not exit."<<endl;
			file.close();
		}
		else//if exit
		{
			LINES=CountLines(filename);
			int *tempInt=new int[LINES];
			char *tempChar=new char[LINES];
			int i=0;
			while(!file.eof()) //read data to array
			{

				file>>tempInt[i];
				file>>tempChar[i];
				i++;
			}
			file.close(); //close file
			for(i=0;i<LINES;i++)
				cout<<tempInt[i]<<"\t"<<tempChar[i]<<endl;
			delete []tempInt;
			delete []tempChar;
		}

		vector<Seed> seed;
		return seed;

}
Raw* initialRegion(vector<Seed> seedlist,int size,int l,int m,int n)
{
	Raw *initialRegion=new Raw(l,m,n);
	memset(initialRegion->getdata(),2,initialRegion->size());
	for (vector<Seed>::iterator it = seedlist.begin();it!=seedlist.end();++it)
	{
		
		//Seed *seed=new Seed(it->x,it->y,it->z);
		for (int i = it->x-size; i < it->x+size; ++i )
		{
			for (int j = it->y-size; j < it->y+size; ++j)
			{
				for (int k= it->z-size; k< it->z+size; ++k)
				{
					initialRegion->put(i,j,k,-2);
				}
				
			}
			
		}
		
	}
}
Raw* polypDetect(Raw * initialregion);