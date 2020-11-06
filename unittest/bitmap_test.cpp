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

class bitmap_test : public testing::Test {};

TEST(bitmap_test, basic_test)
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

TEST(bitmap_test, rawdata_process)
{
    FILE *pf = fopen("../images/sample_1920_1280.bmp", "rb");
    if (pf == nullptr) {
        fprintf(stderr, "Open file failed.\n");
        return;
    }

    BITMAPFILE bmpfile;
    fread(&(bmpfile.bfHeader), sizeof(BITMAP_FILEHEADER), 1, pf);

    fread(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, pf);

    int width  = bmpfile.biInfo.bmiHeader.biWidth;
    int height = bmpfile.biInfo.bmiHeader.biHeight;
    int pixelBytes = bmpfile.biInfo.bmiHeader.biBitCount / 8;
    int rawDataSize = width * height * pixelBytes;

    cout << "width=" << width << endl;
    cout << "height=" << height << endl;
    cout << "pixelBytes=" << pixelBytes << endl;
    cout << "rawDataSize=" << rawDataSize << endl;

    EXPECT_EQ(rawDataSize, bmpfile.biInfo.bmiHeader.biSizeImage);

    int ret = fseek(pf, bmpfile.bfHeader.BitsOffset, SEEK_SET);
    if (ret != 0) {
        perror("fseek errror:");
        fclose(pf);
        return;
    }

    uint8_t * pRawData = (uint8_t *)malloc(rawDataSize*sizeof(uint8_t));

    size_t cntRead = fread(pRawData , sizeof(uint8_t), rawDataSize, pf);
    EXPECT_EQ(cntRead, rawDataSize);

    free(pRawData);
    fclose(pf);
}
