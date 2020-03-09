
#include<filesystem/fat.h>

using namespace myos;
using namespace myos::common;
using namespace myos::filesystem;
using namespace myos::drivers;

void ReadBiosBlock(myos::drivers::AdvanceTechnologyAttachement *hd,common::uint32_t partionOffset)
{
	BiosParameterBlock32 bpb;
	hd->Read(partionOffset, (uint8_t*)&bpb,sizeof(BiosParameterBlock32));
	for(int i= 0x00; i<sizeof(BiosParameterBlock32);i++)
	{
		printfHex(((uint8_t*)&bpb)[i]);
		printf(" ");
	}
	printf("\n");
}