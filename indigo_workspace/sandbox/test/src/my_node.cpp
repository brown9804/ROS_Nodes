//
//  main.c
//  visionPorComputador_Prog_Ref_No1
//
//  Created by Dr. Geovanni Martinez on 9/27/17.
//  Copyright © 2017 Dr. Geovanni Martinez. All rights reserved.
//

//Este programa lee una imagen RGB en formato BMP, obtiene la componente de
//intensidad correspondiente, asi como dubuja un segmento lineal y un circulo
//sobre ella. Los resultados se almacenan en archivos en formato YUV400 y BMP.
//Las dimensiones de las imagenes, el directorio de entrada, el directorio de
//salida, y los parametros para dibujar el segmento lineal y el circulo se
//obtienen de un archivo de parametros de control.

//***
//***Incluir aqui los headers (archivos terminados en .h) que
//***contienen los prototipos de las funciones de otras librerias que
//***usaremos en nuestro programa
//***

//Se incluyó el siguiente header de la biblioteca
//estanda de C para operaciones de entrada y salida
#include <stdio.h>

//Se incluyó el siguiente header de la biblioteca
//estanda de C para gestion de memoria dinamica,
//control de procesos y otras
#include <stdlib.h>

//Se incluyo el siguiente header debido a que usaremos
//funciones matematicas
#include <math.h>

//Se incluyó debido a que se usa la funcion strcpy
#include <string.h>

//***
//***Insertar aqui los prototipos de nuestras funciones
//***

void geoLeerParametrosDeControlDeArchivoDeTexto();
void readRGBImageFromBMPFile(char *filename);
void geoInsertYourCodeHere();
void geoGetIntensityImageFromRGBimage();
void geoDrawALinealSegmentOnIntensityImage();
void geoDrawACircleOnIntensityImage();
void geoSaveIntensityImageIn_YUV400_file(unsigned char *pIntensity, char* filename);
void geoChangeImageCoordinateSystemFromLowerLeftSideToUpperLeftSide(unsigned char *pIntensity, unsigned char *presult);
int SaveIntensityImageIn_BMP_file(unsigned char *pintensity, char *filename);
int SaveRGBImageIn_BMP_file(unsigned char *prgb, char *filename);

//***
//***Insertar aqui las definiciones de nuestros contenedores
//***(estructuras)
//***

//La siguiente definicion describe el contenedor que
//usaremos para guardar los parametros de control
//de flujo del programa

//Contenedor de imagenes
struct pInputImage
{
    int width;  //ancho de imagenes
    int height; //alto de imagenes
    unsigned char *prgb; //imagen rgb de entrada
    unsigned char *pintensity; //imagen de intensidad
    unsigned char *pthresholdedIntensity; //imagen resultado
    unsigned char *pdrawnLinealSegmentOnIntensity; //imagen resultado
    unsigned char *pdrawnCircleOnIntensity; //imagen resultado
};

//Contenedor de parametros de control
struct contenedor_de_parametros_de_control
{
    int width; //ancho de las imagenes
    int height; //alto de las imagenes
    char pathAndInputImageFileName[256]; //directorio de entrada
    char pathOfOutputDirectory[256]; //directorio de salida
    int xi; //(xi,yi) punto inicial del segmento lineal
    int yi;
    int xf; //(xf,yf) punto final del segmento lineal
    int yf;
    int cx; //(cx,cy) centro del circulo
    int cy;
    int r; //radio del circulo
};


//***
//***Insertar aqui las definiciones de variables globales,
//***que son aquellas variables que se podran acceder desde
//***cualquier funcion dentro de este archivo
//***

//El siguiente puntero global apuntara al contenedor que
//usaremos para guardar los valores de control de flujo
//del programa que se leeran de un archivo de texto

struct contenedor_de_parametros_de_control *p_parametros;

//El siguiente puntero global apuntara al contenedor que
//usaremos para guardar las imagenes que utilizaremos
//en el programa

struct pInputImage *pInputImage;

//La siguiente variable global se usara como contador
//el numero de datos leidos

int numeroDeDatosLeidos=0;

//***
//***Insertar aqui las constantes del programa
//***

#define PI 3.141592652

//Inicio de programa principal
int main()
{
    //definición de variables locales
    int i; //contador
        int width, height;

    //Despliegue de autoría en el terminal
    printf("****************************************************************************\n");
    printf("** ROSS node #1                                                           **\n");
    printf("** YUV, linea, circulo en output                                          **\n");
    printf("** Programa de referencia tomado del Prof. Dr.-Ing. Geovanni Martínez     **\n");
    printf("** IE-0449 Vision por Computador                                          **\n");
    printf("** I-2019                                                                 **\n");
    printf("****************************************************************************\n");
    printf("\n");

    //Reservando memoria de contenedor p_parametros
    p_parametros = (struct contenedor_de_parametros_de_control *)malloc(sizeof(struct contenedor_de_parametros_de_control));

    //Esta función lee los parámetros de control de flujo del
    //programa desde un archivo de texto y los almacena en el
    //contenedor p_parametros
    geoLeerParametrosDeControlDeArchivoDeTexto();

    //Reservando memoria para la estructura pInputImage
    pInputImage = (struct pInputImage *)malloc(sizeof(struct pInputImage));
    pInputImage->width=p_parametros->width;
    pInputImage->height=p_parametros->height;

    //Reservando e inicializando la memoria de las imagenes del contenedor pInputImage
    width=p_parametros->width;
    height=p_parametros->height;
    pInputImage->prgb = (unsigned char*)malloc(sizeof(unsigned char)*width*height*3);
    pInputImage->pintensity =(unsigned char*)malloc(sizeof(unsigned char)*width*height);
    pInputImage->pthresholdedIntensity =(unsigned char*)malloc(sizeof(unsigned char)*width*height);
    pInputImage->pdrawnLinealSegmentOnIntensity =(unsigned char*)malloc(sizeof(unsigned char)*width*height);
    pInputImage->pdrawnCircleOnIntensity =(unsigned char*)malloc(sizeof(unsigned char)*width*height);
    //Cada píxel se inicializa en cero
    for (i=0;i<width*height*3;i++) pInputImage->prgb[i]=0;
    for (i=0;i<width*height;i++) {
        pInputImage->pintensity[i]=0;
        pInputImage->pthresholdedIntensity[i]=0;
        pInputImage->pdrawnLinealSegmentOnIntensity[i]=0;
        pInputImage->pdrawnCircleOnIntensity[i]=0;
    }

    //Leyendo la imagen RGB de archivo en formato BMP
    readRGBImageFromBMPFile(p_parametros->pathAndInputImageFileName);

    //Insertar codigo en esta funcion
    geoInsertYourCodeHere();

    //Liberando memoria de los contenedores e imagenes
    free(pInputImage->prgb);
    free(pInputImage->pintensity);
    free(pInputImage->pthresholdedIntensity);
    free(pInputImage->pdrawnLinealSegmentOnIntensity);
    free(pInputImage->pdrawnCircleOnIntensity);
    free(pInputImage);
    free(p_parametros);

    return 0;
}
//Fin de programa principal

//*******************************************************
//*******************************************************
//***** Introduzca aqui sus funciones               *****
//*******************************************************
//*******************************************************

//Esta funcion es para insertar nuevo codigo.
void geoInsertYourCodeHere()
{
    char pathAndFileName[256];
    strcpy(pathAndFileName,"output/rgb.bmp");
    SaveRGBImageIn_BMP_file(pInputImage->prgb, pathAndFileName);

    //Calculando la imagen de intensidad
    geoGetIntensityImageFromRGBimage();
    //Almacenando resultado en archivo en formato YUV400
    strcpy(pathAndFileName,"output/intensity.yuv");
    geoSaveIntensityImageIn_YUV400_file(pInputImage->pintensity, pathAndFileName);
    strcpy(pathAndFileName,"output/intensity.bmp");
    SaveIntensityImageIn_BMP_file(pInputImage->pintensity, pathAndFileName);

    //Dibujando segmento lineal sobre imagen de intensidad
    geoDrawALinealSegmentOnIntensityImage();
    //Almacenando resultado en archivo en formato YUV400
    strcpy(pathAndFileName,"output/linearSegment.yuv");
    geoSaveIntensityImageIn_YUV400_file(pInputImage->pdrawnLinealSegmentOnIntensity, pathAndFileName);
    strcpy(pathAndFileName,"output/linearSegment.bmp");
    SaveIntensityImageIn_BMP_file(pInputImage->pdrawnLinealSegmentOnIntensity, pathAndFileName);

    //Dibujando circulo sobre imagen de intensidad
    geoDrawACircleOnIntensityImage();
    //Almacenando resultado en archivo en formato YUV400
    strcpy(pathAndFileName,"output/circle.yuv");
    geoSaveIntensityImageIn_YUV400_file(pInputImage->pdrawnCircleOnIntensity, pathAndFileName);
    strcpy(pathAndFileName,"output/circle.bmp");
    SaveIntensityImageIn_BMP_file(pInputImage->pdrawnCircleOnIntensity, pathAndFileName);

}
//Esta funcion obtiene la imagen de intensidad de
//una imagen RGB
void geoGetIntensityImageFromRGBimage()
{
    int i,j;
    int width, height;

    //Renombrando para facilitar código
    width= pInputImage->width;
    height=pInputImage->height;

    //Calculando la imagen de intensidad. El resultado será almacenado
    //en el espacio que fue alocado para tal fin en nuestra estructura
    //pInputImage
    for (j=0;j<height; j++) {
        for (i=0;i<width; i++) {
            pInputImage->pintensity[j*width+i] =
            (unsigned char)(0.299*(double)pInputImage->prgb[3*j*width+3*i]+
                            0.587*(double)pInputImage->prgb[3*j*width+3*i+1]+
                            0.114*(double)pInputImage->prgb[3*j*width+3*i+2]);
        }
    }
}

//Esta funcion dibuja un segmento lineal sobre
//la imagen de intensidad
void geoDrawALinealSegmentOnIntensityImage()
{
    int x, y, i;
    double alfa;
    int xi, yi, xf, yf;
    int height, width;

    xi=p_parametros->xi;
    yi=p_parametros->yi;
    xf=p_parametros->xf;
    yf=p_parametros->yf;

    height=pInputImage->height;
    width=pInputImage->width;

    //Copiando la imagen de intensidad en la imagen que contendrá el segmento lineal
    for (i=0;i<pInputImage->height*pInputImage->width;i++)
        pInputImage->pdrawnLinealSegmentOnIntensity[i]=pInputImage->pintensity[i];

    //Por cada valor del parámetro alfa se calcula un punto usando las ecuaciones
    //paramétricas de un segmento lineal. Cada punto se pone en 255 (blanco) en la
    //imagen de salida. Alfa varía entre 0.0 y 1.0 en pasos de GEO_ALFA_STEP. Cuando
    //alfa en 0.0 se estaría en la posición inicial del segmento y cuando alfa es
    //1.0 en el punto final del segmento.
    for (alfa=0.0;alfa<=1.0;alfa=alfa+0.001) {
        //x=xi+alfa*(xf-xi)
        x=(int)((double)xi+alfa*((double)xf-(double)xi));
        //y=iy+alfa*(fy-iy)
        y=(int)((double)yi+alfa*((double)yf-(double)yi));

        //Dibujando el punto (x,y) siempre y cuando no esté fuera de la imagen
        if ((y>=0)&&(x>=0)&&(y<height)&&(x<width)) {
            pInputImage->pdrawnLinealSegmentOnIntensity[y*width+x]=255;
        }
    }
}

//Esta funcion dibuja un circulo sobre la imagen de
//intensidad
void geoDrawACircleOnIntensityImage()
{
    int x, y, i;
    double angle;
    int cx, cy, r;
    int height, width;

    cx=p_parametros->cx;
    cy=p_parametros->cy;
    r=p_parametros->r;

    height=pInputImage->height;
    width=pInputImage->width;

    //Copiando la imagen de intensidad en la imagen que contendrá
    //el círculo
    for (i=0;i<height*width;i++)
        pInputImage->pdrawnCircleOnIntensity[i]=pInputImage->pintensity[i];

    //Por cada valor del parámetro angle se calcula un punto usando las ecuaciones
    //paramétricas de un círculo. Cada punto se pone en 255 (blanco) en la
    //imagen de salida. angle varía entre 0.0 y 2*PI en pasos de 0.001. Cuando
    //angle en 0.0 se estaría en la posición inicial del círculo (a una distancia
    //radius sobre el eje horizontal del círculo) y cuando angle es 2*PI ya
    //habríamos dado la vuelta y estaríamos cerrando el círculo
    for (angle=0.0;angle<2.0*(double)PI;angle=angle+0.001) {
        //x=cx+r*cos(angle)
        x=(int)((double)cx+(double)r*cos(angle));
        //y=cy+r*sin(angle)
        y=(int)((double)cy+(double)r*sin(angle));

        //Dibujando el punto (x,y) siempre y cuando no esté fuera de la imagen
        if ((y>=0)&&(x>=0)&&(y<height)&&(x<width)) {
            pInputImage->pdrawnCircleOnIntensity[y*width+x]=255;
        }
    }
}

//Esta funcion lee los parametros de archivo de parametros
//de control
void geoLeerParametrosDeControlDeArchivoDeTexto()
{
    FILE *archivo;
    char d1[256], d2[256], d3[256];
    int res;

    printf("Leyendo los datos de entrada:\n");

    //Abriendo archivo en mode de lectura
    char nombreDeArchivo[256]="current_control_parameters.txt";
    archivo = fopen(nombreDeArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo: current_control_parameters.txt\n");
        exit(1);
    }

    //Leyendo datos linea por linea

    //Brincando la primera y segunda lineas
    res=fscanf(archivo, "%s %s %s\n", d1, d2, d3);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    res=fscanf(archivo, "\n");
    numeroDeDatosLeidos++;

    printf("  Dimensiones de las imagenes\n");

    //Leyendo width
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->width=(int)atof(d2);
    printf("   width: %d\n", p_parametros->width);
    numeroDeDatosLeidos++;

    //Leyendo height
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->height=(int)atof(d2);
    printf("   height: %d\n", p_parametros->height);
    numeroDeDatosLeidos++;

    //Brincando linea de texto
    res=fscanf(archivo, "\n");

    printf("  Imagen de entrada y directorio de salida\n");

    //Leyendo path y nombre de imagen de entrada
    res=fscanf(archivo, "%s %s %s\n", d1, d2, d3);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    strcpy(p_parametros->pathAndInputImageFileName,d3);
    printf("   imagen de entrada: %s\n", p_parametros->pathAndInputImageFileName);
    numeroDeDatosLeidos++;

    //Leyendo directorio de salida
    res=fscanf(archivo, "%s %s %s\n", d1, d2, d3);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    strcpy(p_parametros->pathOfOutputDirectory,d3);
    printf("   directorio de salida: %s\n", p_parametros->pathOfOutputDirectory);
    numeroDeDatosLeidos++;

    res=fscanf(archivo, "\n");

    printf("  Punto inicial y punto final\n");

    //Leyendo xi
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->xi=(int)atof(d2);
    printf("   xi: %d\n", p_parametros->xi);
    numeroDeDatosLeidos++;

    //Leyendo yi
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->yi=(int)atof(d2);
    printf("   yi: %d\n", p_parametros->yi);
    numeroDeDatosLeidos++;

    //Brincando linea de texto
    res=fscanf(archivo, "\n");

    //Leyendo xi
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->xf=(int)atof(d2);
    printf("   xf: %d\n", p_parametros->xf);
    numeroDeDatosLeidos++;

    //Leyendo yf
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->yf=(int)atof(d2);
    printf("   yf: %d\n", p_parametros->yf);
    numeroDeDatosLeidos++;

    //Brincando linea de texto
    res=fscanf(archivo, "\n");

    printf("  Centro del circulo\n");

    //Leyendo cx
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->cx=(int)atof(d2);
    printf("   cx: %d\n", p_parametros->cx);
    numeroDeDatosLeidos++;

    //Leyendo cy
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->cy=(int)atof(d2);
    printf("   cy: %d\n", p_parametros->cy);
    numeroDeDatosLeidos++;

    //Brincando linea de texto
    res=fscanf(archivo, "\n");

    printf("  Radio dl circulo\n");

    //Leyendo r
    res=fscanf(archivo, "%s %s\n", d1, d2);
    if (res==0) {printf("Error leyendo dato No. %d de archivo de parametros de control\n", numeroDeDatosLeidos); exit(0);}
    p_parametros->r=(int)atof(d2);
    printf("   r: %d\n", p_parametros->r);
    numeroDeDatosLeidos++;

    printf("  Numero de datos leidos: %d\n", numeroDeDatosLeidos);

    //Cerrando archivo
    fclose(archivo);
}

//****************************************
//****************************************
//** FUNCIONES DE LECTURA Y ESCRITURA   **
//** DE IMAGENES                        **
//****************************************
//****************************************

struct BMPHeader
{
    char bfType[3];       /* "BM" */
    int bfSize;           /* Size of file in bytes */
    int bfReserved;       /* set to 0 */
    int bfOffBits;        /* Byte offset to actual bitmap data (= 54) */
    int biSize;           /* Size of BITMAPINFOHEADER, in bytes (= 40) */
    int biWidth;          /* Width of image, in pixels */
    int biHeight;         /* Height of images, in pixels */
    short biPlanes;       /* Number of planes in target device (set to 1) */
    short biBitCount;     /* Bits per pixel (24 in this case) */
    int biCompression;    /* Type of compression (0 if no compression) */
    int biSizeImage;      /* Image size, in bytes (0 if no compression) */
    int biXPelsPerMeter;  /* Resolution in pixels/meter of display device */
    int biYPelsPerMeter;  /* Resolution in pixels/meter of display device */
    int biClrUsed;        /* Number of colors in the color table (if 0, use
                           maximum allowed by biBitCount) */
    int biClrImportant;   /* Number of important colors.  If 0, all colors
                           are important */
};

//Esta funcion lee imagen RGB de archivo en formato BMP
void readRGBImageFromBMPFile(char *filename)
{
    FILE *fd;
    int width, height;
    int i, j;
    int n;

    fd = fopen(filename, "rb");
    if (fd == NULL)
    {
        printf("Error: fopen failed\n");
        return;
    }

    unsigned char header[54];

    // Read header
    n=fread(header, sizeof(unsigned char), 54, fd);
    if (n==0) {printf("No se pudieron leer datos\n"); exit(0);}

    // Capture dimensions
    width = *(int*)&header[18];
    height = *(int*)&header[22];

    int padding = 0;

    // Calculate padding
    while ((width * 3 + padding) % 4 != 0)
    {
        padding++;
    }

    // Compute new width, which includes padding
    int widthnew = width * 3 + padding;

    // Allocate temporary memory to read widthnew size of data
    unsigned char* data = (unsigned char *)malloc(widthnew * sizeof (unsigned int));

    // Read row by row of data and remove padded data.
    for (i = 0; i<height; i++)
    {
        // Read widthnew length of data
        n=fread(data, sizeof(unsigned char), widthnew, fd);
        if (n==0) {printf("No se pudieron leer datos\n"); exit(0);}

        // Retain width length of data, and swizzle RB component.
        // BMP stores in BGR format, my usecase needs RGB format
        for (j = 0; j < width * 3; j += 3)
        {
            int index = (i * width * 3) + (j);
            pInputImage->prgb[index + 0] = data[j + 2];
            pInputImage->prgb[index + 1] = data[j + 1];
            pInputImage->prgb[index + 2] = data[j + 0];
        }
    }

    free(data);
    fclose(fd);
}

//Esta funcion almacena una imagen de intensidad en
//archivo en formato YUV400
void geoSaveIntensityImageIn_YUV400_file(unsigned char *pintensity, char* filename)
{
    int numread, j, jj, i;
    FILE *fpointer;
    int width, height;
    unsigned char *ptempImage;

    width=pInputImage->width;
    height=pInputImage->height;

    //Imagen de uso local y temporal
    ptempImage = (unsigned char *)malloc(sizeof(unsigned char)*width*height);

    printf("Saving unsigned char image in: %s\n", filename);

    //Abriendo archivo
    fpointer = fopen(filename, "w");
    if (fpointer == NULL) {
        printf("could not read the file: %s\n", filename);
        exit(0);
    }

    //Cambiando posición del sistema de coordenadas de la equina inferior
    //izquierda a la esquina superior izquierda.
    for (i=0;i<width*height;i++) ptempImage[i]=0;
    jj=0;
    for (j=height-1;j>=0;j--) {
        for (i=0;i<width;i++) {
            ptempImage[jj*width+i]= pintensity[j*width+i];
        }
        jj++;
    }

    //Almacenando valores de intensidad en archivo
    numread = (int)fwrite(ptempImage, sizeof(unsigned char), (unsigned int)(height*width), fpointer);

    if (numread==0) {
        printf("Por alguna razon no se pudo escribir dato alguno en archivo\n");
        exit(0);
    }

    fclose(fpointer);
    free(ptempImage);
}

//Esta funcion almacena una imagen de intensidad en
//archivo en formato BMP
int SaveIntensityImageIn_BMP_file(unsigned char *pintensity, char *filename)
{
    int i, j, jj, ipos;
    int bytesPerLine;
    unsigned char *line;
    unsigned char *ptempImage;
    int height, width;

    height=pInputImage->height;
    width=pInputImage->width;

    FILE *file;
    struct BMPHeader bmph;

    /* The length of each line must be a multiple of 4 bytes */

    bytesPerLine = (3 * (width + 1) / 4) * 4;

    strcpy(bmph.bfType, "BM");
    bmph.bfOffBits = 54;
    bmph.bfSize = bmph.bfOffBits + bytesPerLine * height;
    bmph.bfReserved = 0;
    bmph.biSize = 40;
    bmph.biWidth = width;
    bmph.biHeight = height;
    bmph.biPlanes = 1;
    bmph.biBitCount = 24;
    bmph.biCompression = 0;
    bmph.biSizeImage = bytesPerLine * height;
    bmph.biXPelsPerMeter = 0;
    bmph.biYPelsPerMeter = 0;
    bmph.biClrUsed = 0;
    bmph.biClrImportant = 0;

    file = fopen (filename, "wb");
    if (file == NULL) return(0);

    fwrite(&bmph.bfType, 2, 1, file);
    fwrite(&bmph.bfSize, 4, 1, file);
    fwrite(&bmph.bfReserved, 4, 1, file);
    fwrite(&bmph.bfOffBits, 4, 1, file);
    fwrite(&bmph.biSize, 4, 1, file);
    fwrite(&bmph.biWidth, 4, 1, file);
    fwrite(&bmph.biHeight, 4, 1, file);
    fwrite(&bmph.biPlanes, 2, 1, file);
    fwrite(&bmph.biBitCount, 2, 1, file);
    fwrite(&bmph.biCompression, 4, 1, file);
    fwrite(&bmph.biSizeImage, 4, 1, file);
    fwrite(&bmph.biXPelsPerMeter, 4, 1, file);
    fwrite(&bmph.biYPelsPerMeter, 4, 1, file);
    fwrite(&bmph.biClrUsed, 4, 1, file);
    fwrite(&bmph.biClrImportant, 4, 1, file);

    line = (unsigned char*) malloc(bytesPerLine);
    if (line == NULL)
    {
        fprintf(stderr, "Can't allocate memory for BMP file.\n");
        return(0);
    }

    //Cambiando posición del sistema de coordenadas de la equina inferior
    //izquierda a la esquina superior izquierda.
    ptempImage = (unsigned char *)malloc(sizeof(unsigned char)*width*height);
    for (i=0;i<width*height;i++) ptempImage[i]=0;
    jj=0;
    for (j=height-1;j>=0;j--) {
        for (i=0;i<width;i++) {
            ptempImage[jj*width+i]= pintensity[j*width+i];
        }
        jj++;
    }

    for (i = height - 1; i >= 0; i--)
    {
        for (j = 0; j < width; j++)
        {
            ipos = (width * i + j);
            line[3*j] = ptempImage[ipos];
            line[3*j+1] = ptempImage[ipos];
            line[3*j+2] = ptempImage[ipos];
        }
        fwrite(line, bytesPerLine, 1, file);
    }

    free(line);
    fclose(file);

    free(ptempImage);

    return(1);
}

//Esta funcion almacena una imagen RGB en
//archivo en formato BMP
int SaveRGBImageIn_BMP_file(unsigned char *prgb, char *filename)
{
    int i, j, jj, ipos;
    int bytesPerLine;
    unsigned char *line;
    unsigned char *ptempImage;
    int height, width;

    height=pInputImage->height;
    width=pInputImage->width;

    FILE *file;
    struct BMPHeader bmph;

    /* The length of each line must be a multiple of 4 bytes */

    bytesPerLine = (3 * (width + 1) / 4) * 4;

    strcpy(bmph.bfType, "BM");
    bmph.bfOffBits = 54;
    bmph.bfSize = bmph.bfOffBits + bytesPerLine * height;
    bmph.bfReserved = 0;
    bmph.biSize = 40;
    bmph.biWidth = width;
    bmph.biHeight = height;
    bmph.biPlanes = 1;
    bmph.biBitCount = 24;
    bmph.biCompression = 0;
    bmph.biSizeImage = bytesPerLine * height;
    bmph.biXPelsPerMeter = 0;
    bmph.biYPelsPerMeter = 0;
    bmph.biClrUsed = 0;
    bmph.biClrImportant = 0;

    file = fopen (filename, "wb");
    if (file == NULL) return(0);

    fwrite(&bmph.bfType, 2, 1, file);
    fwrite(&bmph.bfSize, 4, 1, file);
    fwrite(&bmph.bfReserved, 4, 1, file);
    fwrite(&bmph.bfOffBits, 4, 1, file);
    fwrite(&bmph.biSize, 4, 1, file);
    fwrite(&bmph.biWidth, 4, 1, file);
    fwrite(&bmph.biHeight, 4, 1, file);
    fwrite(&bmph.biPlanes, 2, 1, file);
    fwrite(&bmph.biBitCount, 2, 1, file);
    fwrite(&bmph.biCompression, 4, 1, file);
    fwrite(&bmph.biSizeImage, 4, 1, file);
    fwrite(&bmph.biXPelsPerMeter, 4, 1, file);
    fwrite(&bmph.biYPelsPerMeter, 4, 1, file);
    fwrite(&bmph.biClrUsed, 4, 1, file);
    fwrite(&bmph.biClrImportant, 4, 1, file);

    line = (unsigned char*) malloc(bytesPerLine);
    if (line == NULL)
    {
        fprintf(stderr, "Can't allocate memory for BMP file.\n");
        return(0);
    }

    //Cambiando posición del sistema de coordenadas de la equina inferior
    //izquierda a la esquina superior izquierda.
    ptempImage = (unsigned char *)malloc(sizeof(unsigned char)*width*height*3);
    for (i=0;i<width*height*3;i++) ptempImage[i]=0;
    jj=0;
    for (j=height-1;j>=0;j--) {
        for (i=0;i<width;i++) {
            ptempImage[jj*3*width+3*i]= prgb[j*3*width+3*i];
            ptempImage[jj*3*width+3*i+1]= prgb[j*3*width+3*i+1];
            ptempImage[jj*3*width+3*i+2]= prgb[j*3*width+3*i+2];
        }
        jj++;
    }

    for (i = height - 1; i >= 0; i--)
    {
        for (j = 0; j < width; j++)
        {
            ipos = 3*(width * i + j);
            line[3*j] = ptempImage[ipos+2];
            line[3*j+1] = ptempImage[ipos+1];
            line[3*j+2] = ptempImage[ipos];
        }
        fwrite(line, bytesPerLine, 1, file);
    }

    free(line);
    fclose(file);

    free(ptempImage);

    return(1);
}

