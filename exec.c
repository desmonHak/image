
#include "image.h"

int main()
{

    char name[] = "output";
    image imagen = (image){
        .format = P1,
        .size_image = { .height = 10, .width = 10 },
        .number_colors = MAX_NUMBER_COLORS_P3_P6,
        .name = name
    };

    create_imagen_backfill(&imagen,(RGB){.blue = 0, .gren = 0, .red = 0});
    create_imagen_backfill_random(&imagen);
    
    write_image(&imagen);
    image_info(&imagen);
    free_data_image(&imagen);
    puts("Programa finalizado.\n");
}
