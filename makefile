build:
	gcc -o main main.c -lncurses -O2

run:
	$(MAKE) -B
	./main
