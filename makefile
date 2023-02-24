MAIN=src/Main.c
FILE_UTILITIES=src/FileUtilities.c
TESTS=src/Tests.c

main:
	gcc $(MAIN) -o textEditor

tests:
	gcc $(FILE_UTILITIES) $(TESTS) -o textEditorTests -lcunit

debug:
	gcc $(FILE_UTILITIES) $(TESTS) -o textEditorTests -lcunit -g	
	gdb textEditorTests
