	dd END - $
	dd 0x04206969
	dd 2
	db "test.txt",0
	times (128 - 9) db 0
	dd FILE0
	dd 13
	db "test2.txt",0
	times (128 - 10) db 0
	dd FILE1
	dd 27
FILE0:
	incbin "test.txt"
FILE1:
	incbin "test2.txt"
	dd 0x04206969
END:
