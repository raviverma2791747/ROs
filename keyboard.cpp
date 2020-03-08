
#include <drivers/keyboard.h>

using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

int caps_lock  = 0;
int scroll_lock = 0;
int shift = 0;

KeyboardEventHandler::KeyboardEventHandler()
{
}


void KeyboardEventHandler::OnKeyDown(char)
{
}

void KeyboardEventHandler::OnKeyUp(char)
{
}





KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64)
{
    this->handler = handler;
}

KeyboardDriver::~KeyboardDriver()
{
}

void printf(char*);
void printfHex(uint8_t);


void KeyboardDriver::Activate()
{
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    
    if(handler == 0)
        return esp;
    
    if(key < 0x80)
    {
        switch(key)
        {
            case 0x02: handler->OnKeyDown('1'); break;
            case 0x03: handler->OnKeyDown('2'); break;
            case 0x04: handler->OnKeyDown('3'); break;
            case 0x05: handler->OnKeyDown('4'); break;
            case 0x06: handler->OnKeyDown('5'); break;
            case 0x07: handler->OnKeyDown('6'); break;
            case 0x08: handler->OnKeyDown('7'); break;
            case 0x09: handler->OnKeyDown('8'); break;
            case 0x0A: handler->OnKeyDown('9'); break;
            case 0x0B: handler->OnKeyDown('0'); break;
			case 0x0C: handler->OnKeyDown('-'); break;
			case 0x0D: handler->OnKeyDown('='); break;
			case 0x0E: handler->OnKeyDown('\0'); break; //backspace key
			case 0x0F: for(int i=0;i<4;i++){handler->OnKeyDown(' ');} break;

            case 0x10: if(caps_lock == 0) {handler->OnKeyDown('q');}else{handler->OnKeyDown('Q');} break;
            case 0x11: if(caps_lock == 0) {handler->OnKeyDown('w'); }else{handler->OnKeyDown('W');}break;
            case 0x12: if(caps_lock == 0) {handler->OnKeyDown('e'); }else{handler->OnKeyDown('E');}break;
            case 0x13: if(caps_lock == 0) {handler->OnKeyDown('r'); }else{handler->OnKeyDown('R');}break;
            case 0x14: if(caps_lock == 0) {handler->OnKeyDown('t'); }else{handler->OnKeyDown('T');}break;
            case 0x15: if(caps_lock == 0) {handler->OnKeyDown('z'); }else{handler->OnKeyDown('Z');}break;
            case 0x16: if(caps_lock == 0) {handler->OnKeyDown('u');}else{handler->OnKeyDown('U');} break;
            case 0x17: if(caps_lock == 0) {handler->OnKeyDown('i'); }else{handler->OnKeyDown('I');}break;
            case 0x18: if(caps_lock == 0) {handler->OnKeyDown('o'); }else{handler->OnKeyDown('O');}break;
            case 0x19: if(caps_lock == 0) {handler->OnKeyDown('p'); }else{handler->OnKeyDown('P');}break;
			
            case 0x1A: handler->OnKeyDown('['); break;
			case 0x1B: handler->OnKeyDown(']'); break;
			case 0x1D: handler->OnKeyDown('\0'); break;//control key
            case 0x1E: if(caps_lock == 0) {handler->OnKeyDown('a');}else{handler->OnKeyDown('A');} break;
            case 0x1F: if(caps_lock == 0) {handler->OnKeyDown('s'); }else{handler->OnKeyDown('S');}break;
            case 0x20: if(caps_lock == 0) {handler->OnKeyDown('d'); }else{handler->OnKeyDown('D');}break;
            case 0x21: if(caps_lock == 0) {handler->OnKeyDown('f'); }else{handler->OnKeyDown('F');}break;
            case 0x22: if(caps_lock == 0) {handler->OnKeyDown('g'); }else{handler->OnKeyDown('G');}break;
            case 0x23: if(caps_lock == 0) {handler->OnKeyDown('h');}else{handler->OnKeyDown('H');}break;
            case 0x24: if(caps_lock == 0) {handler->OnKeyDown('j'); }else{handler->OnKeyDown('J');}break;
            case 0x25: if(caps_lock == 0) {handler->OnKeyDown('k'); }else{handler->OnKeyDown('K');}break;
            case 0x26: if(caps_lock == 0) {handler->OnKeyDown('l');}else{handler->OnKeyDown('L');} break;
			case 0x27: handler->OnKeyDown(';'); break;
			case 0x28: handler->OnKeyDown('"'); break;
			//case 0x2B: handler->OnKeyDown('\'); break;

            case 0x2A: handler->OnKeyDown('\0');  if(caps_lock == 0) { caps_lock = 1;}else{caps_lock = 0;} handler->OnKeyUp('\0');if(caps_lock == 1) { caps_lock = 0;}else{caps_lock = 1;} break; //shift key
            case 0x2C: if(caps_lock == 0) {handler->OnKeyDown('y');}else{handler->OnKeyDown('Y');} break;
            case 0x2D: if(caps_lock == 0) {handler->OnKeyDown('x'); }else{handler->OnKeyDown('X');}break;
            case 0x2E: if(caps_lock == 0) {handler->OnKeyDown('c'); }else{handler->OnKeyDown('C');}break;
            case 0x2F: if(caps_lock == 0) {handler->OnKeyDown('v'); }else{handler->OnKeyDown('V');}break;
            case 0x30: if(caps_lock == 0) {handler->OnKeyDown('b');}else{handler->OnKeyDown('B');} break;
            case 0x31: if(caps_lock == 0) {handler->OnKeyDown('n');}else{handler->OnKeyDown('N');} break;
            case 0x32: if(caps_lock == 0) {handler->OnKeyDown('m');}else{handler->OnKeyDown('M');} break;
            case 0x33: handler->OnKeyDown(','); break;
            case 0x34: handler->OnKeyDown('.'); break;
            case 0x35: handler->OnKeyDown('/'); break;
			case 0x36: handler->OnKeyDown('\0'); break;// shift key
			case 0x37: handler->OnKeyDown('*'); break;
			case 0x38: handler->OnKeyDown('\0'); break;// alt key
			case 0x3A: handler->OnKeyDown('\0');  if(caps_lock == 0) { caps_lock = 1;}else{caps_lock = 0;}break; //caps lock key

            case 0x1C: handler->OnKeyDown('\n'); break;
            case 0x39: handler->OnKeyDown(' '); break;//space key
			case 0x29: handler->OnKeyDown('`'); break;
			
			case 0x47: handler->OnKeyDown('7'); break;
			case 0x48: handler->OnKeyDown('8'); break;
			case 0x49: handler->OnKeyDown('9'); break;
			case 0x4A: handler->OnKeyDown('-'); break;
			case 0x4B: handler->OnKeyDown('4'); break;
			case 0x4C: handler->OnKeyDown('5'); break;
			case 0x4D: handler->OnKeyDown('6'); break;
			case 0x4E: handler->OnKeyDown('+'); break;
			case 0x4F: if(shift == 0){handler->OnKeyDown('1');}else{handler->OnKeyDown('!'); }break; 
			
			case 0x50: handler->OnKeyDown('2'); break;
			case 0x51: handler->OnKeyDown('3'); break;
			case 0x52: handler->OnKeyDown('0'); break;
			case 0x53: handler->OnKeyDown('\0'); break; //delete key
			case 0x5B: handler->OnKeyDown('\0'); break; //window key
			case 0x5D: handler->OnKeyDown('\0'); break; //selection key
			
			
			
			
            default:
            {
                printf("KEYBOARD 0x");
                printfHex(key);
                break;
            }
        }
    }
    return esp;
}
