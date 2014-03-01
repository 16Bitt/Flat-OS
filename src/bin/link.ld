OUTPUT_FORMAT("binary")
ENTRY(main)

SECTIONS{
	.text :
	{
		*(.text)
	}

	.data :
	{
		*(.data)
		*(.rodata)
	}

	.bss : 
	{
		*(.bss)
		*(COMMON)
	}
}
