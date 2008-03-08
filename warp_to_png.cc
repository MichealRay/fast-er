#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>

#include <cvd/image_io.h>

#include <gvars3/instances.h>

#include "warp_to_png.h"

using namespace std;
using namespace CVD;
using namespace GVars3;
using namespace TooN;



void mmain(int argc, char** argv)
{
	GUI.parseArguments(argc, argv);

	ImageRef size = GV3::get<ImageRef>("size", ImageRef(768,576), 1);

	
	Image<Rgb<unsigned short> > si(size);

	for(int y=0; y < size.y; y++)
		for(int x=0; x < size.x; x++)
		{
			float f1, f2;
			cin >> f1 >> f2;

			if(!cin.good())
			{
				cerr << "EOF!\n";
				exit(1);
			}

			if(f1 < -5 || f1 > 1000)
			{
				cerr << "Bad value at " << x << ", " << y << ": " << f1;
				exit(2);
			}

			if(f2 < -5 || f2 > 1000)
			{
				cerr << "Bad value at " << x << ", " << y << ": " << f2;
				exit(2);
			}

			Rgb<unsigned short> o;

			o.red = (unsigned short) ((SHIFT + f1)*MULTIPLIER + .5);
			o.green = (unsigned short) ((SHIFT + f2)*MULTIPLIER + .5);
			o.blue = 0;

			si[y][x] = o;
		}

	img_save(si, cout, ImageType::PNG);

}

int main(int argc, char** argv)
{
	try
	{
		mmain(argc, argv);
	}
	catch(Exceptions::All e)
	{
		cerr << "Error: " << e.what << endl;
	}	
}