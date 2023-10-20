#include <iostream>
#include <fstream>

#include "../include/vec3.h"
#include "../include/color.h"
#include "../include/ray.h"

int main()
{
	std::ofstream myfile;
  	myfile.open ("graphic_hw.ppm");


	// We define aspect ratio of the screen, as well as size
  	auto aspect_ratio = 16.0 / 9.0;

	int image_width 	= 800;
	int image_height 	= static_cast<int>(image_width / aspect_ratio);
	image_height 		= (image_height < 1) ? 1 : image_height;

	//We define the viewport size
	auto viewport_height = 2.0;
	auto viewport_width  = viewport_height * (static_cast<double>(image_width/image_height));


	myfile << "P3\n" << image_width << " " << image_height << "\n255\n";

	for(int j = image_height-1; j >= 0; j--)
	{
		for(int i = 0; i < image_width ; i++)
		{
			auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);

            write_color(myfile, pixel_color);
            
		}
	}
	
	myfile.close();

	return 0;
}