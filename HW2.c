/*
 * TCSS 333 Assignment #2
 * Author: Ibrahim Alshubaily
 */

#include <stdio.h>

int main(void) {

    FILE *inFile = fopen("test.bmp","rb");
    FILE *bigOutfile = fopen("big.bmp","wb");
    FILE *smallOutfile = fopen("small.bmp","wb");

    // Read in, modify and write out headers.
    char bm[2];
    int filesize;
    int imagesize;
    int width, height;
    char restofit[28];

    fread(bm, 1 ,2 ,inFile);
    fwrite(bm, sizeof(char) , 2,bigOutfile);
    fwrite(bm, sizeof(char) , 2,smallOutfile);

    fread(&filesize, sizeof(int) , 1,inFile);
    imagesize = filesize-54;
    unsigned int bigFileSize = (imagesize*4) + 54;
    unsigned int smallFileSize = (imagesize/4) + 54;
    fwrite(&bigFileSize, sizeof(int) , 1,bigOutfile);
    fwrite(&smallFileSize, sizeof(int) , 1,smallOutfile);

    fread(restofit, 1 ,12 ,inFile);
    fwrite(restofit, sizeof(char) , 12,bigOutfile);
    fwrite(restofit, sizeof(char) , 12,smallOutfile);

    fread(&width, sizeof(int) , 1,inFile);
    unsigned int bigWidth = width*2;
    unsigned int smallWidth = width/2;
    fwrite(&bigWidth, sizeof(int) , 1,bigOutfile);
    fwrite(&smallWidth, sizeof(int) , 1,smallOutfile);

    fread(&height, sizeof(int) , 1,inFile);
    unsigned int bigHeight = height*2;
    unsigned int smallHeight = height/2;
    fwrite(&bigHeight, sizeof(int) , 1,bigOutfile);
    fwrite(&smallHeight, sizeof(int) , 1,smallOutfile);

    fread(restofit, 1 ,28 ,inFile);
    fwrite(restofit, sizeof(char) , 28,bigOutfile);
    fwrite(restofit, sizeof(char) , 28,smallOutfile);

    unsigned char originalImage[height][width*3];
    fread(originalImage, 1 , imagesize ,inFile);

    unsigned char bigImage[height*2][width*3*2];
    unsigned char smallImage[height/2][(width*3)/2];

    // Loop over the original image pixels and copy each pixels 4 times into the new big image.
    unsigned int bigi = 0;
    unsigned int bigj = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width * 3; j+= 3) {
            for (int copy = 0; copy < 2; copy++) {
                //   X X
                //   * *
                for (int rgb = 0; rgb < 3; rgb++) {
                     bigImage[bigi][bigj+rgb] =   originalImage[i][j+rgb];
                }
                //   * *
                //   X X
                for (int rgb = 0; rgb < 3; rgb++) {
                    bigImage[bigi+1][bigj+rgb] =   originalImage[i][j+rgb];
                }
                bigj += 3;
            }
        }
        bigi += 2;
        bigj = 0;
    }
    //Loop over the image and take one out of four pixels and place it in the small image.
    unsigned int smalli = 0;
    unsigned int smallj = 0;
    for (int i = 0; i < height; i+= 2) {
        for (int j = 0; j < width*3; j+= 6) {
            for (int rgb = 0; rgb < 3; rgb++) {
                smallImage[smalli][smallj+rgb] = originalImage[i][j+rgb];
            }
            smallj += 3;
        }
        smalli++;
        smallj = 0;
    }
    //Write out to the image files and close them.
    fwrite(bigImage, sizeof(char) ,imagesize*4 ,bigOutfile);
    fwrite(smallImage, sizeof(char) ,imagesize/2 ,smallOutfile);
    fclose(inFile);
    fclose(bigOutfile);
    fclose(smallOutfile);
}
