#include "image.h"

int main()
{

    image.format = format_ASCII.P1;

    image.size_image[0] = 10;
    image.size_image[1] = 10;

    image.number_colors = "255";

    image.name = "output";

    for(int i = 0; i <= image.size_image[0]*image.size_image[1]; i++){
        write_buffer(i, i, 115);
    }

    write_buffer(255, 0, 0);
    write_image();
    image_info(image.name);
    puts("Programa finalizado.\n");

}
