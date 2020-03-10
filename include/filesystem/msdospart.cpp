#include<filesystem/msdospart.h>

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::filesystem;

void printf(char*);
void printfHex(uint8_t);

  void MSDOSPartitionTable::ReadPartitions(AdvancedTechnologyAttachment *hd)
 {
	 MasterBootRecord mbr;
	 hd->Read28(0,(uint8_t*)&mbr,sizeof (MasterBootRecord));
	 printf("MBR:");
	 /*
	 for(int i=446;i<446 + 4*16;i++)
	 {
		 printfHex(((uint8_t*)&mbr)[i]);
	 }
	 printf("\n");
	 */
	 
	 if(mbr.magicnumber != 0xAA55)
	 {
		 printf("illegal MBR");
		 return;
	 }
	 
	 for(int i=0; i<4;i++)
	 {
		 printf("Partition");
		 printfHex(i & 0xFF);
		 
		 if(mbr.primaryPartition[i].bootable == 0x80)
		 {
			 printf("bootable Type \n");
		 }
		 else
		 {
			 printf("not bootable Type\n");
		 }
		 printfHex(mbr.primaryPartition[i].partition_id);
	 }
 }