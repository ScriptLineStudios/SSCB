main.out:	
	gcc -Wall -Wextra -pedantic -o main.out examples/main.c src/sscb_instructions.c src/sscb_optimizer.c
	./main.out
	rm main.out