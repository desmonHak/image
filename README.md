# image:
esta cabezera permite la creacion de imagenes del tipo .pbm, .pgm y .ppm<br>
<br>
# Uso(ejemplo):<br>
git clone https://github.com/desmonHak/image.git<br>
gcc -Wall exec.c -o exec.bin<br>
./exec.bin<br>
<br>
# Uso en codigo:<br>

#include "image.h"<br>

int main(){<br>

    image.format = format_ASCII.P2;
    image.size_image[0] = 3;
    image.size_image[1] = 3;
    image.number_colors = "16";
    image.name = "ejemplo";
    
    for(int i = 0; i <= image.size_image[0]*image.size_image[1]; i++){
        write_buffer(i, i, 0);
    }

    write_image();
    image_info(image.name);

}<br>
<br>

primero importamos la cabezera. Ya hay una declaracion de la estructura _image llamada como image la variable, mediante esta estructura configuramos los parametros de la imagen.<br>
imagen.format, esta variable se usa para indicar en la imagen el formato que se usa y la extension que usar para el archivo, si no se asigna por default se usara la extension .ppm.<br>
Lista de los formatos y estructuras:<br>
 ![Alt text](https://github.com/desmonHak/image/blob/main/68747470733a2f2f6d656469612e6765656b73666f726765656b732e6f72672f77702d636f6e74656e742f75706c6f6164732f6e657470626d2e706e67?raw=true) <br>
Los formatos en ASCII son P1, P2 y P3, P1 para colores en blanco y negro mediante 1 y 0 en la funcion de write_buffer. P2 permite usar la escala monocromatica de colores negros, grises y blancos. P3 permite el uso de pixeles de colores en RGB.<br>
<br>
 image.size_image, este es un array de monodimensional que permite indicar el tamano en pixeles de la imagen, el primer parametro de la imagen perteneze a la cordenada X y el seguno a la cordenada Y, por tanto si se ingresa que el array es [3, 3] = 3 * 3 = 9 pixeles.<br>
<br>
image.number_colors, esta variables permite decir a la imagen el tamano de la paleta de colores que se usara, en el modo P1 y P4 se a de usar 2 para el 1 y 0 que son la posibilidades que se presenyta. En el caso de P2 y P3 se recomienda usar 255 lo cual da de resulta una paleta de colores de 255*255*255 lo cual equivale a una cantidad de 16 581 375 de colores distintos.<br>
<br>
image.name, este parametro permite indicar a la cabezera como se llamara la imagen a la hora de crearla.<br>
<br>
write_buffer, este funcion de retorno de tipo void permite crear un pixel tomando como primer argumento la cantidad de rojo. como segundo parametro la cantidad de verde. y como tercer parametro la cantidad de azul que contendra el pixel. Tras el uso de esta funcion la variable image.name es redefinida con el nombre del archio que se le asigno mas la extension que se le asigno.<br>
prototipo de la funcion:              void write_buffer(uint8_t RED, uint8_t GREN, uint8_t BLUE);<br>
<br>
write_image esta funcion de retorno void es usada para la escritura de la imagen final, tras la asignacion de datos con la funcion write_buffer. write_image usa los datos del buffer para plasmarlo en imagen. lo cual creara de salida la imagen con el nombre asignado en image.name con una de las extensiones dependiendo del tipo de formato que escogio. Como argumento recibe el nombre de la imagen, como hemos mencionado podemos usar la variable redefinda image.name la cual contiene despues de haber aplicado la funcion write_buffer el nombre real con la extension.<br>
<br>
image_info, esta funcion devuelve informacion basica de la imagen generada, prototipo:       void image_info(const char *file);<br>
<br>
# Ejemplo de ejecucion:<br>
 ![Alt text](https://raw.githubusercontent.com/desmonHak/image/main/Screenshot%20from%202021-05-01%2003-00-38.png)<br>
