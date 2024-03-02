#include "image.h"

int main()
{
    char name[] = "output"; // nombre de la imagen de salida
    
    image imagen = (image){ 
        .format = P1,       // formato
        .size_image = { .height = 1024, .width = 1024 }, // tamaño de la imagen
        .number_colors = MAX_NUMBER_COLORS_P1_P4, // numero de colores
        .name = name // nombre de la imagen
    };

    create_imagen_backfill(&imagen,(RGB){.blue = 0, .gren = 0, .red = 0}); // crear una imagen completa de blanco
    create_imagen_backfill_random(&imagen); // modiciar la imagen a colores aleatorios
    
    write_image(&imagen); // escribir la imagen
    image_info(&imagen);  // obbtener informacion de la imagen escritra
    free_data_image(&imagen); // liberar la imagen
    puts("Programa finalizado.\n");
}
