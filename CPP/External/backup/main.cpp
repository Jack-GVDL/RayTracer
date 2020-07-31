#include <stdio.h>
#include "../inc/File_BMP.hpp"


int main() {
    File_BMP bmp;
    printf("Result: %i \n", bmp.read("../img/checkerboard.bmp") ? 1 : 0);

    printf("Sizeof: %i %i \n", sizeof(File_BMP_FileHeader), sizeof(File_BMP_InfoHeader));

    printf("Size: %i %i %i \n", 
    bmp.info_header.size, 
    bmp.info_header.width, 
    bmp.info_header.height);
    
    return 0;
}
