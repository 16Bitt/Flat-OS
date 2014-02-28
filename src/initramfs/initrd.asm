	dd END - $$
	dd 0x04206969
	dd 0
	db "test.txt",0
	dd FILE0
	dd 13
FILE0:
	%incbin "test.txt"
	dd 0x04206969
