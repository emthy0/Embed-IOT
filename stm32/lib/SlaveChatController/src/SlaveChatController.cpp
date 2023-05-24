#include <SlaveChatController.h>
#include <SoftwareSerial.h>
SlaveChatController::SlaveChatController()
{
}

SlaveChatController::SlaveChatController(int RX, int TX, int baudrate) // : _chat(RX, TX)
{   
    _chat = SoftwareSerial(RX, TX);
    _chat.begin(baudrate);
}

void SlaveChatController::RecvCommand(int command)
{
    _chat.read()
}