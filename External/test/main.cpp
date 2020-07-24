#include <stdio.h>
#include "../inc/File_BMP.hpp"


// Static Inline Function Prototype
static inline void printMainArg(int argc, char *argv[]);
static inline void printBMPData(File_BMP *bmp);


// Operation
int main(int argc, char *argv[]) {
    // print argv
    // printMainArg(argc, argv);

    // read bmp file
    if (argc < 2) {
        printf("Error: invalid bmp read path \n");
        return 0;
    }

    File_BMP file_bmp_1 = File_BMP();
    bool result = file_bmp_1.read(argv[1]);

    printf("Read BMP: ");
    printf(result ? "Success" : "Fail");
    printf("\n");

    // print bmp data
    // printBMPData(&file_bmp_1);

    // filtering

    // write bmp file
    if (argc < 3) {
        printf("Error: invalid bmp write path \n");
        return 0;
    }

    result = file_bmp_1.write(argv[2]);

    printf("Write BMP: ");
    printf(result ? "Success" : "Fail");
    printf("\n");
    
    return 0;
}


// Static Inline Function Implementation
static inline void printMainArg(int argc, char *argv[]) {
    printf("Argc: %i \n", argc);

    printf("Argv\n");
    for (int i = 0; i < argc; i++) printf("%s \n", argv[i]);
    printf("\n");
}


static inline void printBMPData(File_BMP *bmp) {
    // get file info
    std::vector<uint8_t> *image_data = &(bmp->data);
    printf("Size: %i \n",               image_data->size());
    printf("Width, Height: %i / %i \n", bmp->info_header.width, bmp->info_header.height);
    printf("Compression: %i \n",        bmp->info_header.compression);
    printf("Bit Count: %i \n",          bmp->info_header.bit_count);

    // somehow print the image data
    const int width = 10;
    for (int i = 0; i < width; i++) {
        printf("R: %i ", (*image_data)[i * 3 + 0]);
        printf("G: %i ", (*image_data)[i * 3 + 1]);
        printf("B: %i ", (*image_data)[i * 3 + 2]);
        printf("\n");
    }
    printf("\n");
}
