ENTRY(main)
SECTIONS
{
    . = 0x82000000;
    .text : {
        *(.text)
    }

    .data : { *(.data) }
    __bss_start__ = .;
    .bss : { *(.bss) }
    __bss_end__ = .;
}
