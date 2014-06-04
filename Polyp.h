#pragma once
#include <vector>
#include"ThreeDim_LevelSet.h"
using namespace std;
class Seed
{
public:
	int x;
	int y;
	int z;
public:
	Seed(int x,int y,int z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
};
class Polyp
{
private:
	Raw *colon;
public:
		vector<Seed> seedlist;
		Polyp(void);
		~Polyp(void);
		vector<Seed> readSeedFromTXT(char *txtfilepath);
		Raw* initialRegion(vector<Seed> seedlist);
		Raw* polypDetect(Raw * initialregion);
};

