#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SUCCESS 0
#define FAILURE -1
#define SIZE 1024

int main(int argc, char** argv){
	char c;
	int minutes = -1;
	int hours = -1;
	int rate = 17;
	double payed = 0.0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char filename[100] = {'\n'};
	int fd;
	char buffer[SIZE] = {'\n'};
	int bytes = 0;

	while((c = getopt(argc, argv, "m:t:a:r:h")) != -1){
		switch(c){
			case 'm':
				minutes = atoi(optarg);
				break;
			case 't':
				hours = atoi(optarg);
				break;
			case 'a':
				payed = atof(optarg);
				break;
			case 'r':
				rate = atoi(optarg);
				break;
			case 'h':
				fprintf(stderr, "usage: <-h hours><-m minutes><-a ammount payed>\n");
				exit(SUCCESS);
				break;
		}
	}
	//if no time is entered
	if((minutes == -1) && (hours == -1)){
		fprintf(stderr, "error: no time entered\n");
		exit(FAILURE);
	}
	else {
		if(minutes == -1){
			minutes = 0;
		}
		if(hours == -1){
			hours = 0;
		}
	}

	sprintf(filename, "%d_%d_%d_payment.txt",tm.tm_mon,tm.tm_mday,(tm.tm_year + 1900));
	//fprintf(stderr, "%s\n\n\n", filename);
	if((fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0){
		fd = 1;
	}

	bytes = sprintf(buffer, "bill for Dalton Moehnke\n");
	write(fd, buffer, bytes);
	bytes = sprintf(buffer, "%s\n------------------\n",asctime(&tm));
	write(fd, buffer, bytes);
	bytes = sprintf(buffer, "time worked: %d hours and %d minutes\nrate: %d\nearned: %d.%d\nammount payed: %f\n", hours, minutes, rate, (hours * rate), ((minutes * rate)/60), payed);
	write(fd, buffer, bytes);
	bytes = sprintf(buffer, "\n------------------\n");
	write(fd, buffer, bytes);

	close(fd);


	return SUCCESS;
}