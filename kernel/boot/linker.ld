ENTRY(__kernel)
SECTIONS
{
    . = 0x82000000;
    .text : {
        *(.kernel)
        *(.text)
    }

    .data : { *(.data) }
    __bss_start__ = .;
    .bss : { *(.bss) }
    __bss_end__ = .;
}
