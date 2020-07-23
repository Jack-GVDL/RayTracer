// Created by Jack Tse on 2020/07/20
// Follow TrackingStandard 0.1
//
// Log
// 2020/07/20   initial update


#ifndef FILE_BMP_HPP
#define FILE_BMP_HPP


#include <stdint.h>
#include <vector>


// Define
// ...


// Typedef
// ...


// Enum
// ...


// Data Structure
// reference
// 1. https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/
#pragma pack(push, 1)
struct File_BMP_FileHeader {
	uint16_t	file_type			= 0x4D42;	// file type always BM which is 0x4D42
	uint32_t	file_size			= 0;		// size of the file (in bytes)
	uint16_t	reserved_1			= 0;
	uint16_t	reserved_2			= 0;
	uint32_t	offset_data			= 0;		// start position of pixel data (bytes from the beginning of the file)
};
#pragma pack(pop)


#pragma pack(push, 1)
struct File_BMP_InfoHeader {
	uint32_t	size				= 0;		// size of this header
	int32_t		width				= 0;		// width of bitmap in pixel
	int32_t		height				= 0;		// height of bitmap in pixel

	uint16_t	plane				= 1;
	uint16_t	bit_count			= 0;
	uint32_t	compression			= 0;
	uint32_t	size_image			= 0;
	int32_t		x_pixel_per_meter	= 0;
	int32_t		y_pixel_per_meter	= 0;
	uint32_t	color_used			= 0;
	uint32_t	color_important		= 0;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct File_BMP_ColorHeader {
	uint32_t	mask_red			= 0x00ff0000;	// bit mask for the red channel
	uint32_t	mask_green			= 0x0000ff00;	// bit mask for the green channel
	uint32_t	mask_blue			= 0x000000ff;	// bit mask for the blue channel
	uint32_t	mask_alpha			= 0xff000000;	// bit mask for the alpha channel
	uint32_t	color_space_type	= 0x73524742;	// default "sRGB" (0x73524742)
	uint32_t	unused[16]			= {0};          // unused data for sRGB color space
};
#pragma pack(pop)



class File_BMP {
	// Data
	public:
		File_BMP_FileHeader		file_header;
		File_BMP_InfoHeader		info_header;
		File_BMP_ColorHeader	color_header;
		std::vector<uint8_t>	data;

	// Operation
	public:
		bool	read	(const char *file);
		bool	write	(const char *file);
};


// Macro Function
// ...


// Inline Function Implementation
// ...


#endif  // FILE_BMP_HPP
