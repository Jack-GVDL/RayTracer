#include "../inc/RayTracer_DynamicSkeleton.hpp"
#include "../inc/RayTracer_Dynamic_Surface.hpp"


// Define
// ...


// Typedef
// ...


// Static Function Prototype
// skeleton
// Dynamic_constructTypeSkeleton(constant,	Surface,	Surface);
Dynamic_constructTypeSkeleton(bmp,		Surface,	Surface_BMP);

// table
static int			config_bmp_setPath					(void *object, uint8_t *data, uint32_t size);
static int			interact_bmp_convertToTexture		(void *object, void* *list, uint32_t size);

// Static Data
// ...


// Operation Handling
void RayTracer_Dynamic_Surface_init(std::vector<Dynamic_ContainerType*> *type_list) {
	// table
	table_config_bmp.push_back(		config_bmp_setPath				);
	table_interact_bmp.push_back(	interact_bmp_convertToTexture	);

	// create type
	Dynamic_ContainerType *type;

	// Dynamic_addType(constant,	constant,	type_list);
	Dynamic_addType(bmp,	bmp,	type_list);
}


void RayTracer_Dynamic_Surface_info() {
}


void RayTracer_Dynamic_Surface_del() {
}


// Static Function Implementation
// table
static int config_bmp_setPath(void *object, uint8_t *data, uint32_t size) {
	Surface_BMP	*surface	= (Surface_BMP*)object;
	const char	*path		= (const char*)data;

	// load bmp
	File_BMP *bmp = new File_BMP();
	if (!bmp->read(path)) {
		delete bmp;
		return -1;
	}

	surface->setBMP(bmp);
	return 0;
}


static int interact_bmp_convertToTexture(void *object, void* *list, uint32_t size) {
	Surface_BMP		*surface	= (Surface_BMP*)object;
	Texture_Image	*texture	= (Texture_Image*)(list[0]);

	if (!surface->convertToTexture(texture)) return -1;
	return 0;
}
