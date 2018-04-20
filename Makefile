injector: file_injector.c
	gcc file_injector.c -o file-injector

test: tests/inject-1.txt tests/inject-2.txt tests/inject-3.txt tests/original.txt
	./file-injector '{{INJECT-HERE}}' tests/inject-1.txt '{{another test}}' tests/inject-2.txt ' replace-me ' tests/inject-3.txt 'does not exist' tests/inject-1.txt < tests/original.txt > tests/test-output.txt
	diff tests/test-expected.txt tests/test-output.txt
