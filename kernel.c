/*
 * kernel.c
 */

void kclearscr(char *);
void kprint(char *, char *);
void ksleep(unsigned int);

void kmain(void)
{
	const char *str = "grufwub's first kernel";
	char *vidptr = (char *) 0xb8000; // video memory begins here

	kclearscr(vidptr);
	kprint(vidptr, "grufwub's first kernel");
	ksleep(5);
	kclearscr(vidptr);
	kprint(vidptr, "hello and welcome!");
	ksleep(5);
	kprint(vidptr, "this code is so fucking simple like omg");

	return;
}

void kclearscr(char *vidptr)
{
	unsigned int i = 0;

	/* this loop clears the screen
	 * there are 25 lines each of 80 columns,
	 * each element takes 2 bytes: char then attribute
	 */
	while (i < 80 * 25 * 2) {
		/* blank character */
		vidptr[i] = ' ';
		/* attribute-byte: light grey on black */
		vidptr[i+1] = 0x05;
		i = i + 2;
	}
}

void kprint(char *vidptr, char *str)
{
	unsigned int i = 0, j = 0;

	/* this loop writes the string to video memory */
	while (str[j] != '\0') {
		/* the character's ascii */
		vidptr[i] = str[j];
		/* attribute-byte: character black bg light-grey fg */
		vidptr[i+1] = 0x05;
		++j;
		i = i + 2;
	}
}

void ksleep(unsigned int time)
{
	unsigned int i = 0;
	unsigned long j = 0;
	while (i < time) {
		for (j = 0; j < 200000000; j++ ) asm("nop");
		i++;
		j = 0;
	}
}
