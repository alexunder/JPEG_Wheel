#include <iostream>

#include <stdio.h>

typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;

typedef struct __attribute__((__packed__)) _BITMAP_FILEHEADER {
	uint16_t Signature;
	uint32_t Size;
	uint32_t Reserved;
	uint32_t BitsOffset;
} BITMAP_FILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    U8 rgbBlue;
    U8 rgbGreen;
    U8 rgbRed;
    U8 rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
} BITMAPINFO;

typedef struct tagBITMAP {
    BITMAP_FILEHEADER bfHeader;
    BITMAPINFO biInfo;
} BITMAPFILE;

using namespace std;

void dumpBitmapFileHead(BITMAP_FILEHEADER * h) {
    cout << "BITMAPFILEHEADER:" << endl;
    printf("bfType:%X \n", h->Signature);
    cout << "bfSize:" << h->Size << endl;
    cout << "bfReserved:" << h->Reserved << endl;
    cout << "BitsOffset:" << h->BitsOffset << endl;
}

void dumpBitmapInfoHead(BITMAPINFOHEADER * head) {
    cout << "BITMAPINFOHEADER:" << endl;
    cout << "biSize=" << head->biSize << endl;
    cout << "biWidth=" << head->biWidth << endl;
    cout << "biHeight=" << head->biHeight << endl;
    cout << "biPlanes=" << head->biPlanes << endl;
    cout << "biBitCount=" << head->biBitCount << endl;
    cout << "biCompression=" << head->biCompression << endl;
    cout << "biSizeImage=" << head->biSizeImage << endl;
    cout << "biXPelsPerMeter=" << head->biXPelsPerMeter << endl;
    cout << "biYPelsPerMeter=" << head->biYPelsPerMeter << endl;
    cout << "biClrUsed=" << head->biClrUsed << endl;
    cout << "biClrImportant=" << head->biClrImportant << endl;
}

int main(int, char**) {
    cout << "Hello, Bitmap!\n" << endl;

    FILE *pf = fopen("sample_1280×853.bmp", "rb");
    if (pf == nullptr) {
        fprintf(stderr, "Open file failed.\n");
        return 1;
    }

    BITMAPFILE bmpfile;
    fread(&(bmpfile.bfHeader), sizeof(BITMAP_FILEHEADER), 1, pf);

    cout << "The size of BITMAP_FILEHEADER is:" << sizeof(BITMAP_FILEHEADER) << endl;
    dumpBitmapFileHead(&(bmpfile.bfHeader));

    fread(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pf);
   
    dumpBitmapInfoHead(&(bmpfile.biInfo.bmiHeader));

    fclose(pf);
    return 0;
}
