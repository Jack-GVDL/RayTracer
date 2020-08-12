#include "../inc/RayTracer_Texture_MeanSampler.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// ...


// Static Data
// ...


// Operation Handling
void Texture_MeanSampler::setTexture(Texture *texture) {
	this->texture = texture;
}


Vec3f Texture_MeanSampler::_getPixel_(const Ray *ray) const {
	if (texture == nullptr) return Vec3f();

	// get point
	const double 	double_x 		= ray->getPosition()[0];
	const double 	double_y 		= ray->getPosition()[1];
	
	const int		int_x			= (int)(double_x);
	const int		int_y			= (int)(double_y);
	const int		int_x_increment	= int_x > 0 ? 1 : -1;
	const int		int_y_increment = int_y > 0 ? 1 : -1;

	// get pixel
	Vec3f result_1 = texture->getPixel(Vec3f(int_x,						int_y, 						0));
	Vec3f result_2 = texture->getPixel(Vec3f(int_x + int_x_increment,	int_y, 						0));
	Vec3f result_3 = texture->getPixel(Vec3f(int_x,						int_y + int_y_increment,	0));
	Vec3f result_4 = texture->getPixel(Vec3f(int_x + int_x_increment,	int_y + int_y_increment,	0));

	return (result_1 + result_2 + result_3 + result_4) / 4;
}


void Texture_MeanSampler::setPixel(const Vec3f &point, const Vec3f &pixel) {
}


// Static Function Implementation
// ...
