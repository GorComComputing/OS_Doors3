#ifndef	CALLS_H_SENTRY
#define	CALLS_H_SENTRY

typedef unsigned int mode_t;
typedef long ssize_t;
typedef unsigned int dev_t;
typedef unsigned int ino_t;
typedef unsigned int nlink_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef long long off_t;
typedef unsigned long blksize_t;
typedef unsigned long blkcnt_t;
typedef long long time_t;
typedef unsigned int pid_t;

struct stat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for file system I/O */
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    time_t    st_atime;   /* time of last access */
    time_t    st_mtime;   /* time of last modification */
    time_t    st_ctime;   /* time of last status change */
};

extern int _exit(int exit_code);
extern int fork(); // Should add parameter struct
extern int read(int fd, void* buf, int size);
extern int write(int fd, const void* buf, int size);
extern int open(const void* pathname, int flafs, unsigned int mode);
extern int close(int fd);
extern int waitpid(pid_t pid, unsigned int* status, int param);
extern int execve(const void* pathname, const char* const* argv, const char* const* envp);
extern int chdir(const void* pathname);
extern int sys_chmod(const void* pathname, mode_t mode);
extern int brk(unsigned long size);
extern int stat(const void* pathname,  struct stat* sb);
extern int getcwd(const void* buf,  int size);

extern int sys_errno;


#endif //CALLS_H_SENTRY
