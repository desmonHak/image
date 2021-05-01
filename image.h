#if !defined(__IMAGE__)
#define _tamano 

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define _P1 "P1"
#define _P4 "P4"
#define _P2 "P2"
#define _P5 "P5"
#define _P3 "P3"
#define _P6 "P6"

uint32_t contador;

typedef struct RGB
{

    const uint8_t red;
    const uint8_t gren;
    const uint8_t blue;

} RGB;

typedef struct _image
{
    char *format;
    char *name;
    uint32_t size_image[2];
    char* number_colors;
    RGB *data[];
} _image;

typedef struct _format_ASCII
{
    const char *P1;
    const char *P2;
    const char *P3;
} _format_ASCII;
typedef struct _format_BINARY
{
    const char *P4;
    const char *P5;
    const char *P6;
} _format_BINARY;

const _format_ASCII format_ASCII = {_P1, _P2, _P3};
const _format_BINARY format_BINARY = {_P4, _P5, _P6};
_image image;
typedef struct PGMImage
{
    char pgmType[3];
    unsigned char **data;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
} PGMImage;

void ignoreComments(FILE *fp)
{
    int ch;
    char line[100];

    while ((ch = fgetc(fp)) != EOF && isspace(ch))
        ;

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
    FILE *pgmfile = fopen(filename, "rb");
    if (pgmfile == NULL)
    {
        printf("File does not exist\n");
        return false;
    }

    ignoreComments(pgmfile);
    fscanf(pgmfile, "%s", pgm->pgmType);

    if (strcmp(pgm->pgmType, "P5"))
    {
        fprintf(stderr, "Wrong file type!\n");
        exit(EXIT_FAILURE);
    }

    ignoreComments(pgmfile);

    fscanf(pgmfile, "%d %d", &(pgm->width), &(pgm->height));

    ignoreComments(pgmfile);

    fscanf(pgmfile, "%d", &(pgm->maxValue));
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

void image_info(const char *file)
{
    PGMImage *pgm = malloc(sizeof(PGMImage));
    printf("ip file : %s\n", file);
    if (openPGM(pgm, file))
        printImageDetails(pgm, file);
}

void write_buffer(uint8_t RED, uint8_t GREN, uint8_t BLUE)
{
    image.data[contador] = RED;
    contador++;
    image.data[contador] = GREN;
    contador++;
    image.data[contador] = BLUE;
    contador++;
}

const char *concatenacion(const char *texto1, const char *texto2)
{
    char *FinallyText = malloc((strlen(texto1) + strlen(texto2) + 1) * sizeof(char));
    for (register int i = 0; i <= strlen(texto1); i++)
    {
        FinallyText[i] = (char)texto1[i];
    }
    for (register int i = strlen(texto1); i <= strlen(texto1) + strlen(texto2); i++)
    {
        FinallyText[i] = texto2[i - strlen(texto1)];
    }

    return FinallyText;
}

void write_image()
{
    if (image.format == _P1 || image.format == _P4)
    {
        image.name = concatenacion(image.name, ".pbm");
    }
    else if (image.format == _P2 || image.format == _P5)
    {
        image.name = concatenacion(image.name, ".ppm");
    }
    else if (image.format == _P3 || image.format == _P6)
    {
        image.name = concatenacion(image.name, ".ppm");
    }
    else
    {
        image.name = concatenacion(image.name, ".ppm");
    }
    printf("Se a encontrado la extension correcta que solicito: %s\n", image.name);

    FILE *pgmimg = fopen(image.name, "wb");

    fprintf(pgmimg, concatenacion(concatenacion("", image.format), "\n"));
    char str[5];
    sprintf(str, "%d", image.size_image[0]);
    char _str[5];
    sprintf(_str, "%d", image.size_image[1]);

    fprintf(pgmimg, concatenacion(concatenacion(concatenacion(concatenacion("", str), " "), _str), "\n"));
    fprintf(pgmimg, concatenacion(concatenacion(" ", image.number_colors), "\n"));
    uint8_t c = 0;
    for (int i = 0; i <= (image.size_image[0] * image.size_image[1] * 3-1); i++)
    {
        if (c == 3)
        {
            fprintf(pgmimg, " ");
            c = 0;
        }
        char __str[3];
        sprintf(__str, "%d", image.data[i]);
        fprintf(pgmimg, concatenacion(" ", __str));
        c++;
    }
    fprintf(pgmimg, "\n");
    fclose(pgmimg); //*/
    pgmimg = NULL;
}

#endif