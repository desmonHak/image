#include "image.h"
#include <time.h>

int radnom(){

        srand(time(NULL));
	return rand();
}

int main()
{


    image.format = format_ASCII.P3;

    image.size_image[0] = 1000;
    image.size_image[1] = 1000;

    image.number_colors = "255";

    image.name = "output";

    for(uint64_t i = 0; i <= image.size_image[0]*image.size_image[1]; i++){
	write_buffer(random()%255-1, random()%255-1,random()%255-1);
    }

    //write_buffer(255, 0, 0);
    write_image();
    image_info(image.name);
    puts("Programa finalizado.\n");
    

}
