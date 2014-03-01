	dd END - $
	dd 0x04206969
	dd 2
	db "test.txt",0
	times (128 - 9) db 0
	dd FILE0
	dd 13
	db "test",0
	times (128 - 5) db 0
	dd FILE1
	dd 124
FILE0:
	incbin "test.txt"
FILE1:
	incbin "test"
	dd 0x04206969
END:
