#include windows.h
#include iostream
#include vector

void QueryImagePath(HKEY hKey, const stdwstring& subKey) {
    HKEY hSubKey;
    if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
        WCHAR imagePath[MAX_PATH];
        DWORD bufferSize = sizeof(imagePath);
        if (RegQueryValueEx(hSubKey, LImagePath, nullptr, nullptr, (LPBYTE)imagePath, &bufferSize) == ERROR_SUCCESS) {
            stdwcout  LService   subKey.substr(subKey.find_last_of(L'') + 1)  Ln;
            stdwcout  LImagePath   imagePath  Lnn;
        }
        RegCloseKey(hSubKey);
    }
}

void EnumerateServices() {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, LSYSTEMCurrentControlSetServices, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        WCHAR subKeyName[MAX_PATH];
        DWORD index = 0;
        DWORD subKeySize = MAX_PATH;

        while (RegEnumKeyEx(hKey, index, subKeyName, &subKeySize, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
            stdwstring fullPath = LSYSTEMCurrentControlSetServices + stdwstring(subKeyName);
            QueryImagePath(HKEY_LOCAL_MACHINE, fullPath);
            subKeySize = MAX_PATH;
            index++;
        }
        RegCloseKey(hKey);
    }
    else {
        stdcerr  Failed to open registry key!n;
    }
}

int main() {
    stdwcout  LListing all services and their ImagePath valuesnn;
    EnumerateServices();
    return 0;
}
