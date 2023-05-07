#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(push, 1)

void draw_asym_horizont_line(int width, int height, unsigned char *data);
void draw_sym_horizont_line(int width, int height, unsigned char *data);

typedef struct
{
    unsigned short signature;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int image_size;
    unsigned int x_ppm;
    unsigned int y_ppm;
    unsigned int colors;
    unsigned int important_colors;
} BMP_HEADER;
#pragma pack(pop)

void write_bmp_header(FILE *file, int width, int height)
{
    BMP_HEADER header;
    memset(&header, 0, sizeof(header));
    header.signature = 0x4D42;
    header.size = sizeof(header) + width * height * 3;
    header.offset = sizeof(header);
    header.header_size = 40;
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bpp = 24;

    fwrite(&header, sizeof(header), 1, file);
}

void draw_sym_vertical_line(int width, int height, unsigned char *data)
{
    int rand_num;
    int numbers[height / 2];
    for (int i = 0; i < height / 2; i++)
    {
        do
        {
            rand_num = rand_num + rand() % 3 - 1;

        } while (rand_num < -3 || rand_num > 3);
        numbers[i] = rand_num;
        int index = i * width + width / 2 + rand_num;
        data[index * 3] = 0;
        data[index * 3 + 1] = 0;
        data[index * 3 + 2] = 0;
    }
    int cordinates = height / 2 - 1;

    for (int i = height / 2; i < height; i++)
    {

        int index = i * width + width / 2 + numbers[cordinates];
        data[index * 3] = 0;
        data[index * 3 + 1] = 0;
        data[index * 3 + 2] = 0;
        cordinates = cordinates - 1;
    }
}

void draw_asym_vertical_line(int width, int height, unsigned char *data)
{
    int rand_num;
    for (int i = 0; i < height; i++)
    {
        do
        {
            rand_num = rand_num + rand() % 3 - 1;

        } while (rand_num < -3 || rand_num > 3);
        int index = i * width + width / 2 + rand_num;
        data[index * 3] = 0;
        data[index * 3 + 1] = 0;
        data[index * 3 + 2] = 0;
    }
}

void draw_sym_horizont_line(int width, int height, unsigned char *data)
{

    int rand_num;

    int numbers[width / 2];

    for (int j = 0; j < width / 2; j++)
    {
        do
        {
            rand_num = rand_num + rand() % 3 - 1;

        } while (rand_num < -3 || rand_num > 3);
        numbers[j] = rand_num;

        data[(height / 2 - 1 + rand_num) * width * 3 + j * 3] = 0;
        data[(height / 2 - 1 + rand_num) * width * 3 + j * 3 + 1] = 0;
        data[(height / 2 - 1 + rand_num) * width * 3 + j * 3 + 2] = 0;
    }

    int cordinates = width / 2 - 1;

    for (int j = width / 2; j < width; j++)
    {

        data[(height / 2 - 1 + numbers[cordinates]) * width * 3 + j * 3] = 0;
        data[(height / 2 - 1 + numbers[cordinates]) * width * 3 + j * 3 + 1] = 0;
        data[(height / 2 - 1 + numbers[cordinates]) * width * 3 + j * 3 + 2] = 0;
        cordinates = cordinates - 1;
    }
}
void draw_asym_horizont_line(int width, int height, unsigned char *data)
{

    int rand_num;

    for (int j = 0; j < width; j++)
    {
        do
        {
            rand_num = rand_num + rand() % 3 - 1;

        } while (rand_num < -3 || rand_num > 3);

        data[(height / 2 - 1 + rand_num) * width * 3 + j * 3] = 0;
        data[(height / 2 - 1 + rand_num) * width * 3 + j * 3 + 1] = 0;
        data[(height / 2 - 1 + rand_num) * width * 3 + j * 3 + 2] = 0;
    }
}
void write_bmp_data(FILE *file, unsigned char *data, int width, int height)
{
    int i, j, k;

    // fill the top and bottom rows with black color
    for (j = 0; j < width; j++)
    {
        data[j * 3] = 0;
        data[j * 3 + 1] = 0;
        data[j * 3 + 2] = 0;
        data[(height - 1) * width * 3 + j * 3] = 0;
        data[(height - 1) * width * 3 + j * 3 + 1] = 0;
        data[(height - 1) * width * 3 + j * 3 + 2] = 0;
    }

    // fill the left and right columns with black color
    for (i = 1; i < height - 1; i++)
    {
        data[i * width * 3] = 0;
        data[i * width * 3 + 1] = 0;
        data[i * width * 3 + 2] = 0;
        data[(i + 1) * width * 3 - 3] = 0;
        data[(i + 1) * width * 3 - 2] = 0;
        data[(i + 1) * width * 3 - 1] = 0;
    }

    // write the image data to file
}
void write_image_data_to_the_file(FILE *file, int width, int height, unsigned char *data)
{
    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            int k = i * width + j;
            fputc(data[k * 3 + 2], file);
            fputc(data[k * 3 + 1], file);
            fputc(data[k * 3], file);
        }
    }
}
int main()
{
    // without srand the code will always give same random numbers
    srand(time(NULL));
    int width = 32;
    int height = 32;
    unsigned char data[width * height * 3];
    memset(data, 255, sizeof(data)); // fill the image with white pixels
    FILE *file = fopen("image.bmp", "wb");
    // writing header
    write_bmp_header(file, width, height);
    // adding frame to the file
    write_bmp_data(file, data, width, height);

    // here we call all our functions  to draw a lime-------
    draw_sym_vertical_line(width, height, data);
    // draw_asym_horizont_line(width, height, data);
    // draw_sym_horizont_line(width, height, data);
    // draw_asym_vertical_line(width, height, data);
    //-----------------------------------
    //--filling all the data to the file
    write_image_data_to_the_file(file, width, height, data);
    fclose(file);
    return 0;
}
