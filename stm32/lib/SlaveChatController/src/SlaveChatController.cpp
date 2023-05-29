#include <SlaveChatController.h>
#include <SoftwareSerial.h>
#include <string>
#include <sstream>
#include <vector>

SlaveChatController::SlaveChatController()
{
    // _chat = SoftwareSerial(PA1, PA4);
}

SlaveChatController::SlaveChatController(int RX, int TX, int baudrate) // : _chat(RX, TX)
{   
    chat = SoftwareSerial(RX, TX);
    chat.begin(baudrate);
}

void SlaveChatController::RecvCommand()
{
    // String fullcommand;
    String rawFullcommand = chat.readStringUntil('\n');
    const char *delimiter = " ";
    char* substring;
    char* substrings[4]; 
    int i = 0;
    char fullCommand[rawFullcommand.length() + 1];
    strcpy(fullCommand, rawFullcommand.c_str());
    substring = strtok(fullCommand, delimiter);
    while (substring != NULL && i < 4) 
    {
        substrings[i] = substring;
        substring = strtok(NULL, delimiter);
        i++;
    }
    
}