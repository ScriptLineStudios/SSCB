main.out:	
	gcc -Wall -Wextra -pedantic -o main.out examples/main.c src/ssbc_instructions.c
	./main.out
	rm main.out