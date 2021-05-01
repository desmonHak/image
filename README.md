# image:
esta cabezera permite la creacion de imagenes del tipo .pbm, .pgm y .ppm<br>
<br>
# Uso(ejemplo):<br>
git clone https://github.com/desmonHak/image.git<br>
gcc -Wall exec.c -o exec.bin<br>
./exec.bin<br>
<br>
# Uso en codigo:<br>
#include "image.h"

int main()
{

    image.format = format_ASCII.P2;
    
    image.size_image[0] = 3;
    image.size_image[1] = 3;

    image.number_colors = "16";

    image.name = "ejemplo";

    for(int i = 0; i <= image.size_image[0]*image.size_image[1]; i++){
        write_buffer(i, i, 0);
    }

    write_image();

}

 ![Alt text](https://github.com/desmonHak/image/blob/main/68747470733a2f2f6d656469612e6765656b73666f726765656b732e6f72672f77702d636f6e74656e742f75706c6f6164732f6e657470626d2e706e67?raw=true) 
