#ifndef __IMAGE_C__
#define __IMAGE_C__
#include "image.h"

#define DEBUG_ENABLE

static RGB generate_pixel_rand(void)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(RGB, generate_pixel_rand)
                        END_TYPE_FUNC_DBG);
#endif
    srand(time(NULL));
    return (RGB){.r = rand(), .g = rand(), .b = rand()};
}

void ignoreComments(FILE *fp)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, ignoreComments)
                    TYPE_DATA_DBG(FILE *, "fp = %p")
                        END_TYPE_FUNC_DBG,
                fp);
#endif
    int ch;
    while ((ch = fgetc(fp)) != EOF && isspace(ch))
        ;

    char line[100];
    if (ch == '#')
    {
        fgets(line, sizeof(line), fp);
        ignoreComments(fp);
    }
    else
        fseek(fp, -1, SEEK_CUR);
}

bool openPGM(PGMImage *pgm, const char *filename)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, openPGM)
                    TYPE_DATA_DBG(PGMImage *, "pgm = %p")
                        TYPE_DATA_DBG(const char *, "filename = %p")
                            END_TYPE_FUNC_DBG,
                pgm, filename);
#endif
    FILE *pgmfile = fopen(filename, "rb");
    if (pgmfile == NULL)
    {
        printf("File does not exist\n");
        return false;
    }
    // buscar formato de la imagen:
    ignoreComments(pgmfile);
    fscanf(pgmfile, "%s", pgm->pgmType);
    // buscar tamaño de la imagen:
    ignoreComments(pgmfile);
    fscanf(pgmfile, "%llu %llu", &(pgm->width), &(pgm->height));
    // cantidad de colores de la imagen:
    ignoreComments(pgmfile);
    fscanf(pgmfile, "%u", &(pgm->maxValue));
    // buscar resto de datos de la imagen
    ignoreComments(pgmfile);
    pgm->data = malloc(pgm->height * sizeof(unsigned char *));

    if (pgm->pgmType[1] == '5')
    {

        fgetc(pgmfile);

        for (int i = 0;
             i < pgm->height; i++)
        {
            pgm->data[i] = malloc(pgm->width * sizeof(unsigned char));

            if (pgm->data[i] == NULL)
            {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }

            fread(pgm->data[i], sizeof(unsigned char), pgm->width, pgmfile);
        }
    }

    fclose(pgmfile);

    return true;
}

void printImageDetails(PGMImage *pgm, const char *filename)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, printImageDetails)
                    TYPE_DATA_DBG(PGMImage *, "pgm = %p")
                        TYPE_DATA_DBG(const char *, "filename = '%s'")
                            END_TYPE_FUNC_DBG,
                pgm, filename);
#endif
    FILE *pgmfile = fopen(filename, "rb");

    char *ext = strrchr(filename, '.');

    if (!ext)
        printf("No extension found in file %s", filename);
    else
        printf("File format: %s\n", ext + 1);
    printf("PGM File type  : %s\n", pgm->pgmType);

    if (!strcmp(pgm->pgmType, "P2"))
        printf("PGM File Format: ASCII\n");
    else if (!strcmp(pgm->pgmType, "P5"))
        printf("PGM File Format: Binary\n");
    printf("Width of img   : %d px\n", pgm->width);
    printf("Height of img  : %d px\n", pgm->height);
    printf("Max Gray value : %d\n", pgm->maxValue);

    fclose(pgmfile);
}

bool image_info(image *imagen)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, image_info)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    if (imagen == NULL)
        return false;
    PGMImage *pgm = malloc(sizeof(PGMImage));

    if (imagen->full_name == NULL) create_full_name(imagen);
    printf("Name file : %s\n", imagen->full_name);
    if (openPGM(pgm, imagen->full_name))
        printImageDetails(pgm, imagen->full_name);
    return true;
}

bool init_data_image(image *imagen)
{
/*
 *
 *  Inicializar array de datos donde almacenar pixeles de la imagen
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, init_data_image)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    if (imagen == NULL)
        return false;
    // reservando columnas:
    imagen->data = (RGB **)calloc(imagen->size_image.height, sizeof(RGB *));
    for (max_size_img_length i = 0; i <= imagen->size_image.height; i++){
        // reservando filas:
        imagen->data[i] = (RGB *)calloc(imagen->size_image.width, sizeof(RGB));
    }
    return true;
}
bool free_data_image(image *imagen)
{
/*
 *
 *  liberar array de datos donde almacenar pixeles de la imagen
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, free_data_image)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->data == NULL)
        return false;
    for (max_size_img_length i = 0; i <= imagen->size_image.width; i++)
        // liberando filas:
        if (imagen->data[i] != NULL)
            free(imagen->data[i]);

    // liberando columnas:
    free(imagen->data);
    return true;
}

bool create_imagen_backfill(image *imagen, RGB pixel_backfill)
{
/*
 *
 *  Crear una imagen completa con el color del pixel especicado
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, create_imagen_backfill)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        TYPE_DATA_DBG(RGB, "pixel_backfill = %p")
                            END_TYPE_FUNC_DBG,
                imagen, pixel_backfill);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->data == NULL)
        init_data_image(imagen);
    for (max_size_img_length i = 0; i <= imagen->size_image.height; i++)
        for (max_size_img_length j = 0; j <= imagen->size_image.width; j++)
            imagen->data[i][j] = pixel_backfill;
    return true;
}
bool create_imagen_backfill_random(image *imagen)
{
/*
 *
 *  Crear una imagen completa con colores de pixel aleatorios
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO, \
                INIT_TYPE_FUNC_DBG(bool, create_imagen_backfill_random)\
                    TYPE_DATA_DBG(image *, "imagen = %p") \
                        END_TYPE_FUNC_DBG, \
                imagen);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->data == NULL)
        init_data_image(imagen);
    for (max_size_img_length i = 0; i <= imagen->size_image.height; i++)
        for (max_size_img_length j = 0; j <= imagen->size_image.width; j++)
            imagen->data[i][j] = generate_pixel_rand();
    return true;
}

bool write_pixel_RGB(image *imagen, RGB pixel)
{
/*
 *
 *  Escribir un pixel de en la imagen mediante la estructura RGB
 *  en una cordenada (x, y) de la imagen, modificando contador x y contador y
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, write_pixel_RGB)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        TYPE_DATA_DBG(RGB, "pixel = %p")
                            END_TYPE_FUNC_DBG,
                imagen, pixel);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->size_image.width < imagen->contador.contador_x)
    {
        // subir una columna si la fila ya fue llenada de pixeles
        imagen->contador.contador_y++;
        imagen->contador.contador_x = 0;
    }
    // error se esta intentando escribir mas datos de los especificados
    if (imagen->size_image.height < imagen->contador.contador_y)
        return false;

    imagen->data[imagen->contador.contador_x][imagen->contador.contador_y] = pixel;
    return true;
}

bool write_pixel_RGB_x_y(image *imagen, RGB pixel, max_size_img_length x, max_size_img_length y)
{
/*
 *
 *  Escribir un pixel de en la imagen mediante la estructura RGB
 *  en una cordenada (x, y) de la imagen sin modificar contadores
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, write_pixel_RGB)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        TYPE_DATA_DBG(RGB, "pixel = %p")
                            TYPE_DATA_DBG(max_size_img_length, "x = %llu")
                                TYPE_DATA_DBG(max_size_img_length, "y = %llu")
                                    END_TYPE_FUNC_DBG,
                imagen, pixel, x, y);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->size_image.width < x)
        return false; // la cordenada x supera el size establecido
    if (imagen->size_image.height < y)
        return false; // la cordenada y supera el size establecido
    imagen->data[x][y] = pixel;
    return true;
}

bool write_pixel(image *imagen, uint8_t RED, uint8_t GREN, uint8_t BLUE)
{
/*
 *
 *  Escribir un pixel de en la imagen mediante 3 valores de tipo
 *  uint8_t losc uales representa colores del pixel
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, write_pixel)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        TYPE_DATA_DBG(uint8_t, "RED = %u")
                            TYPE_DATA_DBG(uint8_t, "GREN = %u")
                                TYPE_DATA_DBG(uint8_t, "BLUE = %u")
                                    END_TYPE_FUNC_DBG,
                imagen, RED, GREN, BLUE);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->size_image.width < imagen->contador.contador_x)
    {
        // subir una columna si la fila ya fue llenada de pixeles
        imagen->contador.contador_y++;
        imagen->contador.contador_x = 0;
    }
    // error se esta intentando escribir mas datos de los especificados
    if (imagen->size_image.height < imagen->contador.contador_y)
        return false;

    imagen->data[imagen->contador.contador_x][imagen->contador.contador_y] = (RGB){
        .red = RED, .gren = GREN, .blue = BLUE};
    return true;
}
bool write_pixel_x_y(image *imagen, uint8_t RED, uint8_t GREN, uint8_t BLUE, max_size_img_length x, max_size_img_length y)
{
/*
 *
 *  Escribir un pixel de en la imagen mediante 3 valores de tipo
 *  uint8_t los cuales representa colores del pixel, en una cordenada (x, y)
 *  de la imagen sin modificar contadores
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, write_pixel_RGB)
                    TYPE_DATA_DBG(image *, "imagen = %p")
                        TYPE_DATA_DBG(uint8_t, "RED = %u")
                            TYPE_DATA_DBG(uint8_t, "GREN = %u")
                                TYPE_DATA_DBG(uint8_t, "BLUE = %u")
                                    TYPE_DATA_DBG(max_size_img_length, "x = %llu")
                                        TYPE_DATA_DBG(max_size_img_length, "y = %llu")
                                            END_TYPE_FUNC_DBG,
                imagen, RED, GREN, BLUE, x, y);
#endif
    if (imagen == NULL)
        return false;
    if (imagen->size_image.width < x)
        return false; // la cordenada x supera el size establecido
    if (imagen->size_image.height < y)
        return false; // la cordenada y supera el size establecido
    if (imagen == NULL)
        return false;
    imagen->data[x][y] = (RGB){
        .red = RED, .gren = GREN, .blue = BLUE};
    return true;
}

void assign_extension(image imagen)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, assign_extension)
                    TYPE_DATA_DBG(image, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    switch (imagen.format)
    {
    case P1:
    case P4:
        imagen.extension = pbm;
        break;
    case P2:
    case P5:
        imagen.extension = pgm;
        break;
    case P3:
    case P6:
        imagen.extension = ppm;
        break;
    default:
        break;
    }
}
bool is_pbm(image *imagen)
{
/*
 *
 *  Devuelve si la imagen es un archivo pbm
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, is_pbm)
                    TYPE_DATA_DBG(image*, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    return imagen->extension == pbm;
}

bool is_pgm(image *imagen)
{
/*
 *
 *  Devuelve si la imagen es un archivo pgm
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, is_pgm)
                    TYPE_DATA_DBG(image*, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    return imagen->extension == pgm;
}
bool is_ppm(image *imagen)
{
/*
 *
 *  Devuelve si la imagen es un archivo ppm
 *
 */
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, is_ppm)
                    TYPE_DATA_DBG(image*, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif
    return imagen->extension == ppm;
}

bool create_full_name(image *imagen){
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, create_full_name)
                    TYPE_DATA_DBG(image, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif

    imagen->full_name = (char *)malloc(
        sizeof(char) * strlen(imagen->name) +
        sizeof(char) * strlen(extensions_formats[imagen->extension]) +
        1);
    sprintf(imagen->full_name, "%s%s", imagen->name, extensions_formats[imagen->extension]);
    printf("Se a encontrado la extension correcta que solicito: %s\n", imagen->full_name);

    return true;
}

bool write_image(image *imagen)
{
#ifdef DEBUG_ENABLE
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, write_image)
                    TYPE_DATA_DBG(image, "imagen = %p")
                        END_TYPE_FUNC_DBG,
                imagen);
#endif

    bool status = true;

    if (imagen->full_name == NULL) 
        status = create_full_name(imagen); // si falla se retorna como error la funcion write_image
        if (!status) goto ret_write_image;

    FILE *pgmimg = fopen(imagen->full_name, "wb");

    uint64_t longitud = snprintf(NULL, 0,
                                 "%s\n"        // formato
                                 "%llu %llu\n" // tamaño de la imagen
                                 "%u\n",       // cantidad de colores de la imagen
                                 PX_formats[imagen->format],
                                 imagen->size_image.width, imagen->size_image.height,
                                 imagen->number_colors);      // obtener tamaño a reservar
    char *data = (char *)malloc(sizeof(char) * longitud + 1); // reservar tamaño
    sprintf(data,
            "%s\n"        // formato
            "%llu %llu\n" // tamaño de la imagen
            "%u\n",       // cantidad de colores de la imagen
            PX_formats[imagen->format],
            imagen->size_image.width, imagen->size_image.height,
            imagen->number_colors); // escribir datos en la memoria nueva
    fprintf(pgmimg, data);          // escribir datos en el archivo
    free(data);                     // liberar datos

    RGB example = (RGB){.r = 0, .g = 0, .b = 0};
    longitud = snprintf(NULL, 0,
                        "%u %u %u ",
                        example.r, example.g, example.b);
    data = (char *)malloc(sizeof(char) * longitud + 1); // reservar tamaño

    for (max_size_img_length i = 0; i <= imagen->size_image.width; i++)
    {
        for (max_size_img_length j = 0; j <= imagen->size_image.height; j++)
        {
            sprintf(data, "%u %u %u ",
                    imagen->data[i][j].r,
                    imagen->data[i][j].g,
                    imagen->data[i][j].b);
            fprintf(pgmimg, "%s", data);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);
    pgmimg = NULL;

    ret_write_image:
    return status;
}

#endif
