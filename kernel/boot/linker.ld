ENTRY(__serialhello)
SECTIONS
{
    . = 0x82000000;
    .text : {
        *(.serialhello)
        *(.text)
    }

    .data : { *(.data) }
    __bss_start__ = .;
    .bss : { *(.bss) }
    __bss_end__ = .;
}
