#include <gtest/gtest.h>

#include "bitmap.h"

#include <iostream>
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

class bitmap_test : public testing::Test
{

};

TEST_F(bitmap_test, basic_test)
{
    cout << "Hello, Bitmap!\n" << endl;

    FILE *pf = fopen("../images/sample_1920_1280.bmp", "rb");
    if (pf == nullptr) {
        fprintf(stderr, "Open file failed.\n");
        return;
    }

    BITMAPFILE bmpfile;
    fread(&(bmpfile.bfHeader), sizeof(BITMAP_FILEHEADER), 1, pf);

    cout << "The size of BITMAP_FILEHEADER is:" << sizeof(BITMAP_FILEHEADER) << endl;
    dumpBitmapFileHead(&(bmpfile.bfHeader));

    fread(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pf);

    dumpBitmapInfoHead(&(bmpfile.biInfo.bmiHeader));

    fclose(pf);
}
