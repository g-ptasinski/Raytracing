#include <iostream>
#include <fstream>

#include "../include/vec3.h"
#include "../include/color.h"
#include "../include/ray.h"

int main()
{
	std::ofstream myfile;
  	myfile.open ("graphic_hw.ppm");

	int nx = 800;
	int ny = 600;

	myfile << "P3\n" << nx << " " << ny << "\n255\n";

	for(int j = ny-1; j >= 0; j--)
	{
		for(int i = 0; i < nx ; i++)
		{
			auto pixel_color = color(double(i)/(nx-1), double(j)/(ny-1), 0);

            write_color(myfile, pixel_color);
            
		}
	}
	
	myfile.close();

	return 0;
}