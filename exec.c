#include "image.h"
#include <time.h>


int main()
{


    image.format = format_ASCII.P3;

    image.size_image[0] = 1000;
    image.size_image[1] = 1000;

    image.number_colors = "255";

    image.name = "output";


    srand(time(NULL));
    unsigned char a, b, c;
	a =  rand();
    srand(time(NULL));
    b = rand();
    srand(time(NULL));
    c = rand();
    for(uint64_t i = 0; i <= image.size_image[0]*image.size_image[1]; i++){
	write_buffer(a%255-1, b%255-1,c%255-1);
    }

    //write_buffer(255, 0, 0);
    write_image();
    image_info(image.name);
    puts("Programa finalizado.\n");
    

}
