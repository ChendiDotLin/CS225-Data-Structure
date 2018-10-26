#include "image.h"

void Image::flipleft()
{
	int w = (*this).width();
	int h = (*this).height();
	for (int x =0; x<w/2; x++)
{
		for (int y = 0; y<h; y++)
	{
		RGBAPixel a = *(*this)(x,y);
		*(*this)(x,y) = *(*this)(w-1-x,y);
		*(*this)(w-1-x,y) = a;		
	}
}
	return;
}

void Image::adjustbrightness(int r, int g, int b)
{ 	
	 int w = (*this).width();
        int h = (*this).height();
for (int yi = 0; yi < h; yi++)
{	
        for (int xi = 0; xi<w; xi++)
        {
	int r1 = (*this)(xi,yi)->red;
	int g1 = (*this)(xi,yi)->green;
	int b1 = (*this)(xi,yi)->blue;
	if (r1+r > 255) {
	(*this)(xi,yi)->red = 255;}
	else if (r1+r < 0){
	(*this)(xi,yi)->red = 0;}
	else { (*this)(xi,yi)->red =r+r1;}
	if (g1+g > 255) {
        (*this)(xi,yi)->green = 255;}
        else if (g+g1 < 0){ 
        (*this)(xi,yi)->green = 0;} 
        else { (*this)(xi,yi)->green =g+g1;}
	if (b+b1 > 255) {
        (*this)(xi,yi)->blue = 255;}
        else if (b+b1 < 0){ 
        (*this)(xi,yi)->blue = 0;}
        else { (*this)(xi,yi)->blue =b+b1;}
	}
}
return;
}

void Image::invertcolors()
{
 int w = (*this).width();
        int h = (*this).height();
for (int yi = 0; yi < h; yi++)
{
        for (int xi = 0; xi<w; xi++)
        {
        (*this)(xi,yi)->red = 255-((*this)(xi,yi)->red);
        (*this)(xi,yi)->green = 255-((*this)(xi,yi)->green);
        (*this)(xi,yi)->blue = 255- ((*this)(xi,yi)->blue);
	}
}
return;
}


