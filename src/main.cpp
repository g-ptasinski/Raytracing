#include <iostream>
#include <fstream>

#include "../include/vec3.h"
#include "../include/color.h"
#include "../include/ray.h"
#include "../include/hittable.h"

double hit_sphere(const point3& center, double radius, const ray& r) 
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0) 
    {
        return -1.0;
    } 
    else 
    {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

color ray_color(const ray& r) 
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main()
{
	std::ofstream myfile;
  	myfile.open ("graphic_hw.ppm");

	// We define aspect ratio of the screen, as well as size
  	auto aspect_ratio 	= 16.0 / 9.0;

	int image_width 	= 1368;
	int image_height 	= static_cast<int>(image_width / aspect_ratio);
	image_height 		= (image_height < 1) ? 1 : image_height;

	//We define camera parameters and the viewport size
	auto focal_length 	= 1.0;
    auto viewport_height= 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center 	= point3(0, 0, 0);

    // Calculate vectors across horziontal and vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate delta vectors pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    //Location of upper left pixel
    auto viewport_upper_left 	= camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc 			= viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);    

    //Render itself
	myfile << "P3\n" << image_width << " " << image_height << "\n255\n";

	for(int j = image_height-1; j >= 0; j--)
	{
		for(int i = 0; i < image_width ; i++)
		{
			auto pixel_center 	= pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
			auto ray_direction 	= pixel_center - camera_center; 
			ray r(camera_center, ray_direction);

			auto pixel_color 	= ray_color(r);
            write_color(myfile, pixel_color);        
		}
	}
	
	myfile.close();

	return 0;
}