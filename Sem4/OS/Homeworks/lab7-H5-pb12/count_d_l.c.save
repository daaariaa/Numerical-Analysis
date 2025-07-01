#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, " %s nu e furnizat un argument\n", argv[0]);
		return 1;
	}

	//deschiderea fișierului pt citire
	FILE *fp = fopen(argv[1], "r");
	if(!fp) {
		//dacă nu poate fi deschis, se afișează o eroare
		perror("Error opening file");
		return -1;
	}
	
	int ch; //caracterul curent
	int digit_count = 0;
	int line_nr = 1;
	
	//se citește caracterul și se verifică dacaă este cifră
	while ((ch = fgetc(fp)) != EOF) {
		if (isdigit(ch)) {
			digit_count++;
		}
		//sfârșitul unei linii și se resetează contorul
		if (ch == '\n') {
			printf("Line %d: %d digit(s)\n", line_nr, digit_count);
			digit_count = 0;
			line_nr++;
		}
	}
	if (digit_count > 0 || ch != '\n') {
		printf("Line %d: %d digit(s)\n", line_nr, digit_count);
	}
	
	fclose(fp);
	return 0;
}
