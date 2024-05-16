#include "fat.h"
#include "utils.h"

struct PartitionEntry {
	uint8_t active;
	uint8_t chsStart[3];
	uint8_t type;
	uint8_t chsEnd[3];
	uint32_t lbaStart;
	uint32_t lbaLen;
} __attribute__((packed));

struct Mbr {
	uint8_t _unused[0x1be];
	struct PartitionEntry part[4];
	uint16_t sig;	//aa55
} __attribute__((packed));

struct ElfHeader {
	uint8_t		e_ident[16];
	uint16_t	e_type;
	uint16_t	e_machine;
	uint32_t	e_version;
	uint32_t	e_entry;
	uint32_t	e_phoff;		// -> program header table offset
	uint32_t	e_shoff;		// -> ElfSection[]
	uint32_t	e_flags;
	uint16_t	e_ehsize;		//this header's size in bytes
	uint16_t	e_phentsize;	//size of program header table entries
	uint16_t	e_phnum;		//number of entries in program header table
	uint16_t	e_shentsize;	//sizeof(ElfSection) (size of entry of section table
	uint16_t	e_shnum;		//num sections in section table
	uint16_t	e_shstrndx;		//section header table index of the entry associated with the section name string table. If the file has no section name string table, this member holds the value SHN_UNDEF. See Sections and String Table below for more information.
} __attribute__((packed));

#define EI_MAG0         0               /* e_ident[] indexes */
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3
#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6
#define EI_PAD          7

#define ELFMAG0         0x7F
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'

#define ELFCLASS32      1
#define ELFCLASS64      2

#define ELFDATA2LSB     1
#define ELFDATA2MSB     2

#define ET_EXEC   		2

#define EM_MIPS         8 
#define EM_MIPS_RS4_BE  10

#define EV_CURRENT      1

struct ElfProgHdr{
	uint32_t	p_type;
	uint32_t	p_offset;
	uint32_t	p_vaddr;
	uint32_t	p_paddr;
	uint32_t	p_filesz;
	uint32_t	p_memsz;
	uint32_t	p_flags;
	uint32_t	p_align;
} __attribute__((packed));

void startLinux() {
    static const char *argv[] = {
			"vmlinux",
			"unused_arg",
	};
    static uint8_t __attribute__((aligned(512))) mFatBuf[FAT_SECTOR_SIZE];
    uint32_t startSec = 0, fSize, entryPt, i;
	struct Mbr *mbr = (struct Mbr*)mFatBuf;
	struct FatFileOpenInfoOpaque foi, foik;
	uint8_t foundIdx = -1;
	struct FatFile *dir, *fil;
	struct ElfProgHdr phdr;
	struct ElfHeader ehdr;
	struct FatVolume *vol;
	uint8_t fAttr;
	char fName[13];

    // print_string("\n\n");
    // print_hex((*((uint32_t*) mbr)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 1)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 2)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 3)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 4)));
    // print_string("\n\n");

    char* buf[512];
    readblock(0, buf);
    // print_string("\n\n");
    // print_hex(*(uint32_t*) 0x80001adc);
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 1)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 2)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 3)));
    // print_string("\n");
    // print_hex((*(((uint32_t*) mbr) + 4)));
    // print_string("\n\n");
    // if(mbr->sig != 0xaa55)
	// 	fatal("MBR sig missing!\n");
    // else
    //     print_string("Valid MBR Signature found!");
}