#include "pch.h"
#include "File.h"

bool GetFilePathFromFileDialog(std::string& selectedFilePath)
{
    OPENFILENAMEA ofn; // Use OPENFILENAMEA for ANSI character strings
    char filePath[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Select a File";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameA(&ofn) == TRUE)
    {
        // Convert filePath to a wide character string
        int bufferSize = MultiByteToWideChar(CP_ACP, 0, filePath, -1, NULL, 0);
        std::wstring wideFilePath(bufferSize, L'\0');
        MultiByteToWideChar(CP_ACP, 0, filePath, -1, &wideFilePath[0], bufferSize);

        selectedFilePath = std::string(wideFilePath.begin(), wideFilePath.end());
        return true;
    }
    else
    {
        return false;
    }
}
