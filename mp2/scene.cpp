#include "scene.h"
#include <iostream>
using namespace std;

Scene::Scene (int max)
{
	maxnum = max;
	imagearray = new Image *[max];
	x = new int [max];
	y = new int [max];
	for (int i = 0; i < max; i++){
		imagearray[i] = NULL;
		x[i] = 0;
		y[i] = 0;
	}
}
Scene::~Scene()
{
	for (int i =0; i< maxnum; i++){
		delete imagearray[i];
		imagearray[i] = NULL;
		}
	delete []imagearray;
	delete[]x;
	delete[]y;
	imagearray = NULL;
	x =NULL;
	y = NULL;
}
Scene::Scene(const Scene &source)
{
	maxnum = source.maxnum;
	imagearray = new Image *[maxnum];
	x = new int [maxnum];
	y = new int [maxnum];
	for (int i = 0; i <maxnum; i++){
		if (source.imagearray[i]!=NULL){
		imagearray[i] = new Image (*source.imagearray[i]);
		x[i] = source.x[i];
		y[i] = source.y[i];
		}
		else imagearray[i] = NULL;	
}

}
/*copy Scene (const Scene &source)
{
	maxnum = source.maxnum;
        imagearray = new Image *[maxnum];
        x = new int [maxnum];
        y = new int [maxnum];
        for (int i = 0; i <maxnum; i++){
                imagearray[i] = source.imagearray[i];
                x[i] = source.x[i];
                y[i] = source.y[i];}
}*/

const Scene &Scene::operator= (const Scene &source)
{
	for (int i = 0; i< maxnum ; i++){
	if (imagearray[i]!=NULL)	
	delete imagearray[i];
	imagearray[i] = NULL;
	}
	delete []imagearray;
	delete[]x;
	delete[]y;
	imagearray = NULL;
	x= NULL;
	y= NULL;
	//delete
	(*this).maxnum = source.maxnum;
        (*this).imagearray = new Image *[maxnum];
        x = new int [maxnum];
        y = new int [maxnum];
        for (int i = 0; i <maxnum; i++){
                if (source.imagearray[i]!=NULL){
		imagearray[i] = new Image (*source.imagearray[i]); 
                x[i] = source.x[i];
                y[i] = source.y[i];
		}
		else imagearray[i] = NULL;
	}
	return *this;
}

void Scene::changemaxlayers(int newmax)
{
//invalid
	if (newmax<0) {
	cout<<"invalid newmax"<<endl;
	return;
	}
	if (newmax == maxnum) return;
//newmax<maxnum
	if (newmax<maxnum){
//invalid
		for (int i = newmax; i < maxnum; i++){
			if (imagearray[i]!=NULL){
				cout<<"invalid newmax"<<endl;
				return;
				}
			}

//temparray copy
	Image**temparray  = new Image * [newmax];
	int * xt = new int [newmax];
	int * yt = new int [newmax];
	for (int i = 0; i < newmax ; i++){
		if (imagearray[i] == NULL){
			temparray[i] = NULL;
			xt[i] = 0;
			yt[i] = 0;
		}
		else{
			temparray[i] = imagearray[i];
			xt[i] = x[i];
			yt[i] = y[i];
			}
		}	 
//delete imagearray
	//for (int i = 0 ; i < maxnum; i++){
	//	if (imagearray[i] !=NULL){
	//		delete imagearray[i];
	//		imagearray[i] = NULL;
	//		}
	//``}
	delete []imagearray;
	delete []x;
	delete []y;
//imagearray copy temparray
	imagearray = new Image * [newmax]; 	
	x = new int [newmax];
	y = new int [newmax];
	for (int i = 0; i < newmax; i++){
		if (temparray[i] ==NULL){
			imagearray[i] = NULL;
			x[i] = 0;
			y[i] = 0;
			}
		else{
			imagearray[i] = temparray[i];
			x[i] = xt[i];
			y[i] = yt[i];
			}
	}
	 /*for (int i =0; i <newmax ; i++){
                if (temparray[i] !=NULL){
                        delete temparray[i];
                        temparray[i] = NULL;
                        }
                }*/
        delete []temparray;
        delete []xt;
        delete []yt;
        temparray = NULL;
        xt = NULL;
        yt = NULL;
	} 
//newmax>maxnum
	else
	{
	
//set all elements in temparray to be null
	Image ** temparray = new Image * [newmax];
	int * xt = new int [newmax];
	int * yt = new int [newmax];
	for (int i = 0 ; i< newmax ;i++){
		temparray[i] = NULL;
		xt[i] = 0;
		yt[i] = 0;
	}

//copy from 0 to maxnum
	for (int i = 0; i <maxnum ; i++){
		if (imagearray[i] !=NULL){
		temparray[i] = imagearray[i];
		xt[i] = x[i];
		yt[i] = y[i];
		//delete imagearray
		//delete imagearray[i]; 
		//imagearray[i] = NULL;
	//	x[i] = 0;
	//	y[i] = 0;
		}
	}

//copy from maxnum to newmax
//nothing
//delete imagearray
	delete []imagearray;
	delete []x;
	delete []y;

//imagearray copy temparray
	imagearray = new Image * [newmax];
	x = new int [newmax];
	y = new int [newmax];
	for (int i = 0; i < newmax; i++){
		if(temparray[i] ==NULL){
			imagearray[i] = NULL;
			x[i] = 0;
			y[i] = 0;
		}
		else{
		imagearray[i] = temparray[i];
		x[i] = xt[i];
		y[i] = yt[i];
		}
	}
	/* for (int i =0; i <newmax ; i++){
                if (temparray[i] !=NULL){
                        delete temparray[i];
                        temparray[i] = NULL;
                        }
                }*/
        delete []temparray;
        delete []xt;
        delete []yt;
        temparray = NULL;
        xt = NULL;
        yt = NULL;
} 	

//set maxnum = newmax
	maxnum = newmax;
//delete temparray
/*	for (int i =0; i <newmax ; i++){
		if (temparray[i] !=NULL){
			delete temparray[i];
			temparray[i] = NULL;
			}
		}
	delete []temparray;
	delete []xt;
	delete []yt;
	temparray = NULL;
	xt = NULL;
	yt = NULL;*/
}

/*void Scene::changemaxlayers(int newmax)
{
	if (newmax<maxnum){
	for (int i = newmax; i <maxnum; i++){
	if (imagearray[i]!= NULL){
	cout<<"invalid newmax"<<endl;
	return;
	}
	}
		
	Image** tempimage = new Image * [newmax];
	int *xt = new int [newmax];
	int *yt = new int [newmax];
	for (int i = 0; i < newmax; i++){
		if(imagearray[i]==NULL){
		tempimage[i]= NULL;
		xt[i] = 0;
		yt[i] = 0;}
		else{
	tempimage[i] = new Image (*imagearray[i]);
		xt[i] = (*this).x[i];
		yt[i] = (*this).y[i];
		}
}
	delete []imagearray;
	delete []x;
	delete []y;	
	//imagearray =tempimage;
	imagearray = new Image * [newmax];
	x = new int [newmax];
	y = new int [newmax];
	for (int i = 0; i< newmax ; i++){
	if (tempimage[i] == NULL) {
	imagearray[i] = NULL;
	x[i] = 0;
	y[i] =0;
	}
	else{imagearray[i] = new Image (*tempimage[i]);
	x[i] = xt[i];
	y[i] = yt[i];
	}
	}
	maxnum  = newmax;
	delete []tempimage;
	delete []xt;
	delete []yt;
	tempimage = NULL;
	xt = NULL;
	yt = NULL;
		}//newmax < maxnum
	else {
	Image** tempimage = new Image * [newmax];
        int *xt = new int [newmax];
        int *yt = new int [newmax];
	for (int i = 0; i<newmax ; i++){
	tempimage[i] = NULL;
	xt[i] = 0;
	yt[i] = 0;
		}
	 
       for (int i = 0; i < maxnum; i++){
                if(imagearray[i]!=NULL){
       		tempimage[i] = new Image (*imagearray[i]);
                xt[i] = (*this).x[i];
                yt[i] = (*this).y[i];
                }
}

	
	for (int i = maxnum; i < newmax ; i++){
	tempimage[i] = NULL;
	x[i] = 0;
	y[i] = 0;
	}	
       	
	delete []imagearray;
        delete []x;
        delete []y;
        imagearray = new Image * [newmax];
        x = new int [newmax];
        y = new int [newmax];
        for (int i = 0; i< newmax ; i++){
        if (tempimage[i] == NULL) {
        imagearray[i] = NULL;
        x[i] = 0;
        y[i] =0;
        }
        else{imagearray[i] = new Image (*tempimage[i]);
        x[i] = xt[i];
        y[i] = yt[i];
        }
        }
	
	//imagearray = tempimage;
        //x = xt;
        //y = yt;
        maxnum  = newmax;
        delete []tempimage;
        delete []xt;
        delete []yt;
        tempimage = NULL;
        xt = NULL;
        yt = NULL;


	}

	}
*/
void Scene::addpicture (const char* FileName, int index, int x, int y)
{
	Image *add = new Image();
	add->readFromFile(FileName);
	if (index<0 || index > (maxnum-1)){
	cout<<"index out of bounds"<<endl;
	return;}
	imagearray[index] = add;
	(*this).x[index] = x;
	(*this).y[index] = y;	
}
void Scene::changelayer (int index, int newindex)
{
	if (index<0 || newindex < 0 || index> (maxnum-1) || newindex > (maxnum-1)){
	cout<<"invalid index"<<endl;
	return;}
	if (index == newindex) return;
	if (imagearray[newindex]!=NULL)
	delete imagearray[newindex];
	imagearray[newindex] = imagearray[index];
	x[newindex] = x[index];
	y[newindex] = y[index];
	if (imagearray[index]!=NULL) imagearray[index]=NULL;
}
void Scene::translate (int index, int xcoord, int ycoord)
{
	if (index<0||index>(maxnum-1) || imagearray[index] ==NULL){
	cout<<"invalid index"<<endl;
	return;
	}
	x[index] = xcoord;
	y[index] = ycoord;
	
}
void Scene::deletepicture(int index)
{
	if (index<0 || index > (maxnum-1) || imagearray[index] == NULL){
	cout<<"invalid index"<<endl;
	return;
	}
	delete imagearray[index];
	imagearray[index] = NULL;
}
Image * Scene::getpicture(int index) const
{
	if (index < 0||index > (maxnum-1)||imagearray[index]==NULL){
	cout<<"invalid index"<< endl;
	return NULL;
	}
	return imagearray[index];
}
Image Scene::drawscene()const
{
	int bigw =1;
	int bigh =1;
	//cout<<"0"<<endl;
	for (int i = 0; i <maxnum; i++){
	if (imagearray[i] !=NULL){
	if (x[i]+ (*imagearray[i]).width() > bigw) bigw = x[i]+(*imagearray[i]).width();
	if (y[i]+ (*imagearray[i]).height() > bigh) bigh = y[i]+(*imagearray[i]).height();
	}
	}
	//cout<<"!"<<endl;
	Image overall;
	overall.resize(bigw,bigh);
	//Image *overall = new Image();
	//overall->resize(bigw,bigh);
	for (int i = 0 ; i < maxnum ; i++){//imagearray
	if (imagearray[i]!=NULL){
	int imagew = (*imagearray[i]).width();
	int imageh = (*imagearray[i]).height();
	for (unsigned a = x[i] ; a< x[i]+imagew ;a++){//draw inmage
		for (unsigned b = y[i] ; b<y[i]+imageh; b++){
			RGBAPixel * sceneim = (overall)(a,b);
			RGBAPixel * imageim = (*imagearray[i])(a-x[i],b-y[i]);
			*sceneim = *imageim;
		}
	}
	}
	}

	return overall;
}
