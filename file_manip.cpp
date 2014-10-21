#include <stdio.h>
#include <stdlib.h>
#include <fstream>

// Author: Cassio dos Santos Sousa

int filesize(char* filename);
void print(int a);
void pickup(FILE *f, char* buf, int reference);
char* buffer(char* filename, int window, int position);
void cutbybuffer(char* filename, int window);

/* Simple main function for testing */

int main(){
	char* filename = "test.txt";
	int byte = 4;
	cutbybuffer(filename, byte);
	return 0;
}

/* Returns the size of a file */
/* For Linux users: it may return an extra character */

int filesize(char* filename){
	int length = -1;
	FILE *f;
	f = fopen(filename, "r");
	if(f == NULL)
		return length;
	std::ifstream is(filename, std::ifstream::binary);
	if(is){
		is.seekg(0, is.end);
		length = is.tellg();
		is.seekg(0, is.beg);
		is.close();
	}
	return length;
}

/* Simple function to print an integer */

void print(int a){
	printf("%d\n", a);
}

/* A function that puts the next character of a file in a buffer */
/* The reference is for the buffer. Returns '/0' for EOF */

void pickup(FILE *f, char* buf, int reference){
	char c = fgetc(f);
	if(c!=EOF)
		buf[reference] = c;
	else
		buf[reference] = '\0';
}

/* Returns the next "window" characters of a file */
/* Using a given position as reference */

char* buffer(char* filename, int window, int position){
	int i;
	int size = filesize(filename);

	/* See the remaining bytes */
	/* Return "" for negative position or no remaining characters */
	
	int remaining = size - position;
	if(remaining > size || remaining < 1) return "";

	/* Try to point to a file */
	/* Return "" if it does not exist */

	FILE *pf;
	pf = fopen(filename, "r");
	if(pf == NULL) return "";

	/* Seek out for either the window size or the remaining bytes */

	fseek(pf, position, SEEK_SET);

	/* Choose the smallest value between window and remaining */

	int pick = remaining < window ? remaining : window;
	
	/* Only allocates the needed amount of characters in a buffer */

	char *buf;
	buf = (char*) malloc(pick * sizeof(char));
	
	/* Simple iteration to get the next characters */

	for(int i=0; i<pick; i++)
		pickup(pf, buf, i);

	/* Concatenates a '\0' at the end of the buffer */

	buf[i] = '\0';
	return buf;

}

/* Print as many windows of a file as possible */

void cutbybuffer(char* filename, int window){
	int reference;
	int size = filesize(filename);
	for(reference = 0; reference < size; reference += window)
		std::cout << buffer(filename, window, reference) << "\n";
}
