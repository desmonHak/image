#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#include "debug_c.h"

#define MAX_NUMBER_COLORS_P1_P4 1
#define MAX_NUMBER_COLORS_P2_P5 0xff
#define MAX_NUMBER_COLORS_P3_P6 0xff
#define MAX_NUMBER_COLORS MAX_NUMBER_COLORS_P3_P6

#define CALC_SIZE_IMG(imagen) imagen.size_image.height * imagen.size_image.width

typedef uint64_t max_size_img_length;



typedef enum formats {
    P1, P2, P3,
    P4, P5, P6
} formats;
typedef enum format_ASCII  { P1_A, P2_A, P3_A }      format_ASCII;
typedef enum format_BINARY { P4_B = P4, P5_B, P6_B } format_BINARY;

static const char PX_formats[6][3] = {
    "P1", "P2", "P3",
    "P4", "P5", "P6",
};


typedef enum extension {
    pbm, pgm, ppm
} extension;
static const char extensions_formats[3][5] = {
    ".pbm", ".pgm", ".ppm"
};

typedef union RGB
{
    struct { uint8_t red; uint8_t gren; uint8_t blue; };
    struct { uint8_t r;   uint8_t g;   uint8_t b;     };    
} RGB;

typedef struct image
{
    formats  format;     // formato de la imagen
    extension extension; // extension de la extension usada
    char *name;          // nombre de la imagen
    char *full_name;

    struct contador{
        max_size_img_length contador_x;  // x
        max_size_img_length contador_y;  // y
    } contador;

    RGB **data; // datos de la imagen = matriz x * y

    struct size_image{
        max_size_img_length width;  // x
        max_size_img_length height; // y
    } size_image; // size total = width * height == x * y

    #if   MAX_NUMBER_COLORS == 0xff
        uint8_t number_colors;
    #elif MAX_NUMBER_COLORS == 0xffff
        uint16_t number_colors;
    #elif MAX_NUMBER_COLORS == 0xffffffff
        uint32_t number_colors;
    #elif MAX_NUMBER_COLORS == 0xffffffffffffffff
        uint64_t number_colors;
    #else 
        #error "MAX_NUMBER_COLORS must be 0xff, 0xffff, 0xffffffff or 0xffffffffffffffff"
    #endif
} image;


typedef struct PGMImage
{
    char pgmType[3];
    unsigned char **data;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
} PGMImage;

static RGB generate_pixel_rand(void);
void ignoreComments(FILE *fp);
bool openPGM(PGMImage *pgm, const char *filename);
void printImageDetails(PGMImage *pgm, const char *filename);
bool image_info(image *imagen);
bool init_data_image(image *imagen);
bool free_data_image(image *imagen);
bool create_imagen_backfill(image *imagen, RGB pixel_backfill);
bool create_imagen_backfill_random(image *imagen);
bool write_pixel_RGB(image *imagen, RGB pixel);
bool write_pixel_RGB_x_y(image *imagen, RGB pixel, max_size_img_length x, max_size_img_length y);
bool write_pixel(image *imagen, uint8_t RED, uint8_t GREN, uint8_t BLUE);
bool write_pixel_x_y(image *imagen, uint8_t RED, uint8_t GREN, uint8_t BLUE, max_size_img_length x, max_size_img_length y);
void assign_extension(image imagen);
bool is_pbm(image *imagen);
bool is_pgm(image *imagen);
bool is_ppm(image *imagen);
bool create_full_name(image *imagen);
bool write_image(image *imagen);
void __attribute__((constructor)) __init_dfafad__();
void __attribute__((destructor)) __end_dfafad__();


#include "image.c"
#endif