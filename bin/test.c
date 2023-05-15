#include "../lib/unix.h"

static const char str_hello[] = "Hello UNIX!";

#define BUF_SIZE 1024

// from linux/fcntl.h
#define O_RDONLY 00000000
#define O_CREAT  00000100
#define O_WRONLY 00000001
#define O_TRUNC  00001000
// from linux/stat.h
#define S_IRUSR  00400
#define S_IWUSR  00200
#define S_IRGRP  00040
#define S_IWGRP  00020
#define S_IROTH  00004
#define S_IWOTH  00002

typedef unsigned int mode_t;
typedef long ssize_t;


static const char new_line[] = "\n";
static const char err_param[] = "cp old-file new-file\n";
static const char err_open[] = "Error opening file ";
static const char err_write[] = "Error: couldn't write whole buffer\n";
static const char err_close_input[] = "Error: close input\n";
static const char err_close_output[] = "Error: close_output\n";
static const char err_read[] = "Error: read\n";
static const char err_stat[] = "Error: stat\n";
static const char err_chmod[] = "Error: chmod\n";


char buf[BUF_SIZE];

int main(int argc, char** argv){

	struct stat sb;
	
	int inputFd;
	int outputFd;
	int openFlags;
	ssize_t numRead;
	mode_t filePerms;
	
	
	
/*	write(1, argv[1], sizeof(argv[1]));
	
	if(stat(argv[1], &sb) == -1){
		write(1, err_stat, sizeof(err_stat)-1);// error
		return 1;
	}
	
	// Opening input and output files 
	inputFd = open(argv[1], O_RDONLY, 0);
	if(inputFd == -1){
		write(1, err_open, sizeof(err_open)-1);// error
		write(1, argv[1], sizeof(argv[1])-1);// error
		write(1, new_line, sizeof(new_line)-1);// error
		return 1;
	}
	
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = sb.st_mode;
	//filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
	//	    S_IROTH | S_IWOTH; /* rw-rw-rw- */
/*	outputFd = open(argv[2], openFlags, filePerms);
	if(outputFd == -1){
		write(1, err_open, sizeof(err_open)-1);// error
		write(1, argv[2], sizeof(argv[2])-1);// error
		write(1, new_line, sizeof(new_line)-1);// error
		return 1;
	}
	write(outputFd, str_hello, sizeof(str_hello)-1);
	
	if(close(outputFd) == -1){
		write(1, err_close_output, sizeof(err_close_output)-1);// error
		return 1;
	}
	*/
	
	char buf_pwd[256];
	getcwd(buf_pwd, 256);
	write(1, buf_pwd, strlen(buf_pwd));
	write(1, new_line, sizeof(new_line)-1);
	
	return write(1, argv[1], 10);
}
