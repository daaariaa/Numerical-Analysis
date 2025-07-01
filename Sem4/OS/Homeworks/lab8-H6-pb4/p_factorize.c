#include <stdio.h> //pt printf, fprintf
#include <stdlib.h> //pt atoi
#include <unistd.h> //pt fork()
#include <sys/wait.h> //pt wait()

int is_prime(int num) {
	if(num <= 1) return 0;
	for(int i=2;i*i<=num;i++) {
		if(num%i==0) return 0;
	}
	return 1;
}

void check_divisor(int i, int N) {
	int count = 0;
	int nr = N;
	while (nr%i == 0){
		count++;
		nr = nr/i;
	}
	if (count > 0 && is_prime(i)) {
		printf("%d^%d\n", i, count);
	}
}
int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "%s nu este furnizat argumentul\n", argv[0]);
		return 1;
	}

	//atoi(ascii to integer) converteste argumentul, adica sirul de caractere, intr-un numar intreg
	int N = atoi(argv[1]);

	for(int i=2;i<=N;i++){
		//se creeaza un proces copil
		//fork() returneaza 0 in procesul copilului
		//pid-ul copilului in procesul parintelui
		pid_t pid = fork();
		if(pid==0){
			check_divisor(i,N);
			exit(0);
		}
	}
	//procesul parinte asteapta toate procesele copil sa termine
	while(wait(NULL) > 0);
	return 0;
}
