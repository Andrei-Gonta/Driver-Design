#include <iostream>
#include <Windows.h>
#include <SetupAPI.h>
#include <initguid.h>
#include <devguid.h>

#pragma comment(lib, "SetupAPI.lib")

using namespace std;

void listConnectedDevices() {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD index = 0;

    deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, 0, 0, DIGCF_PRESENT); 

    if (deviceInfoSet == INVALID_HANDLE_VALUE)
    {
        cerr << "EROARE\n";
        return;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    cout << "DISPOZITIVE USB:  \n";

    while (SetupDiEnumDeviceInfo(deviceInfoSet, index, &deviceInfoData)) 
    {
        char deviceName[256];
        DWORD size = 0;

        if (SetupDiGetDeviceInstanceIdA(deviceInfoSet, &deviceInfoData, deviceName, sizeof(deviceName), &size)) 
        {
            cout << "Device USB: " << deviceName << endl;
        }

        index++;
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

int main()
{
    listConnectedDevices();
    cout << "Gata\n";
}
