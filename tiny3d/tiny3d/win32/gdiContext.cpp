/************************************************
 * file  : gdiContext.cpp
 * author: bobding
 * date  : 2015-05-16
 * detail:
 *
************************************************/

#include "gdiContext.h"

NS_TINY3D_BEGIN

DWORD WINAPI createCanvas(LPVOID param)
{
    gdiContext* c = (gdiContext*)param;

    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(0);
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = "tiny3d";

    int ret = RegisterClass(&wc);
    c->hwnd = CreateWindow("tiny3d", "tiny3d-canvas", WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, c->width, c->height, 0, 0, 0, 0);
    c->wndDc = GetDC(c->hwnd);
    c->memDc = CreateCompatibleDC(c->wndDc);
    BITMAPINFO bi = {0};
    BITMAPINFOHEADER& hdr = bi.bmiHeader;
    hdr.biSize  = sizeof(BITMAPINFOHEADER);
    hdr.biWidth = c->width;
    hdr.biHeight= c->height;
    hdr.biPlanes= 1;
    hdr.biBitCount= 32;
    unsigned char* dib = 0;
    c->bitmap = CreateDIBSection(c->memDc, &bi, DIB_RGB_COLORS, (void**)&dib, 0, 0);
    SelectObject(c->memDc, c->bitmap);

    ShowWindow(c->hwnd, SW_SHOW);
    UpdateWindow(c->hwnd);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

bool gdiContext::initialize(int _width, int _height)
{
    width = _width;
    height = _height;

    HANDLE handle = CreateThread(0, 0, createCanvas, this, 0, 0);

    return 0 != handle;
}

void gdiContext::uninitialize()
{
    DeleteObject(bitmap);
    DeleteObject(memDc);
}

NS_TINY3D_END