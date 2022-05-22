#include "defines.h"
#include "elf.h"
#include "lib.h"

struct elf_header{
    struct{
        unsigned char magic[4];
        unsigned char class;
        unsigned char format;
        unsigned char version;
        unsigned char abi;
        unsigned char abi_version;
        unsigned char reserve[7];
    } id;
    short type;
    short arch;
    long version;
    long entry_point;
    long program_header_offset;
    long section_header_offset;
    long flags;
    short header_size;
    short program_header_size;
    short program_header_num;
    short section_header_size;
    short section_header_num;
    short section_name_index;
};

struct elf_program_header
{
    long type;
    long offset;
    long virtual_addr;
    long physical_addr;
    long file_size;
    long memory_size;
    long flags;
    long align;
};

static int elf_check(struct elf_header *header)
{
    if(memcmp(header->id.magic, "\x7f" "ELF",4) < 0)
    {
        puts("[error]header->id.magic is not ELF\n");
        return -1;
    }

    if(header->id.class != 1)
    {
        puts("[error]header->id.class is not 1\n");
        return -1;
    }
    if(header->id.format != 2)
    {
        puts("[error]header->id.format is not 2\n");
        return -1;
    }

    if(header->id.version != 1)
    {
        puts("[error]header->id.version is not 1\n");
        return -1;
    }
    if(header->type != 2)
    {
        puts("[error]header->id.type is not 2\n");
        return -1;
    }

    if(header->version != 1)
    {
        puts("[error]header->id.version is not 1\n");
        return -1;
    }

    if((header->arch != 46) && (header->arch != 47))
    {
        puts("[error]header->id.arch is not 46 or 47\n");
        return -1;
    }

    return 0;
}

static int elf_load_program(struct elf_header *header)
{
    int i;
    struct elf_program_header *phdr;

    for(i=0;i<header->program_header_num;i++)
    {
        phdr = (struct elf_program_header *)((char *)header + header->program_header_offset + header->program_header_size * i);

        if(phdr->type != 1) continue;


        /*
        putxval(phdr->offset,6);
        puts(" ");
        putxval(phdr->virtual_addr,8);
        puts(" ");
        putxval(phdr->physical_addr,8);
        puts(" ");
        putxval(phdr->file_size,5);
        puts(" ");
        putxval(phdr->memory_size,5);
        puts(" ");
        putxval(phdr->flags,2);
        puts(" ");
        putxval(phdr->align,2);
        puts("\n");
        */
        // ファイルの内容をコピー
        memcpy((char *)phdr->physical_addr,(char *)header  + phdr->offset,phdr->file_size);
        // BSS対策
        memset((char *)phdr->physical_addr + phdr->file_size,0,phdr->memory_size - phdr->file_size);
    }

    return 0;
}

char *elf_load(char *buf)
{
    struct elf_header *header = (struct elf_header *)buf;

    puts("[log]elf_load start\n");

    if(elf_check(header) < 0)
    {
        puts("[error]elf_check\n");
        return NULL;
    }

    if(elf_load_program(header) < 0)
    {
        puts("[error]elf_load_program\n");
        return NULL;
    }
    
    puts("[log]end\n");

    return (char *)header->entry_point;
}
