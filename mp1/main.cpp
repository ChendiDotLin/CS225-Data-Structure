
#include "rgbapixel.h"
#include "png.h"

int main()
{
PNG input = PNG ("in.png");
PNG output = PNG (input.width(), input.height());
 for (size_t yi = 0; yi < input.height(); yi++)
{
        for (size_t xi = 0; xi < input.width();xi++){
		output(output.width()-xi-1,output.height()-yi-1)->red = input(xi,yi)->red;	
		 output(output.width()-xi-1,output.height()-yi-1)->green = input(xi,yi)->green;
		 output(output.width()-xi-1,output.height()-yi-1)->blue = input(xi,yi)->blue;
	
	}
}
	output.writeToFile("out.png");
    return 0;
}
