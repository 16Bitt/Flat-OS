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
	}

	.bss : 
	{
		*(.bss)
	}
}
