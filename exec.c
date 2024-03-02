
#include "image.h"

int main()
{

    char name[] = "output";
    image imagen = (image){
        .format = P2,
        .size_image = { .height = 10, .width = 10 },
        .number_colors = MAX_NUMBER_COLORS_P2_P5,
        .name = name
    };

    create_imagen_backfill(&imagen,(RGB){.blue = 0, .gren = 0, .red = 0});
    create_imagen_backfill_random(&imagen);
    
    write_image(&imagen);
    image_info(&imagen);
    free_data_image(&imagen);

    char name2[] = "output2";
    imagen = (image){
        .format = P3,
        .size_image = { .height = 50, .width = 50 },
        .number_colors = MAX_NUMBER_COLORS_P3_P6,
        .name = name2
    };
    create_imagen_backfill(&imagen,(RGB){.blue = 0, .gren = 0, .red = 0});
    for (max_size_img_length i = 0; i <= imagen.size_image.height; i++)
        for (max_size_img_length j = 0; j <= imagen.size_image.width; j++)
            write_pixel_RGB(&imagen, generate_pixel_rand());
    write_image(&imagen);
    image_info(&imagen);
    free_data_image(&imagen);

    puts("Programa finalizado.\n");
}
