#include <iostream>
#include <fstream>

#include "../include/vec3.h"
#include "../include/color.h"

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
			vec3 col( float(i) / float(nx), float(j) / float(ny) , 0.2);

			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;

			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);

			//std::cout << i << " | "<< j<< "\n";
			myfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	myfile.close();

	return 0;
}