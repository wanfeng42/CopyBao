#ifdef UNICODE
#undef UNICODE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Commctrl.h>

#define IDD_MAIN                        101
#define IDC_RECV                        1001
#define IDC_PBAR                        1002
#define IDC_RESET                       1003
#define IDC_SAVE                        1004
#define IDC_PERCENT                     1005
#define IDC_DATA                        1006
#define IDC_COPY                        1007

typedef unsigned char u8;
u8 dec[256];

static unsigned char dlg[] =
{
0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC0, 0x08, 0xC8, 0x80, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x01,
0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x69, 0x00, 0x61, 0x00,
0x6C, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x90, 0x01,
0x00, 0x86, 0xB0, 0x65, 0x8B, 0x5B, 0x53, 0x4F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x50,
0x09, 0x00, 0x09, 0x00, 0x32, 0x00, 0x0E, 0x00, 0xE9, 0x03, 0x00, 0x00,
0xFF, 0xFF, 0x80, 0x00, 0x52, 0x00, 0x65, 0x00, 0x63, 0x00, 0x65, 0x00,
0x69, 0x00, 0x76, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x50,
0x2F, 0x00, 0x1B, 0x00, 0x15, 0x01, 0x0E, 0x00, 0xEA, 0x03, 0x00, 0x00,
0x6D, 0x00, 0x73, 0x00, 0x63, 0x00, 0x74, 0x00, 0x6C, 0x00, 0x73, 0x00,
0x5F, 0x00, 0x70, 0x00, 0x72, 0x00, 0x6F, 0x00, 0x67, 0x00, 0x72, 0x00,
0x65, 0x00, 0x73, 0x00, 0x73, 0x00, 0x33, 0x00, 0x32, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x40, 0x3C, 0x00, 0x09, 0x00, 0x32, 0x00, 0x0E, 0x00,
0xEB, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0x52, 0x00, 0x65, 0x00,
0x73, 0x00, 0x65, 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40,
0x2C, 0x01, 0x09, 0x00, 0x32, 0x00, 0x0E, 0x00, 0xEC, 0x03, 0x00, 0x00,
0xFF, 0xFF, 0x80, 0x00, 0x53, 0x00, 0x61, 0x00, 0x76, 0x00, 0x65, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0x50, 0x09, 0x00, 0x1D, 0x00, 0x25, 0x00, 0x08, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0x00, 0x50, 0x00, 0x72, 0x00,
0x6F, 0x00, 0x67, 0x00, 0x72, 0x00, 0x65, 0x00, 0x73, 0x00, 0x73, 0x00,
0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x50, 0x45, 0x01, 0x1D, 0x00,
0x19, 0x00, 0x08, 0x00, 0xED, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0x82, 0x00,
0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x2E, 0x00, 0x30, 0x00, 0x25, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x44, 0x10, 0xA1, 0x58, 0x09, 0x00, 0x2B, 0x00, 0x56, 0x01, 0x43, 0x00,
0xEE, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40,
0xF9, 0x00, 0x09, 0x00, 0x32, 0x00, 0x0E, 0x00, 0xEF, 0x03, 0x00, 0x00,
0xFF, 0xFF, 0x80, 0x00, 0x43, 0x00, 0x6F, 0x00, 0x70, 0x00, 0x79, 0x00,
0x00, 0x00, 0x00, 0x00
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static int data_len;
	static int data_len2;
	static int last_length;
	int new_length;
	static int idle_ticks;

	switch(message) {
	case WM_INITDIALOG:
		return FALSE;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return TRUE;

	case WM_COMMAND:
		if(HIWORD(wparam) == BN_CLICKED) {
			switch(LOWORD(wparam)) {
			case IDC_RECV:
				EnableWindow(GetDlgItem(hwnd, IDC_DATA), TRUE);
				SetFocus(GetDlgItem(hwnd, IDC_DATA));
				EnableWindow(GetDlgItem(hwnd, IDC_RECV), FALSE);
				ShowWindow(GetDlgItem(hwnd, IDC_RESET), SW_SHOW);
				SetTimer(hwnd, 1, 500, NULL);
				break;

			case IDC_RESET:
				SetDlgItemText(hwnd, IDC_DATA, "");
				EnableWindow(GetDlgItem(hwnd, IDC_DATA), FALSE);
				EnableWindow(GetDlgItem(hwnd, IDC_RECV), TRUE);
				ShowWindow(GetDlgItem(hwnd, IDC_RESET), SW_HIDE);
				ShowWindow(GetDlgItem(hwnd, IDC_SAVE), SW_HIDE);
				KillTimer(hwnd, 1);
				KillTimer(hwnd, 2);
				break;

			case IDC_SAVE:
			{
				OPENFILENAME ofn;
				char path[MAX_PATH] = "";
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hwnd;
				ofn.lpstrFile = path;
				ofn.nMaxFile = MAX_PATH;
				ofn.Flags = OFN_OVERWRITEPROMPT;
				ofn.lpstrFilter = "All Files(*.*)\0*.*\0";
				ofn.nFilterIndex = 1;

				if(GetSaveFileName(&ofn)) {
					int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_DATA)) + 1;
					FILE *fp = fopen(path, "wb");
					u8 *buf = (u8 *)malloc(len);
					u8 *p = buf + 8;
					int i;
					GetDlgItemText(hwnd, IDC_DATA, (char *)buf, len);
					for(i = data_len; i > 0;) {
						fputc((dec[p[0]] << 2) | (dec[p[1]] >> 4), fp); i--;
						if(i) { fputc(((dec[p[1]] & 15) << 4) | (dec[p[2]] >> 2), fp); i--; }
						if(i) { fputc(((dec[p[2]] & 3) << 6) | dec[p[3]], fp); i--; }
						if(i) {
							p += 4;
							if(*p == '\r') p += 2;
						}
					}
					free(buf);
					fclose(fp);
				}
				break;
			}
				
			}
		}

		return TRUE;

	case WM_TIMER:
		switch(wparam) {
		case 1:
			if(GetWindowTextLength(GetDlgItem(hwnd, IDC_DATA)) > 6) {
				char buf[10];
				int len;

				GetWindowText(GetDlgItem(hwnd, IDC_DATA), buf, 10);
				sscanf(buf, "%x", &len);
				data_len = len;
				data_len2 = (len + 2) / 3 * 4;
				KillTimer(hwnd, 1);
				
				last_length = 0;
				idle_ticks = 0;
				SetTimer(hwnd, 2, 100, NULL);
				EnableWindow(GetDlgItem(hwnd, IDC_RESET), FALSE);
			}
			break;
		case 2:
			new_length = GetWindowTextLength(GetDlgItem(hwnd, IDC_DATA));
			if(new_length == last_length) {
				if(++idle_ticks > 5) {
					EnableWindow(GetDlgItem(hwnd, IDC_RESET), TRUE);
					return FALSE;
				}
			} else {
				int len, len2;
				char buf[10];
				EnableWindow(GetDlgItem(hwnd, IDC_RESET), FALSE);

				last_length = new_length;
				len = (new_length - 8) - (new_length - 8) / 82 * 2;
				len2 = len > data_len2 ? data_len2 : len;

				SendDlgItemMessage(hwnd, IDC_PBAR, PBM_SETPOS, len2 * 100 / data_len2, 0);
				sprintf(buf, "%.1f%%", len2 * 100.0f / data_len2);
				SetDlgItemText(hwnd, IDC_PERCENT, buf);

				if(new_length - 8 == data_len2 + (data_len2 + 79) / 80 * 2) {
					KillTimer(hwnd, 2);
					EnableWindow(GetDlgItem(hwnd, IDC_DATA), FALSE);
					EnableWindow(GetDlgItem(hwnd, IDC_RESET), TRUE);
					ShowWindow(GetDlgItem(hwnd, IDC_SAVE), SW_SHOW);
				}
			}
			break;
		}
		return TRUE;
	default:
		return FALSE;
	}
}

int __stdcall WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR lpcmdline, int ncmdshow)
{
	char *s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", *p;

	ZeroMemory(dec, sizeof(dec));
	for(p = s; *p; p++) {
		dec[*p] = p - s;
	}
	
	DialogBoxIndirectParam(hinst, (LPDLGTEMPLATE)&dlg, NULL, DlgProc, 0);
	
	return 0;
}
