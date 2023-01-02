#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char ErrorString[256];
char *ErrPtr;

void CreateErrorA(char *a);
void GetMyError();

int main()
{
    HANDLE hComm;
    char comPortName[] = "\\\\.\\COM6"; //<<-- Set the COM port here.
    BOOL status;
    int IntStatus;
    DWORD dwEventMask;                     // Event mask to trigger
    char  TempChar;                        // Temperory Character
    char  SerialBuffer[256];               // Buffer Containing Rxed Data
    DWORD NoBytesRead;                     // Bytes read by ReadFile()
    int i = 0;
    DWORD dNoOFBytestoWrite;
    DWORD dNoOfBytesWritten = 0;
    DWORD dwRes;
    OVERLAPPED osWrite = {0};

    hComm = CreateFile(comPortName,                  //port name
                       GENERIC_READ | GENERIC_WRITE, //Read/Write
                       0,                            // No Sharing
                       NULL,                         // No Security
                       OPEN_EXISTING,                // Open existing port only
                       0,                            // Non Overlapped I/O
                       NULL);                        // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
    {
        strcpy(ErrorString, "Error: opening serial port: ");
        strcat(ErrorString, comPortName);
        strcat(ErrorString, " failed !");
        ErrPtr = &ErrorString;
        CreateErrorA(ErrPtr);
        return -1;
    }
    else
    {
        printf("Opening serial port %s successful.\n", comPortName);
    }
    //DBC Structures
    DCB dcbSerialParams = { 0 }; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    status = GetCommState(hComm, &dcbSerialParams);

    if(status == FALSE)
    {
        strcpy(ErrorString, "ERROR: GetCommState failed !");
        ErrPtr = &ErrorString;
        CreateErrorA(ErrPtr);
        return -1;
    }
    else
    {
        printf("Status get successful.\n");
    }

    //DCB Structure Settings
    dcbSerialParams.BaudRate = CBR_115200;    // Setting BaudRate = 115200
    dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None

    status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

    if (status == FALSE)
    {
        strcpy(ErrorString, "Error: Setting DCB Structure failed !");
        ErrPtr = &ErrorString;
        CreateErrorA(ErrPtr);
        return -1;
    }
    else
    {
        printf("Status Set successful.\n");
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE) //Configuring response timeout
    {
        strcpy(ErrorString, "Error: Setting Time Outs failed !");
        ErrPtr = &ErrorString;
        CreateErrorA(ErrPtr);
        return -1;
    }
    else
    {
        printf("Setting Serial Port Timeouts Successfull. \n");
    }
    status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

    if (status == FALSE)
    {
        strcpy(ErrorString, "Error: Setting CommMask failed !");
        ErrPtr = &ErrorString;
        CreateErrorA(ErrPtr);
        return -1;
    }
    else
    {
        printf("Setting CommMask successfull. \n");
    }
    printf("Waiting for Data Reception... \n");

    status = WaitCommEvent(hComm, &dwEventMask, NULL);

    if (status == FALSE)
    {
        strcpy(ErrorString, "Error: Setting WaitCommEvent() failed !");
        ErrPtr = &ErrorString;
        CreateErrorA(ErrPtr);
        CloseHandle(hComm);
        return -1;
    }
    else
    {
        printf("Characters Received: \n\n");
        while(1)
        {
            do
            {
                status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
                SerialBuffer[i] = TempChar;
                i++;
            }
            while (NoBytesRead > 0);
            int j = 0;
            if (i > 1)
            {
                for (j = 0; j < i; j++)
                {
                    //printf("%d \n", SerialBuffer[j]);
                    if (SerialBuffer[j] == 49)
                    {
                        //printf("%c \n", SerialBuffer[j]);
                        //Pulpit to the right shortcut WIN+LCTRL+RIGHT
                    ///////////////////////////////////////////////////
                        INPUT inputs[6] = {};
                        ZeroMemory(inputs, sizeof(inputs));

                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_LWIN;

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_CONTROL;

                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = VK_RIGHT;

                        inputs[3].type = INPUT_KEYBOARD;
                        inputs[3].ki.wVk = VK_RIGHT;
                        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

                        inputs[4].type = INPUT_KEYBOARD;
                        inputs[4].ki.wVk = VK_CONTROL;
                        inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

                        inputs[5].type = INPUT_KEYBOARD;
                        inputs[5].ki.wVk = VK_LWIN;
                        inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

                        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                    ///////////////////////////////////////////////////
                    }
                    //Pulpit to the left shortcut WIN+LCTRL+LEFT
                    if (SerialBuffer[j] == 50)
                    {
                        INPUT inputs[6] = {};
                        ZeroMemory(inputs, sizeof(inputs));

                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_LWIN;

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_CONTROL;

                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = VK_LEFT;

                        inputs[3].type = INPUT_KEYBOARD;
                        inputs[3].ki.wVk = VK_LEFT;
                        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

                        inputs[4].type = INPUT_KEYBOARD;
                        inputs[4].ki.wVk = VK_CONTROL;
                        inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

                        inputs[5].type = INPUT_KEYBOARD;
                        inputs[5].ki.wVk = VK_LWIN;
                        inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

                        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
                    }
                }
            }
            i = 0;
        }
    }
    CloseHandle(hComm);//Closing the Serial Port
    return 0;
}

void CreateErrorA(char *a)
{
    MessageBox( NULL, a, "ERROR !", MB_OKCANCEL | MB_ICONSTOP );
}

void GetMyError()
{
    char buf[1024];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, buf, sizeof(buf), NULL);
    strcpy(ErrorString, buf);
    ErrPtr = &ErrorString;
    CreateErrorA(ErrPtr);
}
