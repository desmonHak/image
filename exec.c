#include "image.h"
#include <time.h>


int main()
{


    image.format = format_ASCII.P3;

    image.size_image[0] = 1024;
    image.size_image[1] = 576;

    image.number_colors = "255";

    image.name = "output";


    srand(time(NULL));
    unsigned char a, b, c;
    for(uint64_t i = 0; i <= image.size_image[0]*image.size_image[1]; i++){
        a = rand();
        b = rand();
        c = rand();
    	write_buffer(a%255-1, b%255-1,c%255-1);
    }

    //write_buffer(255, 0, 0);
    write_image();
    image_info(image.name);
    puts("Programa finalizado.\n");


}
