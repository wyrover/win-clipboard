/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>
#include <stdio.h>
#include <string>

/* --- DLL Èë¿Ú ---*/

BOOL APIENTRY DllMain(HINSTANCE hInst     /* Library instance handle. */ ,
                      DWORD reason        /* Reason this function is being called. */ ,
                      LPVOID reserved     /* Not used. */)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_PROCESS_DETACH:
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}

/* -------------------------------------------------------------------------- */

DllClass::DllClass()
{
}


DllClass::~DllClass()
{
}

void ClearClipboard()
{
    OpenClipboard(NULL);
    EmptyClipboard();
    CloseClipboard();
}

void set_clipboard_text(const std::wstring& s)
{
    if (::OpenClipboard(nullptr)) {
        int len = (s.size() + 1) * sizeof(wchar_t);
        HGLOBAL hMem = ::GlobalAlloc(GHND, len);

        if (hMem) {
            wchar_t* pmem = (wchar_t*)::GlobalLock(hMem);
            ::EmptyClipboard();
            ::memcpy(pmem, s.c_str(), len);
            ::SetClipboardData(CF_UNICODETEXT, hMem);
        }

        CloseClipboard();

        if (hMem) {
            GlobalFree(hMem);
        }
    }
}

std::wstring get_clipboard_text()
{
    std::wstring s;

    if (::OpenClipboard(nullptr)) {
        if (HANDLE clip = ::GetClipboardData(CF_UNICODETEXT)) {
            if (auto p = reinterpret_cast<wchar_t*>(::GlobalLock(clip))) {
                s = p;
                ::GlobalUnlock(p);
            }
        }

        ::CloseClipboard();
    }

    return std::move(s);
}


void SetClipboardText(LPWSTR _Text)
{
    LPWSTR _TextBuffer;
    HGLOBAL _SetBuffer;
    wprintf(L"Settings [%s] text to clipboard...", _Text);
    _SetBuffer = GlobalAlloc(GHND, (wcslen(_Text) + 1) * sizeof(wchar_t));

    if (_SetBuffer != NULL) {
        _TextBuffer = (LPWSTR)GlobalLock(_SetBuffer);

        if (_TextBuffer != NULL) {
            wcscpy(_TextBuffer, _Text);
            GlobalUnlock(_SetBuffer);
            OpenClipboard(NULL);
            EmptyClipboard();
            SetClipboardData(CF_UNICODETEXT, _SetBuffer);
            GlobalUnlock(_TextBuffer);
            CloseClipboard();
        }
    }
}


extern "C" DLLIMPORT void WINAPI Hello1()
{
    ::MessageBoxA(NULL, "hello world!", "from dll", MB_OK);
}

void getClipboardData(HWND hWnd)
{
    HGLOBAL hGlobal;
    PTSTR pGlobal;
    OpenClipboard(hWnd);
#ifdef UNICODE
    hGlobal = GetClipboardData(CF_UNICODETEXT);
#else
    hGlobal = GetClipboardData(CF_TEXT);
#endif

    if (hGlobal != NULL) {
        pGlobal = (PTSTR)GlobalLock(hGlobal);
        //DrawText(hdc, pGlobal, -1, &rect, DT_EXPANDTABS);
        GlobalUnlock(hGlobal);
    }

    CloseClipboard();
}



