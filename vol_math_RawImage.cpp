#include "vol_math_RawImage.h"
#include <cassert>
#include <map>
//#include"vol_math_Raw3D_Independt.h"
/*
RawImage is to change the all the three data types to double or float
*/
//=====================================================================================================
char* double2char(float *buf, long length)
{
	int i=0;
	char *imgf=new char[length];
	while(i < length)
	{
		imgf[i]= (char)buf[i++];
	}
	return imgf;
}

RawImage::RawImage(int length,int height,int width)
{
	this->height=height;
	this->length=length;
	this->width=width;
	int length1=this->getlength();
	this->buf=new PIXTYPE[length1];
}
RawImage::RawImage()
{
	this->height=0;
	this->length=0;
	this->width=0;
	this->buf=NULL;

}
float * RawImage::readStreamfloat(char const *filename,int *l,int * m,int  * n)
{
	ifstream file;
	file.open(filename,ios::out |ios::app| ios::binary);
	if (!file.is_open()) {
		cout<< "The file open failed, Please check it and try again"<< endl;
		exit(0);
	}
	//file.read(reinterpret_cast<char *>(&lx),sizeof(int));
	//file.read(reinterpret_cast<char *>(&ly),sizeof(int));
	//file.read(reinterpret_cast<char *>(&lz),sizeof(int));
	int size=*l**m**n*sizeof(float);
	//*l=lx;*m=ly;*n=lz;
	float *buf=new float[size];
	file.read((char *)buf,size);
	file.close();
	return buf;

}
void RawImage::readImage(unsigned char * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	//fseek(op,281*481*500L,SEEK_SET);
	fread(buf,sizeof(unsigned char),size,op);

	fclose(op);
	printf("read is ok\n");
}
void RawImage::readImage2(float * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	//fseek(op,281*481*500L,SEEK_SET);
	fread(buf,sizeof(float),size,op);

	fclose(op);
	printf("read is ok\n");
}
short * RawImage::readStream(char const *filename,int *l,int * m,int  * n)
{
	
	int lx=0,ly=0,lz=0;
	float rate=0;
	ifstream file;
	file.open(filename, ios::out | ios::app | ios::binary);
	if (!file.is_open()) {
		cout<< "The file open failed, Please check it and try again"<< endl;
		exit(0);
	}
	file.read(reinterpret_cast<char *>(&lx),sizeof(int));
	file.read(reinterpret_cast<char *>(&ly),sizeof(int));
	file.read(reinterpret_cast<char *>(&lz),sizeof(int));
	file.read(reinterpret_cast<char *>(&rate),sizeof(float));
	cout<<rate<<endl;
	int size=lx*ly*lz*sizeof(short);
	*l=lx;*m=ly;*n=lz;
	short *buf=new short[size];
	file.seekg(24L+*l**m*(212-20),ios::beg);//+512*512*345*sizeof(short)
	file.read((char *)buf,size);
	file.close();
	return buf;

}
unsigned char * RawImage::readStreamuchar(char const *filename,int l,int m,int  n,int seedz)
{

	//int lx= 0,ly=0,lz=0;
	float rate=0;
	ifstream file;
	file.open(filename, ios::out | ios::app | ios::binary);
	if (!file.is_open()) {
		cout<< "The file open failed, Please check it and try again"<< endl;
		exit(0);
	}
	//file.read(reinterpret_cast<char *>(&lx),sizeof(int));
	//file.read(reinterpret_cast<char *>(&ly),sizeof(int));
	//file.read(reinterpret_cast<char *>(&lz),sizeof(int));
	//file.read(reinterpret_cast<char *>(&rate),sizeof(float));
	//cout<<rate<<endl;
	int size=l*m*n*sizeof(unsigned char);
	unsigned char *buf=new unsigned char [size];
	file.seekg(24L+l*m*(seedz-20),ios::beg);//+512*512*345*sizeof(short)
	file.read((char *)buf,size);
	file.close();
	return buf;

}
void RawImage::readImagesi(short  * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	//fseek(op,24L+43253760L,SEEK_SET);
	fread((char *)buf,sizeof(signed int ),size,op);

	fclose(op);
	printf("read is ok\n");
}
void RawImage::writeImagecolon(Raw &destImg)
{
	FILE *p=fopen("D:\\swfdata20140420res\\58_3035P\\newthickness\\3Dlevel_good.raw","wb");
	//char* data = double2char(destImg.getdata(), destImg.size());
	PIXTYPE *data=destImg.getdata();
	//for (int i=0;i<destImg.getXsize()*destImg.getYsize()*destImg.getZsize();i++)
	//{

	//	if (data[i]<1)
	//	{
	//		data[i]=data[i];
	//	}
	//	else data[i]=0;

	//}
	//swf 10140418 delete for wirite centerline
	//for (int i=0;i<destImg.getZsize();i++)
	//{
	//	for (int j=0;j<destImg.getYsize();j++)
	//	{
	//		for (int k=0;k<destImg.getXsize();k++)
	//		{
	//			PIXTYPE *val=&data[i*destImg.getXsize()*destImg.getYsize()+j*destImg.getXsize()+k];
	//			if(k<451 &&k> 45 && j>162 &&j <391)
	//			{
	//				if (*val>1)
	//				{
	//					*val=0;
	//					
	//				}
	//				else *val=100;
	//			}
	//			else *val=0;
	//		}
	//	}
	//}
	fwrite(data, sizeof(float), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
void RawImage::writeImage(Raw &destImg)
{
	FILE *p=fopen("K:\\3Dlevelcolon.raw","wb");
	PIXTYPE *data=(PIXTYPE *)destImg.getdata();
	for (int i=0;i<destImg.getZsize();i++)
	{
		for (int j=0;j<destImg.getYsize();j++)
		{
			for (int k=0;k<destImg.getXsize();k++)
			{
				PIXTYPE *val=&data[i*destImg.getXsize()*destImg.getYsize()+j*destImg.getXsize()+k];
				if((( j - 256 ) * ( j - 256 ) + ( k - 256 ) * ( k-256 )) < 220*220)//k<409 && k> 107 && j>156 &&j <390
				{
					if (*val>1)
					{
						*val=100;

					}
					else *val=0;
				}
				else *val=0;
			}
		}
	}
	fwrite(data, sizeof(PIXTYPE), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	//delete[] data;
	printf("write is ok");
}
void RawImage::writenormal(Raw &destImg,const char *name)
{
	FILE *p=fopen(name,"wb");
	PIXTYPE *data=(PIXTYPE *)destImg.getdata();
	short * sdata=new short[destImg.size()];
	for (int i=0;i<destImg.size();i++)
	{
		sdata[i]=(short)data[i];
	}
	int xsize=destImg.getXsize();
	int ysize=destImg.getYsize();
	int zsize=destImg.getZsize();
	fwrite(&xsize,sizeof(int),1,p);
	fwrite(&ysize,sizeof(int),1,p);
	fwrite(&zsize,sizeof(int),1,p);
	fseek(p,24L,SEEK_SET);
	fwrite(sdata, sizeof(short), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	delete[] sdata;
	printf("write is ok");
}
void RawImage::writeMRI(Raw &destImg, char *name)
{
	FILE *p=fopen(name,"wb");
	PIXTYPE *data=new PIXTYPE[destImg.size()];
	memcpy(data,destImg.getdata(),sizeof(PIXTYPE)*destImg.size());

	//for (int i=0;i<destImg.getZsize();i++)
	//{
	//	for (int j=0;j<destImg.getYsize();j++)
	//	{
	//		for (int k=0;k<destImg.getXsize();k++)
	//		{
	//			PIXTYPE *val = &data[i*destImg.getXsize()*destImg.getYsize()+j*destImg.getXsize()+k];
	//			if (((k-256)*(k-256)+(j-256)*(j-256) )<(230*230))//k<409 && k> 107 && j>156 &&j <390
	//			{
	//				if (*val > 1)
	//				{
	//					*val = 100;  //change to 100 for roc computing *val=0; 

	//				}
	//				else *val = 0; ////change to 0 for roc computing *val=100; 
	//			}
	//			else *val = 0;
	//		}
	//	}
	//}
	fwrite(data, sizeof(PIXTYPE), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
void RawImage::writeImageName(Raw &destImg, char *name)
{
	FILE *p=fopen(name,"wb");
	PIXTYPE *data=new PIXTYPE[destImg.size()];
		memcpy(data,destImg.getdata(),sizeof(PIXTYPE)*destImg.size());
	
	//for (int i=0;i<destImg.getZsize();i++)
	//{
	//	for (int j=0;j<destImg.getYsize();j++)
	//	{
	//		for (int k=0;k<destImg.getXsize();k++)
	//		{
	//			PIXTYPE *val = &data[i*destImg.getXsize()*destImg.getYsize()+j*destImg.getXsize()+k];
	//			if (((k-256)*(k-256)+(j-256)*(j-256) )<(230*230))//k<409 && k> 107 && j>156 &&j <390
	//			{
	//				if (*val > 1)
	//				{
	//					*val = 100;  //change to 100 for roc computing *val=0; 

	//				}
	//				else *val = 0; ////change to 0 for roc computing *val=100; 
	//			}
	//			else *val = 0;
	//		}
	//	}
	//}
	fwrite(data, sizeof(PIXTYPE), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
void RawImage::writeImagesesmic(Raw &destImg)
{
	FILE *p=fopen("F:\\3Dlevel.raw","wb");

	unsigned char *data=(unsigned char *)destImg.getdata();

	fwrite(data, sizeof(unsigned char), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
float* RawImage::buf2float(unsigned char *buf)
{
	unsigned char *p;
	p=buf;
	int i=0;
	long length=this->getlength();
	float *imgf=new float[length];
	while(p)
	{
		imgf[i]= (float)p[i] ;
		imgf+=i;
		p++;i++;
	}
	return imgf;
}

RawImage::~RawImage(void)
{
	delete[] buf;
}

//=====================================================================================================

Raw::Raw(void)
{
	xsize=0;
	ysize=0;
	zsize=0;
	is_shared = false;
	data=NULL;
}
Raw::Raw(int xsize,int ysize,int zsize,PIXTYPE *y,bool _is_shared)
{
	//float i=0.0f;
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	is_shared = _is_shared;
	this->data=y;
}
Raw::Raw(int xsize,int ysize,int zsize,bool _is_shared)
{
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	this->is_shared = _is_shared;
	this->data=new PIXTYPE[size()];
}

Raw::Raw(const Raw & src, bool _is_shared)
{
	this->xsize=src.xsize;
	this->ysize=src.ysize;
	this->zsize=src.zsize;
	this->is_shared = _is_shared;

	if (src.is_shared == true) {
		this->data = src.data;
	} else {
		this->data=new PIXTYPE[size()];
		memcpy(this->data,src.data,sizeof(PIXTYPE)*size());
	}
}

Raw::~Raw(void)
{
	if(this->is_shared == false && this->data!=NULL) {
		delete [] this->data;
		data=NULL;
	}
}

Raw& Raw::set_shared(bool _is_shared)
{
	this->is_shared = _is_shared;
	return *this;
}

void Raw::sizer(int ixsize, int iysize,int izsize) {
	if(data!=NULL)
		delete [] this->data;
	data=NULL;
	this->data = new PIXTYPE[ixsize*iysize*izsize];	// & allocate memory.
	xsize = ixsize;				// set new RawImage size,
	ysize = iysize;
	zsize=izsize;
}

void Raw::sizer(Raw* src) {
	int ix, iy,iz;

	ix = src->getXsize();
	iy = src->getYsize();
	iz = src->getZsize();
	sizer(ix,iy,iz);
}

int Raw::wipecopy(Raw* src) {
	int out=1;
	int i,imax;	

	if(getYsize() != src->getYsize() || getXsize()!=src->getXsize()) { // resize to fit 'src'.
		sizer(src);
		out=0;
	}
	imax = getXsize()*getYsize();
	for(i=0; i<imax; i++) {
		putXYZ(i,src->getXYZ(i));
	}

	return(out);
}

Raw operator /(const PIXTYPE val, const Raw &volume)
{
	Raw res(volume);

	for (int i = 0; i < res.size(); i ++ )
	{
		res.data[i]= val/volume.data[i];
	}


	return res.set_shared(true);
}

//=====================================================================================================
RawArray::RawArray(int rawNum,Raw *src)
{
	this->rawNum=rawNum;
	this->z=src;
}
RawArray::RawArray(void)
{
	z=0;
}
RawArray::~RawArray(void)
{
	if(this->z!=NULL)
		delete [] this->z;
	z=NULL;
	//cout<<"RawArray is deconstruct"<<endl;
}
void RawArray::sizer(int ixsize, int iysize, int izsize,int rawNum) {
	int ii;
	if(z!=NULL)
		delete[]this->z;
	z = new Raw[rawNum];			// make room for the 2D objects,
	this->rawNum = 0;   //rawNum

	for(ii=0; ii< rawNum; ii++) 
		z[ii].sizer(ixsize,iysize,izsize);	// use the Raw sizer.	
}
void RawArray::sizer(RawArray* src)
{
	z=src->z;
	rawNum=src->rawNum;

}
void RawArray::wipecopy(RawArray& src) {
	int k,kmax;

	if(&src==NULL)return;
	if(src.rawNum==0) return;		// ignore empty inputs.
	if(src.getrawNum()!=rawNum || src.getZsize() != z[0].getZsize() || src.getYsize() != z[0].getYsize() ||
		src.getXsize() != getXsize()) {
			sizer(&src);
	}
	kmax = getrawNum();
	for(k=0; k< kmax; k++) {		// copy each field;
		z[k].wipecopy(&(src.z[k]));
	}
}


///////////////////////////////////queue///////////////////////////////////////

Queue::Queue()
{
	head=-1;
	rear=-1;
}
Queue::~Queue()
{

}
QueueData Queue::front()
{
	QueueData ret;
	return ret;

}

void Queue::push(QueueData var)
{
	points [ ++rear ] = var;
	if (rear == 0)
	{
		head = 0;
	}
}

void Queue::pop()
{
	++head;
}
bool Queue::isEmpty()
{
	bool flag = head >rear;
	if (head == -1 && rear == -1)
		flag = true;
	if (flag)
	{
		head = rear = -1;
	}
	return flag;
}
bool Queue::isFull()
{
	return rear == 100000-1;
}
