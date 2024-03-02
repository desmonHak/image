
#include "image.h"

int main()
{
    /*
     *
     *  Crear 6 imagenes en los 6 formatos distintos
     *  con el mismo relleno
     * 
     */


    uint64_t longitud = snprintf(NULL, 0, "output_%u", 0);
    char *data;
    debug_malloc( char *, data, sizeof(char) * longitud + 1);
    
    sprintf(data, "output_%u", 1);
    image imagen1 = (image){
        .size_image = { .height = 1024, .width = 300 },
        .format = P1,
        .number_colors = MAX_NUMBER_COLORS_P1_P4,
        .name = data
    };
    // crear una imagen en negro:
    create_imagen_backfill(&imagen1,(RGB){.blue = 0, .gren = 0, .red = 0});

    // crear una imagen de pixeles random:
    create_imagen_backfill_random(&imagen1);
    if (!write_image(&imagen1)) printf("error %s\n", data);
    image_info(&imagen1);
    

    sprintf(data, "output_%u", 2);
    image imagen2 = (image){
        .size_image = imagen1.size_image, // tamaño de la imagen 1
        .format = P2,
        .number_colors = MAX_NUMBER_COLORS_P2_P5,
        .name = data,
        .data = imagen1.data // usar los datos de la imagen1
    };
    if (!write_image(&imagen2)) printf("error %s\n", data);
    image_info(&imagen2);

    sprintf(data, "output_%u", 3);
    image imagen3 = (image){
        .size_image = imagen1.size_image,
        .format = P3,
        .number_colors = MAX_NUMBER_COLORS_P3_P6,
        .name = data,
        .data = imagen1.data // usar los datos de la imagen1
    };
    if (!write_image(&imagen3)) printf("error %s\n", data);
    image_info(&imagen3);

    sprintf(data, "output_%u", 4);
    image imagen4 = (image){
        .size_image = imagen1.size_image,
        .format = P4,
        .number_colors = MAX_NUMBER_COLORS_P1_P4,
        .name = data,
        .data = imagen1.data // usar los datos de la imagen1
    };
    if (!write_image(&imagen4)) printf("error %s\n", data);
    image_info(&imagen4);


    sprintf(data, "output_%u", 5);
    image imagen5 = (image){
        .size_image = imagen1.size_image,
        .format = P5,
        .number_colors = MAX_NUMBER_COLORS_P2_P5,
        .name = data,
        .data = imagen1.data // usar los datos de la imagen1
    };
    if (!write_image(&imagen5)) printf("error %s\n", data);
    image_info(&imagen5);


    sprintf(data, "output_%u", 6);
    image imagen6 = (image){
        .size_image = imagen1.size_image,
        .format = P6,
        .number_colors = MAX_NUMBER_COLORS_P3_P6,
        .name = data,
        .data = imagen1.data // usar los datos de la imagen1
    };
    if (!write_image(&imagen6)) printf("error %s\n", data);
    image_info(&imagen6);


    free_data_image(&imagen1);
    puts("Programa finalizado.\n");
}
