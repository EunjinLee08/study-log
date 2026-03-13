// Name: chall.c
// compile: gcc -m32 -o chall chall.c -z lazy -no-pie
// Partial RELRO, No PIE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler() {
  exit(-1);
}

void initialize() {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  signal(SIGALRM, alarm_handler);
  alarm(60);
}

void my_code() {
  system("/bin/sh");
}

void block() {
  puts("You are on the blacklist.\n");
}

void(*block_ptr)() = block;

int enter_name() {
  printf("Please enter your name: ");
  char name[0x80] = {};
  read(0, name, 0x80 - 1);
  printf("So your name is ");
  printf(name);
  block_ptr();
  return 0;
}

void make_card() {
  int result = enter_name();
  if (result != 0) {
    printf("Take your card!\n");
  }
}

void print_menu() {
  printf("1. Listen about the museum.\n");
  printf("2. Make your ID card.\n");
  printf("3. Go to the Gift shop.\n");
  printf("> ");
}

void museum_info() {
  printf("1F: Welcome Hall & Gift Shop\n");
	printf(" - Discover the history of life on Earth and pick up a unique souvenir at out welcoming first floor.\n\n");
	printf("2F: Dinosaur Gallery\n");
	printf(" - Walk among life-sized dinosaur skeletons and learn about these ancient giants.\n\n");
	printf("3F: Ocean & Marine Life Exhibit\n");
	printf(" - Dive into the wonders of the deep sea with interactive displays of marine creatrues and ecosystems.\n\n");

  char buf[4] = {0};
	int floor;
	printf("Which floor do you want to visit?: ");
	read(0, buf, sizeof(buf) - 1);
	floor = (int)strtol(buf, NULL, 10);

	if (floor >= 1 && floor <= 3)  {
		printf("Let's go to the %dF!\n", floor);
		printf("Before, do you have your ID card?\n");
	        make_card();

	} else {
		printf("There isn't such floor.\n");
	}
}

void gift_shop() {
	printf("Follow me!\n");
}

int main(void) {
	initialize();
	
	char buf[4] = {0};
	int choice;
	printf("Hello. How can I help you?\n");
	printf("----------------------------\n");
	print_menu();
	read(0, buf, sizeof(buf) - 1);
	choice = (int)strtol(buf, NULL, 10);

	if (choice == 1) {
		museum_info();
	} else if (choice == 2) {
		make_card();
	} else if (choice == 3) {
		gift_shop();
	} else {
		printf("Invalid choice.\n\n");
	}
	return 0;
}
