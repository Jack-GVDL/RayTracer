#include <fstream>
#include "../inc/File_BMP.hpp"


// Define
// ...


// Static Data
// ...


// Static Function Prototype
static inline bool		check_color_header	(File_BMP_ColorHeader *header);
static inline uint32_t	make_stride_aligned	(uint32_t stride, uint32_t align_stride);


// Operation Handling
bool File_BMP::read(const char *f) {
	// open file
	std::ifstream file(f, std::ios::binary);
	if (!file.is_open()) return false;

	// read file header
	file.read((char*)(&file_header), sizeof(File_BMP_FileHeader));
	if (file_header.file_type != 0x4D42) return false;

	// read info header
	file.read((char*)(&info_header), sizeof(File_BMP_InfoHeader));

	if (info_header.bit_count == 32) {
		// check if the file has bit mask color information
		if (info_header.size < sizeof(File_BMP_InfoHeader) + sizeof(File_BMP_ColorHeader)) return false;
		
		// get the color mask and check if valid or not
		// valid:pixel data stored as BGRA and color space type is sRGB
		file.read((char*)(&color_header), sizeof(File_BMP_ColorHeader));
		if (!check_color_header(&color_header)) return false;
	}

	// read pixel data
	// jump to pixel data location
	file.seekg(file_header.offset_data, file.beg);

	// adjust the header field for output
	// some editor will put extra info in the image
	// we only save the header and the data
	if (info_header.bit_count == 32) {
		info_header.size		= sizeof(File_BMP_InfoHeader) + sizeof(File_BMP_ColorHeader);
		file_header.offset_data = sizeof(File_BMP_FileHeader) + sizeof(File_BMP_InfoHeader) + sizeof(File_BMP_ColorHeader);
	} else {
		info_header.size		= sizeof(File_BMP_InfoHeader);
		file_header.offset_data	= sizeof(File_BMP_FileHeader) + sizeof(File_BMP_InfoHeader);
	}
	file_header.file_size = file_header.offset_data;

	if (info_header.height < 0) return false;

	data.resize(info_header.width * info_header.height * info_header.bit_count / 8);

	// check if need to take into account row padding
	//
	// col 1 | col 2 | ...
	//
	// row 1
	// row 2
	// ...
	if (info_header.width % 4 == 0) {
		file.read((char*)data.data(), data.size());
		file_header.file_size += data.size();

	} else {
		uint32_t	row_stride	= info_header.width * info_header.bit_count / 8;
		uint32_t	new_stride	= make_stride_aligned(row_stride, 4);
		std::vector<uint8_t> padding_row(new_stride - row_stride);

		for (int y = 0; y < info_header.height; y++) {
			file.read((char*)(data.data() + row_stride * y), row_stride);
			file.read((char*)padding_row.data(), padding_row.size());
		}
		file_header.file_size += data.size() + info_header.height * padding_row.size();

	}

	// close the file
	file.close();

	return true;
}


bool File_BMP::write(const char *file) {
	return false;
}


// Static Function Implementation
static inline bool check_color_header(File_BMP_ColorHeader *header) {
	File_BMP_ColorHeader expected_color_header;
	if (
		expected_color_header.mask_red		!= header->mask_red		||
		expected_color_header.mask_blue		!= header->mask_blue	||
		expected_color_header.mask_green	!= header->mask_green	||
		expected_color_header.mask_alpha	!= header->mask_alpha)			return false;

	if (expected_color_header.color_space_type != header->color_space_type)	return false;

	return true;
}


static inline uint32_t make_stride_aligned(uint32_t stride, uint32_t align_stride) {
	uint32_t new_stride = stride;
	while (new_stride % align_stride != 0) new_stride++;
	return new_stride;
}
