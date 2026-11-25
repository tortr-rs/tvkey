/* c.h: the whole libc of Chamesle Source Linux, in one file. x86-64 and i386 Linux.
 * this copy lives in rifle and has grown: directories, links, users and groups, the errno messages, a real
 * malloc, strftime, setenv. what rifle added is marked [rifle]. nothing the original had was taken out.
 * include it once (in one .c file) and you get everything: the start-up code, system calls, strings, memory,
 * files and printf. it builds with tcc (your programs) and gcc (vi and tcc themselves). */
#ifndef C_H
#define C_H

/* ---- types ---- */
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ssize_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
#ifdef __i386__
typedef long long off_t;      /* files past 2G on i386 too */
#else
typedef long off_t;
#endif
typedef long time_t;
typedef int pid_t;
typedef int mode_t;
typedef unsigned int uid_t;    /* [rifle] */
typedef unsigned int gid_t;
#ifdef __i386__
typedef unsigned long long dev_t;
typedef unsigned long long ino_t;
#else
typedef unsigned long dev_t;
typedef unsigned long ino_t;
#endif
typedef unsigned long nlink_t;
typedef long clock_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
typedef int wchar_t_c; /* not wchar_t: tcc and gcc both predefine their own */
#define NULL ((void *)0)
#define offsetof(t, m) ((size_t)&((t *)0)->m)
#define CHAR_BIT 8
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
#define UINT_MAX 4294967295U
#ifdef __i386__
#define LONG_MAX 2147483647L
#define ULONG_MAX 4294967295UL
#else
#define LONG_MAX 9223372036854775807L
#define ULONG_MAX 18446744073709551615UL
#endif
#define LONG_MIN (-LONG_MAX - 1)
#define LLONG_MAX 9223372036854775807LL
#define LLONG_MIN (-LLONG_MAX - 1)
#define ULLONG_MAX 18446744073709551615ULL
#define PATH_MAX 4096
#define NAME_MAX 255
#define SIZE_MAX ULONG_MAX
#define SSIZE_MAX LONG_MAX
#define SHRT_MAX 32767
#define UINT32_MAX 4294967295U
#define INT64_MAX LONG_MAX
#define INT64_MIN LONG_MIN
#define UINT64_MAX ULONG_MAX
#ifndef __cplusplus
typedef _Bool bool;
#define true 1
#define false 0
#endif
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, t) __builtin_va_arg(ap, t)
#define va_end(ap) __builtin_va_end(ap)
#define va_copy(d, s) __builtin_va_copy(d, s)

/* ---- system calls ----
 * sys6(n, a..f): the number goes in rax, the arguments in rdi rsi rdx r10 r8 r9. written in plain asm so it
 * builds the same under gcc and tcc. returns -errno on failure, like the kernel */
#ifdef C_DECLS_ONLY
extern long sys6(long n, long a, long b, long c, long d, long e, long f);
#else
long sys6(long n, long a, long b, long c, long d, long e, long f);
#endif
#ifdef __i386__
/* i386: int 0x80, the number in eax, the arguments in ebx ecx edx esi edi ebp */
#ifndef C_DECLS_ONLY
__asm__(".text\n.global sys6\nsys6:\n push %ebx\n push %esi\n push %edi\n push %ebp\n"
        " mov 20(%esp),%eax\n mov 24(%esp),%ebx\n mov 28(%esp),%ecx\n mov 32(%esp),%edx\n"
        " mov 36(%esp),%esi\n mov 40(%esp),%edi\n mov 44(%esp),%ebp\n int $0x80\n"
        " pop %ebp\n pop %edi\n pop %esi\n pop %ebx\n ret\n");
#endif
#else
#ifndef C_DECLS_ONLY
__asm__(".text\n.global sys6\nsys6:\n"
        " mov %rdi,%rax\n mov %rsi,%rdi\n mov %rdx,%rsi\n mov %rcx,%rdx\n mov %r8,%r10\n mov %r9,%r8\n"
        " mov 8(%rsp),%r9\n syscall\n ret\n");
#endif
#endif
#define sys0(n) sys6(n, 0, 0, 0, 0, 0, 0)
#define sys1(n, a) sys6(n, (long)(a), 0, 0, 0, 0, 0)
#define sys2(n, a, b) sys6(n, (long)(a), (long)(b), 0, 0, 0, 0)
#define sys3(n, a, b, c) sys6(n, (long)(a), (long)(b), (long)(c), 0, 0, 0)

#ifdef __i386__
/* where i386 has an old call and a new one, the new one: stat64, mmap2, _llseek, the 32-bit uids */
#define SYS_accept 364
#define SYS_accept4 364
#define SYS_access 33
#define SYS_alarm 27
#define SYS_arch_prctl 384
#define SYS_bind 361
#define SYS_brk 45
#define SYS_chdir 12
#define SYS_chmod 15
#define SYS_chown 212
#define SYS_chroot 61
#define SYS_clock_getres 266
#define SYS_clock_gettime 265
#define SYS_clock_nanosleep 267
#define SYS_clone 120
#define SYS_close 6
#define SYS_connect 362
#define SYS_copy_file_range 377
#define SYS_creat 8
#define SYS_dup 41
#define SYS_dup2 63
#define SYS_dup3 330
#define SYS_execve 11
#define SYS_exit 1
#define SYS_exit_group 252
#define SYS_faccessat 307
#define SYS_fchdir 133
#define SYS_fchmod 94
#define SYS_fchmodat 306
#define SYS_fchmodat2 452
#define SYS_fchown 207
#define SYS_fchownat 298
#define SYS_fcntl 221
#define SYS_fdatasync 148
#define SYS_flock 143
#define SYS_fork 2
#define SYS_fstat 197
#define SYS_fstatfs 100
#define SYS_fsync 118
#define SYS_ftruncate 194
#define SYS_futex 240
#define SYS_getcwd 183
#define SYS_getdents 141
#define SYS_getdents64 220
#define SYS_getegid 202
#define SYS_geteuid 201
#define SYS_getgid 200
#define SYS_getgroups 205
#define SYS_getitimer 105
#define SYS_getpeername 368
#define SYS_getpgid 132
#define SYS_getpgrp 65
#define SYS_getpid 20
#define SYS_getppid 64
#define SYS_getpriority 96
#define SYS_getrandom 355
#define SYS_getrlimit 191
#define SYS_getrusage 77
#define SYS_getsid 147
#define SYS_getsockname 367
#define SYS_getsockopt 365
#define SYS_gettid 224
#define SYS_gettimeofday 78
#define SYS_getuid 199
#define SYS_ioctl 54
#define SYS_kill 37
#define SYS_lchown 198
#define SYS_link 9
#define SYS_linkat 303
#define SYS_listen 363
#define SYS_lseek 140
#define SYS_lstat 196
#define SYS_madvise 219
#define SYS_mkdir 39
#define SYS_mkdirat 296
#define SYS_mknod 14
#define SYS_mknodat 297
#define SYS_mmap 192
#define SYS_mount 21
#define SYS_mprotect 125
#define SYS_mremap 163
#define SYS_msync 144
#define SYS_munmap 91
#define SYS_nanosleep 162
#define SYS_newfstatat 300
#define SYS_open 5
#define SYS_openat 295
#define SYS_pause 29
#define SYS_pipe 42
#define SYS_pipe2 331
#define SYS_poll 168
#define SYS_ppoll 309
#define SYS_prctl 172
#define SYS_pread64 180
#define SYS_pwrite64 181
#define SYS_read 3
#define SYS_readlink 85
#define SYS_readlinkat 305
#define SYS_readv 145
#define SYS_recvfrom 371
#define SYS_recvmsg 372
#define SYS_rename 38
#define SYS_renameat 302
#define SYS_rmdir 40
#define SYS_rt_sigaction 174
#define SYS_rt_sigpending 176
#define SYS_rt_sigprocmask 175
#define SYS_rt_sigreturn 173
#define SYS_rt_sigsuspend 179
#define SYS_rt_sigtimedwait 177
#define SYS_sched_getaffinity 242
#define SYS_sched_yield 158
#define SYS_select 142
#define SYS_sendfile 239
#define SYS_sendmsg 370
#define SYS_sendto 369
#define SYS_set_tid_address 258
#define SYS_setgid 214
#define SYS_setgroups 206
#define SYS_sethostname 74
#define SYS_setitimer 104
#define SYS_setpgid 57
#define SYS_setpriority 97
#define SYS_setregid 204
#define SYS_setresgid 210
#define SYS_setresuid 208
#define SYS_setreuid 203
#define SYS_setrlimit 75
#define SYS_setsid 66
#define SYS_setsockopt 366
#define SYS_setuid 213
#define SYS_shutdown 373
#define SYS_sigaltstack 186
#define SYS_socket 359
#define SYS_socketpair 360
#define SYS_stat 195
#define SYS_statfs 99
#define SYS_symlink 83
#define SYS_symlinkat 304
#define SYS_sync 36
#define SYS_syncfs 344
#define SYS_sysinfo 116
#define SYS_tgkill 270
#define SYS_time 13
#define SYS_times 43
#define SYS_truncate 193
#define SYS_umask 60
#define SYS_umount2 52
#define SYS_uname 122
#define SYS_unlink 10
#define SYS_unlinkat 301
#define SYS_utime 30
#define SYS_utimensat 320
#define SYS_utimes 271
#define SYS_vfork 190
#define SYS_wait4 114
#define SYS_write 4
#define SYS_writev 146
#define O_LARGEFILE 0100000
#else
#define O_LARGEFILE 0
#endif

#ifndef __i386__
#define SYS_read 0
#define SYS_write 1
#define SYS_open 2
#define SYS_close 3
#define SYS_lseek 8
#define SYS_mmap 9
#define SYS_mprotect 10
#define SYS_munmap 11
#define SYS_ioctl 16
#define SYS_fork 57
#define SYS_execve 59
#define SYS_exit 60
#define SYS_wait4 61
#define SYS_getcwd 79
#define SYS_mkdir 83
#define SYS_unlink 87
#define SYS_mount 165
#define SYS_time 201
#define SYS_gettimeofday 96
#define SYS_stat 4
#define SYS_fstat 5
#define SYS_brk 12
#define SYS_rt_sigaction 13
#define SYS_rt_sigreturn 15
#define SYS_getpid 39
#define SYS_chdir 80
#define SYS_creat 85
#define SYS_chmod 90
#define SYS_pipe 22
#define SYS_dup 32
#define SYS_getuid 102
#endif

/* errno: the libc keeps the last error here. one program, one thread: a plain variable does it */
#ifdef C_DECLS_ONLY
extern int errno;
#else
int errno;
#endif
#define EPERM 1
#define ENOENT 2
#define ESRCH 3
#define EINTR 4
#define EIO 5
#define ENXIO 6
#define E2BIG 7
#define ENOEXEC 8
#define EBADF 9
#define ECHILD 10
#define EAGAIN 11
#define ENOMEM 12
#define EACCES 13
#define EFAULT 14
#define EBUSY 16
#define EEXIST 17
#define EXDEV 18
#define ENODEV 19
#define ENOTDIR 20
#define EISDIR 21
#define EINVAL 22
#define ENFILE 23
#define EMFILE 24
#define ENOTTY 25
#define ETXTBSY 26
#define EFBIG 27
#define ENOSPC 28
#define ESPIPE 29
#define EROFS 30
#define EMLINK 31
#define EPIPE 32
#define EDOM 33
#define ERANGE 34
#define EDEADLK 35
#define ENAMETOOLONG 36
#define ENOSYS 38
#define ENOTEMPTY 39
#define ELOOP 40
#define ENODATA 61
#define EOVERFLOW 75
#define EILSEQ 84
#define EOPNOTSUPP 95
#define ETIMEDOUT 110
#define ESTALE 116
#define EDQUOT 122
#ifndef C_DECLS_ONLY
static long fail(long r) { if (r < 0 && r > -4096) { errno = -r; return -1; } return r; }
#endif

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 0100
#define O_TRUNC 01000
#define O_APPEND 02000
#define O_EXCL 0200          /* [rifle] */
#define O_NOCTTY 0400
#define O_NONBLOCK 04000
#define O_SYNC 04010000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW 0400000
#define O_CLOEXEC 02000000
#define AT_FDCWD (-100)
#define AT_SYMLINK_NOFOLLOW 0x100
#define AT_REMOVEDIR 0x200
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
#define _SC_PAGESIZE 30

ssize_t read(int fd, void *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_read, fd, buf, n)); }
#endif
ssize_t write(int fd, const void *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_write, fd, buf, n)); }
#endif
int open(const char *path, int flags, ...)
#ifdef C_DECLS_ONLY
;
#else
{
    va_list ap; int mode;
    va_start(ap, flags); mode = va_arg(ap, int); va_end(ap);
    return fail(sys3(SYS_open, path, flags | O_LARGEFILE, flags & O_CREAT ? mode : 0));
}
#endif
int close(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_close, fd)); }
#endif
#ifdef __i386__
/* i386 hands 64-bit offsets over in two halves, high first for _llseek */
off_t lseek(int fd, off_t off, int whence)
#ifdef C_DECLS_ONLY
;
#else
{
    off_t r;
    if (fail(sys6(SYS_lseek, fd, (long)(off >> 32), (long)off, (long)&r, whence, 0)) < 0) return -1;
    return r;
}
#endif
#else
off_t lseek(int fd, off_t off, int whence)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_lseek, fd, off, whence)); }
#endif
#endif
int ioctl(int fd, unsigned long req, void *arg)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_ioctl, fd, req, arg)); }
#endif
int mprotect(void *p, size_t n, int prot)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_mprotect, p, n, prot)); }
#endif
int unlink(const char *path)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_unlink, path)); }
#endif
int mkdir(const char *path, mode_t mode)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_mkdir, path, mode)); }
#endif
pid_t fork(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys0(SYS_fork)); }
#endif
int execve(const char *path, char *const argv[], char *const envp[])
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_execve, path, argv, envp)); }
#endif
pid_t waitpid(pid_t pid, int *status, int options)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_wait4, pid, (long)status, options, 0, 0, 0)); }
#endif
int mount(const char *src, const char *dst, const char *type, unsigned long flags, const void *data)
#ifdef C_DECLS_ONLY
;
#else
{
    return fail(sys6(SYS_mount, (long)src, (long)dst, (long)type, flags, (long)data, 0));
}
#endif
char *getcwd(char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_getcwd, buf, n)) < 0 ? NULL : buf; }
#endif
time_t time(time_t *t)
#ifdef C_DECLS_ONLY
;
#else
{ time_t now = sys1(SYS_time, 0); if (t) *t = now; return now; }
#endif
long sysconf(int name)
#ifdef C_DECLS_ONLY
;
#else
{ return name == _SC_PAGESIZE ? 4096 : -1; }
#endif
int creat(const char *path, mode_t mode)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_creat, path, mode)); }
#endif
int chdir(const char *path)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_chdir, path)); }
#endif
int chmod(const char *path, mode_t mode)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_chmod, path, mode)); }
#endif
int dup(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_dup, fd)); }
#endif
int pipe(int fd[2])
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_pipe, fd)); }
#endif
pid_t getpid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_getpid); }
#endif
int getuid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_getuid); }
#endif
pid_t wait(int *status)
#ifdef C_DECLS_ONLY
;
#else
{ return waitpid(-1, status, 0); }
#endif

/* the end of the data segment, the "break". brk(p) moves it to p, sbrk(n) moves it n bytes and returns where it was */
#ifndef C_DECLS_ONLY
static char *cur_brk;
#endif
int brk(void *p)
#ifdef C_DECLS_ONLY
;
#else
{
    char *r = (char *)sys1(SYS_brk, p);
    cur_brk = r;
    if (r != p) { errno = ENOMEM; return -1; }
    return 0;
}
#endif
void *sbrk(long n)
#ifdef C_DECLS_ONLY
;
#else
{
    char *old;
    if (!cur_brk) cur_brk = (char *)sys1(SYS_brk, 0);
    old = cur_brk;
    if (n && brk(old + n) < 0) return (void *)-1;
    return old;
}
#endif

/* ---- files' details ---- */
#ifdef __i386__
/* the kernel's stat64 */
struct stat {
    unsigned long long st_dev;
    unsigned int pad0, st_ino32, st_mode, st_nlink, st_uid, st_gid;
    unsigned long long st_rdev;
    unsigned int pad1;
    long long st_size;
    unsigned long st_blksize;
    unsigned long long st_blocks;
    unsigned long st_atime, st_atime_nsec, st_mtime, st_mtime_nsec, st_ctime, st_ctime_nsec;
    unsigned long long st_ino;
};
#else
struct stat {
    unsigned long st_dev, st_ino, st_nlink;
    unsigned int st_mode, st_uid, st_gid, pad0;
    unsigned long st_rdev;
    long st_size, st_blksize, st_blocks;
    unsigned long st_atime, st_atime_nsec, st_mtime, st_mtime_nsec, st_ctime, st_ctime_nsec;
    long unused[3];
};
#endif
#define S_IFMT 0170000
#define S_IFDIR 0040000
#define S_IFCHR 0020000
#define S_IFREG 0100000
#define S_IFBLK 0060000     /* [rifle] */
#define S_IFIFO 0010000
#define S_IFLNK 0120000
#define S_IFSOCK 0140000
#define S_ISUID 04000
#define S_ISGID 02000
#define S_ISVTX 01000
#define S_IRWXU 0700
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXG 070
#define S_IRGRP 040
#define S_IWGRP 020
#define S_IXGRP 010
#define S_IRWXO 07
#define S_IROTH 04
#define S_IWOTH 02
#define S_IXOTH 01
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)
int stat(const char *path, struct stat *st)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_stat, path, st)); }
#endif
int fstat(int fd, struct stat *st)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_fstat, fd, st)); }
#endif

/* ---- the terminal ---- */
struct termios { unsigned int c_iflag, c_oflag, c_cflag, c_lflag; unsigned char c_line, c_cc[19]; };
#define TCGETS 0x5401
#define TCSETSW 0x5403
#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VTIME 5
#define VMIN 6
#define ICRNL 0400
#define IXON 02000
#define OPOST 01
#define ONLCR 04
#define TAB3 014000
#define ISIG 01
#define ICANON 02
#define ECHO 010
#define IEXTEN 0100000
int tcgetattr(int fd, struct termios *t)
#ifdef C_DECLS_ONLY
;
#else
{ return ioctl(fd, TCGETS, t); }
#endif
int tcsetattr(int fd, int when, struct termios *t)
#ifdef C_DECLS_ONLY
;
#else
{ (void)when; return ioctl(fd, TCSETSW, t); }
#endif
int isatty(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ struct termios t; return tcgetattr(fd, &t) == 0; }
#endif

/* ---- signals ----
 * signal(n, f): f runs when signal n comes. SIG_DFL (0) puts back what the kernel does, SIG_IGN (1) ignores it.
 * the kernel needs a way back from f: restore_rt, which asks it to carry on where the signal hit */
typedef void (*sighandler_t)(int);
#define SIG_DFL ((sighandler_t)0)
#define SIG_IGN ((sighandler_t)1)
#define SIG_ERR ((sighandler_t)-1)
#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGKILL 9
#define SIGTERM 15
#define SIGCHLD 17
#ifdef C_DECLS_ONLY
extern void c_restore_rt(void);
#else
void c_restore_rt(void);
#endif
#ifdef __i386__
#ifndef C_DECLS_ONLY
__asm__(".text\n.global c_restore_rt\nc_restore_rt:\n mov $173,%eax\n int $0x80\n");
#endif
#else
#ifndef C_DECLS_ONLY
__asm__(".text\n.global c_restore_rt\nc_restore_rt:\n mov $15,%rax\n syscall\n");
#endif
#endif
struct c_sigaction { sighandler_t handler; unsigned long flags; void (*restorer)(void); unsigned long long mask; };
sighandler_t signal(int n, sighandler_t f)
#ifdef C_DECLS_ONLY
;
#else
{
    struct c_sigaction new = { f, 0x04000000 | 0x10000000 /* restorer, restart */, c_restore_rt, 0 }, old;
    if (fail(sys6(SYS_rt_sigaction, n, (long)&new, (long)&old, 8, 0, 0)) < 0) return SIG_ERR;
    return old.handler;
}
#endif
__attribute__((noreturn)) void _exit(int code)
#ifdef C_DECLS_ONLY
;
#else
{ for (;;) sys1(SYS_exit, code); }
#endif

/* ---- more system calls [rifle] ---- */
#ifndef __i386__
#define SYS_lstat 6
#define SYS_access 21
#define SYS_mremap 25
#define SYS_dup2 33
#define SYS_nanosleep 35
#define SYS_kill 62
#define SYS_uname 63
#define SYS_fcntl 72
#define SYS_fsync 74
#define SYS_fdatasync 75
#define SYS_truncate 76
#define SYS_ftruncate 77
#define SYS_rename 82
#define SYS_rmdir 84
#define SYS_link 86
#define SYS_symlink 88
#define SYS_readlink 89
#define SYS_fchmod 91
#define SYS_chown 92
#define SYS_fchown 93
#define SYS_lchown 94
#define SYS_umask 95
#define SYS_getgid 104
#define SYS_geteuid 107
#define SYS_getegid 108
#define SYS_getppid 110
#define SYS_getgroups 115
#define SYS_mknod 133
#define SYS_sync 162
#define SYS_sethostname 170
#define SYS_sched_getaffinity 204
#define SYS_getdents64 217
#define SYS_clock_gettime 228
#define SYS_utimensat 280
#define SYS_openat 257
#define SYS_mkdirat 258
#define SYS_newfstatat 262
#define SYS_unlinkat 263
#define SYS_syncfs 306
#define SYS_statfs 137
#define SYS_fstatfs 138
#define SYS_getrandom 318
#define SYS_fchdir 81
#define SYS_pread64 17
#define SYS_pwrite64 18
#define SYS_sysinfo 99
#define SYS_chroot 161
#define SYS_setuid 105
#define SYS_setgid 106
#define SYS_times 100
#define SYS_getpgid 121
#define SYS_setsid 112
#define SYS_sendfile 40
#define SYS_copy_file_range 326
#endif
#define F_GETFL 3
#define F_SETFL 4
#define F_GETFD 1
#define F_SETFD 2
#define FD_CLOEXEC 1
#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0
#define UTIME_NOW ((1L << 30) - 1L)
#define UTIME_OMIT ((1L << 30) - 2L)
struct timespec { long tv_sec, tv_nsec; };
struct utsname { char sysname[65], nodename[65], release[65], version[65], machine[65], domainname[65]; };
struct statfs {
    long f_type, f_bsize;
    unsigned long f_blocks, f_bfree, f_bavail, f_files, f_ffree;
    int f_fsid[2];
    long f_namelen, f_frsize, f_flags, f_spare[4];
};
int lstat(const char *path, struct stat *st)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_lstat, path, st)); }
#endif
int fstatat(int dirfd, const char *path, struct stat *st, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_newfstatat, dirfd, (long)path, (long)st, flags, 0, 0)); }
#endif
int openat(int dirfd, const char *path, int flags, ...)
#ifdef C_DECLS_ONLY
;
#else
{
    va_list ap; int mode;
    va_start(ap, flags); mode = va_arg(ap, int); va_end(ap);
    return fail(sys6(SYS_openat, dirfd, (long)path, flags | O_LARGEFILE, flags & O_CREAT ? mode : 0, 0, 0));
}
#endif
int unlinkat(int dirfd, const char *path, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_unlinkat, dirfd, path, flags)); }
#endif
int mkdirat(int dirfd, const char *path, mode_t mode)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_mkdirat, dirfd, path, mode)); }
#endif
int rmdir(const char *path)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_rmdir, path)); }
#endif
int rename(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_rename, a, b)); }
#endif
int link(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_link, a, b)); }
#endif
int symlink(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_symlink, a, b)); }
#endif
ssize_t readlink(const char *path, char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_readlink, path, buf, n)); }
#endif
int fchmod(int fd, mode_t mode)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_fchmod, fd, mode)); }
#endif
int chown(const char *path, uid_t u, gid_t g)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_chown, path, u, g)); }
#endif
int lchown(const char *path, uid_t u, gid_t g)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_lchown, path, u, g)); }
#endif
int fchown(int fd, uid_t u, gid_t g)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_fchown, fd, u, g)); }
#endif
mode_t umask(mode_t m)
#ifdef C_DECLS_ONLY
;
#else
{ return sys1(SYS_umask, m); }
#endif
int access(const char *path, int mode)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_access, path, mode)); }
#endif
#ifdef __i386__
int truncate(const char *path, off_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_truncate, path, (long)n, (long)(n >> 32))); }
#endif
int ftruncate(int fd, off_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_ftruncate, fd, (long)n, (long)(n >> 32))); }
#endif
#else
int truncate(const char *path, off_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_truncate, path, n)); }
#endif
int ftruncate(int fd, off_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_ftruncate, fd, n)); }
#endif
#endif
int fsync(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_fsync, fd)); }
#endif
int fdatasync(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_fdatasync, fd)); }
#endif
void sync(void)
#ifdef C_DECLS_ONLY
;
#else
{ sys0(SYS_sync); }
#endif
int syncfs(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_syncfs, fd)); }
#endif
int mknod(const char *path, mode_t mode, dev_t dev)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_mknod, path, mode, dev)); }
#endif
int mkfifo(const char *path, mode_t mode)
#ifdef C_DECLS_ONLY
;
#else
{ return mknod(path, (mode & 07777) | S_IFIFO, 0); }
#endif
int dup2(int a, int b)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_dup2, a, b)); }
#endif
int fcntl(int fd, int cmd, long arg)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_fcntl, fd, cmd, arg)); }
#endif
int fchdir(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_fchdir, fd)); }
#endif
int kill(pid_t pid, int sig)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_kill, pid, sig)); }
#endif
int uname(struct utsname *u)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_uname, u)); }
#endif
int sethostname(const char *name, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_sethostname, name, n)); }
#endif
int nanosleep(const struct timespec *req, struct timespec *rem)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_nanosleep, req, rem)); }
#endif
int clock_gettime(int clk, struct timespec *t)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_clock_gettime, clk, t)); }
#endif
int utimensat(int dirfd, const char *path, const struct timespec t[2], int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_utimensat, dirfd, (long)path, (long)t, flags, 0, 0)); }
#endif
int statfs(const char *path, struct statfs *s)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_statfs, path, s)); }
#endif
pid_t getppid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_getppid); }
#endif
uid_t geteuid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_geteuid); }
#endif
gid_t getgid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_getgid); }
#endif
gid_t getegid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_getegid); }
#endif
int getgroups(int n, gid_t *list)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_getgroups, n, list)); }
#endif
int sched_getaffinity(pid_t pid, size_t n, void *mask)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_sched_getaffinity, pid, n, mask)); }
#endif
ssize_t getrandom(void *buf, size_t n, unsigned flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_getrandom, buf, n, flags)); }
#endif
#ifdef __i386__
ssize_t pread(int fd, void *buf, size_t n, off_t off)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_pread64, fd, (long)buf, n, (long)off, (long)(off >> 32), 0)); }
#endif
ssize_t pwrite(int fd, const void *buf, size_t n, off_t off)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_pwrite64, fd, (long)buf, n, (long)off, (long)(off >> 32), 0)); }
#endif
#else
ssize_t pread(int fd, void *buf, size_t n, off_t off)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_pread64, fd, (long)buf, n, off, 0, 0)); }
#endif
ssize_t pwrite(int fd, const void *buf, size_t n, off_t off)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_pwrite64, fd, (long)buf, n, off, 0, 0)); }
#endif
#endif
int setuid(uid_t u)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_setuid, u)); }
#endif
int setgid(gid_t g)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_setgid, g)); }
#endif
int chroot(const char *path)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_chroot, path)); }
#endif
#define major(d) ((unsigned)((((d) >> 32) & 0xfffff000) | (((d) >> 8) & 0xfff)))
#define minor(d) ((unsigned)((((d) >> 12) & 0xffffff00) | ((d) & 0xff)))
#define makedev(ma, mi) ((dev_t)((((unsigned long long)(ma) & 0xfffff000ULL) << 32) | (((unsigned long long)(ma) & 0xfffULL) << 8) | \
                                 (((unsigned long long)(mi) & 0xffffff00ULL) << 12) | ((unsigned long long)(mi) & 0xffULL)))

/* ---- characters ---- */
int isdigit(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c >= '0' && c <= '9'; }
#endif
int isalpha(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return (c | 32) >= 'a' && (c | 32) <= 'z'; }
#endif
int isalnum(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return isalpha(c) || isdigit(c); }
#endif
int isspace(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c == ' ' || (c >= '\t' && c <= '\r'); }
#endif
int isupper(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c >= 'A' && c <= 'Z'; }
#endif
int islower(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c >= 'a' && c <= 'z'; }
#endif
int isxdigit(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return isdigit(c) || ((c | 32) >= 'a' && (c | 32) <= 'f'); }
#endif
int isprint(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c >= 32 && c < 127; }
#endif
int ispunct(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return isprint(c) && c != ' ' && !isalnum(c); }
#endif   /* [rifle] */
int toupper(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return islower(c) ? c - 32 : c; }
#endif
int tolower(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return isupper(c) ? c + 32 : c; }
#endif

/* ---- strings ---- */
size_t strlen(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ size_t n = 0; while (s[n]) n++; return n; }
#endif
int strcmp(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{ while (*a && *a == *b) a++, b++; return (unsigned char)*a - (unsigned char)*b; }
#endif
int strncmp(const char *a, const char *b, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    for (; n && *a && *a == *b; n--) a++, b++;
    return n ? (unsigned char)*a - (unsigned char)*b : 0;
}
#endif
char *strcpy(char *d, const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ char *r = d; while ((*d++ = *s++)); return r; }
#endif
char *strncpy(char *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t i = 0; for (; i < n && s[i]; i++) d[i] = s[i]; for (; i < n; i++) d[i] = 0; return d; }
#endif
char *strcat(char *d, const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ strcpy(d + strlen(d), s); return d; }
#endif
char *strchr(const char *s, int c)
#ifdef C_DECLS_ONLY
;
#else
{ for (;; s++) { if (*s == (char)c) return (char *)s; if (!*s) return NULL; } }
#endif
char *strrchr(const char *s, int c)
#ifdef C_DECLS_ONLY
;
#else
{ const char *r = NULL; for (;; s++) { if (*s == (char)c) r = s; if (!*s) return (char *)r; } }
#endif
char *strstr(const char *h, const char *n)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(n);
    for (; *h; h++) if (!strncmp(h, n, l)) return (char *)h;
    return l ? NULL : (char *)h;
}
#endif
char *strpbrk(const char *s, const char *set)
#ifdef C_DECLS_ONLY
;
#else
{ for (; *s; s++) if (strchr(set, *s)) return (char *)s; return NULL; }
#endif
void *memcpy(void *d, const void *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ char *a = d; const char *b = s; while (n--) *a++ = *b++; return d; }
#endif
void *memmove(void *d, const void *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    char *a = d; const char *b = s;
    if (a < b) while (n--) *a++ = *b++;
    else while (n--) a[n] = b[n];
    return d;
}
#endif
void *memset(void *d, int c, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ char *a = d; while (n--) *a++ = c; return d; }
#endif
int memcmp(const void *x, const void *y, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    const unsigned char *a = x, *b = y;
    for (; n; n--, a++, b++) if (*a != *b) return *a - *b;
    return 0;
}
#endif
void *memchr(const void *s, int c, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ const unsigned char *p = s; for (; n; n--, p++) if (*p == (unsigned char)c) return (void *)p; return NULL; }
#endif
/* the messages are glibc's, so what rifle says matches what everyone's scripts expect [rifle] */
#ifndef C_DECLS_ONLY
static const struct { int e; const char *m; } c_errlist[] = {
    { EPERM, "Operation not permitted" }, { ENOENT, "No such file or directory" }, { ESRCH, "No such process" },
    { EINTR, "Interrupted system call" }, { EIO, "Input/output error" }, { ENXIO, "No such device or address" },
    { E2BIG, "Argument list too long" }, { ENOEXEC, "Exec format error" }, { EBADF, "Bad file descriptor" },
    { ECHILD, "No child processes" }, { EAGAIN, "Resource temporarily unavailable" }, { ENOMEM, "Cannot allocate memory" },
    { EACCES, "Permission denied" }, { EFAULT, "Bad address" }, { EBUSY, "Device or resource busy" },
    { EEXIST, "File exists" }, { EXDEV, "Invalid cross-device link" }, { ENODEV, "No such device" },
    { ENOTDIR, "Not a directory" }, { EISDIR, "Is a directory" }, { EINVAL, "Invalid argument" },
    { ENFILE, "Too many open files in system" }, { EMFILE, "Too many open files" },
    { ENOTTY, "Inappropriate ioctl for device" }, { ETXTBSY, "Text file busy" }, { EFBIG, "File too large" },
    { ENOSPC, "No space left on device" }, { ESPIPE, "Illegal seek" }, { EROFS, "Read-only file system" },
    { EMLINK, "Too many links" }, { EPIPE, "Broken pipe" }, { EDOM, "Numerical argument out of domain" },
    { ERANGE, "Numerical result out of range" }, { EDEADLK, "Resource deadlock avoided" },
    { ENAMETOOLONG, "File name too long" }, { ENOSYS, "Function not implemented" },
    { ENOTEMPTY, "Directory not empty" }, { ELOOP, "Too many levels of symbolic links" },
    { ENODATA, "No data available" }, { EOVERFLOW, "Value too large for defined data type" },
    { EILSEQ, "Invalid or incomplete multibyte or wide character" }, { EOPNOTSUPP, "Operation not supported" },
    { ETIMEDOUT, "Connection timed out" }, { ESTALE, "Stale file handle" }, { EDQUOT, "Disk quota exceeded" },
};
#endif
#ifdef C_DECLS_ONLY
extern int snprintf(char *buf, size_t cap, const char *fmt, ...);
#else
int snprintf(char *buf, size_t cap, const char *fmt, ...);
#endif
char *strerror(int e)
#ifdef C_DECLS_ONLY
;
#else
{
    static char unknown[32];
    unsigned i;
    for (i = 0; i < sizeof c_errlist / sizeof c_errlist[0]; i++) if (c_errlist[i].e == e) return (char *)c_errlist[i].m;
    snprintf(unknown, sizeof unknown, "Unknown error %d", e);
    return unknown;
}
#endif

/* ---- memory ----
 * [rifle] small blocks (up to 2032 bytes) come from 256K chunks and go on a list for their size when freed, big
 * blocks are their own mmap and grow with mremap. every block has 16 bytes in front of it holding its size. */
#define MALLOC_BIG 2048
#ifndef C_DECLS_ONLY
static void *malloc_lists[12];
#endif
#ifndef C_DECLS_ONLY
static char *malloc_cur, *malloc_end;
#endif
#ifndef C_DECLS_ONLY
static void *c_mmap(size_t len)
{
    long p = sys6(SYS_mmap, 0, len, PROT_READ | PROT_WRITE, 0x22 /* private, anonymous */, -1, 0);
    return (p < 0 && p > -4096) ? NULL : (void *)p;
}
#endif
void *malloc(size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t need = n + 16;
    if (need < n) { errno = ENOMEM; return NULL; }
    if (need <= MALLOC_BIG) {
        size_t sz = 32; int cl = 5;
        while (sz < need) { sz <<= 1; cl++; }
        char *b = malloc_lists[cl];
        if (b) { malloc_lists[cl] = *(void **)(b + 16); return b + 16; }
        if (malloc_cur + sz > malloc_end) {
            malloc_cur = c_mmap(256 * 1024);
            if (!malloc_cur) { malloc_end = NULL; errno = ENOMEM; return NULL; }
            malloc_end = malloc_cur + 256 * 1024;
        }
        b = malloc_cur; malloc_cur += sz;
        *(size_t *)b = sz;
        return b + 16;
    }
    size_t len = (need + 4095) & ~4095UL;
    if (len < need) { errno = ENOMEM; return NULL; }
    char *p = c_mmap(len);
    if (!p) { errno = ENOMEM; return NULL; }
    *(size_t *)p = len;
    return p + 16; /* 16: what a long double or an SSE value wants */
}
#endif
void free(void *p)
#ifdef C_DECLS_ONLY
;
#else
{
    if (!p) return;
    char *h = (char *)p - 16;
    size_t sz = *(size_t *)h;
    if (sz <= MALLOC_BIG) {
        int cl = 5; size_t c = 32;
        while (c < sz) { c <<= 1; cl++; }
        *(void **)p = malloc_lists[cl]; malloc_lists[cl] = h;
    } else sys2(SYS_munmap, h, sz);
}
#endif
void *calloc(size_t n, size_t m)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t total = n * m;
    if (m && total / m != n) { errno = ENOMEM; return NULL; }
    void *p = malloc(total);
    if (p && total + 16 <= MALLOC_BIG) memset(p, 0, total); /* big blocks come from mmap, already zero */
    return p;
}
#endif
void *realloc(void *p, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    if (!p) return malloc(n);
    char *h = (char *)p - 16;
    size_t sz = *(size_t *)h, old = sz - 16;
    if (n <= old) return p;
    if (sz > MALLOC_BIG && n + 16 > n) {
        size_t len = (n + 16 + 4095) & ~4095UL;
        long q = sys6(SYS_mremap, (long)h, sz, len, 1 /* may move */, 0, 0);
        if (q < 0 && q > -4096) { errno = ENOMEM; return NULL; }
        *(size_t *)q = len;
        return (char *)q + 16;
    }
    void *q = malloc(n);
    if (q) { memcpy(q, p, old); free(p); }
    return q;
}
#endif
size_t strspn(const char *s, const char *set)
#ifdef C_DECLS_ONLY
;
#else
{ size_t n = 0; while (s[n] && strchr(set, s[n])) n++; return n; }
#endif  /* [rifle] */
size_t strcspn(const char *s, const char *set)
#ifdef C_DECLS_ONLY
;
#else
{ size_t n = 0; while (s[n] && !strchr(set, s[n])) n++; return n; }
#endif
int strcasecmp(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{ while (*a && tolower(*a) == tolower(*b)) a++, b++; return tolower((unsigned char)*a) - tolower((unsigned char)*b); }
#endif
int strncasecmp(const char *a, const char *b, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    for (; n && *a && tolower(*a) == tolower(*b); n--) a++, b++;
    return n ? tolower((unsigned char)*a) - tolower((unsigned char)*b) : 0;
}
#endif
void *memrchr(const void *s, int c, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ const unsigned char *p = (const unsigned char *)s + n; while (n--) if (*--p == (unsigned char)c) return (void *)p; return NULL; }
#endif
char *strndup(const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t l = 0; char *d; while (l < n && s[l]) l++; d = malloc(l + 1); if (!d) return NULL; memcpy(d, s, l); d[l] = 0; return d; }
#endif
char *stpcpy(char *d, const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ while ((*d = *s++)) d++; return d; }
#endif
int abs(int x)
#ifdef C_DECLS_ONLY
;
#else
{ return x < 0 ? -x : x; }
#endif
long labs(long x)
#ifdef C_DECLS_ONLY
;
#else
{ return x < 0 ? -x : x; }
#endif
char *strdup(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ char *d = malloc(strlen(s) + 1); return d ? strcpy(d, s) : NULL; }
#endif

/* ---- numbers from text ---- */
#ifndef C_DECLS_ONLY
static int digit_of(int c) { return isdigit(c) ? c - '0' : isalpha(c) ? (c | 32) - 'a' + 10 : 99; }
#endif
unsigned long long strtoull(const char *s, char **end, int base)
#ifdef C_DECLS_ONLY
;
#else
{
    const char *p = s; unsigned long long v = 0; int neg = 0, any = 0;
    while (isspace(*p)) p++;
    if (*p == '-' || *p == '+') neg = *p++ == '-';
    if ((base == 0 || base == 16) && p[0] == '0' && (p[1] | 32) == 'x' && isxdigit(p[2])) { p += 2; base = 16; }
    else if (base == 0) base = *p == '0' ? 8 : 10;
    for (; digit_of(*p) < base; p++, any = 1) v = v * base + digit_of(*p);
    if (end) *end = (char *)(any ? p : s);
    return neg ? -v : v;
}
#endif
long long strtoll(const char *s, char **end, int base)
#ifdef C_DECLS_ONLY
;
#else
{ return (long long)strtoull(s, end, base); }
#endif
unsigned long strtoul(const char *s, char **end, int base)
#ifdef C_DECLS_ONLY
;
#else
{ return strtoull(s, end, base); }
#endif
long strtol(const char *s, char **end, int base)
#ifdef C_DECLS_ONLY
;
#else
{ return strtoull(s, end, base); }
#endif
int atoi(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ return strtol(s, NULL, 10); }
#endif
long atol(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ return strtol(s, NULL, 10); }
#endif
long long atoll(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ return strtoll(s, NULL, 10); }
#endif

long double ldexpl(long double x, int e)
#ifdef C_DECLS_ONLY
;
#else
{
    while (e > 0) { x *= 2; e--; }
    while (e < 0) { x /= 2; e++; }
    return x;
}
#endif
double ldexp(double x, int e)
#ifdef C_DECLS_ONLY
;
#else
{ return ldexpl(x, e); }
#endif
/* decimal and hex floating point. good to the last digit or so, not correctly rounded in every case */
long double strtold(const char *s, char **end)
#ifdef C_DECLS_ONLY
;
#else
{
    const char *p = s; long double v = 0; int neg = 0, any = 0, ex = 0;
    while (isspace(*p)) p++;
    if (*p == '-' || *p == '+') neg = *p++ == '-';
    if (p[0] == '0' && (p[1] | 32) == 'x') {
        p += 2;
        for (; isxdigit(*p); p++, any = 1) v = v * 16 + digit_of(*p);
        if (*p == '.') for (p++; isxdigit(*p); p++, any = 1) { v = v * 16 + digit_of(*p); ex -= 4; }
        if (any && (*p | 32) == 'p') { char *e2; long x = strtol(p + 1, &e2, 10); if (e2 != p + 1) { ex += x; p = e2; } }
        v = ldexpl(v, ex);
    } else {
        for (; isdigit(*p); p++, any = 1) v = v * 10 + (*p - '0');
        if (*p == '.') for (p++; isdigit(*p); p++, any = 1) { v = v * 10 + (*p - '0'); ex--; }
        if (any && (*p | 32) == 'e') { char *e2; long x = strtol(p + 1, &e2, 10); if (e2 != p + 1) { ex += x; p = e2; } }
        for (; ex > 0; ex--) v *= 10;
        for (; ex < 0; ex++) v /= 10;
    }
    if (end) *end = (char *)(any ? p : s);
    return neg ? -v : v;
}
#endif
double strtod(const char *s, char **end)
#ifdef C_DECLS_ONLY
;
#else
{ return strtold(s, end); }
#endif
float strtof(const char *s, char **end)
#ifdef C_DECLS_ONLY
;
#else
{ return strtold(s, end); }
#endif
double atof(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ return strtod(s, NULL); }
#endif

/* ---- sorting ---- */
#ifndef C_DECLS_ONLY
static void swap_bytes(char *a, char *b, size_t n) { while (n--) { char t = *a; *a++ = *b; *b++ = t; } }
#endif
void qsort(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *))
#ifdef C_DECLS_ONLY
;
#else
{
    /* shell sort: short, no recursion, fine for the sizes a compiler sorts */
    char *b = base; size_t gap, i, j;
    for (gap = n / 2; gap; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i; j >= gap && cmp(b + (j - gap) * size, b + j * size) > 0; j -= gap)
                swap_bytes(b + (j - gap) * size, b + j * size, size);
}
#endif

/* ---- jumps ---- */
typedef long jmp_buf[8];
#ifdef C_DECLS_ONLY
extern int setjmp(jmp_buf b);
#else
int setjmp(jmp_buf b);
#endif
#ifdef C_DECLS_ONLY
extern __attribute__((noreturn)) void longjmp(jmp_buf b, int v);
#else
__attribute__((noreturn)) void longjmp(jmp_buf b, int v);
#endif
#ifdef __i386__
#ifndef C_DECLS_ONLY
__asm__(".text\n.global setjmp\n.global _setjmp\nsetjmp:\n_setjmp:\n"
        " mov 4(%esp),%eax\n mov %ebx,(%eax)\n mov %esi,4(%eax)\n mov %edi,8(%eax)\n mov %ebp,12(%eax)\n"
        " lea 4(%esp),%ecx\n mov %ecx,16(%eax)\n mov (%esp),%ecx\n mov %ecx,20(%eax)\n xor %eax,%eax\n ret\n"
        ".global longjmp\nlongjmp:\n"
        " mov 4(%esp),%edx\n mov 8(%esp),%eax\n test %eax,%eax\n jnz 1f\n inc %eax\n1:\n"
        " mov (%edx),%ebx\n mov 4(%edx),%esi\n mov 8(%edx),%edi\n mov 12(%edx),%ebp\n mov 16(%edx),%esp\n jmp *20(%edx)\n");
#endif
#else
#ifndef C_DECLS_ONLY
__asm__(".text\n.global setjmp\n.global _setjmp\nsetjmp:\n_setjmp:\n"
        " mov %rbx,(%rdi)\n mov %rbp,8(%rdi)\n mov %r12,16(%rdi)\n mov %r13,24(%rdi)\n mov %r14,32(%rdi)\n"
        " mov %r15,40(%rdi)\n lea 8(%rsp),%rdx\n mov %rdx,48(%rdi)\n mov (%rsp),%rdx\n mov %rdx,56(%rdi)\n"
        " xor %eax,%eax\n ret\n"
        ".global longjmp\nlongjmp:\n"
        " mov %esi,%eax\n test %eax,%eax\n jnz 1f\n inc %eax\n1:\n"
        " mov (%rdi),%rbx\n mov 8(%rdi),%rbp\n mov 16(%rdi),%r12\n mov 24(%rdi),%r13\n mov 32(%rdi),%r14\n"
        " mov 40(%rdi),%r15\n mov 48(%rdi),%rsp\n jmp *56(%rdi)\n");
#endif
#endif

/* ---- time ---- */
struct tm { int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst; };
/* there are no time zones here: local time is UTC */
struct tm *localtime(const time_t *t)
#ifdef C_DECLS_ONLY
;
#else
{
    static struct tm r;
    long s = *t, days = s / 86400, rem = s % 86400, y = 1970;
    static const int md[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    r.tm_hour = rem / 3600; r.tm_min = rem / 60 % 60; r.tm_sec = rem % 60;
    r.tm_wday = (days + 4) % 7;
    for (;;) {
        int len = (y % 4 == 0 && (y % 100 || y % 400 == 0)) ? 366 : 365;
        if (days < len) break;
        days -= len; y++;
    }
    r.tm_year = y - 1900; r.tm_yday = days;
    for (r.tm_mon = 0; ; r.tm_mon++) {
        int len = md[r.tm_mon] + (r.tm_mon == 1 && (y % 4 == 0 && (y % 100 || y % 400 == 0)));
        if (days < len) break;
        days -= len;
    }
    r.tm_mday = days + 1; r.tm_isdst = 0;
    return &r;
}
#endif
struct tm *gmtime(const time_t *t)
#ifdef C_DECLS_ONLY
;
#else
{ return localtime(t); }
#endif
struct timeval { long tv_sec, tv_usec; };
int gettimeofday(struct timeval *tv, void *tz)
#ifdef C_DECLS_ONLY
;
#else
{ (void)tz; return fail(sys2(SYS_gettimeofday, tv, 0)); }
#endif

/* ---- files with buffers ----
 * a FILE reads or writes through one buffer. write: n bytes wait to go out. read: [pos, n) is what is left.
 * ug is a pushed back character plus one, mode is 0 full, 1 line, 2 none buffered, 3 not asked yet */
typedef struct FILE { int fd, write, err, eof, n, pos, line, ug, mode, rd, wr, pid, append; struct FILE *next; char buf[4096]; } FILE;
typedef long fpos_t;
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2
#ifndef C_DECLS_ONLY
static FILE files_std[3] = { { 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0 }, { 1, 1, 0, 0, 0, 0, 0, 0, 3, 0, 1 }, { 2, 1, 0, 0, 0, 0, 0, 0, 2, 0, 1 } };
#endif
#ifndef C_DECLS_ONLY
static FILE *c_files;
#endif
/*nosplit*/
#ifdef C_DECLS_ONLY
extern FILE *stdin, *stdout, *stderr;
#else
#ifdef C_DECLS_ONLY
extern FILE *stdin;
#else
FILE *stdin = &files_std[0], *stdout = &files_std[1], *stderr = &files_std[2];
#endif
#endif
#define EOF (-1)
#define BUFSIZ 4096
#define FILENAME_MAX 4096
#define FOPEN_MAX 16
#define L_tmpnam 20
#define TMP_MAX 238328

#ifndef C_DECLS_ONLY
static int flush_one(FILE *f)
{
    if (f->write && f->n) {
        int off = 0;
        while (off < f->n) { ssize_t w = write(f->fd, f->buf + off, f->n - off); if (w <= 0) { if (w < 0 && errno == EINTR) continue; f->err = 1; break; } off += w; }
        f->n = 0;
    }
    return f->err ? EOF : 0;
}
#endif
int fflush(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    if (!f) {
        FILE *p;
        int r = 0;
        for (p = c_files; p; p = p->next) if (flush_one(p)) r = EOF;
        for (p = files_std; p < files_std + 3; p++) if (flush_one(p)) r = EOF;
        return r;
    }
    if (!f->write && f->n > f->pos && f->rd && !f->wr) return 0;
    return flush_one(f);
}
#endif
/* going from writing to reading, or back: whatever is buffered goes first, or the file position is put right */
#ifndef C_DECLS_ONLY
static int switch_to(FILE *f, int writing)
{
    if (writing && !f->write) {
        if (f->n > f->pos || f->ug) lseek(f->fd, -(long)(f->n - f->pos) - (f->ug ? 1 : 0), SEEK_CUR);
        f->n = f->pos = 0; f->ug = 0; f->write = 1;
    } else if (!writing && f->write) {
        if (flush_one(f)) return -1;
        f->n = f->pos = 0; f->write = 0;
    }
    return 0;
}
#endif
#ifndef C_DECLS_ONLY
static int open_flags(const char *mode)
{
    int f = mode[0] == 'r' ? O_RDONLY : mode[0] == 'w' ? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;
    const char *m;
    if (strchr(mode, '+')) f = (f & ~(O_RDONLY | O_WRONLY)) | O_RDWR;
    for (m = mode; *m; m++) { if (*m == 'x') f |= O_EXCL; else if (*m == 'e') f |= O_CLOEXEC; }
    return f;
}
#endif
FILE *fdopen(int fd, const char *mode)
#ifdef C_DECLS_ONLY
;
#else
{
    FILE *f = calloc(1, sizeof *f);
    if (!f) return NULL;
    f->fd = fd; f->mode = 3;
    f->rd = mode[0] == 'r' || strchr(mode, '+') != NULL;
    f->wr = mode[0] != 'r' || strchr(mode, '+') != NULL;
    f->write = !f->rd;
    f->append = mode[0] == 'a';
    f->next = c_files; c_files = f;
    return f;
}
#endif
FILE *fopen(const char *path, const char *mode)
#ifdef C_DECLS_ONLY
;
#else
{
    int fd;
    if (mode[0] != 'r' && mode[0] != 'w' && mode[0] != 'a') { errno = EINVAL; return NULL; }
    fd = open(path, open_flags(mode), 0666);
    return fd < 0 ? NULL : fdopen(fd, mode);
}
#endif
FILE *freopen(const char *path, const char *mode, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    int fd;
    fflush(f);
    if (!path) return f;
    if ((fd = open(path, open_flags(mode), 0666)) < 0) return NULL;
    dup2(fd, f->fd); close(fd);
    f->rd = mode[0] == 'r' || strchr(mode, '+') != NULL;
    f->wr = mode[0] != 'r' || strchr(mode, '+') != NULL;
    f->write = !f->rd; f->n = f->pos = f->err = f->eof = f->ug = 0;
    return f;
}
#endif
int fclose(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    int r = flush_one(f);
    FILE **pp;
    close(f->fd);
    for (pp = &c_files; *pp; pp = &(*pp)->next) if (*pp == f) { *pp = f->next; break; }
    if (f < files_std || f > files_std + 2) free(f);
    return r;
}
#endif
int setvbuf(FILE *f, char *buf, int mode, size_t size)
#ifdef C_DECLS_ONLY
;
#else
{ (void)buf; (void)size; flush_one(f); f->mode = mode; return 0; }
#endif
void setbuf(FILE *f, char *buf)
#ifdef C_DECLS_ONLY
;
#else
{ setvbuf(f, buf, buf ? _IOFBF : _IONBF, BUFSIZ); }
#endif
void setbuffer(FILE *f, char *buf, size_t size)
#ifdef C_DECLS_ONLY
;
#else
{ setvbuf(f, buf, buf ? _IOFBF : _IONBF, size); }
#endif
void setlinebuf(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ setvbuf(f, NULL, _IOLBF, 0); }
#endif
/* stdout is flushed at every newline when it's a terminal, and when it's a pipe or a file only when full, like
 * everything else does. stderr always goes out at once [rifle] */
size_t fwrite(const void *p, size_t size, size_t n, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    const char *s = p; size_t len = size * n, left = len;
    if (size && len / size != n) return 0;
    if (!f->wr && f->rd) { f->err = 1; errno = EBADF; return 0; }
    if (switch_to(f, 1)) return 0;
    if (f->append) lseek(f->fd, 0, SEEK_END);
    while (left) {
        size_t room = BUFSIZ - f->n, c = left < room ? left : room;
        memcpy(f->buf + f->n, s, c);
        f->n += c; s += c; left -= c;
        if (f->n == BUFSIZ) flush_one(f);
    }
    if (f->mode == 3) f->mode = f == stdout ? (isatty(1) ? _IOLBF : _IOFBF) : _IOFBF;
    if (f->mode == _IONBF) flush_one(f);
    else if (f->mode == _IOLBF && len && memchr(p, '\n', len)) flush_one(f);
    return f->err ? 0 : n;
}
#endif
int fputc(int c, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ unsigned char ch = c; return fwrite(&ch, 1, 1, f) ? ch : EOF; }
#endif
int putc(int c, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fputc(c, f); }
#endif
int putchar(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return fputc(c, stdout); }
#endif
int fputs(const char *s, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ size_t l = strlen(s); return l && !fwrite(s, 1, l, f) ? EOF : 0; }
#endif
int puts(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ if (fputs(s, stdout) == EOF) return EOF; return putchar('\n') == EOF ? EOF : 0; }
#endif
#ifndef C_DECLS_ONLY
static int fill(FILE *f)
{
    ssize_t r;
    if (!f->rd && f->wr) { f->err = 1; errno = EBADF; return EOF; }
    if (switch_to(f, 0)) return EOF;
    if (f == stdin) fflush(stdout);
    do r = read(f->fd, f->buf, BUFSIZ); while (r < 0 && errno == EINTR);
    if (r <= 0) { if (r < 0) f->err = 1; else f->eof = 1; f->n = f->pos = 0; return EOF; }
    f->n = r; f->pos = 0;
    return 0;
}
#endif
int fgetc(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    if (f->ug) { int c = f->ug - 1; f->ug = 0; return c; }
    if (f->write || f->pos == f->n) { if (fill(f) == EOF) return EOF; }
    return (unsigned char)f->buf[f->pos++];
}
#endif
int ungetc(int c, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    if (c == EOF || f->ug) return EOF;
    if (f->write && switch_to(f, 0)) return EOF;
    f->ug = (unsigned char)c + 1; f->eof = 0;
    return (unsigned char)c;
}
#endif
int getc(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fgetc(f); }
#endif
int getchar(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fgetc(stdin); }
#endif
size_t fread(void *p, size_t size, size_t n, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    char *d = p; size_t len = size * n, i = 0; int c;
    if (size && len / size != n) return 0;
    while (i < len) {
        if (!f->ug && !f->write && f->pos < f->n) {
            size_t c2 = f->n - f->pos; if (c2 > len - i) c2 = len - i;
            memcpy(d + i, f->buf + f->pos, c2); f->pos += c2; i += c2;
        } else if ((c = fgetc(f)) == EOF) break;
        else d[i++] = c;
    }
    return size ? i / size : 0;
}
#endif
char *fgets(char *s, int n, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    int i = 0, c;
    if (n < 1) return NULL;
    while (i < n - 1 && (c = fgetc(f)) != EOF) { s[i++] = c; if (c == '\n') break; }
    s[i] = 0;
    return i ? s : NULL;
}
#endif
int feof(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return f->eof; }
#endif
int ferror(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return f->err; }
#endif
void clearerr(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ f->err = f->eof = 0; }
#endif
int fileno(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return f->fd; }
#endif
int fseek(FILE *f, long off, int whence)
#ifdef C_DECLS_ONLY
;
#else
{
    if (f->write) { if (flush_one(f)) return -1; }
    else if (whence == SEEK_CUR) off -= (f->n - f->pos) + (f->ug ? 1 : 0);
    f->n = f->pos = 0; f->eof = 0; f->ug = 0;
    return lseek(f->fd, off, whence) < 0 ? -1 : 0;
}
#endif
long ftell(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    long p = lseek(f->fd, 0, SEEK_CUR);
    return p < 0 ? -1 : f->write ? p + f->n : p - (f->n - f->pos) - (f->ug ? 1 : 0);
}
#endif
int fseeko(FILE *f, off_t off, int whence)
#ifdef C_DECLS_ONLY
;
#else
{ return fseek(f, off, whence); }
#endif
off_t ftello(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return ftell(f); }
#endif
void rewind(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ fseek(f, 0, SEEK_SET); f->err = 0; }
#endif
int fgetpos(FILE *f, fpos_t *p)
#ifdef C_DECLS_ONLY
;
#else
{ long v = ftell(f); if (v < 0) return -1; *p = v; return 0; }
#endif
int fsetpos(FILE *f, const fpos_t *p)
#ifdef C_DECLS_ONLY
;
#else
{ return fseek(f, *p, SEEK_SET); }
#endif
int remove(const char *path)
#ifdef C_DECLS_ONLY
;
#else
{ if (unlink(path) == 0) return 0; if (errno == EISDIR || errno == EPERM) return rmdir(path); return -1; }
#endif
void flockfile(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ (void)f; }
#endif
void funlockfile(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ (void)f; }
#endif
int ftrylockfile(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ (void)f; return 0; }
#endif
int getc_unlocked(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fgetc(f); }
#endif
int getchar_unlocked(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fgetc(stdin); }
#endif
int putc_unlocked(int c, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fputc(c, f); }
#endif
int putchar_unlocked(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return fputc(c, stdout); }
#endif
size_t fread_unlocked(void *p, size_t s, size_t n, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fread(p, s, n, f); }
#endif
size_t fwrite_unlocked(const void *p, size_t s, size_t n, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fwrite(p, s, n, f); }
#endif
int fflush_unlocked(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fflush(f); }
#endif
int feof_unlocked(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return f->eof; }
#endif
int ferror_unlocked(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return f->err; }
#endif
void perror(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ fflush(stdout); if (s && *s) { fputs(s, stderr); fputs(": ", stderr); } fputs(strerror(errno), stderr); fputc('\n', stderr); }
#endif

/* ---- printf ----
 * flags - + space # 0, width and precision (numbers or *), sizes hh h l ll z j t L,
 * conversions d i u o x X c s p f F e E g G and %% */
struct out { char *buf; size_t cap, len; FILE *f; };
#ifndef C_DECLS_ONLY
static void out_c(struct out *o, char c)
{
    if (o->f) fputc(c, o->f);
    else if (o->len + 1 < o->cap) o->buf[o->len] = c;
    o->len++;
}
#endif
#ifndef C_DECLS_ONLY
static void out_pad(struct out *o, char c, int n) { while (n-- > 0) out_c(o, c); }
#endif
#ifndef C_DECLS_ONLY
static void out_field(struct out *o, const char *pre, const char *s, int len, int width, int left, int zero)
{
    int plen = strlen(pre), pad = width - plen - len;
    if (!left && !zero) out_pad(o, ' ', pad);
    while (*pre) out_c(o, *pre++);
    if (!left && zero) out_pad(o, '0', pad);
    while (len-- > 0) out_c(o, *s++);
    if (left) out_pad(o, ' ', pad);
}
#endif
/* a long double as digits: fixed (f), exponent (e) or the shorter of both (g) */
#ifndef C_DECLS_ONLY
static int fmt_float(char *b, long double v, int prec, char conv, int alt)
{
    int n = 0, e = 0, i, upper = conv == 'E' || conv == 'G' || conv == 'F';
    char c = conv | 32;
    if (v != v) { strcpy(b, upper ? "NAN" : "nan"); return 3; }
    if (v > 1e4900L || v < -1e4900L) { strcpy(b, upper ? "INF" : "inf"); return 3; }
    if (prec < 0) prec = 6;
    if (v != 0) { long double a = v < 0 ? -v : v; while (a >= 10) { a /= 10; e++; } while (a < 1) { a *= 10; e--; } }
    if (c == 'g') {
        if (prec == 0) prec = 1;
        c = (e < -4 || e >= prec) ? 'e' : 'f';
        prec = c == 'e' ? prec - 1 : prec - 1 - e;
        if (prec < 0) prec = 0;
        if (!alt) alt = -1; /* -1: drop the trailing zeros */
    }
    long double a = v < 0 ? -v : v, r = 0.5L;
    if (c == 'e') { if (v != 0) { for (i = 0; i < e; i++) a /= 10; for (i = 0; i > e; i--) a *= 10; } }
    for (i = 0; i < prec; i++) r /= 10;
    a += r;
    if (c == 'e' && a >= 10) { a /= 10; e++; }
    long double ip = 1; int idig = 1;
    while (ip * 10 <= a) { ip *= 10; idig++; }
    for (i = 0; i < idig; i++) { int d = (int)(a / ip); if (d > 9) d = 9; b[n++] = '0' + d; a -= d * ip; ip /= 10; }
    if (prec > 0 || alt > 0) b[n++] = '.';
    for (i = 0; i < prec; i++) { a *= 10; int d = (int)a; if (d > 9) d = 9; b[n++] = '0' + d; a -= d; }
    if (alt < 0 && prec > 0) { while (b[n - 1] == '0') n--; if (b[n - 1] == '.') n--; }
    if (c == 'e') {
        b[n++] = upper ? 'E' : 'e'; b[n++] = e < 0 ? '-' : '+';
        if (e < 0) e = -e;
        if (e >= 100) b[n++] = '0' + e / 100;
        b[n++] = '0' + e / 10 % 10; b[n++] = '0' + e % 10;
    }
    b[n] = 0;
    return n;
}
#endif
#ifndef C_DECLS_ONLY
static int format(struct out *o, const char *fmt, va_list ap)
{
    for (; *fmt; fmt++) {
        if (*fmt != '%') { out_c(o, *fmt); continue; }
        int left = 0, plus = 0, space = 0, alt = 0, zero = 0, width = 0, prec = -1, size = 0;
        for (;; fmt++) {
            if (fmt[1] == '-') left = 1; else if (fmt[1] == '+') plus = 1; else if (fmt[1] == ' ') space = 1;
            else if (fmt[1] == '#') alt = 1; else if (fmt[1] == '0') zero = 1; else break;
        }
        fmt++;
        if (*fmt == '*') { width = va_arg(ap, int); if (width < 0) { left = 1; width = -width; } fmt++; }
        else while (isdigit(*fmt)) width = width * 10 + *fmt++ - '0';
        if (*fmt == '.') {
            fmt++; prec = 0;
            if (*fmt == '*') { prec = va_arg(ap, int); fmt++; }
            else while (isdigit(*fmt)) prec = prec * 10 + *fmt++ - '0';
        }
        for (;; fmt++) {
            if (*fmt == 'h') size = size == -1 ? -2 : -1;
            else if (*fmt == 'l') size++;
            else if (*fmt == 'j') size = 2;
            else if (*fmt == 'z' || *fmt == 't') size = sizeof(size_t) == 8 ? 2 : 0;
            else if (*fmt == 'L') size = 3;
            else break;
        }
        char b[128], *s = b; int len = 0; const char *pre = "";
        switch (*fmt) {
        case 'd': case 'i': {
            long long v = size >= 2 ? va_arg(ap, long long) : size == 1 ? va_arg(ap, long) : va_arg(ap, int);
            if (size == -1) v = (short)v; else if (size == -2) v = (signed char)v;
            unsigned long long u = v < 0 ? -(unsigned long long)v : v;
            pre = v < 0 ? "-" : plus ? "+" : space ? " " : "";
            char *p = b + sizeof b; *--p = 0;
            do *--p = '0' + u % 10; while (u /= 10);
            if (prec == 0 && v == 0) p++;
            while (prec > (int)(b + sizeof b - 1 - p)) *--p = '0';
            if (prec >= 0) zero = 0;
            out_field(o, pre, p, strlen(p), width, left, zero);
            continue;
        }
        case 'u': case 'o': case 'x': case 'X': case 'p': {
            unsigned long long u;
            int base = *fmt == 'o' ? 8 : *fmt == 'u' ? 10 : 16;
            const char *dig = *fmt == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
            if (*fmt == 'p') { u = (uintptr_t)va_arg(ap, void *); alt = 1; }
            else u = size >= 2 ? va_arg(ap, unsigned long long) : size == 1 ? va_arg(ap, unsigned long) : va_arg(ap, unsigned int);
            if (size == -1) u = (unsigned short)u; else if (size == -2) u = (unsigned char)u;
            if (alt && base == 16 && u) pre = *fmt == 'X' ? "0X" : "0x";
            char *p = b + sizeof b; *--p = 0;
            do *--p = dig[u % base]; while (u /= base);
            if (prec == 0 && p[0] == '0' && !p[1] && *fmt != 'p') p++;
            while (prec > (int)(b + sizeof b - 1 - p)) *--p = '0';
            if (alt && base == 8 && *p != '0') *--p = '0';
            if (prec >= 0) zero = 0;
            out_field(o, pre, p, strlen(p), width, left, zero);
            continue;
        }
        case 'c': b[0] = va_arg(ap, int); len = 1; break;
        case 's': s = va_arg(ap, char *); if (!s) s = "(null)"; len = strlen(s); if (prec >= 0 && prec < len) len = prec; break;
        case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': {
            long double v = size == 3 ? va_arg(ap, long double) : va_arg(ap, double);
            pre = v < 0 ? "-" : plus ? "+" : space ? " " : "";
            len = fmt_float(b, v, prec, *fmt, alt);
            out_field(o, pre, b, len, width, left, zero);
            continue;
        }
        case '%': b[0] = '%'; len = 1; break;
        default: out_c(o, '%'); out_c(o, *fmt); continue;
        }
        out_field(o, "", s, len, width, left, 0);
    }
    return o->len;
}
#endif
int vsnprintf(char *buf, size_t cap, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{
    struct out o = { buf, cap, 0, NULL };
    int n = format(&o, fmt, ap);
    if (cap) buf[o.len < cap ? o.len : cap - 1] = 0;
    return n;
}
#endif
int vsprintf(char *buf, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{ return vsnprintf(buf, (size_t)-1 / 2, fmt, ap); }
#endif
int vfprintf(FILE *f, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{ struct out o = { NULL, 0, 0, f }; return format(&o, fmt, ap); }
#endif
int vprintf(const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{ return vfprintf(stdout, fmt, ap); }
#endif
int snprintf(char *buf, size_t cap, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; va_start(ap, fmt); int n = vsnprintf(buf, cap, fmt, ap); va_end(ap); return n; }
#endif
int sprintf(char *buf, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; va_start(ap, fmt); int n = vsprintf(buf, fmt, ap); va_end(ap); return n; }
#endif
int fprintf(FILE *f, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; va_start(ap, fmt); int n = vfprintf(f, fmt, ap); va_end(ap); return n; }
#endif
int printf(const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; va_start(ap, fmt); int n = vfprintf(stdout, fmt, ap); va_end(ap); return n; }
#endif

/* ---- the end of a program ---- */
#ifdef C_DECLS_ONLY
extern void c_run_exit(void);
#else
void c_run_exit(void);
#endif
__attribute__((noreturn)) void exit(int code)
#ifdef C_DECLS_ONLY
;
#else
{ c_run_exit(); _exit(code); }
#endif
__attribute__((noreturn)) void abort(void)
#ifdef C_DECLS_ONLY
;
#else
{ fputs("abort\n", stderr); _exit(134); }
#endif
#define assert(x) ((x) ? (void)0 : (fprintf(stderr, "%s:%d: assertion failed: %s\n", __FILE__, __LINE__, #x), abort()))

/* ---- paths ---- */
/* the absolute path, with . and .. taken out (links aren't followed, there are none to follow here) */
char *realpath(const char *path, char *out)
#ifdef C_DECLS_ONLY
;
#else
{
    char tmp[PATH_MAX], *r = out ? out : malloc(PATH_MAX), *p, *seg;
    size_t n = 0;
    if (!r) return NULL;
    if (path[0] == '/') strcpy(tmp, path);
    else { if (!getcwd(tmp, sizeof tmp)) return NULL; strcat(tmp, "/"); strcat(tmp, path); }
    r[0] = 0;
    for (p = tmp; *p; ) {
        while (*p == '/') p++;
        seg = p;
        while (*p && *p != '/') p++;
        size_t l = p - seg;
        if (l == 0 || (l == 1 && seg[0] == '.')) continue;
        if (l == 2 && seg[0] == '.' && seg[1] == '.') { while (n && r[--n] != '/'); r[n] = 0; continue; }
        r[n++] = '/'; memcpy(r + n, seg, l); n += l; r[n] = 0;
    }
    if (!n) strcpy(r, "/");
    return r;
}
#endif

/* ---- tcc's helper for va_arg ----
 * under tcc every va_arg calls __va_arg(ap, kind, size, align): kind 0 = a general register, 1 = an SSE register,
 * 2 = the stack. the layout is the x86-64 ABI's: 6 general registers (48 bytes), then 8 SSE ones of 16 */
#ifdef __TINYC__
void *__va_arg(__builtin_va_list ap, int kind, int size, int align)
#ifdef C_DECLS_ONLY
;
#else
{
    size = (size + 7) & ~7; align = (align + 7) & ~7;
    if (kind == 0 && ap->gp_offset + size <= 48) { ap->gp_offset += size; return ap->reg_save_area + ap->gp_offset - size; }
    if (kind == 1 && size <= 8 && ap->fp_offset < 176) { ap->fp_offset += 16; return ap->reg_save_area + ap->fp_offset - 16; }
    ap->overflow_arg_area = (char *)(((uintptr_t)ap->overflow_arg_area + align - 1) & -(uintptr_t)align);
    ap->overflow_arg_area += size;
    return ap->overflow_arg_area - size;
}
#endif
#endif

/* ---- the environment and running programs ---- */
#ifdef C_DECLS_ONLY
extern char **environ;
#else
char **environ;
#endif
char *getenv(const char *name)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(name); char **e;
    for (e = environ; e && *e; e++) if (!strncmp(*e, name, l) && (*e)[l] == '=') return *e + l + 1;
    return NULL;
}
#endif
/* execl(path, arg0, arg1, ..., 0): execve with the arguments written out */
int execl(const char *path, const char *arg, ...)
#ifdef C_DECLS_ONLY
;
#else
{
    char *argv[64]; int n = 0; va_list ap;
    argv[n++] = (char *)arg;
    va_start(ap, arg);
    while (n < 63 && (argv[n] = va_arg(ap, char *))) n++;
    va_end(ap);
    argv[n] = NULL;
    return execve(path, argv, environ);
}
#endif
/* execve, looking through $PATH when the name has no / in it */
int execvp(const char *file, char *const argv[])
#ifdef C_DECLS_ONLY
;
#else
{
    char path[PATH_MAX]; const char *p = getenv("PATH"), *q;
    if (strchr(file, '/')) return execve(file, argv, environ);
    if (!p) p = "/bin";
    for (; *p; p = *q ? q + 1 : q) {
        q = strchr(p, ':'); if (!q) q = p + strlen(p);
        snprintf(path, sizeof path, "%.*s/%s", (int)(q - p), p, file);
        execve(path, argv, environ);
    }
    return -1;
}
#endif

/* ---- directories [rifle] ----
 * opendir/readdir over getdents64. readdir hands back a pointer into the buffer, good until the next call */
struct dirent { ino_t d_ino; long long d_off; unsigned short d_reclen; unsigned char d_type; char d_name[256]; };
#define DT_UNKNOWN 0
#define DT_FIFO 1
#define DT_CHR 2
#define DT_DIR 4
#define DT_BLK 6
#define DT_REG 8
#define DT_LNK 10
#define DT_SOCK 12
typedef struct DIR { int fd, pos, len; char buf[8192]; } DIR;
DIR *fdopendir(int fd)
#ifdef C_DECLS_ONLY
;
#else
{
    DIR *d = malloc(sizeof *d);
    if (!d) return NULL;
    d->fd = fd; d->pos = d->len = 0;
    return d;
}
#endif
DIR *opendir(const char *path)
#ifdef C_DECLS_ONLY
;
#else
{
    int fd = open(path, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    DIR *d;
    if (fd < 0) return NULL;
    if (!(d = fdopendir(fd))) { close(fd); return NULL; }
    return d;
}
#endif
struct dirent *readdir(DIR *d)
#ifdef C_DECLS_ONLY
;
#else
{
    if (d->pos >= d->len) {
        long r = sys3(SYS_getdents64, d->fd, d->buf, sizeof d->buf);
        if (r <= 0) { if (r < 0) errno = -r; return NULL; }   /* errno stays alone at the end of the list */
        d->len = r; d->pos = 0;
    }
    struct dirent *e = (struct dirent *)(d->buf + d->pos);
    d->pos += e->d_reclen;
    return e;
}
#endif
int closedir(DIR *d)
#ifdef C_DECLS_ONLY
;
#else
{ int r = close(d->fd); free(d); return r; }
#endif
int dirfd(DIR *d)
#ifdef C_DECLS_ONLY
;
#else
{ return d->fd; }
#endif

/* ---- users and groups [rifle] ----
 * read straight from /etc/passwd and /etc/group each time. no NSS, no caches: what's in the files is the answer */
struct passwd { char *pw_name, *pw_passwd; uid_t pw_uid; gid_t pw_gid; char *pw_gecos, *pw_dir, *pw_shell; };
struct group { char *gr_name, *gr_passwd; gid_t gr_gid; char **gr_mem; };
#ifndef C_DECLS_ONLY
static char *c_field(char **p)
{
    char *r = *p, *q = strchr(*p, ':');
    if (q) { *q = 0; *p = q + 1; } else *p += strlen(*p);
    return r;
}
#endif
#ifndef C_DECLS_ONLY
static struct passwd *c_getpw(const char *name, long id)
{
    static struct passwd pw; static char line[2048];
    FILE *f = fopen("/etc/passwd", "r");
    if (!f) return NULL;
    while (fgets(line, sizeof line, f)) {
        char *p = line, *nl = strchr(line, '\n'), *uid, *gid;
        if (nl) *nl = 0;
        if (!line[0] || line[0] == '#') continue;
        pw.pw_name = c_field(&p); pw.pw_passwd = c_field(&p); uid = c_field(&p); gid = c_field(&p);
        pw.pw_gecos = c_field(&p); pw.pw_dir = c_field(&p); pw.pw_shell = c_field(&p);
        pw.pw_uid = strtoul(uid, NULL, 10); pw.pw_gid = strtoul(gid, NULL, 10);
        if (name ? !strcmp(pw.pw_name, name) : (long)pw.pw_uid == id) { fclose(f); return &pw; }
    }
    fclose(f);
    return NULL;
}
#endif
struct passwd *getpwnam(const char *name)
#ifdef C_DECLS_ONLY
;
#else
{ return c_getpw(name, 0); }
#endif
struct passwd *getpwuid(uid_t uid)
#ifdef C_DECLS_ONLY
;
#else
{ return c_getpw(NULL, uid); }
#endif
#ifndef C_DECLS_ONLY
static struct group *c_getgr(const char *name, long id)
{
    static struct group gr; static char line[8192]; static char *mem[512];
    FILE *f = fopen("/etc/group", "r");
    if (!f) return NULL;
    while (fgets(line, sizeof line, f)) {
        char *p = line, *nl = strchr(line, '\n'), *gid, *list;
        int n = 0;
        if (nl) *nl = 0;
        if (!line[0] || line[0] == '#') continue;
        gr.gr_name = c_field(&p); gr.gr_passwd = c_field(&p); gid = c_field(&p); list = p;
        gr.gr_gid = strtoul(gid, NULL, 10);
        while (*list && n < 511) { mem[n++] = list; while (*list && *list != ',') list++; if (*list) *list++ = 0; }
        mem[n] = NULL; gr.gr_mem = mem;
        if (name ? !strcmp(gr.gr_name, name) : (long)gr.gr_gid == id) { fclose(f); return &gr; }
    }
    fclose(f);
    return NULL;
}
#endif
struct group *getgrnam(const char *name)
#ifdef C_DECLS_ONLY
;
#else
{ return c_getgr(name, 0); }
#endif
struct group *getgrgid(gid_t gid)
#ifdef C_DECLS_ONLY
;
#else
{ return c_getgr(NULL, gid); }
#endif

/* ---- time, written out [rifle] ----
 * the days between 1970 and a date, counted the way everyone does it. TZ isn't read yet: the time is UTC */
#ifndef C_DECLS_ONLY
static long c_days(long y, int m, int d)   /* m 1..12 */
{
    y -= m <= 2;
    long era = (y >= 0 ? y : y - 399) / 400, yoe = y - era * 400;
    long doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1, doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}
#endif
time_t timegm(struct tm *t)
#ifdef C_DECLS_ONLY
;
#else
{
    long y = t->tm_year + 1900 + t->tm_mon / 12; int m = t->tm_mon % 12;
    if (m < 0) { m += 12; y--; }
    return c_days(y, m + 1, 1) * 86400L + (t->tm_mday - 1) * 86400L + t->tm_hour * 3600L + t->tm_min * 60L + t->tm_sec;
}
#endif
time_t mktime(struct tm *t)
#ifdef C_DECLS_ONLY
;
#else
{ return timegm(t); }
#endif
#ifndef C_DECLS_ONLY
static const char *c_wday[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
#endif
#ifndef C_DECLS_ONLY
static const char *c_month[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September",
                                 "October", "November", "December" };
#endif
size_t strftime(char *buf, size_t cap, const char *fmt, const struct tm *t)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t n = 0;
    char tmp[64];
    for (; *fmt; fmt++) {
        const char *r = tmp; int pad = 0;
        if (*fmt != '%') { if (n + 1 >= cap) return 0; buf[n++] = *fmt; continue; }
        fmt++;
        if (*fmt == '-' || *fmt == '_' || *fmt == '0') { pad = *fmt++; }   /* %-d no padding, %_d spaces */
        tmp[0] = 0;
        switch (*fmt) {
        case 'a': r = c_wday[t->tm_wday % 7]; snprintf(tmp, 4, "%s", r); r = tmp; break;
        case 'A': r = c_wday[t->tm_wday % 7]; break;
        case 'b': case 'h': snprintf(tmp, 4, "%s", c_month[t->tm_mon % 12]); break;
        case 'B': r = c_month[t->tm_mon % 12]; break;
        case 'c': snprintf(tmp, sizeof tmp, "%.3s %.3s %2d %02d:%02d:%02d %d", c_wday[t->tm_wday % 7], c_month[t->tm_mon % 12],
                           t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, t->tm_year + 1900); break;
        case 'C': snprintf(tmp, sizeof tmp, "%02d", (t->tm_year + 1900) / 100); break;
        case 'd': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '_' ? "%2d" : "%02d", t->tm_mday); break;
        case 'D': snprintf(tmp, sizeof tmp, "%02d/%02d/%02d", t->tm_mon + 1, t->tm_mday, t->tm_year % 100); break;
        case 'e': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '0' ? "%02d" : "%2d", t->tm_mday); break;
        case 'F': snprintf(tmp, sizeof tmp, "%d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday); break;
        case 'H': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '_' ? "%2d" : "%02d", t->tm_hour); break;
        case 'I': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '_' ? "%2d" : "%02d", t->tm_hour % 12 ? t->tm_hour % 12 : 12); break;
        case 'j': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : "%03d", t->tm_yday + 1); break;
        case 'k': snprintf(tmp, sizeof tmp, "%2d", t->tm_hour); break;
        case 'l': snprintf(tmp, sizeof tmp, "%2d", t->tm_hour % 12 ? t->tm_hour % 12 : 12); break;
        case 'm': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '_' ? "%2d" : "%02d", t->tm_mon + 1); break;
        case 'M': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '_' ? "%2d" : "%02d", t->tm_min); break;
        case 'n': r = "\n"; break;
        case 'p': r = t->tm_hour < 12 ? "AM" : "PM"; break;
        case 'P': r = t->tm_hour < 12 ? "am" : "pm"; break;
        case 'r': snprintf(tmp, sizeof tmp, "%02d:%02d:%02d %s", t->tm_hour % 12 ? t->tm_hour % 12 : 12, t->tm_min, t->tm_sec, t->tm_hour < 12 ? "AM" : "PM"); break;
        case 'R': snprintf(tmp, sizeof tmp, "%02d:%02d", t->tm_hour, t->tm_min); break;
        case 's': { struct tm c = *t; snprintf(tmp, sizeof tmp, "%ld", (long)timegm(&c)); break; }
        case 'S': snprintf(tmp, sizeof tmp, pad == '-' ? "%d" : pad == '_' ? "%2d" : "%02d", t->tm_sec); break;
        case 't': r = "\t"; break;
        case 'T': case 'X': snprintf(tmp, sizeof tmp, "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec); break;
        case 'u': snprintf(tmp, sizeof tmp, "%d", t->tm_wday ? t->tm_wday : 7); break;
        case 'w': snprintf(tmp, sizeof tmp, "%d", t->tm_wday); break;
        case 'x': snprintf(tmp, sizeof tmp, "%02d/%02d/%02d", t->tm_mon + 1, t->tm_mday, t->tm_year % 100); break;
        case 'y': snprintf(tmp, sizeof tmp, "%02d", t->tm_year % 100); break;
        case 'Y': snprintf(tmp, sizeof tmp, "%d", t->tm_year + 1900); break;
        case 'z': r = "+0000"; break;
        case 'Z': r = "UTC"; break;
        case '%': r = "%"; break;
        default: snprintf(tmp, sizeof tmp, "%%%c", *fmt); break;
        }
        size_t l = strlen(r);
        if (n + l >= cap) return 0;
        memcpy(buf + n, r, l); n += l;
    }
    if (n >= cap) return 0;
    buf[n] = 0;
    return n;
}
#endif
unsigned sleep(unsigned s)
#ifdef C_DECLS_ONLY
;
#else
{ struct timespec t = { s, 0 }; return nanosleep(&t, &t) < 0 ? t.tv_sec : 0; }
#endif

/* ---- the environment, changed [rifle] ----
 * the first change copies the list the kernel gave us onto the heap; after that it grows as needed */
#ifndef C_DECLS_ONLY
static int c_env_own;
#endif
#ifndef C_DECLS_ONLY
static int c_env_len(void) { int n = 0; while (environ && environ[n]) n++; return n; }
#endif
#ifndef C_DECLS_ONLY
static int c_env_copy(void)
{
    if (!c_env_own) {
        int n = c_env_len(), i;
        char **e = malloc((n + 2) * sizeof *e);
        if (!e) return -1;
        for (i = 0; i < n; i++) e[i] = environ[i];
        e[n] = NULL; environ = e; c_env_own = 1;
    }
    return 0;
}
#endif
int unsetenv(const char *name)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(name); int i, j;
    if (!l || strchr(name, '=')) { errno = EINVAL; return -1; }
    if (c_env_copy()) return -1;
    for (i = j = 0; environ[i]; i++)
        if (!(!strncmp(environ[i], name, l) && environ[i][l] == '=')) environ[j++] = environ[i];
    environ[j] = NULL;
    return 0;
}
#endif
int putenv(char *entry)
#ifdef C_DECLS_ONLY
;
#else
{
    char *eq = strchr(entry, '='); size_t l; int i, n;
    if (!eq || eq == entry) { errno = EINVAL; return -1; }
    l = eq - entry;
    if (c_env_copy()) return -1;
    for (i = 0; environ[i]; i++)
        if (!strncmp(environ[i], entry, l) && environ[i][l] == '=') { environ[i] = entry; return 0; }
    n = i;
    {
        char **e = realloc(environ, (n + 2) * sizeof *e);
        if (!e) return -1;
        environ = e; e[n] = entry; e[n + 1] = NULL;
    }
    return 0;
}
#endif
int setenv(const char *name, const char *value, int overwrite)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(name), v = strlen(value); char *e;
    if (!l || strchr(name, '=')) { errno = EINVAL; return -1; }
    if (!overwrite && getenv(name)) return 0;
    if (!(e = malloc(l + v + 2))) return -1;
    memcpy(e, name, l); e[l] = '='; memcpy(e + l + 1, value, v + 1);
    return putenv(e);
}
#endif
int clearenv(void)
#ifdef C_DECLS_ONLY
;
#else
{ if (c_env_copy()) return -1; environ[0] = NULL; return 0; }
#endif

#ifdef __i386__
/* i386 has no 64-bit divide: the compiler calls these, as it would call libgcc's */
unsigned long long __udivmoddi4(unsigned long long a, unsigned long long b, unsigned long long *rem)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned long long q = 0, r = 0;
    int i;
    if (!(a >> 32) && !(b >> 32)) {
        q = (unsigned)a / (unsigned)b;
        if (rem) *rem = (unsigned)a % (unsigned)b;
        return q;
    }
    for (i = 63; i >= 0; i--) {
        r = r << 1 | (a >> i & 1);
        if (r >= b) { r -= b; q |= 1ULL << i; }
    }
    if (rem) *rem = r;
    return q;
}
#endif
unsigned long long __udivdi3(unsigned long long a, unsigned long long b)
#ifdef C_DECLS_ONLY
;
#else
{ return __udivmoddi4(a, b, 0); }
#endif
unsigned long long __umoddi3(unsigned long long a, unsigned long long b)
#ifdef C_DECLS_ONLY
;
#else
{ unsigned long long r; __udivmoddi4(a, b, &r); return r; }
#endif
long long __divdi3(long long a, long long b)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned long long q = __udivmoddi4(a < 0 ? -(unsigned long long)a : a, b < 0 ? -(unsigned long long)b : b, 0);
    return (a < 0) != (b < 0) ? -(long long)q : (long long)q;
}
#endif
long long __moddi3(long long a, long long b)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned long long r;
    __udivmoddi4(a < 0 ? -(unsigned long long)a : a, b < 0 ? -(unsigned long long)b : b, &r);
    return a < 0 ? -(long long)r : (long long)r;
}
#endif
#endif

/* ---- start-up ----
 * the kernel leaves argc, argv and the environment on the stack, then jumps to _start */
#ifdef C_DECLS_ONLY
extern int main();
#else
int main();
#endif /* no prototype: int main(void), main(argc, argv) and main(argc, argv, envp) all work */
void c_start(long *sp)
#ifdef C_DECLS_ONLY
;
#else
{
    int argc = (int)sp[0];
    char **argv = (char **)(sp + 1);
    environ = argv + argc + 1;
    exit(main(argc, argv, environ));
}
#endif
#ifndef C_NO_START
#ifdef __i386__
#ifndef C_DECLS_ONLY
__asm__(".text\n.global _start\n_start:\n xor %ebp,%ebp\n mov %esp,%eax\n and $-16,%esp\n sub $12,%esp\n push %eax\n call c_start\n hlt\n");
#endif
#else
#ifndef C_DECLS_ONLY
__asm__(".text\n.global _start\n_start:\n xor %rbp,%rbp\n mov %rsp,%rdi\n and $-16,%rsp\n call c_start\n hlt\n");
#endif
#endif
#endif

/* [rifle] priorities and getline */
int strcoll(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{ return strcmp(a, b); }
#endif
#ifndef __i386__
#define SYS_getpriority 140
#define SYS_setpriority 141
#endif
int getpriority(int which, int who)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_getpriority, which, who)); }
#endif
int setpriority(int which, int who, int prio)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_setpriority, which, who, prio)); }
#endif
ssize_t getline(char **lp, size_t *cap, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t n = 0;
    int c;
    if (!*lp || !*cap) { *cap = 128; *lp = malloc(*cap); }
    while ((c = getc(f)) != EOF) {
        if (n + 2 > *cap) { *cap *= 2; *lp = realloc(*lp, *cap); }
        (*lp)[n++] = c;
        if (c == '\n') break;
    }
    if (!n) return -1;
    (*lp)[n] = 0;
    return n;
}
#endif
/* ---- what the rest of the additions lean on [chamesle] ---- */
#define sys4(n, a, b, c, d) sys6(n, (long)(a), (long)(b), (long)(c), (long)(d), 0, 0)
#define sys5(n, a, b, c, d, e) sys6(n, (long)(a), (long)(b), (long)(c), (long)(d), (long)(e), 0)
#ifndef ENOTBLK
#define ENOTBLK 15
#endif
#ifndef ENOMSG
#define ENOMSG 42
#endif
#ifndef EPROTO
#define EPROTO 71
#endif
#ifndef EBADMSG
#define EBADMSG 74
#endif
#ifndef ENOTSOCK
#define ENOTSOCK 88
#endif
#ifndef EDESTADDRREQ
#define EDESTADDRREQ 89
#endif
#ifndef EMSGSIZE
#define EMSGSIZE 90
#endif
#ifndef EPROTOTYPE
#define EPROTOTYPE 91
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT 92
#endif
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT 93
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT 97
#endif
#ifndef EADDRINUSE
#define EADDRINUSE 98
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL 99
#endif
#ifndef ENETDOWN
#define ENETDOWN 100
#endif
#ifndef ENETUNREACH
#define ENETUNREACH 101
#endif
#ifndef ECONNABORTED
#define ECONNABORTED 103
#endif
#ifndef ECONNRESET
#define ECONNRESET 104
#endif
#ifndef ENOBUFS
#define ENOBUFS 105
#endif
#ifndef EISCONN
#define EISCONN 106
#endif
#ifndef ENOTCONN
#define ENOTCONN 107
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED 111
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH 113
#endif
#ifndef EALREADY
#define EALREADY 114
#endif
#ifndef EINPROGRESS
#define EINPROGRESS 115
#endif
#ifndef ECANCELED
#define ECANCELED 125
#endif
#ifndef ENOTSUP
#define ENOTSUP 95
#endif
#ifndef EWOULDBLOCK
#define EWOULDBLOCK 11
#endif
#ifndef ENOLCK
#define ENOLCK 37
#endif
#ifndef EIDRM
#define EIDRM 43
#endif
#ifndef ENOLINK
#define ENOLINK 67
#endif
#ifndef ETIME
#define ETIME 62
#endif
#ifndef ENOSR
#define ENOSR 63
#endif
#ifndef ENOSTR
#define ENOSTR 60
#endif
#ifndef EMULTIHOP
#define EMULTIHOP 72
#endif
#ifndef EOWNERDEAD
#define EOWNERDEAD 130
#endif
#ifndef ENOTRECOVERABLE
#define ENOTRECOVERABLE 131
#endif
#ifndef ESHUTDOWN
#define ESHUTDOWN 108
#endif
#ifndef ETOOMANYREFS
#define ETOOMANYREFS 109
#endif
#ifndef EHOSTDOWN
#define EHOSTDOWN 112
#endif
/* ---- system call numbers [chamesle] ---- */
#ifndef SYS_read
#define SYS_read 0
#endif
#ifndef SYS_write
#define SYS_write 1
#endif
#ifndef SYS_open
#define SYS_open 2
#endif
#ifndef SYS_close
#define SYS_close 3
#endif
#ifndef SYS_stat
#define SYS_stat 4
#endif
#ifndef SYS_fstat
#define SYS_fstat 5
#endif
#ifndef SYS_lstat
#define SYS_lstat 6
#endif
#ifndef SYS_poll
#define SYS_poll 7
#endif
#ifndef SYS_lseek
#define SYS_lseek 8
#endif
#ifndef SYS_mmap
#define SYS_mmap 9
#endif
#ifndef SYS_mprotect
#define SYS_mprotect 10
#endif
#ifndef SYS_munmap
#define SYS_munmap 11
#endif
#ifndef SYS_brk
#define SYS_brk 12
#endif
#ifndef SYS_rt_sigaction
#define SYS_rt_sigaction 13
#endif
#ifndef SYS_rt_sigprocmask
#define SYS_rt_sigprocmask 14
#endif
#ifndef SYS_rt_sigreturn
#define SYS_rt_sigreturn 15
#endif
#ifndef SYS_ioctl
#define SYS_ioctl 16
#endif
#ifndef SYS_pread64
#define SYS_pread64 17
#endif
#ifndef SYS_pwrite64
#define SYS_pwrite64 18
#endif
#ifndef SYS_readv
#define SYS_readv 19
#endif
#ifndef SYS_writev
#define SYS_writev 20
#endif
#ifndef SYS_access
#define SYS_access 21
#endif
#ifndef SYS_pipe
#define SYS_pipe 22
#endif
#ifndef SYS_select
#define SYS_select 23
#endif
#ifndef SYS_sched_yield
#define SYS_sched_yield 24
#endif
#ifndef SYS_mremap
#define SYS_mremap 25
#endif
#ifndef SYS_msync
#define SYS_msync 26
#endif
#ifndef SYS_madvise
#define SYS_madvise 28
#endif
#ifndef SYS_dup
#define SYS_dup 32
#endif
#ifndef SYS_dup2
#define SYS_dup2 33
#endif
#ifndef SYS_pause
#define SYS_pause 34
#endif
#ifndef SYS_nanosleep
#define SYS_nanosleep 35
#endif
#ifndef SYS_getitimer
#define SYS_getitimer 36
#endif
#ifndef SYS_alarm
#define SYS_alarm 37
#endif
#ifndef SYS_setitimer
#define SYS_setitimer 38
#endif
#ifndef SYS_getpid
#define SYS_getpid 39
#endif
#ifndef SYS_sendfile
#define SYS_sendfile 40
#endif
#ifndef SYS_socket
#define SYS_socket 41
#endif
#ifndef SYS_connect
#define SYS_connect 42
#endif
#ifndef SYS_accept
#define SYS_accept 43
#endif
#ifndef SYS_sendto
#define SYS_sendto 44
#endif
#ifndef SYS_recvfrom
#define SYS_recvfrom 45
#endif
#ifndef SYS_sendmsg
#define SYS_sendmsg 46
#endif
#ifndef SYS_recvmsg
#define SYS_recvmsg 47
#endif
#ifndef SYS_shutdown
#define SYS_shutdown 48
#endif
#ifndef SYS_bind
#define SYS_bind 49
#endif
#ifndef SYS_listen
#define SYS_listen 50
#endif
#ifndef SYS_getsockname
#define SYS_getsockname 51
#endif
#ifndef SYS_getpeername
#define SYS_getpeername 52
#endif
#ifndef SYS_socketpair
#define SYS_socketpair 53
#endif
#ifndef SYS_setsockopt
#define SYS_setsockopt 54
#endif
#ifndef SYS_getsockopt
#define SYS_getsockopt 55
#endif
#ifndef SYS_clone
#define SYS_clone 56
#endif
#ifndef SYS_fork
#define SYS_fork 57
#endif
#ifndef SYS_vfork
#define SYS_vfork 58
#endif
#ifndef SYS_execve
#define SYS_execve 59
#endif
#ifndef SYS_exit
#define SYS_exit 60
#endif
#ifndef SYS_wait4
#define SYS_wait4 61
#endif
#ifndef SYS_kill
#define SYS_kill 62
#endif
#ifndef SYS_uname
#define SYS_uname 63
#endif
#ifndef SYS_fcntl
#define SYS_fcntl 72
#endif
#ifndef SYS_flock
#define SYS_flock 73
#endif
#ifndef SYS_fsync
#define SYS_fsync 74
#endif
#ifndef SYS_fdatasync
#define SYS_fdatasync 75
#endif
#ifndef SYS_truncate
#define SYS_truncate 76
#endif
#ifndef SYS_ftruncate
#define SYS_ftruncate 77
#endif
#ifndef SYS_getdents
#define SYS_getdents 78
#endif
#ifndef SYS_getcwd
#define SYS_getcwd 79
#endif
#ifndef SYS_chdir
#define SYS_chdir 80
#endif
#ifndef SYS_fchdir
#define SYS_fchdir 81
#endif
#ifndef SYS_rename
#define SYS_rename 82
#endif
#ifndef SYS_mkdir
#define SYS_mkdir 83
#endif
#ifndef SYS_rmdir
#define SYS_rmdir 84
#endif
#ifndef SYS_creat
#define SYS_creat 85
#endif
#ifndef SYS_link
#define SYS_link 86
#endif
#ifndef SYS_unlink
#define SYS_unlink 87
#endif
#ifndef SYS_symlink
#define SYS_symlink 88
#endif
#ifndef SYS_readlink
#define SYS_readlink 89
#endif
#ifndef SYS_chmod
#define SYS_chmod 90
#endif
#ifndef SYS_fchmod
#define SYS_fchmod 91
#endif
#ifndef SYS_chown
#define SYS_chown 92
#endif
#ifndef SYS_fchown
#define SYS_fchown 93
#endif
#ifndef SYS_lchown
#define SYS_lchown 94
#endif
#ifndef SYS_umask
#define SYS_umask 95
#endif
#ifndef SYS_gettimeofday
#define SYS_gettimeofday 96
#endif
#ifndef SYS_getrlimit
#define SYS_getrlimit 97
#endif
#ifndef SYS_getrusage
#define SYS_getrusage 98
#endif
#ifndef SYS_sysinfo
#define SYS_sysinfo 99
#endif
#ifndef SYS_times
#define SYS_times 100
#endif
#ifndef SYS_getuid
#define SYS_getuid 102
#endif
#ifndef SYS_getgid
#define SYS_getgid 104
#endif
#ifndef SYS_setuid
#define SYS_setuid 105
#endif
#ifndef SYS_setgid
#define SYS_setgid 106
#endif
#ifndef SYS_geteuid
#define SYS_geteuid 107
#endif
#ifndef SYS_getegid
#define SYS_getegid 108
#endif
#ifndef SYS_setpgid
#define SYS_setpgid 109
#endif
#ifndef SYS_getppid
#define SYS_getppid 110
#endif
#ifndef SYS_getpgrp
#define SYS_getpgrp 111
#endif
#ifndef SYS_setsid
#define SYS_setsid 112
#endif
#ifndef SYS_setreuid
#define SYS_setreuid 113
#endif
#ifndef SYS_setregid
#define SYS_setregid 114
#endif
#ifndef SYS_getgroups
#define SYS_getgroups 115
#endif
#ifndef SYS_setgroups
#define SYS_setgroups 116
#endif
#ifndef SYS_setresuid
#define SYS_setresuid 117
#endif
#ifndef SYS_setresgid
#define SYS_setresgid 119
#endif
#ifndef SYS_getpgid
#define SYS_getpgid 121
#endif
#ifndef SYS_getsid
#define SYS_getsid 124
#endif
#ifndef SYS_rt_sigpending
#define SYS_rt_sigpending 127
#endif
#ifndef SYS_rt_sigtimedwait
#define SYS_rt_sigtimedwait 128
#endif
#ifndef SYS_rt_sigsuspend
#define SYS_rt_sigsuspend 130
#endif
#ifndef SYS_sigaltstack
#define SYS_sigaltstack 131
#endif
#ifndef SYS_utime
#define SYS_utime 132
#endif
#ifndef SYS_mknod
#define SYS_mknod 133
#endif
#ifndef SYS_statfs
#define SYS_statfs 137
#endif
#ifndef SYS_fstatfs
#define SYS_fstatfs 138
#endif
#ifndef SYS_getpriority
#define SYS_getpriority 140
#endif
#ifndef SYS_setpriority
#define SYS_setpriority 141
#endif
#ifndef SYS_prctl
#define SYS_prctl 157
#endif
#ifndef SYS_arch_prctl
#define SYS_arch_prctl 158
#endif
#ifndef SYS_setrlimit
#define SYS_setrlimit 160
#endif
#ifndef SYS_chroot
#define SYS_chroot 161
#endif
#ifndef SYS_sync
#define SYS_sync 162
#endif
#ifndef SYS_mount
#define SYS_mount 165
#endif
#ifndef SYS_umount2
#define SYS_umount2 166
#endif
#ifndef SYS_gettid
#define SYS_gettid 186
#endif
#ifndef SYS_time
#define SYS_time 201
#endif
#ifndef SYS_futex
#define SYS_futex 202
#endif
#ifndef SYS_getdents64
#define SYS_getdents64 217
#endif
#ifndef SYS_set_tid_address
#define SYS_set_tid_address 218
#endif
#ifndef SYS_clock_gettime
#define SYS_clock_gettime 228
#endif
#ifndef SYS_clock_getres
#define SYS_clock_getres 229
#endif
#ifndef SYS_clock_nanosleep
#define SYS_clock_nanosleep 230
#endif
#ifndef SYS_exit_group
#define SYS_exit_group 231
#endif
#ifndef SYS_tgkill
#define SYS_tgkill 234
#endif
#ifndef SYS_utimes
#define SYS_utimes 235
#endif
#ifndef SYS_openat
#define SYS_openat 257
#endif
#ifndef SYS_mkdirat
#define SYS_mkdirat 258
#endif
#ifndef SYS_mknodat
#define SYS_mknodat 259
#endif
#ifndef SYS_fchownat
#define SYS_fchownat 260
#endif
#ifndef SYS_newfstatat
#define SYS_newfstatat 262
#endif
#ifndef SYS_unlinkat
#define SYS_unlinkat 263
#endif
#ifndef SYS_renameat
#define SYS_renameat 264
#endif
#ifndef SYS_linkat
#define SYS_linkat 265
#endif
#ifndef SYS_symlinkat
#define SYS_symlinkat 266
#endif
#ifndef SYS_readlinkat
#define SYS_readlinkat 267
#endif
#ifndef SYS_fchmodat
#define SYS_fchmodat 268
#endif
#ifndef SYS_faccessat
#define SYS_faccessat 269
#endif
#ifndef SYS_ppoll
#define SYS_ppoll 271
#endif
#ifndef SYS_utimensat
#define SYS_utimensat 280
#endif
#ifndef SYS_accept4
#define SYS_accept4 288
#endif
#ifndef SYS_dup3
#define SYS_dup3 292
#endif
#ifndef SYS_pipe2
#define SYS_pipe2 293
#endif
#ifndef SYS_getrandom
#define SYS_getrandom 318
#endif
#ifndef SYS_copy_file_range
#define SYS_copy_file_range 326
#endif
#ifndef SYS_setsid
#define SYS_setsid 112
#endif
#ifndef SYS_fchmodat2
#define SYS_fchmodat2 452
#endif
/* ---- more of unistd, fcntl, sys/...: the thin system calls [chamesle] ---- */

#ifndef O_NONBLOCK
#define O_NONBLOCK 04000
#endif
#ifndef O_NOCTTY
#define O_NOCTTY 0400
#endif
#ifndef O_SYNC
#define O_SYNC 04010000
#endif
#ifndef O_DSYNC
#define O_DSYNC 010000
#endif
#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0400000
#endif
#ifndef O_DIRECTORY
#define O_DIRECTORY 0200000
#endif
#ifndef O_NOATIME
#define O_NOATIME 01000000
#endif
#ifndef O_LARGEFILE
#define O_LARGEFILE 0
#endif
#ifndef O_ACCMODE
#define O_ACCMODE 3
#endif
#define O_NDELAY O_NONBLOCK
#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define F_GETLK 5
#define F_SETLK 6
#define F_SETLKW 7
#define F_DUPFD_CLOEXEC 1030
#define FD_CLOEXEC 1
#define F_RDLCK 0
#define F_WRLCK 1
#define F_UNLCK 2
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB 4
#define LOCK_UN 8
#define AT_EACCESS 0x200
#define AT_SYMLINK_FOLLOW 0x400
#ifndef AT_REMOVEDIR
#define AT_REMOVEDIR 0x200
#endif
#ifndef AT_SYMLINK_NOFOLLOW
#define AT_SYMLINK_NOFOLLOW 0x100
#endif
#define _SC_ARG_MAX 0
#define _SC_CHILD_MAX 1
#define _SC_CLK_TCK 2
#define _SC_NGROUPS_MAX 3
#define _SC_OPEN_MAX 4
#define _SC_PAGESIZE 30
#define _SC_PAGE_SIZE 30
#define _SC_NPROCESSORS_CONF 83
#define _SC_NPROCESSORS_ONLN 84
#define _SC_PHYS_PAGES 85
#define _SC_GETPW_R_SIZE_MAX 70
#define _SC_GETGR_R_SIZE_MAX 69
#define _SC_HOST_NAME_MAX 180
#define _SC_LINE_MAX 43
#define _POSIX_VERSION 200809L
#define _POSIX_PATH_MAX 256
#define NGROUPS_MAX 65536
#define HOST_NAME_MAX 64
#define LOGIN_NAME_MAX 256
#define NAME_MAX 255
#define PIPE_BUF 4096
#define IOV_MAX 1024
#define SSIZE_MAX LONG_MAX
#define CLOCKS_PER_SEC 1000000

struct iovec { void *iov_base; size_t iov_len; };
ssize_t readv(int fd, const struct iovec *v, int n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_readv, fd, v, n)); }
#endif
ssize_t writev(int fd, const struct iovec *v, int n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_writev, fd, v, n)); }
#endif

int dup3(int a, int b, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_dup3, a, b, flags)); }
#endif
int pipe2(int fd[2], int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_pipe2, fd, flags)); }
#endif
int flock(int fd, int op)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_flock, fd, op)); }
#endif
pid_t vfork(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fork(); }
#endif
pid_t getpgrp(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_getpgrp); }
#endif
pid_t getpgid(pid_t p)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_getpgid, p)); }
#endif
int setpgid(pid_t p, pid_t g)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_setpgid, p, g)); }
#endif
int setpgrp(void)
#ifdef C_DECLS_ONLY
;
#else
{ return setpgid(0, 0); }
#endif
pid_t getsid(pid_t p)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_getsid, p)); }
#endif
pid_t setsid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys0(SYS_setsid)); }
#endif
int setreuid(uid_t r, uid_t e)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_setreuid, r, e)); }
#endif
int setregid(gid_t r, gid_t e)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_setregid, r, e)); }
#endif
int setresuid(uid_t r, uid_t e, uid_t s)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_setresuid, r, e, s)); }
#endif
int setresgid(gid_t r, gid_t e, gid_t s)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_setresgid, r, e, s)); }
#endif
int seteuid(uid_t e)
#ifdef C_DECLS_ONLY
;
#else
{ return setresuid(-1, e, -1); }
#endif
int setegid(gid_t e)
#ifdef C_DECLS_ONLY
;
#else
{ return setresgid(-1, e, -1); }
#endif
int setgroups(size_t n, const gid_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_setgroups, n, l)); }
#endif
pid_t gettid(void)
#ifdef C_DECLS_ONLY
;
#else
{ return sys0(SYS_gettid); }
#endif
unsigned alarm(unsigned s)
#ifdef C_DECLS_ONLY
;
#else
{
    struct { long ti[2], tv[2]; } nw = { { 0, 0 }, { s, 0 } }, old = { { 0, 0 }, { 0, 0 } };
    if (fail(sys3(SYS_setitimer, 0, &nw, &old)) < 0) return 0;
    return old.tv[0] + (old.tv[1] ? 1 : 0);
}
#endif
int pause(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys0(SYS_pause)); }
#endif
unsigned usleep(unsigned us)
#ifdef C_DECLS_ONLY
;
#else
{ struct timespec t = { us / 1000000, (us % 1000000) * 1000L }; return nanosleep(&t, NULL); }
#endif
int clock_getres(int clk, struct timespec *t)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_clock_getres, clk, t)); }
#endif
int clock_nanosleep(int clk, int flags, const struct timespec *t, struct timespec *rem)
#ifdef C_DECLS_ONLY
;
#else
{ long r = sys4(SYS_clock_nanosleep, clk, flags, t, rem); return r < 0 && r > -4096 ? -r : 0; }
#endif
int getpagesize(void)
#ifdef C_DECLS_ONLY
;
#else
{ return 4096; }
#endif
int nice(int inc)
#ifdef C_DECLS_ONLY
;
#else
{ int cur = getpriority(0, 0); if (cur < 0) return -1; return setpriority(0, 0, 20 - cur + inc) < 0 ? -1 : 20 - getpriority(0, 0); }
#endif
int fchmodat(int dirfd, const char *p, mode_t m, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ (void)flags; return fail(sys3(SYS_fchmodat, dirfd, p, m)); }
#endif
int fchownat(int dirfd, const char *p, uid_t u, gid_t g, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_fchownat, dirfd, (long)p, u, g, flags, 0)); }
#endif
int faccessat(int dirfd, const char *p, int mode, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ (void)flags; return fail(sys3(SYS_faccessat, dirfd, p, mode)); }
#endif
int renameat(int a, const char *p, int b, const char *q)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_renameat, a, p, b, q)); }
#endif
int linkat(int a, const char *p, int b, const char *q, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_linkat, a, (long)p, b, (long)q, flags, 0)); }
#endif
int symlinkat(const char *t, int dirfd, const char *p)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_symlinkat, t, dirfd, p)); }
#endif
ssize_t readlinkat(int dirfd, const char *p, char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_readlinkat, dirfd, p, buf, n)); }
#endif
int mknodat(int dirfd, const char *p, mode_t m, dev_t d)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_mknodat, dirfd, p, m, d)); }
#endif
int mkfifoat(int dirfd, const char *p, mode_t m)
#ifdef C_DECLS_ONLY
;
#else
{ return mknodat(dirfd, p, (m & 07777) | S_IFIFO, 0); }
#endif
int fstatfs(int fd, struct statfs *s)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_fstatfs, fd, s)); }
#endif
int utimes(const char *path, const struct timeval tv[2])
#ifdef C_DECLS_ONLY
;
#else
{
    struct timespec t[2];
    if (!tv) return utimensat(AT_FDCWD, path, NULL, 0);
    t[0].tv_sec = tv[0].tv_sec; t[0].tv_nsec = tv[0].tv_usec * 1000;
    t[1].tv_sec = tv[1].tv_sec; t[1].tv_nsec = tv[1].tv_usec * 1000;
    return utimensat(AT_FDCWD, path, t, 0);
}
#endif
int futimens(int fd, const struct timespec t[2])
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_utimensat, fd, 0, (long)t, 0, 0, 0)); }
#endif
struct utimbuf { time_t actime, modtime; };
int utime(const char *path, const struct utimbuf *u)
#ifdef C_DECLS_ONLY
;
#else
{
    struct timespec t[2];
    if (!u) return utimensat(AT_FDCWD, path, NULL, 0);
    t[0].tv_sec = u->actime; t[0].tv_nsec = 0; t[1].tv_sec = u->modtime; t[1].tv_nsec = 0;
    return utimensat(AT_FDCWD, path, t, 0);
}
#endif
int lockf(int fd, int cmd, off_t len)
#ifdef C_DECLS_ONLY
;
#else
{
    (void)len;
    return flock(fd, cmd == 0 ? LOCK_UN : cmd == 1 || cmd == 2 ? LOCK_EX : cmd == 3 ? LOCK_EX | LOCK_NB : LOCK_UN);
}
#endif
int posix_fadvise(int fd, off_t o, off_t l, int a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)fd; (void)o; (void)l; (void)a; return 0; }
#endif
int posix_fallocate(int fd, off_t o, off_t l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(285, fd, 0, o, l)) < 0 ? errno : 0; }
#endif
ssize_t sendfile(int out, int in, off_t *off, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_sendfile, out, in, off, n)); }
#endif
ssize_t copy_file_range(int in, off_t *io, int out, off_t *oo, size_t n, unsigned flags)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_copy_file_range, in, (long)io, out, (long)oo, n, flags)); }
#endif

int gethostname(char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    struct utsname u;
    if (uname(&u) < 0) return -1;
    if (strlen(u.nodename) >= n) { errno = ENAMETOOLONG; return -1; }
    strcpy(buf, u.nodename);
    return 0;
}
#endif
int getdomainname(char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ struct utsname u; if (uname(&u) < 0) return -1; strncpy(buf, u.domainname, n); return 0; }
#endif
char *getlogin(void)
#ifdef C_DECLS_ONLY
;
#else
{ struct passwd *p = getpwuid(getuid()); return p ? p->pw_name : getenv("LOGNAME"); }
#endif
int getlogin_r(char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ char *l = getlogin(); if (!l) return ENOENT; strncpy(buf, l, n); return 0; }
#endif
char *ttyname(int fd)
#ifdef C_DECLS_ONLY
;
#else
{
    static char buf[64];
    char p[32];
    ssize_t n;
    snprintf(p, sizeof p, "/proc/self/fd/%d", fd);
    n = readlink(p, buf, sizeof buf - 1);
    if (n < 0) return NULL;
    buf[n] = 0;
    return buf;
}
#endif
int ttyname_r(int fd, char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ char *t = ttyname(fd); if (!t) return errno; strncpy(buf, t, n); return 0; }
#endif
char *ctermid(char *s)
#ifdef C_DECLS_ONLY
;
#else
{ static char d[] = "/dev/tty"; if (!s) return d; strcpy(s, d); return s; }
#endif
pid_t tcgetpgrp(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ int p; if (ioctl(fd, 0x540F, &p) < 0) return -1; return p; }
#endif
int tcsetpgrp(int fd, pid_t p)
#ifdef C_DECLS_ONLY
;
#else
{ return ioctl(fd, 0x5410, &p); }
#endif
pid_t tcgetsid(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ int p; if (ioctl(fd, 0x5429, &p) < 0) return -1; return p; }
#endif
long pathconf(const char *p, int name)
#ifdef C_DECLS_ONLY
;
#else
{ (void)p; (void)name; return name == 3 ? 255 : 4096; }
#endif
long fpathconf(int fd, int name)
#ifdef C_DECLS_ONLY
;
#else
{ (void)fd; return pathconf("/", name); }
#endif
char *getpass(const char *prompt)
#ifdef C_DECLS_ONLY
;
#else
{ static char buf[128]; fputs(prompt, stderr); if (!fgets(buf, sizeof buf, stdin)) return NULL; buf[strcspn(buf, "\n")] = 0; return buf; }
#endif
int daemon(int nochdir, int noclose)
#ifdef C_DECLS_ONLY
;
#else
{
    pid_t p = fork();
    if (p < 0) return -1;
    if (p) _exit(0);
    if (setsid() < 0) return -1;
    if (!nochdir) chdir("/");
    if (!noclose) { int fd = open("/dev/null", O_RDWR); if (fd >= 0) { dup2(fd, 0); dup2(fd, 1); dup2(fd, 2); if (fd > 2) close(fd); } }
    return 0;
}
#endif

/* exec and spawn */
extern char **environ;
int execv(const char *path, char *const argv[])
#ifdef C_DECLS_ONLY
;
#else
{ return execve(path, argv, environ); }
#endif
int execvpe(const char *file, char *const argv[], char *const envp[])
#ifdef C_DECLS_ONLY
;
#else
{
    char **save = environ;
    int r;
    environ = (char **)envp;
    r = execvp(file, argv);
    environ = save;
    return r;
}
#endif
int execle(const char *path, const char *arg, ...)
#ifdef C_DECLS_ONLY
;
#else
{
    char *av[256];
    char **envp;
    int n = 0;
    va_list ap;
    va_start(ap, arg);
    av[n++] = (char *)arg;
    while (n < 255 && (av[n] = va_arg(ap, char *))) n++;
    envp = va_arg(ap, char **);
    va_end(ap);
    return execve(path, av, envp);
}
#endif
int execlp(const char *file, const char *arg, ...)
#ifdef C_DECLS_ONLY
;
#else
{
    char *av[256];
    int n = 0;
    va_list ap;
    va_start(ap, arg);
    av[n++] = (char *)arg;
    while (n < 255 && (av[n] = va_arg(ap, char *))) n++;
    va_end(ap);
    return execvp(file, av);
}
#endif
int system(const char *cmd)
#ifdef C_DECLS_ONLY
;
#else
{
    pid_t pid;
    int st;
    if (!cmd) return 1;
    fflush(NULL);
    pid = fork();
    if (pid < 0) return -1;
    if (!pid) {
        char *av[] = { "sh", "-c", (char *)cmd, NULL };
        execve("/bin/sh", av, environ);
        _exit(127);
    }
    while (waitpid(pid, &st, 0) < 0) if (errno != EINTR) return -1;
    return st;
}
#endif
FILE *popen(const char *cmd, const char *mode)
#ifdef C_DECLS_ONLY
;
#else
{
    int p[2], parent_end, child_end;
    pid_t pid;
    FILE *f;
    int rd = mode[0] == 'r';
    if (pipe(p) < 0) return NULL;
    parent_end = rd ? p[0] : p[1]; child_end = rd ? p[1] : p[0];
    fflush(NULL);
    pid = fork();
    if (pid < 0) { close(p[0]); close(p[1]); return NULL; }
    if (!pid) {
        char *av[] = { "sh", "-c", (char *)cmd, NULL };
        close(parent_end);
        if (child_end != (rd ? 1 : 0)) { dup2(child_end, rd ? 1 : 0); close(child_end); }
        execve("/bin/sh", av, environ);
        _exit(127);
    }
    close(child_end);
    f = fdopen(parent_end, rd ? "r" : "w");
    if (!f) { close(parent_end); return NULL; }
    f->pid = pid;
    return f;
}
#endif
int pclose(FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    int st;
    pid_t pid = f->pid;
    fclose(f);
    while (waitpid(pid, &st, 0) < 0) if (errno != EINTR) return -1;
    return st;
}
#endif

/* wait */
#define WNOHANG 1
#define WUNTRACED 2
#define WCONTINUED 8
#define WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define WTERMSIG(s) ((s) & 0x7f)
#define WSTOPSIG(s) WEXITSTATUS(s)
#define WIFEXITED(s) (!WTERMSIG(s))
#define WIFSIGNALED(s) ((signed char)(((s) & 0x7f) + 1) >> 1 > 0)
#define WIFSTOPPED(s) (((s) & 0xff) == 0x7f)
#define WIFCONTINUED(s) ((s) == 0xffff)
#define WCOREDUMP(s) ((s) & 0x80)
struct rusage { struct timeval ru_utime, ru_stime; long ru_maxrss, ru_ixrss, ru_idrss, ru_isrss, ru_minflt, ru_majflt, ru_nswap, ru_inblock, ru_oublock, ru_msgsnd, ru_msgrcv, ru_nsignals, ru_nvcsw, ru_nivcsw; };
#define RUSAGE_SELF 0
#define RUSAGE_CHILDREN (-1)
pid_t wait3(int *st, int options, struct rusage *ru)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_wait4, -1, st, options, ru)); }
#endif
pid_t wait4(pid_t pid, int *st, int options, struct rusage *ru)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_wait4, pid, st, options, ru)); }
#endif
int getrusage(int who, struct rusage *ru)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_getrusage, who, ru)); }
#endif
struct rlimit { unsigned long rlim_cur, rlim_max; };
typedef unsigned long rlim_t;
#define RLIM_INFINITY (~0UL)
#define RLIMIT_CPU 0
#define RLIMIT_FSIZE 1
#define RLIMIT_DATA 2
#define RLIMIT_STACK 3
#define RLIMIT_CORE 4
#define RLIMIT_NOFILE 7
#define RLIMIT_AS 9
int getrlimit(int r, struct rlimit *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_getrlimit, r, l)); }
#endif
int setrlimit(int r, const struct rlimit *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_setrlimit, r, l)); }
#endif
struct tms { long tms_utime, tms_stime, tms_cutime, tms_cstime; };
clock_t times(struct tms *t)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_times, t)); }
#endif
clock_t clock(void)
#ifdef C_DECLS_ONLY
;
#else
{ struct timespec t; if (clock_gettime(2, &t) < 0) return -1; return t.tv_sec * 1000000L + t.tv_nsec / 1000; }
#endif
struct sysinfo { long uptime; unsigned long loads[3], totalram, freeram, sharedram, bufferram, totalswap, freeswap; unsigned short procs, pad; unsigned long totalhigh, freehigh; unsigned mem_unit; char f[4]; };
int sysinfo(struct sysinfo *s)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(SYS_sysinfo, s)); }
#endif
int get_nprocs(void)
#ifdef C_DECLS_ONLY
;
#else
{ unsigned long m[16]; long r = sys3(SYS_sched_getaffinity, 0, sizeof m, m); int i, n = 0; if (r < 0) return 1; for (i = 0; i < 16; i++) n += __builtin_popcountl(m[i]); return n ? n : 1; }
#endif
int prctl(int op, unsigned long a, unsigned long b, unsigned long c, unsigned long d)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_prctl, op, a, b, c, d, 0)); }
#endif

/* memory */
#ifndef MAP_PRIVATE
#define MAP_SHARED 1
#define MAP_PRIVATE 2
#endif
#ifndef MAP_ANONYMOUS
#define MAP_FIXED 0x10
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS
#define MAP_NORESERVE 0x4000
#define MAP_POPULATE 0x8000
#endif
#define MAP_FAILED ((void *)-1)
#define PROT_NONE 0
#define MS_ASYNC 1
#define MS_INVALIDATE 2
#define MS_SYNC 4
#define MADV_NORMAL 0
#define MADV_RANDOM 1
#define MADV_SEQUENTIAL 2
#define MADV_WILLNEED 3
#define MADV_DONTNEED 4
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t off)
#ifdef C_DECLS_ONLY
;
#else
{
#ifdef __i386__
    long r = sys6(SYS_mmap, (long)addr, len, prot, flags, fd, (long)(off >> 12));  /* mmap2 counts in pages */
#else
    long r = sys6(SYS_mmap, (long)addr, len, prot, flags, fd, off);
#endif
    if (r < 0 && r > -4096) { errno = -r; return MAP_FAILED; }
    return (void *)r;
}
#endif
int munmap(void *a, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_munmap, a, n)); }
#endif
int msync(void *a, size_t n, int f)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_msync, a, n, f)); }
#endif
int madvise(void *a, size_t n, int adv)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_madvise, a, n, adv)); }
#endif
int posix_madvise(void *a, size_t n, int adv)
#ifdef C_DECLS_ONLY
;
#else
{ return madvise(a, n, adv); }
#endif
int mlock(const void *a, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)n; return 0; }
#endif
int munlock(const void *a, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)n; return 0; }
#endif

/* the ioctl / termios corner */
#define TIOCGWINSZ 0x5413
#define TIOCSWINSZ 0x5414
#define FIONREAD 0x541B
#define FIONBIO 0x5421
#define TIOCSCTTY 0x540E
struct winsize { unsigned short ws_row, ws_col, ws_xpixel, ws_ypixel; };
#define B0 0
#define B9600 015
#define B19200 016
#define B38400 017
#define B57600 010001
#define B115200 010002
#define TCSANOW 0
#define TCSADRAIN 1
#define TCSAFLUSH 2
#define TCIFLUSH 0
#define TCOFLUSH 1
#define TCIOFLUSH 2
#define TCOOFF 0
#define TCOON 1
typedef unsigned int speed_t;
typedef unsigned char cc_t;
typedef unsigned int tcflag_t;
#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VTIME 5
#define VMIN 6
#define VSTART 8
#define VSTOP 9
#define VSUSP 10
#define NCCS 32
#define IGNBRK 1
#define BRKINT 2
#define IGNPAR 4
#define PARMRK 8
#define INPCK 16
#define ISTRIP 32
#define INLCR 64
#define IGNCR 128
#define ECHONL 0100
#define IXON 02000
#define IXANY 04000
#define IXOFF 010000
#define CSIZE 060
#define CS5 0
#define CS6 020
#define CS7 040
#define CS8 060
#define CSTOPB 0100
#define CREAD 0200
#define PARENB 0400
#define PARODD 01000
#define HUPCL 02000
#define CLOCAL 04000
#define CBAUD 010017
int tcflush(int fd, int q)
#ifdef C_DECLS_ONLY
;
#else
{ return ioctl(fd, 0x540B, (void *)(long)q); }
#endif
int tcdrain(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ return ioctl(fd, 0x5409, (void *)1L); }
#endif
int tcflow(int fd, int a)
#ifdef C_DECLS_ONLY
;
#else
{ return ioctl(fd, 0x540A, (void *)(long)a); }
#endif
int tcsendbreak(int fd, int d)
#ifdef C_DECLS_ONLY
;
#else
{ (void)d; return ioctl(fd, 0x5409, (void *)0L); }
#endif
speed_t cfgetospeed(const struct termios *t)
#ifdef C_DECLS_ONLY
;
#else
{ return t->c_cflag & CBAUD; }
#endif
speed_t cfgetispeed(const struct termios *t)
#ifdef C_DECLS_ONLY
;
#else
{ return t->c_cflag & CBAUD; }
#endif
int cfsetospeed(struct termios *t, speed_t s)
#ifdef C_DECLS_ONLY
;
#else
{ t->c_cflag = (t->c_cflag & ~CBAUD) | s; return 0; }
#endif
int cfsetispeed(struct termios *t, speed_t s)
#ifdef C_DECLS_ONLY
;
#else
{ (void)t; (void)s; return 0; }
#endif
int cfsetspeed(struct termios *t, speed_t s)
#ifdef C_DECLS_ONLY
;
#else
{ return cfsetospeed(t, s); }
#endif
void cfmakeraw(struct termios *t)
#ifdef C_DECLS_ONLY
;
#else
{
    t->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    t->c_oflag &= ~OPOST;
    t->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    t->c_cflag &= ~(CSIZE | PARENB);
    t->c_cflag |= CS8;
    t->c_cc[VMIN] = 1; t->c_cc[VTIME] = 0;
}
#endif
int posix_openpt(int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return open("/dev/ptmx", flags); }
#endif
int grantpt(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ (void)fd; return 0; }
#endif
int unlockpt(int fd)
#ifdef C_DECLS_ONLY
;
#else
{ int z = 0; return ioctl(fd, 0x40045431, &z); }
#endif
char *ptsname(int fd)
#ifdef C_DECLS_ONLY
;
#else
{
    static char buf[32];
    int n;
    if (ioctl(fd, 0x80045430, &n) < 0) return NULL;
    snprintf(buf, sizeof buf, "/dev/pts/%d", n);
    return buf;
}
#endif

/* getopt */
#ifdef C_DECLS_ONLY
extern char *optarg;
#else
char *optarg;
#endif
#ifdef C_DECLS_ONLY
extern int optind;
#else
int optind = 1, opterr = 1, optopt;
#endif
#ifndef C_DECLS_ONLY
static int c_optpos;
#endif
int getopt(int argc, char *const argv[], const char *shorts)
#ifdef C_DECLS_ONLY
;
#else
{
    const char *p;
    char *a;
    int c;
    if (optind == 0) { optind = 1; c_optpos = 0; }
    if (!c_optpos) {
        if (optind >= argc) return -1;
        a = argv[optind];
        if (a[0] != '-' || !a[1]) return -1;
        if (a[1] == '-' && !a[2]) { optind++; return -1; }
        c_optpos = 1;
    }
    a = argv[optind];
    c = a[c_optpos++];
    p = strchr(shorts[0] == '+' || shorts[0] == ':' ? shorts + 1 : shorts, c);
    if (!a[c_optpos]) { optind++; c_optpos = 0; }
    if (!p || c == ':') {
        optopt = c;
        if (opterr && shorts[0] != ':') fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], c);
        return '?';
    }
    if (p[1] == ':') {
        if (c_optpos) { optarg = argv[optind] + c_optpos; optind++; c_optpos = 0; }
        else if (p[2] == ':') optarg = NULL;
        else if (optind >= argc) {
            optopt = c;
            if (opterr && shorts[0] != ':') fprintf(stderr, "%s: option requires an argument -- '%c'\n", argv[0], c);
            return shorts[0] == ':' ? ':' : '?';
        } else optarg = argv[optind++];
    } else optarg = NULL;
    return c;
}
#endif
struct option { const char *name; int has_arg; int *flag; int val; };
#define no_argument 0
#define required_argument 1
#define optional_argument 2
int getopt_long(int argc, char *const argv[], const char *shorts, const struct option *longs, int *idx)
#ifdef C_DECLS_ONLY
;
#else
{
    char *a;
    const struct option *o, *hit = NULL;
    size_t l;
    char *eq;
    if (optind == 0) { optind = 1; c_optpos = 0; }
    if (c_optpos || optind >= argc) return getopt(argc, argv, shorts);
    a = argv[optind];
    if (a[0] != '-' || a[1] != '-') return getopt(argc, argv, shorts);
    if (!a[2]) { optind++; return -1; }
    eq = strchr(a + 2, '=');
    l = eq ? (size_t)(eq - a - 2) : strlen(a + 2);
    for (o = longs; o->name; o++) {
        if (!strncmp(o->name, a + 2, l)) {
            if (strlen(o->name) == l) { hit = o; break; }
            if (!hit) hit = o;
            else if (hit->has_arg != o->has_arg || hit->flag != o->flag || hit->val != o->val) { if (opterr) fprintf(stderr, "%s: option '%s' is ambiguous\n", argv[0], a); optind++; return '?'; }
        }
    }
    if (!hit) { if (opterr) fprintf(stderr, "%s: unrecognized option '%s'\n", argv[0], a); optind++; return '?'; }
    optind++;
    if (idx) *idx = hit - longs;
    if (hit->has_arg == no_argument) {
        if (eq) { if (opterr) fprintf(stderr, "%s: option '--%s' doesn't allow an argument\n", argv[0], hit->name); return '?'; }
        optarg = NULL;
    } else if (eq) optarg = eq + 1;
    else if (hit->has_arg == required_argument) {
        if (optind >= argc) { if (opterr) fprintf(stderr, "%s: option '--%s' requires an argument\n", argv[0], hit->name); return shorts[0] == ':' ? ':' : '?'; }
        optarg = argv[optind++];
    } else optarg = NULL;
    if (hit->flag) { *hit->flag = hit->val; return 0; }
    return hit->val;
}
#endif
int getopt_long_only(int argc, char *const argv[], const char *shorts, const struct option *longs, int *idx)
#ifdef C_DECLS_ONLY
;
#else
{ return getopt_long(argc, argv, shorts, longs, idx); }
#endif
/* ---- string, ctype, stdlib, time: what real programs reach for [chamesle] ---- */

/* strings */
char *strsep(char **sp, const char *delim)
#ifdef C_DECLS_ONLY
;
#else
{
    char *s = *sp, *e;
    if (!s) return NULL;
    e = s + strcspn(s, delim);
    if (*e) *e++ = 0; else e = NULL;
    *sp = e;
    return s;
}
#endif
char *strtok_r(char *s, const char *delim, char **save)
#ifdef C_DECLS_ONLY
;
#else
{
    char *e;
    if (!s) s = *save;
    if (!s) return NULL;
    s += strspn(s, delim);
    if (!*s) { *save = NULL; return NULL; }
    e = s + strcspn(s, delim);
    if (*e) *e++ = 0; else e = NULL;
    *save = e;
    return s;
}
#endif
char *strtok(char *s, const char *delim)
#ifdef C_DECLS_ONLY
;
#else
{ static char *save; return strtok_r(s, delim, &save); }
#endif
size_t strnlen(const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t i = 0; while (i < n && s[i]) i++; return i; }
#endif
size_t strlcpy(char *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(s);
    if (n) { size_t c = l < n - 1 ? l : n - 1; memcpy(d, s, c); d[c] = 0; }
    return l;
}
#endif
size_t strlcat(char *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t dl = strnlen(d, n), sl = strlen(s);
    if (dl == n) return n + sl;
    strlcpy(d + dl, s, n - dl);
    return dl + sl;
}
#endif
char *strncat(char *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ char *r = d; d += strlen(d); while (n-- && *s) *d++ = *s++; *d = 0; return r; }
#endif
char *stpncpy(char *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t l = strnlen(s, n); memcpy(d, s, l); memset(d + l, 0, n - l); return d + l; }
#endif
char *strchrnul(const char *s, int c)
#ifdef C_DECLS_ONLY
;
#else
{ while (*s && *s != (char)c) s++; return (char *)s; }
#endif
void *mempcpy(void *d, const void *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return (char *)memcpy(d, s, n) + n; }
#endif
void *memccpy(void *d, const void *s, int c, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned char *dd = d; const unsigned char *ss = s;
    while (n--) { if ((*dd++ = *ss++) == (unsigned char)c) return dd; }
    return NULL;
}
#endif
void *memmem(const void *h, size_t hl, const void *n, size_t nl)
#ifdef C_DECLS_ONLY
;
#else
{
    const char *p = h;
    if (!nl) return (void *)h;
    while (hl >= nl) {
        const char *q = memchr(p, *(const char *)n, hl - nl + 1);
        if (!q) return NULL;
        if (!memcmp(q, n, nl)) return (void *)q;
        hl -= q + 1 - p; p = q + 1;
    }
    return NULL;
}
#endif
char *strcasestr(const char *h, const char *n)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t nl = strlen(n);
    for (; *h; h++) if (!strncasecmp(h, n, nl)) return (char *)h;
    return nl ? NULL : (char *)h;
}
#endif
size_t strxfrm(char *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t l = strlen(s); if (n) strlcpy(d, s, n); return l; }
#endif
int strverscmp(const char *a, const char *b)
#ifdef C_DECLS_ONLY
;
#else
{
    while (*a && *b) {
        if (isdigit((unsigned char)*a) && isdigit((unsigned char)*b)) {
            const char *ea = a, *eb = b;
            while (*a == '0') a++;
            while (*b == '0') b++;
            ea = a; eb = b;
            while (isdigit((unsigned char)*ea)) ea++;
            while (isdigit((unsigned char)*eb)) eb++;
            if (ea - a != eb - b) return ea - a < eb - b ? -1 : 1;
            while (a < ea) { if (*a != *b) return (unsigned char)*a - (unsigned char)*b; a++; b++; }
        } else {
            if (*a != *b) return (unsigned char)*a - (unsigned char)*b;
            a++; b++;
        }
    }
    return (unsigned char)*a - (unsigned char)*b;
}
#endif
int ffs(int i)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_ffs(i); }
#endif
int ffsl(long i)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_ffsl(i); }
#endif
int ffsll(long long i)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_ffsll(i); }
#endif
void bcopy(const void *s, void *d, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ memmove(d, s, n); }
#endif
void bzero(void *d, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ memset(d, 0, n); }
#endif
int bcmp(const void *a, const void *b, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return memcmp(a, b, n); }
#endif
char *index(const char *s, int c)
#ifdef C_DECLS_ONLY
;
#else
{ return strchr(s, c); }
#endif
char *rindex(const char *s, int c)
#ifdef C_DECLS_ONLY
;
#else
{ return strrchr(s, c); }
#endif
void explicit_bzero(void *d, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ volatile char *p = d; while (n--) *p++ = 0; }
#endif
#ifndef C_DECLS_ONLY
static const char *const c_signames[] = { "Unknown signal 0", "Hangup", "Interrupt", "Quit", "Illegal instruction", "Trace/breakpoint trap", "Aborted",
    "Bus error", "Floating point exception", "Killed", "User defined signal 1", "Segmentation fault", "User defined signal 2", "Broken pipe",
    "Alarm clock", "Terminated", "Stack fault", "Child exited", "Continued", "Stopped (signal)", "Stopped", "Stopped (tty input)",
    "Stopped (tty output)", "Urgent I/O condition", "CPU time limit exceeded", "File size limit exceeded", "Virtual timer expired",
    "Profiling timer expired", "Window changed", "I/O possible", "Power failure", "Bad system call" };
#endif
char *strsignal(int s)
#ifdef C_DECLS_ONLY
;
#else
{ return (char *)(s > 0 && s < 32 ? c_signames[s] : "Unknown signal"); }
#endif

/* ctype */
int isblank(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c == ' ' || c == '\t'; }
#endif
int iscntrl(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return (c >= 0 && c < 32) || c == 127; }
#endif
int isgraph(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c > 32 && c < 127; }
#endif
int isascii(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c >= 0 && c < 128; }
#endif
int toascii(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c & 127; }
#endif

/* numbers */
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;
div_t div(int a, int b)
#ifdef C_DECLS_ONLY
;
#else
{ div_t r = { a / b, a % b }; return r; }
#endif
ldiv_t ldiv(long a, long b)
#ifdef C_DECLS_ONLY
;
#else
{ ldiv_t r = { a / b, a % b }; return r; }
#endif
lldiv_t lldiv(long long a, long long b)
#ifdef C_DECLS_ONLY
;
#else
{ lldiv_t r = { a / b, a % b }; return r; }
#endif
long long llabs(long long a)
#ifdef C_DECLS_ONLY
;
#else
{ return a < 0 ? -a : a; }
#endif
intmax_t imaxabs(intmax_t a)
#ifdef C_DECLS_ONLY
;
#else
{ return a < 0 ? -a : a; }
#endif
intmax_t strtoimax(const char *s, char **e, int base)
#ifdef C_DECLS_ONLY
;
#else
{ return strtoll(s, e, base); }
#endif
uintmax_t strtoumax(const char *s, char **e, int base)
#ifdef C_DECLS_ONLY
;
#else
{ return strtoull(s, e, base); }
#endif
#define RAND_MAX 2147483647
#ifndef C_DECLS_ONLY
static unsigned long long c_rand_state = 1;
#endif
void srandom(unsigned seed)
#ifdef C_DECLS_ONLY
;
#else
{ c_rand_state = seed ? seed : 1; }
#endif
long random(void)
#ifdef C_DECLS_ONLY
;
#else
{
    c_rand_state = c_rand_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (long)(c_rand_state >> 33);
}
#endif
void srand(unsigned seed)
#ifdef C_DECLS_ONLY
;
#else
{ srandom(seed); }
#endif
int rand(void)
#ifdef C_DECLS_ONLY
;
#else
{ return (int)random(); }
#endif
int rand_r(unsigned *seed)
#ifdef C_DECLS_ONLY
;
#else
{ unsigned long long s = *seed * 6364136223846793005ULL + 1442695040888963407ULL; *seed = s >> 32; return (int)((s >> 33) & RAND_MAX); }
#endif
void srand48(long seed)
#ifdef C_DECLS_ONLY
;
#else
{ srandom(seed); }
#endif
long lrand48(void)
#ifdef C_DECLS_ONLY
;
#else
{ return random(); }
#endif
long mrand48(void)
#ifdef C_DECLS_ONLY
;
#else
{ return (long)(int)random() * 2; }
#endif
double drand48(void)
#ifdef C_DECLS_ONLY
;
#else
{ return (random() >> 7) / 16777216.0 + (random() % 128) / (16777216.0 * 128); }
#endif
unsigned arc4random(void)
#ifdef C_DECLS_ONLY
;
#else
{ unsigned v; if (getrandom(&v, sizeof v, 0) != sizeof v) v = random(); return v; }
#endif
void arc4random_buf(void *b, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ if (getrandom(b, n, 0) != (ssize_t)n) { unsigned char *p = b; while (n--) *p++ = random(); } }
#endif
unsigned arc4random_uniform(unsigned n)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned lim, v;
    if (n < 2) return 0;
    lim = -n % n;
    do v = arc4random(); while (v < lim);
    return v % n;
}
#endif

void *bsearch(const void *key, const void *base, size_t n, size_t size, int (*cmp)(const void *, const void *))
#ifdef C_DECLS_ONLY
;
#else
{
    size_t lo = 0, hi = n;
    while (lo < hi) {
        size_t mid = lo + (hi - lo) / 2;
        const char *p = (const char *)base + mid * size;
        int c = cmp(key, p);
        if (!c) return (void *)p;
        if (c < 0) hi = mid; else lo = mid + 1;
    }
    return NULL;
}
#endif
#ifndef C_DECLS_ONLY
static void c_sort_r(char *base, size_t n, size_t size, int (*cmp)(const void *, const void *, void *), void *arg, char *tmp)
{
    size_t mid, i, j, k;
    if (n < 2) return;
    mid = n / 2;
    c_sort_r(base, mid, size, cmp, arg, tmp);
    c_sort_r(base + mid * size, n - mid, size, cmp, arg, tmp);
    i = 0; j = mid; k = 0;
    while (i < mid && j < n) {
        if (cmp(base + j * size, base + i * size, arg) < 0) memcpy(tmp + k++ * size, base + j++ * size, size);
        else memcpy(tmp + k++ * size, base + i++ * size, size);
    }
    while (i < mid) memcpy(tmp + k++ * size, base + i++ * size, size);
    while (j < n) memcpy(tmp + k++ * size, base + j++ * size, size);
    memcpy(base, tmp, n * size);
}
#endif
void qsort_r(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *, void *), void *arg)
#ifdef C_DECLS_ONLY
;
#else
{
    char *tmp;
    if (n < 2 || !size) return;
    tmp = malloc(n * size);
    if (!tmp) return;
    c_sort_r(base, n, size, cmp, arg, tmp);
    free(tmp);
}
#endif

/* atexit: exit runs them backwards, then flushes everything */
#ifndef C_DECLS_ONLY
static void (*c_atexit_fns[64])(void);
#endif
#ifndef C_DECLS_ONLY
static int c_atexit_n;
#endif
int atexit(void (*f)(void))
#ifdef C_DECLS_ONLY
;
#else
{ if (c_atexit_n == 64) return -1; c_atexit_fns[c_atexit_n++] = f; return 0; }
#endif
void c_run_exit(void)
#ifdef C_DECLS_ONLY
;
#else
{ while (c_atexit_n) c_atexit_fns[--c_atexit_n](); fflush(NULL); }
#endif
__attribute__((noreturn)) void _Exit(int code)
#ifdef C_DECLS_ONLY
;
#else
{ _exit(code); }
#endif
int at_quick_exit(void (*f)(void))
#ifdef C_DECLS_ONLY
;
#else
{ return atexit(f); }
#endif
__attribute__((noreturn)) void quick_exit(int code)
#ifdef C_DECLS_ONLY
;
#else
{ exit(code); }
#endif

/* memory */
int posix_memalign(void **out, size_t align, size_t size)
#ifdef C_DECLS_ONLY
;
#else
{
    char *p;
    if (align < sizeof(void *) || (align & (align - 1))) return EINVAL;
    p = malloc(size + align + sizeof(void *));
    if (!p) return ENOMEM;
    {
        char *a = (char *)(((unsigned long)p + sizeof(void *) + align - 1) & ~(align - 1));
        ((void **)a)[-1] = p;
        *out = a;
    }
    return 0;
}
#endif
void *aligned_alloc(size_t align, size_t size)
#ifdef C_DECLS_ONLY
;
#else
{ void *p; return posix_memalign(&p, align, size) ? NULL : p; }
#endif
void *memalign(size_t align, size_t size)
#ifdef C_DECLS_ONLY
;
#else
{ return aligned_alloc(align, size); }
#endif
void *valloc(size_t size)
#ifdef C_DECLS_ONLY
;
#else
{ return aligned_alloc(4096, size); }
#endif
void *reallocarray(void *p, size_t n, size_t size)
#ifdef C_DECLS_ONLY
;
#else
{ if (size && n > (size_t)-1 / size) { errno = ENOMEM; return NULL; } return realloc(p, n * size); }
#endif
#define alloca(n) __builtin_alloca(n)

/* temporary files */
#ifndef C_DECLS_ONLY
static void c_fill_x(char *x)
{
    static const char a[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    unsigned char r[8];
    int i;
    arc4random_buf(r, sizeof r);
    for (i = 0; i < 6; i++) x[i] = a[r[i] % 62];
}
#endif
int mkostemps(char *tpl, int suffix, int flags)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(tpl);
    int tries;
    if (l < 6 + (size_t)suffix || strncmp(tpl + l - 6 - suffix, "XXXXXX", 6)) { errno = EINVAL; return -1; }
    for (tries = 0; tries < 100; tries++) {
        int fd;
        c_fill_x(tpl + l - 6 - suffix);
        fd = open(tpl, O_RDWR | O_CREAT | O_EXCL | flags, 0600);
        if (fd >= 0 || errno != EEXIST) return fd;
    }
    return -1;
}
#endif
int mkstemp(char *tpl)
#ifdef C_DECLS_ONLY
;
#else
{ return mkostemps(tpl, 0, 0); }
#endif
int mkstemps(char *tpl, int suffix)
#ifdef C_DECLS_ONLY
;
#else
{ return mkostemps(tpl, suffix, 0); }
#endif
int mkostemp(char *tpl, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ return mkostemps(tpl, 0, flags); }
#endif
char *mkdtemp(char *tpl)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(tpl);
    int tries;
    if (l < 6 || strcmp(tpl + l - 6, "XXXXXX")) { errno = EINVAL; return NULL; }
    for (tries = 0; tries < 100; tries++) {
        c_fill_x(tpl + l - 6);
        if (mkdir(tpl, 0700) == 0) return tpl;
        if (errno != EEXIST) return NULL;
    }
    return NULL;
}
#endif
char *mktemp(char *tpl)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l = strlen(tpl);
    struct stat st;
    if (l < 6 || strcmp(tpl + l - 6, "XXXXXX")) { errno = EINVAL; tpl[0] = 0; return tpl; }
    do c_fill_x(tpl + l - 6); while (lstat(tpl, &st) == 0);
    return tpl;
}
#endif
char *tmpnam(char *s)
#ifdef C_DECLS_ONLY
;
#else
{
    static char buf[L_tmpnam];
    char *d = s ? s : buf;
    strcpy(d, "/tmp/tmpXXXXXX");
    mktemp(d);
    return d;
}
#endif
char *tempnam(const char *dir, const char *prefix)
#ifdef C_DECLS_ONLY
;
#else
{
    char *d = malloc(strlen(dir ? dir : "/tmp") + (prefix ? strlen(prefix) : 0) + 16);
    if (!d) return NULL;
    sprintf(d, "%s/%sXXXXXX", dir ? dir : "/tmp", prefix ? prefix : "");
    mktemp(d);
    return d;
}
#endif
FILE *tmpfile(void)
#ifdef C_DECLS_ONLY
;
#else
{
    char name[] = "/tmp/tmpfileXXXXXX";
    int fd = mkstemp(name);
    FILE *f;
    if (fd < 0) return NULL;
    unlink(name);
    f = fdopen(fd, "w+");
    if (!f) close(fd);
    return f;
}
#endif

/* printf pieces built on the core ones */
int vasprintf(char **out, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{
    va_list ap2;
    int n;
    va_copy(ap2, ap);
    n = vsnprintf(NULL, 0, fmt, ap2);
    va_end(ap2);
    if (n < 0) return -1;
    *out = malloc(n + 1);
    if (!*out) return -1;
    return vsnprintf(*out, n + 1, fmt, ap);
}
#endif
int asprintf(char **out, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; int n; va_start(ap, fmt); n = vasprintf(out, fmt, ap); va_end(ap); return n; }
#endif
int vdprintf(int fd, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{
    char *s;
    int n = vasprintf(&s, fmt, ap);
    if (n < 0) return -1;
    if (write(fd, s, n) < 0) n = -1;
    free(s);
    return n;
}
#endif
int dprintf(int fd, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; int n; va_start(ap, fmt); n = vdprintf(fd, fmt, ap); va_end(ap); return n; }
#endif
ssize_t getdelim(char **lp, size_t *cap, int delim, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t n = 0;
    int c;
    if (!*lp || !*cap) { *cap = 128; *lp = malloc(*cap); if (!*lp) return -1; }
    while ((c = fgetc(f)) != EOF) {
        if (n + 2 > *cap) { char *p = realloc(*lp, *cap * 2); if (!p) return -1; *lp = p; *cap *= 2; }
        (*lp)[n++] = c;
        if (c == delim) break;
    }
    if (!n) return -1;
    (*lp)[n] = 0;
    return n;
}
#endif
int fputs_unlocked(const char *s, FILE *f)
#ifdef C_DECLS_ONLY
;
#else
{ return fputs(s, f); }
#endif

/* time */
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID 3
#define CLOCK_MONOTONIC_RAW 4
#define CLOCK_REALTIME_COARSE 5
#define CLOCK_MONOTONIC_COARSE 6
#define CLOCK_BOOTTIME 7
#define TIMER_ABSTIME 1
#ifdef C_DECLS_ONLY
extern long timezone;
#else
long timezone;
#endif
#ifdef C_DECLS_ONLY
extern int daylight;
#else
int daylight;
#endif
#ifdef C_DECLS_ONLY
extern char *tzname[2];
#else
char *tzname[2] = { "UTC", "UTC" };
#endif
void tzset(void)
#ifdef C_DECLS_ONLY
;
#else
{ }
#endif
struct tm *gmtime_r(const time_t *t, struct tm *out)
#ifdef C_DECLS_ONLY
;
#else
{ *out = *gmtime(t); return out; }
#endif
struct tm *localtime_r(const time_t *t, struct tm *out)
#ifdef C_DECLS_ONLY
;
#else
{ *out = *localtime(t); return out; }
#endif
double difftime(time_t a, time_t b)
#ifdef C_DECLS_ONLY
;
#else
{ return (double)(a - b); }
#endif
char *asctime_r(const struct tm *t, char *buf)
#ifdef C_DECLS_ONLY
;
#else
{
    static const char wd[] = "SunMonTueWedThuFriSat", mo[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    sprintf(buf, "%.3s %.3s %2d %02d:%02d:%02d %d\n", wd + 3 * (t->tm_wday % 7), mo + 3 * (t->tm_mon % 12), t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, t->tm_year + 1900);
    return buf;
}
#endif
char *asctime(const struct tm *t)
#ifdef C_DECLS_ONLY
;
#else
{ static char buf[32]; return asctime_r(t, buf); }
#endif
char *ctime_r(const time_t *t, char *buf)
#ifdef C_DECLS_ONLY
;
#else
{ return asctime_r(localtime(t), buf); }
#endif
char *ctime(const time_t *t)
#ifdef C_DECLS_ONLY
;
#else
{ static char buf[32]; return ctime_r(t, buf); }
#endif
int clock_settime(int clk, const struct timespec *t)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(227, clk, t)); }
#endif
int settimeofday(const struct timeval *tv, const void *tz)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(164, tv, tz)); }
#endif
int timespec_get(struct timespec *t, int base)
#ifdef C_DECLS_ONLY
;
#else
{ if (base != 1) return 0; return clock_gettime(CLOCK_REALTIME, t) < 0 ? 0 : base; }
#endif
struct itimerval { struct timeval it_interval, it_value; };
#define ITIMER_REAL 0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF 2
int setitimer(int which, const struct itimerval *nw, struct itimerval *old)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_setitimer, which, nw, old)); }
#endif
int getitimer(int which, struct itimerval *cur)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_getitimer, which, cur)); }
#endif
#define timeradd(a, b, r) do { (r)->tv_sec = (a)->tv_sec + (b)->tv_sec; (r)->tv_usec = (a)->tv_usec + (b)->tv_usec; if ((r)->tv_usec >= 1000000) { (r)->tv_sec++; (r)->tv_usec -= 1000000; } } while (0)
#define timersub(a, b, r) do { (r)->tv_sec = (a)->tv_sec - (b)->tv_sec; (r)->tv_usec = (a)->tv_usec - (b)->tv_usec; if ((r)->tv_usec < 0) { (r)->tv_sec--; (r)->tv_usec += 1000000; } } while (0)
#define timercmp(a, b, op) (((a)->tv_sec == (b)->tv_sec) ? ((a)->tv_usec op (b)->tv_usec) : ((a)->tv_sec op (b)->tv_sec))
#define timerclear(t) ((t)->tv_sec = (t)->tv_usec = 0)
#define timerisset(t) ((t)->tv_sec || (t)->tv_usec)

char *strptime(const char *s, const char *fmt, struct tm *tm)
#ifdef C_DECLS_ONLY
;
#else
{
    static const char *const mon[] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
    static const char *const day[] = { "sun", "mon", "tue", "wed", "thu", "fri", "sat" };
    for (; *fmt; fmt++) {
        char *e;
        long v;
        int i;
        if (isspace((unsigned char)*fmt)) { while (isspace((unsigned char)*s)) s++; continue; }
        if (*fmt != '%') { if (*s++ != *fmt) return NULL; continue; }
        fmt++;
        if (*fmt == 'E' || *fmt == 'O') fmt++;
        switch (*fmt) {
        case 'Y': v = strtol(s, &e, 10); if (e == s) return NULL; tm->tm_year = v - 1900; s = e; break;
        case 'y': v = strtol(s, &e, 10); if (e == s) return NULL; tm->tm_year = v < 69 ? v + 100 : v; s = e; break;
        case 'm': v = strtol(s, &e, 10); if (e == s || v < 1 || v > 12) return NULL; tm->tm_mon = v - 1; s = e; break;
        case 'd': case 'e': while (*s == ' ') s++; v = strtol(s, &e, 10); if (e == s || v < 1 || v > 31) return NULL; tm->tm_mday = v; s = e; break;
        case 'H': v = strtol(s, &e, 10); if (e == s || v > 23) return NULL; tm->tm_hour = v; s = e; break;
        case 'M': v = strtol(s, &e, 10); if (e == s || v > 59) return NULL; tm->tm_min = v; s = e; break;
        case 'S': v = strtol(s, &e, 10); if (e == s || v > 61) return NULL; tm->tm_sec = v; s = e; break;
        case 'j': v = strtol(s, &e, 10); if (e == s) return NULL; tm->tm_yday = v - 1; s = e; break;
        case 'b': case 'B': case 'h':
            for (i = 0; i < 12; i++) if (!strncasecmp(s, mon[i], 3)) break;
            if (i == 12) return NULL;
            tm->tm_mon = i; s += 3;
            while (isalpha((unsigned char)*s)) s++;
            break;
        case 'a': case 'A':
            for (i = 0; i < 7; i++) if (!strncasecmp(s, day[i], 3)) break;
            if (i == 7) return NULL;
            tm->tm_wday = i; s += 3;
            while (isalpha((unsigned char)*s)) s++;
            break;
        case 'T': s = strptime(s, "%H:%M:%S", tm); if (!s) return NULL; break;
        case 'R': s = strptime(s, "%H:%M", tm); if (!s) return NULL; break;
        case 'F': s = strptime(s, "%Y-%m-%d", tm); if (!s) return NULL; break;
        case 'D': s = strptime(s, "%m/%d/%y", tm); if (!s) return NULL; break;
        case 'n': case 't': while (isspace((unsigned char)*s)) s++; break;
        case 'z': if (*s == 'Z') { s++; break; } if (*s != '+' && *s != '-') return NULL; s++; while (isdigit((unsigned char)*s) || *s == ':') s++; break;
        case 'Z': while (isalpha((unsigned char)*s)) s++; break;
        case '%': if (*s++ != '%') return NULL; break;
        default: return NULL;
        }
    }
    return (char *)s;
}
#endif
/* ---- signals the POSIX way [chamesle] ---- */
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGIOT 6
#define SIGBUS 7
#define SIGFPE 8
#define SIGUSR1 10
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGSTKFLT 16
#define SIGCONT 18
#define SIGSTOP 19
#define SIGTSTP 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGURG 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGIO 29
#define SIGPOLL 29
#define SIGPWR 30
#define SIGSYS 31
#define NSIG 65
#define SA_NOCLDSTOP 1
#define SA_NOCLDWAIT 2
#define SA_SIGINFO 4
#define SA_ONSTACK 0x08000000
#define SA_RESTART 0x10000000
#define SA_NODEFER 0x40000000
#define SA_RESETHAND 0x80000000
#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
typedef int sig_atomic_t;
typedef struct { unsigned long __bits[16]; } sigset_t;
typedef struct {
    int si_signo, si_errno, si_code, __pad0;
    union {
        struct { pid_t si_pid; uid_t si_uid; int si_status; };
        void *si_addr;
        char __pad[112];
    };
} siginfo_t;
struct sigaction {
    union { sighandler_t sa_handler; void (*sa_sigaction)(int, siginfo_t *, void *); };
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};
typedef struct { void *ss_sp; int ss_flags; size_t ss_size; } stack_t;
#define SS_ONSTACK 1
#define SS_DISABLE 2
#define MINSIGSTKSZ 2048
#define SIGSTKSZ 8192

int sigemptyset(sigset_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ memset(s, 0, sizeof *s); return 0; }
#endif
int sigfillset(sigset_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ memset(s, 0xff, sizeof *s); return 0; }
#endif
int sigaddset(sigset_t *s, int n)
#ifdef C_DECLS_ONLY
;
#else
{ if (n < 1 || n > 64) { errno = EINVAL; return -1; } s->__bits[(n - 1) / (8 * sizeof(long))] |= 1UL << (n - 1) % (8 * sizeof(long)); return 0; }
#endif
int sigdelset(sigset_t *s, int n)
#ifdef C_DECLS_ONLY
;
#else
{ if (n < 1 || n > 64) { errno = EINVAL; return -1; } s->__bits[(n - 1) / (8 * sizeof(long))] &= ~(1UL << (n - 1) % (8 * sizeof(long))); return 0; }
#endif
int sigismember(const sigset_t *s, int n)
#ifdef C_DECLS_ONLY
;
#else
{ if (n < 1 || n > 64) { errno = EINVAL; return -1; } return (s->__bits[(n - 1) / (8 * sizeof(long))] >> (n - 1) % (8 * sizeof(long))) & 1; }
#endif
int sigisemptyset(const sigset_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ return !s->__bits[0] && !s->__bits[1]; }
#endif
int sigaction(int n, const struct sigaction *act, struct sigaction *old)
#ifdef C_DECLS_ONLY
;
#else
{
    struct c_sigaction k, ko;
    long r;
    if (act) { k.handler = act->sa_handler; k.flags = (unsigned long)(unsigned)act->sa_flags | 0x04000000; k.restorer = c_restore_rt; memcpy(&k.mask, act->sa_mask.__bits, 8); }
    r = fail(sys4(SYS_rt_sigaction, n, act ? &k : NULL, old ? &ko : NULL, 8));
    if (r < 0) return -1;
    if (old) { memset(old, 0, sizeof *old); old->sa_handler = ko.handler; old->sa_flags = ko.flags & ~0x04000000UL; memcpy(old->sa_mask.__bits, &ko.mask, 8); }
    return 0;
}
#endif
int sigprocmask(int how, const sigset_t *set, sigset_t *old)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned long long o = 0;
    long r = fail(sys4(SYS_rt_sigprocmask, how, set ? set->__bits : NULL, old ? &o : NULL, 8));
    if (r < 0) return -1;
    if (old) { memset(old, 0, sizeof *old); memcpy(old->__bits, &o, 8); }
    return 0;
}
#endif
int pthread_sigmask(int how, const sigset_t *set, sigset_t *old)
#ifdef C_DECLS_ONLY
;
#else
{ return sigprocmask(how, set, old) < 0 ? errno : 0; }
#endif
int sigpending(sigset_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ unsigned long long o = 0; if (fail(sys2(SYS_rt_sigpending, &o, 8)) < 0) return -1; memset(s, 0, sizeof *s); memcpy(s->__bits, &o, 8); return 0; }
#endif
int sigsuspend(const sigset_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_rt_sigsuspend, s->__bits, 8)); }
#endif
int sigaltstack(const stack_t *ss, stack_t *old)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_sigaltstack, ss, old)); }
#endif
int raise(int sig)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_tgkill, getpid(), gettid(), sig)); }
#endif
int killpg(int pg, int sig)
#ifdef C_DECLS_ONLY
;
#else
{ return kill(-pg, sig); }
#endif
int sigignore(int n)
#ifdef C_DECLS_ONLY
;
#else
{ return signal(n, SIG_IGN) == SIG_ERR ? -1 : 0; }
#endif
sighandler_t sysv_signal(int n, sighandler_t f)
#ifdef C_DECLS_ONLY
;
#else
{ return signal(n, f); }
#endif
void psignal(int sig, const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ fprintf(stderr, "%s%s%s\n", s ? s : "", s && *s ? ": " : "", strsignal(sig)); }
#endif
typedef struct { jmp_buf b; } sigjmp_buf[1];
#define sigsetjmp(env, save) setjmp((env)->b)
#define siglongjmp(env, v) longjmp((env)->b, v)
#define _setjmp(b) setjmp(b)
#define _longjmp(b, v) longjmp(b, v)
/* ---- libm: sqrt and the roundings by hand, the transcendental ones on the x87 [chamesle] ---- */
#define M_E 2.7182818284590452354
#define M_LOG2E 1.4426950408889634074
#define M_LOG10E 0.43429448190325182765
#define M_LN2 0.69314718055994530942
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.78539816339744830962
#define M_1_PI 0.31830988618379067154
#define M_2_PI 0.63661977236758134308
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT1_2 0.70710678118654752440
#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
#define INFINITY (__builtin_inff())
#define NAN (__builtin_nanf(""))
#define FP_NAN 0
#define FP_INFINITE 1
#define FP_ZERO 2
#define FP_SUBNORMAL 3
#define FP_NORMAL 4
#define FP_ILOGB0 (-2147483647 - 1)
#define FP_ILOGBNAN (-2147483647 - 1)
#define MATH_ERRNO 1
#define math_errhandling 1
typedef float float_t;
typedef double double_t;
#define isnan(x) __builtin_isnan(x)
#define isinf(x) __builtin_isinf(x)
#define isfinite(x) __builtin_isfinite(x)
#define isnormal(x) __builtin_isnormal(x)
#define signbit(x) __builtin_signbit(x)
#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
#define isgreater(a, b) __builtin_isgreater(a, b)
#define isgreaterequal(a, b) __builtin_isgreaterequal(a, b)
#define isless(a, b) __builtin_isless(a, b)
#define islessequal(a, b) __builtin_islessequal(a, b)
#define islessgreater(a, b) __builtin_islessgreater(a, b)
#define isunordered(a, b) __builtin_isunordered(a, b)

#ifndef C_DECLS_ONLY
static long double c_fyl2x(long double y, long double x) { long double r; __asm__("fyl2x" : "=t"(r) : "0"(x), "u"(y) : "st(1)"); return r; }
#endif
#ifndef C_DECLS_ONLY
static long double c_f2xm1(long double x) { long double r; __asm__("f2xm1" : "=t"(r) : "0"(x)); return r; }
#endif
#ifndef C_DECLS_ONLY
static long double c_fscale(long double x, long double n) { long double r; __asm__("fscale" : "=t"(r) : "0"(x), "u"(n)); return r; }
#endif
#ifndef C_DECLS_ONLY
static long double c_frndint(long double x) { long double r; __asm__("frndint" : "=t"(r) : "0"(x)); return r; }
#endif
#ifndef C_DECLS_ONLY
static long double c_exp2(long double x)
{
    long double n, f;
    if (x > 16400) return __builtin_infl();
    if (x < -16400) return 0;
    n = c_frndint(x); f = x - n;
    return c_fscale(c_f2xm1(f) + 1, n);
}
#endif

double fabs(double x)
#ifdef C_DECLS_ONLY
;
#else
{ union { double d; unsigned long long u; } v = { x }; v.u &= ~(1ULL << 63); return v.d; }
#endif
float fabsf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)fabs(x); }
#endif
long double fabsl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ return x < 0 ? -x : x; }
#endif
double copysign(double x, double y)
#ifdef C_DECLS_ONLY
;
#else
{ union { double d; unsigned long long u; } a = { x }, b = { y }; a.u = (a.u & ~(1ULL << 63)) | (b.u & (1ULL << 63)); return a.d; }
#endif
float copysignf(float x, float y)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)copysign(x, y); }
#endif
double sqrt(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double r; __asm__("sqrtsd %1, %0" : "=x"(r) : "x"(x)); return r; }
#endif
float sqrtf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ float r; __asm__("sqrtss %1, %0" : "=x"(r) : "x"(x)); return r; }
#endif
long double sqrtl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double r; __asm__("fsqrt" : "=t"(r) : "0"(x)); return r; }
#endif
double trunc(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    union { double d; unsigned long long u; } v = { x };
    int e = (int)((v.u >> 52) & 0x7ff) - 0x3ff;
    if (e >= 52) return x;
    if (e < 0) { v.u &= 1ULL << 63; return v.d; }
    v.u &= ~(0x000fffffffffffffULL >> e);
    return v.d;
}
#endif
double floor(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double t = trunc(x); return t > x ? t - 1 : t; }
#endif
double ceil(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double t = trunc(x); return t < x ? t + 1 : t; }
#endif
double round(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double t = trunc(x); if (fabs(x - t) >= 0.5) t += copysign(1.0, x); return t; }
#endif
double rint(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (double)c_frndint(x); }
#endif
double nearbyint(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return rint(x); }
#endif
float floorf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)floor(x); }
#endif
float ceilf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)ceil(x); }
#endif
float truncf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)trunc(x); }
#endif
float roundf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)round(x); }
#endif
float rintf(float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)rint(x); }
#endif
long double floorl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double t = (long double)(long long)x; return t > x ? t - 1 : t; }
#endif
long double ceill(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double t = (long double)(long long)x; return t < x ? t + 1 : t; }
#endif
long double truncl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (long double)(long long)x; }
#endif
long lround(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (long)round(x); }
#endif
long long llround(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (long long)round(x); }
#endif
long lrint(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (long)rint(x); }
#endif
long long llrint(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (long long)rint(x); }
#endif
double fmod(double x, double y)
#ifdef C_DECLS_ONLY
;
#else
{
    long double r = x, d = y;
    if (y == 0 || isinf(x) || isnan(x) || isnan(y)) return __builtin_nan("");
    if (isinf(y)) return x;
    __asm__ __volatile__("1: fprem\n fnstsw %%ax\n testb $4, %%ah\n jnz 1b" : "+t"(r) : "u"(d) : "ax", "cc");
    return (double)r;
}
#endif
float fmodf(float x, float y)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)fmod(x, y); }
#endif
double remainder(double x, double y)
#ifdef C_DECLS_ONLY
;
#else
{ double n = rint(x / y); return x - n * y; }
#endif
double modf(double x, double *ip)
#ifdef C_DECLS_ONLY
;
#else
{ double t = trunc(x); *ip = t; return isinf(x) ? copysign(0.0, x) : x - t; }
#endif
double frexp(double x, int *e)
#ifdef C_DECLS_ONLY
;
#else
{
    union { double d; unsigned long long u; } v = { x };
    int ex = (int)((v.u >> 52) & 0x7ff);
    if (!ex) {
        if (x == 0) { *e = 0; return x; }
        x *= 18014398509481984.0;
        v.d = x; ex = (int)((v.u >> 52) & 0x7ff) - 54;
    } else if (ex == 0x7ff) { *e = 0; return x; }
    *e = ex - 0x3fe;
    v.u = (v.u & ~(0x7ffULL << 52)) | (0x3feULL << 52);
    return v.d;
}
#endif
double scalbn(double x, int n)
#ifdef C_DECLS_ONLY
;
#else
{ return ldexp(x, n); }
#endif
double scalbln(double x, long n)
#ifdef C_DECLS_ONLY
;
#else
{ return ldexp(x, n > 100000 ? 100000 : n < -100000 ? -100000 : (int)n); }
#endif
int ilogb(double x)
#ifdef C_DECLS_ONLY
;
#else
{ int e; if (x == 0) return FP_ILOGB0; if (isnan(x)) return FP_ILOGBNAN; if (isinf(x)) return 2147483647; frexp(x, &e); return e - 1; }
#endif
double logb(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (double)ilogb(x); }
#endif
double fmin(double a, double b)
#ifdef C_DECLS_ONLY
;
#else
{ return isnan(a) ? b : isnan(b) ? a : a < b ? a : b; }
#endif
double fmax(double a, double b)
#ifdef C_DECLS_ONLY
;
#else
{ return isnan(a) ? b : isnan(b) ? a : a > b ? a : b; }
#endif
float fminf(float a, float b)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)fmin(a, b); }
#endif
float fmaxf(float a, float b)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)fmax(a, b); }
#endif
double fdim(double a, double b)
#ifdef C_DECLS_ONLY
;
#else
{ return a > b ? a - b : 0; }
#endif
double fma(double a, double b, double c)
#ifdef C_DECLS_ONLY
;
#else
{ return (double)((long double)a * b + c); }
#endif
double nan(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ (void)s; return __builtin_nan(""); }
#endif
double nextafter(double x, double y)
#ifdef C_DECLS_ONLY
;
#else
{
    union { double d; unsigned long long u; } v = { x };
    if (isnan(x) || isnan(y)) return x + y;
    if (x == y) return y;
    if (x == 0) { v.u = 1; return y > 0 ? v.d : -v.d; }
    if ((x < y) == (x > 0)) v.u++; else v.u--;
    return v.d;
}
#endif

double exp2(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (double)c_exp2(x); }
#endif
double exp(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return (double)c_exp2((long double)x * 1.4426950408889634073599246810018921L); }
#endif
double expm1(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    long double t = (long double)x * 1.4426950408889634073599246810018921L;
    if (fabs(x) < 0.3) return (double)(c_f2xm1(t));
    return (double)(c_exp2(t) - 1);
}
#endif
double log(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (x < 0) return __builtin_nan(""); return (double)c_fyl2x(0.693147180559945309417232121458176568L, x); }
#endif
double log2(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (x < 0) return __builtin_nan(""); return (double)c_fyl2x(1, x); }
#endif
double log10(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (x < 0) return __builtin_nan(""); return (double)c_fyl2x(0.301029995663981195213738894724493027L, x); }
#endif
double log1p(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    long double r;
    if (x < -1) return __builtin_nan("");
    if (fabs(x) < 0.29) { __asm__("fyl2xp1" : "=t"(r) : "0"((long double)x), "u"(0.693147180559945309417232121458176568L) : "st(1)"); return (double)r; }
    return log(1 + x);
}
#endif
double pow(double x, double y)
#ifdef C_DECLS_ONLY
;
#else
{
    long double r;
    int yint;
    if (y == 0 || x == 1) return 1;
    if (isnan(x) || isnan(y)) return __builtin_nan("");
    yint = fabs(y) < 9007199254740992.0 && y == trunc(y);
    if (x == 0) {
        if (y < 0) return yint && fmod(y, 2) != 0 ? copysign(HUGE_VAL, x) : HUGE_VAL;
        return yint && fmod(y, 2) != 0 ? x : 0;
    }
    if (isinf(y)) { double a = fabs(x); return a == 1 ? 1 : (a > 1) == (y > 0) ? HUGE_VAL : 0; }
    if (isinf(x)) { if (x > 0) return y > 0 ? HUGE_VAL : 0; return y > 0 ? (yint && fmod(y, 2) != 0 ? -HUGE_VAL : HUGE_VAL) : (yint && fmod(y, 2) != 0 ? -0.0 : 0.0); }
    if (x < 0) {
        if (!yint) return __builtin_nan("");
        r = c_exp2((long double)y * c_fyl2x(1, -(long double)x));
        return fmod(y, 2) != 0 ? -(double)r : (double)r;
    }
    return (double)c_exp2((long double)y * c_fyl2x(1, (long double)x));
}
#endif
double sin(double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double r = x; if (isinf(x) || isnan(x)) return __builtin_nan(""); if (fabs(x) > 1e18) r = fmod(x, 6.283185307179586476925286766559); __asm__("fsin" : "+t"(r)); return (double)r; }
#endif
double cos(double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double r = x; if (isinf(x) || isnan(x)) return __builtin_nan(""); if (fabs(x) > 1e18) r = fmod(x, 6.283185307179586476925286766559); __asm__("fcos" : "+t"(r)); return (double)r; }
#endif
double tan(double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double r = x, one; if (isinf(x) || isnan(x)) return __builtin_nan(""); __asm__("fptan" : "+t"(r), "=u"(one)); return (double)one; }
#endif
double atan2(double y, double x)
#ifdef C_DECLS_ONLY
;
#else
{ long double r; __asm__("fpatan" : "=t"(r) : "0"((long double)x), "u"((long double)y) : "st(1)"); return (double)r; }
#endif
double atan(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return atan2(x, 1); }
#endif
double asin(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (fabs(x) > 1) return __builtin_nan(""); return atan2(x, sqrt((1 - x) * (1 + x))); }
#endif
double acos(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (fabs(x) > 1) return __builtin_nan(""); return atan2(sqrt((1 - x) * (1 + x)), x); }
#endif
double sinh(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double e = expm1(fabs(x)); double r = e < 1e300 ? (e + e / (e + 1)) / 2 : exp(fabs(x)) / 2; return copysign(r, x); }
#endif
double cosh(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double e = exp(fabs(x)); return (e + 1 / e) / 2; }
#endif
double tanh(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double a = fabs(x), e; if (a > 20) return copysign(1.0, x); e = expm1(2 * a); return copysign(e / (e + 2), x); }
#endif
double asinh(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double a = fabs(x); return copysign(log(a + sqrt(a * a + 1)), x); }
#endif
double acosh(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (x < 1) return __builtin_nan(""); return log(x + sqrt(x * x - 1)); }
#endif
double atanh(double x)
#ifdef C_DECLS_ONLY
;
#else
{ return 0.5 * log1p(2 * x / (1 - x)); }
#endif
double hypot(double x, double y)
#ifdef C_DECLS_ONLY
;
#else
{
    double a = fabs(x), b = fabs(y), t;
    if (isinf(a) || isinf(b)) return HUGE_VAL;
    if (a < b) { t = a; a = b; b = t; }
    if (a == 0) return 0;
    t = b / a;
    return a * sqrt(1 + t * t);
}
#endif
double cbrt(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    double r;
    if (x == 0 || isinf(x) || isnan(x)) return x;
    r = copysign(pow(fabs(x), 1.0 / 3.0), x);
    return r - (r * r * r - x) / (3 * r * r);
}
#endif
double c_erf_series(double x)
#ifdef C_DECLS_ONLY
;
#else
{ double t = x, s = x; int n; for (n = 1; n < 80; n++) { t *= -x * x / n; s += t / (2 * n + 1); } return 1.1283791670955126 * s; }
#endif
#ifdef C_DECLS_ONLY
extern double erfc(double x);
#else
double erfc(double x);
#endif
double erf(double x)
#ifdef C_DECLS_ONLY
;
#else
{ if (fabs(x) < 2.5) return c_erf_series(x); return x > 0 ? 1 - erfc(x) : erfc(-x) - 1; }
#endif
double erfc(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    double f = 0;
    int n;
    if (x < 2.5) return 1 - erf(x);
    for (n = 60; n >= 1; n--) f = n / 2.0 / (x + f);
    return exp(-x * x) / (1.7724538509055160 * (x + f));
}
#endif
double lgamma(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    static const double c[] = { 76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2, -0.5395239384953e-5 };
    double y, tmp, ser;
    int j;
    if (x < 0.5) return log(M_PI / fabs(sin(M_PI * x))) - lgamma(1 - x);
    y = x; tmp = x + 5.5; tmp -= (x + 0.5) * log(tmp); ser = 1.000000000190015;
    for (j = 0; j < 6; j++) ser += c[j] / ++y;
    return -tmp + log(2.5066282746310005 * ser / x);
}
#endif
double tgamma(double x)
#ifdef C_DECLS_ONLY
;
#else
{
    if (x == trunc(x) && x > 0 && x < 24) { double r = 1; int i; for (i = 2; i < (int)x; i++) r *= i; return r; }
    if (x < 0.5) return M_PI / (sin(M_PI * x) * tgamma(1 - x));
    return exp(lgamma(x));
}
#endif
#ifdef C_DECLS_ONLY
#define c_float_fn(name) float name##f(float x);
#else
#define c_float_fn(name) float name##f(float x) { return (float)name(x); }
#endif
c_float_fn(sin) c_float_fn(cos) c_float_fn(tan) c_float_fn(asin) c_float_fn(acos) c_float_fn(atan) c_float_fn(exp) c_float_fn(log) c_float_fn(log2)
c_float_fn(log10) c_float_fn(sinh) c_float_fn(cosh) c_float_fn(tanh) c_float_fn(exp2) c_float_fn(expm1) c_float_fn(log1p) c_float_fn(cbrt)
float powf(float x, float y)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)pow(x, y); }
#endif
float atan2f(float y, float x)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)atan2(y, x); }
#endif
float hypotf(float x, float y)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)hypot(x, y); }
#endif
float ldexpf(float x, int n)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)ldexp(x, n); }
#endif
float frexpf(float x, int *e)
#ifdef C_DECLS_ONLY
;
#else
{ return (float)frexp(x, e); }
#endif
long double expl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ return c_exp2(x * 1.4426950408889634073599246810018921L); }
#endif
long double logl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ return c_fyl2x(0.693147180559945309417232121458176568L, x); }
#endif
long double powl(long double x, long double y)
#ifdef C_DECLS_ONLY
;
#else
{ return (long double)pow((double)x, (double)y); }
#endif
long double sinl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ return sin((double)x); }
#endif
long double cosl(long double x)
#ifdef C_DECLS_ONLY
;
#else
{ return cos((double)x); }
#endif
/* ---- scanf, locale and wide char stubs, threads that aren't, dlopen that can't [chamesle] ---- */
#ifndef C_DECLS_ONLY
static int c_scan(int (*get)(void *), void (*unget)(int, void *), void *src, const char *fmt, va_list ap)
{
    int n = 0, c, count = 0;
    for (; *fmt; fmt++) {
        int sup = 0, width = 0, lng = 0, hh = 0, ok;
        if (isspace((unsigned char)*fmt)) { while (isspace(c = get(src))) ; unget(c, src); continue; }
        if (*fmt != '%') {
            c = get(src);
            if (c != (unsigned char)*fmt) { unget(c, src); return n ? n : (c == EOF ? EOF : 0); }
            count++;
            continue;
        }
        fmt++;
        if (*fmt == '%') { while (isspace(c = get(src))) ; if (c != '%') { unget(c, src); return n; } continue; }
        if (*fmt == '*') { sup = 1; fmt++; }
        while (isdigit((unsigned char)*fmt)) width = width * 10 + *fmt++ - '0';
        for (;; fmt++) {
            if (*fmt == 'l') lng++;
            else if (*fmt == 'h') hh++;
            else if (*fmt == 'z' || *fmt == 'j' || *fmt == 't' || *fmt == 'L' || *fmt == 'q') lng = 2;
            else break;
        }
        if (!width) width = 1 << 30;
        if (*fmt != 'c' && *fmt != '[' && *fmt != 'n') { while (isspace(c = get(src))) ; unget(c, src); }
        if (*fmt == 'n') { if (!sup) *va_arg(ap, int *) = count; continue; }
        {
            char tok[512];
            int len = 0;
            switch (*fmt) {
            case 'd': case 'i': case 'u': case 'x': case 'X': case 'o': case 'p': {
                int base = *fmt == 'd' || *fmt == 'u' ? 10 : *fmt == 'o' ? 8 : *fmt == 'i' ? 0 : 16;
                int neg = 0;
                unsigned long long v = 0;
                int digits = 0;
                c = get(src);
                if (c == '-' || c == '+') { neg = c == '-'; width--; c = get(src); }
                if (width > 0 && c == '0' && (base == 0 || base == 16)) {
                    int c2;
                    count++; width--;
                    c2 = get(src);
                    if ((c2 == 'x' || c2 == 'X') && width > 0) { base = 16; width--; count++; c = get(src); }
                    else { unget(c2, src); if (base == 0) base = 8; digits = 1; c = '0'; if (c2 != 'x') { c = get(src); unget(c, src); c = c2; (void)c; c = get(src); } }
                    if (digits) { c = c2; }
                }
                if (base == 0) base = 10;
                while (width > 0) {
                    int d = c >= '0' && c <= '9' ? c - '0' : c >= 'a' && c <= 'f' ? c - 'a' + 10 : c >= 'A' && c <= 'F' ? c - 'A' + 10 : 99;
                    if (d >= base) break;
                    v = v * base + d; digits = 1; width--; count++;
                    c = get(src);
                }
                unget(c, src);
                if (!digits) return n ? n : (c == EOF ? EOF : 0);
                if (neg) v = -v;
                if (!sup) {
                    if (*fmt == 'd' || *fmt == 'i') {
                        if (lng >= 2) *va_arg(ap, long long *) = v; else if (lng == 1) *va_arg(ap, long *) = v; else if (hh == 1) *va_arg(ap, short *) = v; else if (hh > 1) *va_arg(ap, signed char *) = v; else *va_arg(ap, int *) = v;
                    } else if (*fmt == 'p') *va_arg(ap, void **) = (void *)(unsigned long)v;
                    else if (lng >= 2) *va_arg(ap, unsigned long long *) = v; else if (lng == 1) *va_arg(ap, unsigned long *) = v; else if (hh == 1) *va_arg(ap, unsigned short *) = v; else if (hh > 1) *va_arg(ap, unsigned char *) = v; else *va_arg(ap, unsigned *) = v;
                    n++;
                }
                break;
            }
            case 'f': case 'e': case 'g': case 'E': case 'G': case 'a': {
                char *end;
                double v;
                c = get(src);
                while (len < 500 && width > 0 && (isdigit(c) || c == '.' || c == '-' || c == '+' || c == 'e' || c == 'E' || c == 'x' || c == 'X' || c == 'n' || c == 'a' || c == 'i' || c == 'f' || c == 'N' || c == 'A' || c == 'I' || c == 'p' || (c >= 'b' && c <= 'd'))) {
                    tok[len++] = c; width--; c = get(src);
                }
                unget(c, src);
                tok[len] = 0;
                v = strtod(tok, &end);
                if (end == tok) return n ? n : (c == EOF ? EOF : 0);
                count += len;
                if (!sup) { if (lng) *va_arg(ap, double *) = v; else *va_arg(ap, float *) = v; n++; }
                break;
            }
            case 's': {
                char *d = sup ? NULL : va_arg(ap, char *);
                c = get(src);
                while (c != EOF && !isspace(c) && width > 0) { if (d) d[len] = c; len++; width--; c = get(src); }
                unget(c, src);
                if (!len) return n ? n : EOF;
                if (d) { d[len] = 0; n++; }
                count += len;
                break;
            }
            case 'c': {
                char *d = sup ? NULL : va_arg(ap, char *);
                if (width == 1 << 30) width = 1;
                while (width-- > 0) { c = get(src); if (c == EOF) return n ? n : EOF; if (d) d[len] = c; len++; }
                if (d) n++;
                count += len;
                break;
            }
            case '[': {
                char set[256];
                int neg = 0, i;
                char *d = sup ? NULL : va_arg(ap, char *);
                memset(set, 0, sizeof set);
                fmt++;
                if (*fmt == '^') { neg = 1; fmt++; }
                if (*fmt == ']') { set[']'] = 1; fmt++; }
                while (*fmt && *fmt != ']') {
                    if (fmt[1] == '-' && fmt[2] && fmt[2] != ']') { for (i = (unsigned char)fmt[0]; i <= (unsigned char)fmt[2]; i++) set[i] = 1; fmt += 3; }
                    else set[(unsigned char)*fmt++] = 1;
                }
                c = get(src);
                while (c != EOF && width > 0 && set[c] != neg) { if (d) d[len] = c; len++; width--; c = get(src); }
                unget(c, src);
                if (!len) return n ? n : (c == EOF ? EOF : 0);
                if (d) { d[len] = 0; n++; }
                count += len;
                break;
            }
            default: return n;
            }
            (void)ok;
        }
    }
    return n;
}
#endif
#ifndef C_DECLS_ONLY
static int c_sget(void *p) { const char **s = p; int c = (unsigned char)**s; if (!c) return EOF; (*s)++; return c; }
#endif
#ifndef C_DECLS_ONLY
static void c_sunget(int c, void *p) { const char **s = p; if (c != EOF) (*s)--; }
#endif
#ifndef C_DECLS_ONLY
static int c_fget(void *p) { return fgetc(p); }
#endif
#ifndef C_DECLS_ONLY
static void c_funget(int c, void *p) { if (c != EOF) ungetc(c, p); }
#endif
int vsscanf(const char *s, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{ return c_scan(c_sget, c_sunget, &s, fmt, ap); }
#endif
int sscanf(const char *s, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; int n; va_start(ap, fmt); n = vsscanf(s, fmt, ap); va_end(ap); return n; }
#endif
int vfscanf(FILE *f, const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{ return c_scan(c_fget, c_funget, f, fmt, ap); }
#endif
int fscanf(FILE *f, const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; int n; va_start(ap, fmt); n = vfscanf(f, fmt, ap); va_end(ap); return n; }
#endif
int scanf(const char *fmt, ...)
#ifdef C_DECLS_ONLY
;
#else
{ va_list ap; int n; va_start(ap, fmt); n = vfscanf(stdin, fmt, ap); va_end(ap); return n; }
#endif
int vscanf(const char *fmt, va_list ap)
#ifdef C_DECLS_ONLY
;
#else
{ return vfscanf(stdin, fmt, ap); }
#endif

/* locale: there is only the C one */
#define LC_CTYPE 0
#define LC_NUMERIC 1
#define LC_TIME 2
#define LC_COLLATE 3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_ALL 6
struct lconv { char *decimal_point, *thousands_sep, *grouping, *int_curr_symbol, *currency_symbol, *mon_decimal_point, *mon_thousands_sep, *mon_grouping, *positive_sign, *negative_sign;
    char int_frac_digits, frac_digits, p_cs_precedes, p_sep_by_space, n_cs_precedes, n_sep_by_space, p_sign_posn, n_sign_posn; };
char *setlocale(int cat, const char *name)
#ifdef C_DECLS_ONLY
;
#else
{ (void)cat; if (!name || !*name || !strcmp(name, "C") || !strcmp(name, "POSIX") || !strcmp(name, "C.UTF-8")) return "C"; return NULL; }
#endif
struct lconv *localeconv(void)
#ifdef C_DECLS_ONLY
;
#else
{
    static struct lconv l = { ".", "", "", "", "", "", "", "", "", "", 127, 127, 127, 127, 127, 127, 127, 127 };
    return &l;
}
#endif
typedef void *locale_t;
locale_t newlocale(int mask, const char *name, locale_t base)
#ifdef C_DECLS_ONLY
;
#else
{ (void)mask; (void)name; (void)base; return (locale_t)1; }
#endif
void freelocale(locale_t l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; }
#endif
locale_t uselocale(locale_t l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return (locale_t)1; }
#endif
#define LC_GLOBAL_LOCALE ((locale_t)-1)
#define CODESET 14
#define D_T_FMT 0x20028
#define RADIXCHAR 0x10000
char *nl_langinfo(int item)
#ifdef C_DECLS_ONLY
;
#else
{ return item == CODESET ? "ANSI_X3.4-1968" : item == RADIXCHAR ? "." : ""; }
#endif
char *gettext(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ return (char *)s; }
#endif
char *dgettext(const char *d, const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ (void)d; return (char *)s; }
#endif
char *ngettext(const char *a, const char *b, unsigned long n)
#ifdef C_DECLS_ONLY
;
#else
{ return (char *)(n == 1 ? a : b); }
#endif
char *textdomain(const char *d)
#ifdef C_DECLS_ONLY
;
#else
{ return (char *)d; }
#endif
char *bindtextdomain(const char *d, const char *dir)
#ifdef C_DECLS_ONLY
;
#else
{ (void)d; return (char *)dir; }
#endif
#define _(s) (s)
int isalpha_l(int c, locale_t l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return isalpha(c); }
#endif
int strcoll_l(const char *a, const char *b, locale_t l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return strcmp(a, b); }
#endif
int strcasecmp_l(const char *a, const char *b, locale_t l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return strcasecmp(a, b); }
#endif

typedef int wchar_t;
typedef int wint_t;
typedef int wctype_t;
typedef struct { int c_; } mbstate_t;
#define WEOF (-1)
#define MB_LEN_MAX 4
#define MB_CUR_MAX 1
int mbtowc(wchar_t *w, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ if (!s) return 0; if (!n) return -1; if (w) *w = (unsigned char)*s; return *s ? 1 : 0; }
#endif
int wctomb(char *s, wchar_t w)
#ifdef C_DECLS_ONLY
;
#else
{ if (!s) return 0; *s = w; return 1; }
#endif
size_t mbrtowc(wchar_t *w, const char *s, size_t n, mbstate_t *st)
#ifdef C_DECLS_ONLY
;
#else
{ (void)st; if (!s) return 0; if (!n) return (size_t)-2; if (w) *w = (unsigned char)*s; return *s ? 1 : 0; }
#endif
size_t wcrtomb(char *s, wchar_t w, mbstate_t *st)
#ifdef C_DECLS_ONLY
;
#else
{ (void)st; if (!s) return 1; *s = w; return 1; }
#endif
size_t mbstowcs(wchar_t *d, const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t i = 0; while (s[i] && (!d || i < n)) { if (d) d[i] = (unsigned char)s[i]; i++; } if (d && i < n) d[i] = 0; return i; }
#endif
size_t wcstombs(char *d, const wchar_t *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t i = 0; while (s[i] && (!d || i < n)) { if (d) d[i] = s[i]; i++; } if (d && i < n) d[i] = 0; return i; }
#endif
size_t mbrlen(const char *s, size_t n, mbstate_t *st)
#ifdef C_DECLS_ONLY
;
#else
{ return mbrtowc(NULL, s, n, st); }
#endif
int mbsinit(const mbstate_t *st)
#ifdef C_DECLS_ONLY
;
#else
{ (void)st; return 1; }
#endif
int mblen(const char *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return mbtowc(NULL, s, n); }
#endif
size_t wcslen(const wchar_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ size_t n = 0; while (s[n]) n++; return n; }
#endif
int wcscmp(const wchar_t *a, const wchar_t *b)
#ifdef C_DECLS_ONLY
;
#else
{ while (*a && *a == *b) { a++; b++; } return *a - *b; }
#endif
wchar_t *wcscpy(wchar_t *d, const wchar_t *s)
#ifdef C_DECLS_ONLY
;
#else
{ wchar_t *r = d; while ((*d++ = *s++)) ; return r; }
#endif
wchar_t *wmemcpy(wchar_t *d, const wchar_t *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ return memcpy(d, s, n * sizeof *d); }
#endif
wchar_t *wmemset(wchar_t *d, wchar_t c, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ size_t i; for (i = 0; i < n; i++) d[i] = c; return d; }
#endif
int iswalpha(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return isalpha(c); }
#endif
int iswdigit(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return isdigit(c); }
#endif
int iswspace(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return isspace(c); }
#endif
int iswupper(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return isupper(c); }
#endif
int iswlower(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return islower(c); }
#endif
int iswalnum(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return isalnum(c); }
#endif
int iswprint(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return c >= 32 && c < 127; }
#endif
int iswpunct(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return ispunct(c); }
#endif
int iswcntrl(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return iscntrl(c); }
#endif
wint_t towlower(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return tolower(c); }
#endif
wint_t towupper(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return toupper(c); }
#endif
int wcwidth(wchar_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return c == 0 ? 0 : c < 32 || (c >= 127 && c < 160) ? -1 : 1; }
#endif
int wcswidth(const wchar_t *s, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{ int w = 0; while (n-- && *s) { int c = wcwidth(*s++); if (c < 0) return -1; w += c; } return w; }
#endif
wint_t btowc(int c)
#ifdef C_DECLS_ONLY
;
#else
{ return c; }
#endif
int wctob(wint_t c)
#ifdef C_DECLS_ONLY
;
#else
{ return c < 256 ? c : EOF; }
#endif

/* threads: one of them. a mutex always locks, a thread is run to the end when it's made */
typedef unsigned long pthread_t;
typedef struct { int k; } pthread_mutex_t, pthread_mutexattr_t, pthread_cond_t, pthread_condattr_t, pthread_rwlock_t, pthread_attr_t, pthread_rwlockattr_t, pthread_spinlock_t_;
typedef struct { int done; } pthread_once_t;
typedef unsigned pthread_key_t;
#define PTHREAD_MUTEX_INITIALIZER { 0 }
#define PTHREAD_COND_INITIALIZER { 0 }
#define PTHREAD_RWLOCK_INITIALIZER { 0 }
#define PTHREAD_ONCE_INIT { 0 }
#define PTHREAD_MUTEX_RECURSIVE 1
#define PTHREAD_MUTEX_NORMAL 0
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_CREATE_DETACHED 1
#define PTHREAD_CREATE_JOINABLE 0
int pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)m; (void)a; return 0; }
#endif
int pthread_mutex_lock(pthread_mutex_t *m)
#ifdef C_DECLS_ONLY
;
#else
{ (void)m; return 0; }
#endif
int pthread_mutex_trylock(pthread_mutex_t *m)
#ifdef C_DECLS_ONLY
;
#else
{ (void)m; return 0; }
#endif
int pthread_mutex_unlock(pthread_mutex_t *m)
#ifdef C_DECLS_ONLY
;
#else
{ (void)m; return 0; }
#endif
int pthread_mutex_destroy(pthread_mutex_t *m)
#ifdef C_DECLS_ONLY
;
#else
{ (void)m; return 0; }
#endif
int pthread_mutexattr_init(pthread_mutexattr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; return 0; }
#endif
int pthread_mutexattr_settype(pthread_mutexattr_t *a, int t)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)t; return 0; }
#endif
int pthread_mutexattr_destroy(pthread_mutexattr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; return 0; }
#endif
int pthread_cond_init(pthread_cond_t *c, const pthread_condattr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)c; (void)a; return 0; }
#endif
int pthread_cond_signal(pthread_cond_t *c)
#ifdef C_DECLS_ONLY
;
#else
{ (void)c; return 0; }
#endif
int pthread_cond_broadcast(pthread_cond_t *c)
#ifdef C_DECLS_ONLY
;
#else
{ (void)c; return 0; }
#endif
int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m)
#ifdef C_DECLS_ONLY
;
#else
{ (void)c; (void)m; return 0; }
#endif
int pthread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, const struct timespec *t)
#ifdef C_DECLS_ONLY
;
#else
{ (void)c; (void)m; (void)t; return ETIMEDOUT; }
#endif
int pthread_cond_destroy(pthread_cond_t *c)
#ifdef C_DECLS_ONLY
;
#else
{ (void)c; return 0; }
#endif
int pthread_rwlock_init(pthread_rwlock_t *l, const pthread_rwlockattr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; (void)a; return 0; }
#endif
int pthread_rwlock_rdlock(pthread_rwlock_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return 0; }
#endif
int pthread_rwlock_wrlock(pthread_rwlock_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return 0; }
#endif
int pthread_rwlock_unlock(pthread_rwlock_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return 0; }
#endif
int pthread_rwlock_destroy(pthread_rwlock_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ (void)l; return 0; }
#endif
int pthread_once(pthread_once_t *o, void (*f)(void))
#ifdef C_DECLS_ONLY
;
#else
{ if (!o->done) { o->done = 1; f(); } return 0; }
#endif
pthread_t pthread_self(void)
#ifdef C_DECLS_ONLY
;
#else
{ return 1; }
#endif
int pthread_equal(pthread_t a, pthread_t b)
#ifdef C_DECLS_ONLY
;
#else
{ return a == b; }
#endif
#ifndef C_DECLS_ONLY
static void *c_tls[64];
#endif
#ifndef C_DECLS_ONLY
static int c_tls_n;
#endif
int pthread_key_create(pthread_key_t *k, void (*d)(void *))
#ifdef C_DECLS_ONLY
;
#else
{ (void)d; if (c_tls_n == 64) return EAGAIN; *k = c_tls_n++; return 0; }
#endif
int pthread_key_delete(pthread_key_t k)
#ifdef C_DECLS_ONLY
;
#else
{ (void)k; return 0; }
#endif
void *pthread_getspecific(pthread_key_t k)
#ifdef C_DECLS_ONLY
;
#else
{ return k < 64 ? c_tls[k] : NULL; }
#endif
int pthread_setspecific(pthread_key_t k, const void *v)
#ifdef C_DECLS_ONLY
;
#else
{ if (k >= 64) return EINVAL; c_tls[k] = (void *)v; return 0; }
#endif
int pthread_attr_init(pthread_attr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; return 0; }
#endif
int pthread_attr_destroy(pthread_attr_t *a)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; return 0; }
#endif
int pthread_attr_setdetachstate(pthread_attr_t *a, int s)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)s; return 0; }
#endif
int pthread_attr_setstacksize(pthread_attr_t *a, size_t s)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)s; return 0; }
#endif
int pthread_create(pthread_t *t, const pthread_attr_t *a, void *(*fn)(void *), void *arg)
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)fn; (void)arg; (void)t; return EAGAIN; }
#endif
int pthread_join(pthread_t t, void **r)
#ifdef C_DECLS_ONLY
;
#else
{ (void)t; (void)r; return ESRCH; }
#endif
int pthread_detach(pthread_t t)
#ifdef C_DECLS_ONLY
;
#else
{ (void)t; return 0; }
#endif
int pthread_atfork(void (*a)(void), void (*b)(void), void (*c)(void))
#ifdef C_DECLS_ONLY
;
#else
{ (void)a; (void)b; (void)c; return 0; }
#endif
int pthread_setcancelstate(int s, int *o)
#ifdef C_DECLS_ONLY
;
#else
{ (void)s; if (o) *o = 0; return 0; }
#endif
int pthread_kill(pthread_t t, int sig)
#ifdef C_DECLS_ONLY
;
#else
{ (void)t; return raise(sig); }
#endif
int sched_yield(void)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys0(SYS_sched_yield)); }
#endif

/* dlopen: static binaries have nothing to open */
#define RTLD_LAZY 1
#define RTLD_NOW 2
#define RTLD_GLOBAL 0x100
#define RTLD_LOCAL 0
#define RTLD_DEFAULT ((void *)0)
void *dlopen(const char *f, int flags)
#ifdef C_DECLS_ONLY
;
#else
{ (void)f; (void)flags; return NULL; }
#endif
void *dlsym(void *h, const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ (void)h; (void)s; return NULL; }
#endif
int dlclose(void *h)
#ifdef C_DECLS_ONLY
;
#else
{ (void)h; return 0; }
#endif
char *dlerror(void)
#ifdef C_DECLS_ONLY
;
#else
{ return "dynamic loading is not available"; }
#endif

void endpwent(void)
#ifdef C_DECLS_ONLY
;
#else
{ }
#endif
void endgrent(void)
#ifdef C_DECLS_ONLY
;
#else
{ }
#endif
/* ---- sockets, poll, select, name lookup [chamesle] ---- */
#define AF_UNSPEC 0
#define AF_UNIX 1
#define AF_LOCAL 1
#define AF_INET 2
#define AF_INET6 10
#define PF_UNSPEC 0
#define PF_UNIX 1
#define PF_INET 2
#define PF_INET6 10
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3
#define SOCK_NONBLOCK 04000
#define SOCK_CLOEXEC 02000000
#define SOL_SOCKET 1
#define SO_DEBUG 1
#define SO_REUSEADDR 2
#define SO_TYPE 3
#define SO_ERROR 4
#define SO_BROADCAST 6
#define SO_SNDBUF 7
#define SO_RCVBUF 8
#define SO_KEEPALIVE 9
#define SO_LINGER 13
#define SO_REUSEPORT 15
#define SO_RCVTIMEO 20
#define SO_SNDTIMEO 21
#define SOMAXCONN 4096
#define MSG_PEEK 2
#define MSG_DONTWAIT 0x40
#define MSG_NOSIGNAL 0x4000
#define MSG_WAITALL 0x100
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#define IPPROTO_IP 0
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
#define IPPROTO_IPV6 41
#define TCP_NODELAY 1
#define IPV6_V6ONLY 26
#define INADDR_ANY ((in_addr_t)0)
#define INADDR_LOOPBACK ((in_addr_t)0x7f000001)
#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46
typedef unsigned socklen_t;
typedef unsigned short sa_family_t;
typedef unsigned short in_port_t;
typedef unsigned in_addr_t;
struct sockaddr { sa_family_t sa_family; char sa_data[14]; };
struct sockaddr_storage { sa_family_t ss_family; char pad[126]; unsigned long align; };
struct in_addr { in_addr_t s_addr; };
struct in6_addr { unsigned char s6_addr[16]; };
struct sockaddr_in { sa_family_t sin_family; in_port_t sin_port; struct in_addr sin_addr; unsigned char sin_zero[8]; };
struct sockaddr_in6 { sa_family_t sin6_family; in_port_t sin6_port; unsigned sin6_flowinfo; struct in6_addr sin6_addr; unsigned sin6_scope_id; };
struct sockaddr_un { sa_family_t sun_family; char sun_path[108]; };
struct linger { int l_onoff, l_linger; };
struct msghdr { void *msg_name; socklen_t msg_namelen; struct iovec *msg_iov; size_t msg_iovlen; void *msg_control; size_t msg_controllen; int msg_flags; };
#ifndef C_DECLS_ONLY
static const struct in6_addr in6addr_any = { { 0 } };
#endif
#ifndef C_DECLS_ONLY
static const struct in6_addr in6addr_loopback = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 } };
#endif
#define IN6ADDR_ANY_INIT { { 0 } }
unsigned short htons(unsigned short x)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_bswap16(x); }
#endif
unsigned short ntohs(unsigned short x)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_bswap16(x); }
#endif
unsigned htonl(unsigned x)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_bswap32(x); }
#endif
unsigned ntohl(unsigned x)
#ifdef C_DECLS_ONLY
;
#else
{ return __builtin_bswap32(x); }
#endif
int socket(int d, int t, int p)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_socket, d, t, p)); }
#endif
int socketpair(int d, int t, int p, int sv[2])
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_socketpair, d, t, p, sv)); }
#endif
int bind(int fd, const struct sockaddr *a, socklen_t l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_bind, fd, a, l)); }
#endif
int listen(int fd, int n)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_listen, fd, n)); }
#endif
int accept(int fd, struct sockaddr *a, socklen_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_accept, fd, a, l)); }
#endif
int accept4(int fd, struct sockaddr *a, socklen_t *l, int fl)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(SYS_accept4, fd, a, l, fl)); }
#endif
int connect(int fd, const struct sockaddr *a, socklen_t l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_connect, fd, a, l)); }
#endif
int shutdown(int fd, int how)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys2(SYS_shutdown, fd, how)); }
#endif
int getsockname(int fd, struct sockaddr *a, socklen_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_getsockname, fd, a, l)); }
#endif
int getpeername(int fd, struct sockaddr *a, socklen_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_getpeername, fd, a, l)); }
#endif
int setsockopt(int fd, int lv, int n, const void *v, socklen_t l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys5(SYS_setsockopt, fd, lv, n, v, l)); }
#endif
int getsockopt(int fd, int lv, int n, void *v, socklen_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys5(SYS_getsockopt, fd, lv, n, v, l)); }
#endif
ssize_t send(int fd, const void *b, size_t n, int fl)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_sendto, fd, (long)b, n, fl, 0, 0)); }
#endif
ssize_t recv(int fd, void *b, size_t n, int fl)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_recvfrom, fd, (long)b, n, fl, 0, 0)); }
#endif
ssize_t sendto(int fd, const void *b, size_t n, int fl, const struct sockaddr *a, socklen_t l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_sendto, fd, (long)b, n, fl, (long)a, l)); }
#endif
ssize_t recvfrom(int fd, void *b, size_t n, int fl, struct sockaddr *a, socklen_t *l)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(SYS_recvfrom, fd, (long)b, n, fl, (long)a, (long)l)); }
#endif
ssize_t sendmsg(int fd, const struct msghdr *m, int fl)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_sendmsg, fd, m, fl)); }
#endif
ssize_t recvmsg(int fd, struct msghdr *m, int fl)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys3(SYS_recvmsg, fd, m, fl)); }
#endif

struct pollfd { int fd; short events, revents; };
#define POLLIN 1
#define POLLPRI 2
#define POLLOUT 4
#define POLLERR 8
#define POLLHUP 16
#define POLLNVAL 32
typedef unsigned long nfds_t;
int poll(struct pollfd *f, nfds_t n, int ms)
#ifdef C_DECLS_ONLY
;
#else
{
    struct timespec t, *tp = NULL;
    if (ms >= 0) { t.tv_sec = ms / 1000; t.tv_nsec = (ms % 1000) * 1000000L; tp = &t; }
    return fail(sys5(SYS_ppoll, f, n, tp, 0, 8));
}
#endif
int ppoll(struct pollfd *f, nfds_t n, const struct timespec *t, const sigset_t *m)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys5(SYS_ppoll, f, n, t, m, 8)); }
#endif
#define FD_SETSIZE 1024
#define C_FDBITS (8 * (int)sizeof(long))
typedef struct { unsigned long fds_bits[FD_SETSIZE / C_FDBITS]; } fd_set;
#define FD_ZERO(s) memset((s), 0, sizeof(fd_set))
#define FD_SET(fd, s) ((s)->fds_bits[(fd) / C_FDBITS] |= 1UL << ((fd) % C_FDBITS))
#define FD_CLR(fd, s) ((s)->fds_bits[(fd) / C_FDBITS] &= ~(1UL << ((fd) % C_FDBITS)))
#define FD_ISSET(fd, s) (((s)->fds_bits[(fd) / C_FDBITS] >> ((fd) % C_FDBITS)) & 1)
int select(int n, fd_set *r, fd_set *w, fd_set *e, struct timeval *tv)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys5(SYS_select, n, r, w, e, tv)); }
#endif
int pselect(int n, fd_set *r, fd_set *w, fd_set *e, const struct timespec *t, const sigset_t *m)
#ifdef C_DECLS_ONLY
;
#else
{
    struct timeval tv, *tp = NULL;
    if (t) { tv.tv_sec = t->tv_sec; tv.tv_usec = t->tv_nsec / 1000; tp = &tv; }
    (void)m;
    return select(n, r, w, e, tp);
}
#endif

#define EPOLLIN 1
#define EPOLLOUT 4
#define EPOLLERR 8
#define EPOLLHUP 16
#define EPOLLET (1u << 31)
#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3
#define EPOLL_CLOEXEC 02000000
struct epoll_event { unsigned events; union { void *ptr; int fd; unsigned u32; unsigned long u64; } data; } __attribute__((packed));
int epoll_create1(int fl)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys1(291, fl)); }
#endif
int epoll_create(int n)
#ifdef C_DECLS_ONLY
;
#else
{ (void)n; return epoll_create1(0); }
#endif
int epoll_ctl(int ep, int op, int fd, struct epoll_event *ev)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys4(233, ep, op, fd, ev)); }
#endif
int epoll_wait(int ep, struct epoll_event *ev, int max, int ms)
#ifdef C_DECLS_ONLY
;
#else
{ return fail(sys6(232, ep, (long)ev, max, ms, 0, 0)); }
#endif

int inet_aton(const char *s, struct in_addr *a)
#ifdef C_DECLS_ONLY
;
#else
{
    unsigned v = 0;
    int i;
    for (i = 0; i < 4; i++) {
        char *e;
        unsigned long p = strtoul(s, &e, 10);
        if (e == s || p > 255) return 0;
        v = v << 8 | p;
        if (i < 3) { if (*e != '.') return 0; s = e + 1; } else if (*e) return 0;
    }
    a->s_addr = htonl(v);
    return 1;
}
#endif
in_addr_t inet_addr(const char *s)
#ifdef C_DECLS_ONLY
;
#else
{ struct in_addr a; return inet_aton(s, &a) ? a.s_addr : (in_addr_t)-1; }
#endif
char *inet_ntoa(struct in_addr a)
#ifdef C_DECLS_ONLY
;
#else
{ static char b[16]; unsigned char *p = (unsigned char *)&a; sprintf(b, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]); return b; }
#endif
#ifndef C_DECLS_ONLY
static int c_pton6(const char *s, unsigned char *d)
{
    unsigned short w[8] = { 0 };
    int n = 0, gap = -1;
    if (s[0] == ':' && s[1] == ':') { gap = 0; s += 2; if (!*s) goto done; }
    for (;;) {
        char *e;
        unsigned long v = strtoul(s, &e, 16);
        if (e == s || e - s > 4 || n >= 8) return 0;
        w[n++] = v;
        s = e;
        if (!*s) break;
        if (*s != ':') return 0;
        s++;
        if (*s == ':') { if (gap >= 0) return 0; gap = n; s++; if (!*s) break; }
    }
done:
    if (gap < 0 && n != 8) return 0;
    if (gap >= 0) { int k = 8 - n; memmove(w + gap + k, w + gap, (n - gap) * 2); memset(w + gap, 0, k * 2); }
    for (n = 0; n < 8; n++) { d[2 * n] = w[n] >> 8; d[2 * n + 1] = w[n]; }
    return 1;
}
#endif
int inet_pton(int af, const char *s, void *d)
#ifdef C_DECLS_ONLY
;
#else
{
    if (af == AF_INET) return inet_aton(s, d) ? 1 : 0;
    if (af == AF_INET6) return c_pton6(s, d);
    errno = EAFNOSUPPORT; return -1;
}
#endif
const char *inet_ntop(int af, const void *s, char *d, socklen_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    const unsigned char *p = s;
    char buf[48];
    if (af == AF_INET) snprintf(buf, sizeof buf, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    else if (af == AF_INET6) {
        int i, best = -1, bl = 0, cur = -1, cl = 0;
        char *o = buf;
        for (i = 0; i < 8; i++) {
            if (!p[2 * i] && !p[2 * i + 1]) { if (cur < 0) { cur = i; cl = 0; } if (++cl > bl) { bl = cl; best = cur; } } else cur = -1;
        }
        if (bl < 2) best = -1;
        for (i = 0; i < 8; i++) {
            if (i == best) { *o++ = ':'; i += bl - 1; if (i == 7) *o++ = ':'; continue; }
            if (i) *o++ = ':';
            o += sprintf(o, "%x", p[2 * i] << 8 | p[2 * i + 1]);
        }
        *o = 0;
    } else { errno = EAFNOSUPPORT; return NULL; }
    if (strlen(buf) >= n) { errno = ENOSPC; return NULL; }
    strcpy(d, buf);
    return d;
}
#endif

/* names: /etc/hosts, then a plain UDP query to the first nameserver in /etc/resolv.conf */
struct hostent { char *h_name, **h_aliases; int h_addrtype, h_length; char **h_addr_list; };
#define h_addr h_addr_list[0]
struct addrinfo { int ai_flags, ai_family, ai_socktype, ai_protocol; socklen_t ai_addrlen; struct sockaddr *ai_addr; char *ai_canonname; struct addrinfo *ai_next; };
struct servent { char *s_name, **s_aliases; int s_port; char *s_proto; };
#define AI_PASSIVE 1
#define AI_CANONNAME 2
#define AI_NUMERICHOST 4
#define AI_NUMERICSERV 0x400
#define AI_ADDRCONFIG 0x20
#define AI_V4MAPPED 8
#define AI_ALL 0x10
#define NI_NUMERICHOST 1
#define NI_NUMERICSERV 2
#define NI_NAMEREQD 8
#define NI_DGRAM 16
#define NI_MAXHOST 1025
#define NI_MAXSERV 32
#define EAI_BADFLAGS (-1)
#define EAI_NONAME (-2)
#define EAI_AGAIN (-3)
#define EAI_FAIL (-4)
#define EAI_FAMILY (-6)
#define EAI_SOCKTYPE (-7)
#define EAI_SERVICE (-8)
#define EAI_MEMORY (-10)
#define EAI_SYSTEM (-11)
#define HOST_NOT_FOUND 1
#ifdef C_DECLS_ONLY
extern int h_errno;
#else
int h_errno;
#endif
#ifndef C_DECLS_ONLY
static int c_hosts(const char *name, int fam, unsigned char *out, int *outfam)
{
    char line[512];
    FILE *f = fopen("/etc/hosts", "r");
    if (!f) return 0;
    while (fgets(line, sizeof line, f)) {
        char *p = line, *tok, *save;
        unsigned char a[16];
        int af;
        line[strcspn(line, "#\n")] = 0;
        tok = strtok_r(p, " \t", &save);
        if (!tok) continue;
        af = inet_pton(AF_INET, tok, a) == 1 ? AF_INET : inet_pton(AF_INET6, tok, a) == 1 ? AF_INET6 : 0;
        if (!af || (fam != AF_UNSPEC && fam != af)) continue;
        while ((tok = strtok_r(NULL, " \t", &save))) if (!strcasecmp(tok, name)) { memcpy(out, a, 16); *outfam = af; fclose(f); return 1; }
    }
    fclose(f);
    return 0;
}
#endif
#ifndef C_DECLS_ONLY
static int c_dns(const char *name, unsigned char *out)
{
    unsigned char q[300], r[600];
    char line[256], ns[64] = "127.0.0.1";
    struct sockaddr_in sa;
    struct timeval tv = { 3, 0 };
    int fd, n = 0, i, an, pos;
    FILE *f = fopen("/etc/resolv.conf", "r");
    if (f) { while (fgets(line, sizeof line, f)) if (!strncmp(line, "nameserver", 10)) { sscanf(line + 10, "%63s", ns); break; } fclose(f); }
    memset(q, 0, 12);
    q[0] = 0x43; q[1] = 0x68; q[2] = 1; q[5] = 1;
    n = 12;
    while (*name) {
        const char *dot = strchr(name, '.');
        int l = dot ? (int)(dot - name) : (int)strlen(name);
        if (l > 63 || n + l + 6 > (int)sizeof q) return 0;
        q[n++] = l; memcpy(q + n, name, l); n += l;
        name += l; if (*name == '.') name++;
    }
    q[n++] = 0; q[n++] = 0; q[n++] = 1; q[n++] = 0; q[n++] = 1;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET; sa.sin_port = htons(53);
    if (!inet_aton(ns, &sa.sin_addr)) return 0;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) return 0;
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
    for (i = 0; i < 2; i++) {
        long len;
        sendto(fd, q, n, 0, (struct sockaddr *)&sa, sizeof sa);
        len = recv(fd, r, sizeof r, 0);
        if (len < 12 || r[0] != q[0] || r[1] != q[1]) continue;
        close(fd);
        if ((r[3] & 15) != 0) return 0;
        an = r[6] << 8 | r[7];
        pos = n;
        while (an-- > 0 && pos < len) {
            int rl, ty;
            while (pos < len && r[pos]) { if ((r[pos] & 0xc0) == 0xc0) { pos++; break; } pos += r[pos] + 1; }
            pos++;
            if (pos + 10 > len) return 0;
            ty = r[pos] << 8 | r[pos + 1]; rl = r[pos + 8] << 8 | r[pos + 9]; pos += 10;
            if (ty == 1 && rl == 4 && pos + 4 <= len) { memcpy(out, r + pos, 4); return 1; }
            pos += rl;
        }
        return 0;
    }
    close(fd);
    return 0;
}
#endif
int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
#ifdef C_DECLS_ONLY
;
#else
{
    int fam = hints ? hints->ai_family : AF_UNSPEC, socktype = hints ? hints->ai_socktype : 0, flags = hints ? hints->ai_flags : 0;
    unsigned char addr[16];
    int af = 0, port = 0;
    struct addrinfo *ai;
    struct sockaddr_in *s4;
    struct sockaddr_in6 *s6;
    char *e;
    if (!node && !service) return EAI_NONAME;
    if (service) {
        port = strtol(service, &e, 10);
        if (*e) {
            if (flags & AI_NUMERICSERV) return EAI_NONAME;
            port = !strcmp(service, "http") ? 80 : !strcmp(service, "https") ? 443 : !strcmp(service, "ftp") ? 21 : !strcmp(service, "ssh") ? 22 : !strcmp(service, "domain") ? 53 : !strcmp(service, "smtp") ? 25 : !strcmp(service, "git") ? 9418 : 0;
            if (!port) return EAI_SERVICE;
        }
    }
    if (!node) { af = fam == AF_INET6 ? AF_INET6 : AF_INET; memset(addr, 0, 16); if (!(flags & AI_PASSIVE)) { if (af == AF_INET) { addr[0] = 127; addr[3] = 1; } else addr[15] = 1; } }
    else if (inet_pton(AF_INET, node, addr) == 1) af = AF_INET;
    else if (inet_pton(AF_INET6, node, addr) == 1) af = AF_INET6;
    else if (flags & AI_NUMERICHOST) return EAI_NONAME;
    else if (!strcmp(node, "localhost")) { af = fam == AF_INET6 ? AF_INET6 : AF_INET; memset(addr, 0, 16); if (af == AF_INET) { addr[0] = 127; addr[3] = 1; } else addr[15] = 1; }
    else if (c_hosts(node, fam, addr, &af)) ;
    else if (fam != AF_INET6 && c_dns(node, addr)) af = AF_INET;
    else return EAI_NONAME;
    if (fam != AF_UNSPEC && fam != af) return EAI_FAMILY;
    ai = calloc(1, sizeof *ai + sizeof(struct sockaddr_in6) + (node ? strlen(node) + 1 : 1));
    if (!ai) return EAI_MEMORY;
    ai->ai_family = af; ai->ai_socktype = socktype ? socktype : SOCK_STREAM;
    ai->ai_protocol = ai->ai_socktype == SOCK_DGRAM ? IPPROTO_UDP : IPPROTO_TCP;
    ai->ai_addr = (struct sockaddr *)(ai + 1);
    if (af == AF_INET) { s4 = (struct sockaddr_in *)ai->ai_addr; s4->sin_family = AF_INET; s4->sin_port = htons(port); memcpy(&s4->sin_addr, addr, 4); ai->ai_addrlen = sizeof *s4; }
    else { s6 = (struct sockaddr_in6 *)ai->ai_addr; s6->sin6_family = AF_INET6; s6->sin6_port = htons(port); memcpy(&s6->sin6_addr, addr, 16); ai->ai_addrlen = sizeof *s6; }
    if ((flags & AI_CANONNAME) && node) { ai->ai_canonname = (char *)(ai + 1) + sizeof(struct sockaddr_in6); strcpy(ai->ai_canonname, node); }
    *res = ai;
    return 0;
}
#endif
void freeaddrinfo(struct addrinfo *ai)
#ifdef C_DECLS_ONLY
;
#else
{ while (ai) { struct addrinfo *n = ai->ai_next; free(ai); ai = n; } }
#endif
const char *gai_strerror(int e)
#ifdef C_DECLS_ONLY
;
#else
{ return e == EAI_NONAME ? "Name or service not known" : e == EAI_AGAIN ? "Temporary failure in name resolution" : e == EAI_FAMILY ? "Address family not supported" : e == EAI_SERVICE ? "Service not known" : e == EAI_MEMORY ? "Out of memory" : "Name resolution failed"; }
#endif
int getnameinfo(const struct sockaddr *sa, socklen_t l, char *host, socklen_t hl, char *serv, socklen_t sl, int flags)
#ifdef C_DECLS_ONLY
;
#else
{
    (void)l; (void)flags;
    if (host && hl) { if (!inet_ntop(sa->sa_family, sa->sa_family == AF_INET ? (void *)&((struct sockaddr_in *)sa)->sin_addr : (void *)&((struct sockaddr_in6 *)sa)->sin6_addr, host, hl)) return EAI_FAMILY; }
    if (serv && sl) snprintf(serv, sl, "%d", ntohs(((struct sockaddr_in *)sa)->sin_port));
    return 0;
}
#endif
struct hostent *gethostbyname(const char *name)
#ifdef C_DECLS_ONLY
;
#else
{
    static struct hostent h;
    static char *list[2], *al[1], buf[16], nm[256];
    struct addrinfo hints, *r;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    if (getaddrinfo(name, NULL, &hints, &r)) { h_errno = HOST_NOT_FOUND; return NULL; }
    memcpy(buf, &((struct sockaddr_in *)r->ai_addr)->sin_addr, 4);
    freeaddrinfo(r);
    strlcpy(nm, name, sizeof nm);
    list[0] = buf; list[1] = NULL; al[0] = NULL;
    h.h_name = nm; h.h_aliases = al; h.h_addrtype = AF_INET; h.h_length = 4; h.h_addr_list = list;
    return &h;
}
#endif
struct servent *getservbyname(const char *n, const char *p)
#ifdef C_DECLS_ONLY
;
#else
{ (void)n; (void)p; return NULL; }
#endif
const char *hstrerror(int e)
#ifdef C_DECLS_ONLY
;
#else
{ (void)e; return "Unknown host"; }
#endif
/* ---- fnmatch, glob, ftw, regex, path names [chamesle] ---- */
#define FNM_NOMATCH 1
#define FNM_PATHNAME 1
#define FNM_NOESCAPE 2
#define FNM_PERIOD 4
#define FNM_CASEFOLD 16
#ifndef C_DECLS_ONLY
static int c_fn_class(const char *name, int c)
{
    if (!strncmp(name, "alpha:", 6)) return isalpha(c);
    if (!strncmp(name, "digit:", 6)) return isdigit(c);
    if (!strncmp(name, "alnum:", 6)) return isalnum(c);
    if (!strncmp(name, "upper:", 6)) return isupper(c);
    if (!strncmp(name, "lower:", 6)) return islower(c);
    if (!strncmp(name, "space:", 6)) return isspace(c);
    if (!strncmp(name, "blank:", 6)) return c == ' ' || c == '\t';
    if (!strncmp(name, "punct:", 6)) return ispunct(c);
    if (!strncmp(name, "print:", 6)) return c >= 32 && c < 127;
    if (!strncmp(name, "graph:", 6)) return c > 32 && c < 127;
    if (!strncmp(name, "cntrl:", 6)) return iscntrl(c);
    if (!strncmp(name, "xdigit:", 7)) return isxdigit(c);
    return 0;
}
#endif
int fnmatch(const char *p, const char *s, int flags)
#ifdef C_DECLS_ONLY
;
#else
{
    const char *start = s;
    for (; *p; p++, s++) {
        int fold = flags & FNM_CASEFOLD;
        if (*p == '*') {
            while (*p == '*') p++;
            if ((flags & FNM_PERIOD) && *s == '.' && (s == start || ((flags & FNM_PATHNAME) && s[-1] == '/'))) return FNM_NOMATCH;
            if (!*p) return (flags & FNM_PATHNAME) && strchr(s, '/') ? FNM_NOMATCH : 0;
            for (;; s++) {
                if (!fnmatch(p, s, flags & ~FNM_PERIOD)) return 0;
                if (!*s || ((flags & FNM_PATHNAME) && *s == '/')) return FNM_NOMATCH;
            }
        }
        if (!*s) return FNM_NOMATCH;
        if ((flags & FNM_PERIOD) && *s == '.' && *p != '.' && (s == start || ((flags & FNM_PATHNAME) && s[-1] == '/'))) return FNM_NOMATCH;
        if (*p == '?') { if ((flags & FNM_PATHNAME) && *s == '/') return FNM_NOMATCH; continue; }
        if (*p == '[') {
            const char *q = p + 1;
            int neg = 0, ok = 0, c = (unsigned char)*s, first = 1;
            if (*q == '!' || *q == '^') { neg = 1; q++; }
            if ((flags & FNM_PATHNAME) && c == '/') return FNM_NOMATCH;
            while (*q && (*q != ']' || first)) {
                first = 0;
                if (q[0] == '[' && q[1] == ':') { const char *e = strstr(q, ":]"); if (e) { if (c_fn_class(q + 2, c)) ok = 1; q = e + 2; continue; } }
                if (*q == '\\' && !(flags & FNM_NOESCAPE) && q[1]) q++;
                if (q[1] == '-' && q[2] && q[2] != ']') {
                    int lo = (unsigned char)q[0], hi = (unsigned char)q[2];
                    if (fold) { if (tolower(c) >= tolower(lo) && tolower(c) <= tolower(hi)) ok = 1; }
                    if (c >= lo && c <= hi) ok = 1;
                    q += 3;
                } else { if (fold ? tolower(c) == tolower((unsigned char)*q) : c == (unsigned char)*q) ok = 1; q++; }
            }
            if (!*q) { if (*s != '[') return FNM_NOMATCH; continue; }
            if (ok == neg) return FNM_NOMATCH;
            p = q;
            continue;
        }
        if (*p == '\\' && !(flags & FNM_NOESCAPE) && p[1]) p++;
        if (fold ? tolower((unsigned char)*p) != tolower((unsigned char)*s) : *p != *s) return FNM_NOMATCH;
    }
    return *s ? FNM_NOMATCH : 0;
}
#endif

#define GLOB_ERR 1
#define GLOB_MARK 2
#define GLOB_NOSORT 4
#define GLOB_DOOFFS 8
#define GLOB_NOCHECK 16
#define GLOB_APPEND 32
#define GLOB_NOESCAPE 64
#define GLOB_PERIOD 128
#define GLOB_BRACE 1024
#define GLOB_TILDE 4096
#define GLOB_NOSPACE 1
#define GLOB_ABORTED 2
#define GLOB_NOMATCH 3
typedef struct { size_t gl_pathc; char **gl_pathv; size_t gl_offs; } glob_t;
#ifndef C_DECLS_ONLY
static int c_glob_add(glob_t *g, size_t *cap, const char *path)
{
    if (g->gl_pathc + g->gl_offs + 2 > *cap) {
        char **n;
        *cap = *cap * 2 + 16;
        n = realloc(g->gl_pathv, *cap * sizeof *n);
        if (!n) return -1;
        g->gl_pathv = n;
    }
    g->gl_pathv[g->gl_offs + g->gl_pathc] = strdup(path);
    if (!g->gl_pathv[g->gl_offs + g->gl_pathc]) return -1;
    g->gl_pathv[g->gl_offs + ++g->gl_pathc] = NULL;
    return 0;
}
#endif
#ifndef C_DECLS_ONLY
static int c_glob_walk(const char *dir, const char *pat, int flags, glob_t *g, size_t *cap)
{
    char seg[512];
    const char *rest;
    size_t l;
    int magic;
    DIR *d;
    struct dirent *e;
    char **names = NULL;
    size_t nn = 0, i;
    while (*pat == '/') pat++;
    if (!*pat) return c_glob_add(g, cap, dir);
    l = strcspn(pat, "/");
    if (l >= sizeof seg) return 0;
    memcpy(seg, pat, l); seg[l] = 0;
    rest = pat + l;
    magic = strpbrk(seg, "*?[") != NULL;
    if (!magic) {
        char full[4096];
        struct stat st;
        char *u = seg;
        if (!(flags & GLOB_NOESCAPE)) { char *r = seg, *w = seg; while (*r) { if (*r == '\\' && r[1]) r++; *w++ = *r++; } *w = 0; }
        snprintf(full, sizeof full, "%s%s%s", dir, !*dir || dir[strlen(dir) - 1] == '/' ? "" : "/", u);
        if (lstat(full, &st) < 0) return 0;
        if (*rest && !S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode)) return 0;
        return c_glob_walk(full, rest, flags, g, cap);
    }
    d = opendir(*dir ? dir : ".");
    if (!d) return (flags & GLOB_ERR) ? -2 : 0;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.' && seg[0] != '.' && !(flags & GLOB_PERIOD)) continue;
        if (fnmatch(seg, e->d_name, (flags & GLOB_NOESCAPE ? FNM_NOESCAPE : 0) | FNM_PERIOD * !(flags & GLOB_PERIOD))) continue;
        names = realloc(names, (nn + 1) * sizeof *names);
        names[nn++] = strdup(e->d_name);
    }
    closedir(d);
    for (i = 0; i < nn; i++) {
        char full[4096];
        struct stat st;
        snprintf(full, sizeof full, "%s%s%s", dir, !*dir || dir[strlen(dir) - 1] == '/' ? "" : "/", names[i]);
        if (*rest && (stat(full, &st) < 0 || !S_ISDIR(st.st_mode))) continue;
        if (c_glob_walk(full, rest, flags, g, cap) < 0) return -1;
    }
    for (i = 0; i < nn; i++) free(names[i]);
    free(names);
    return 0;
}
#endif
#ifndef C_DECLS_ONLY
static int c_cmp_str(const void *a, const void *b) { return strcmp(*(char *const *)a, *(char *const *)b); }
#endif
int glob(const char *pat, int flags, int (*err)(const char *, int), glob_t *g)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t cap = 0, start;
    int r;
    (void)err;
    if (!(flags & GLOB_APPEND)) { g->gl_pathc = 0; g->gl_pathv = NULL; if (!(flags & GLOB_DOOFFS)) g->gl_offs = 0; }
    else cap = g->gl_pathc + g->gl_offs + 2;
    if (!g->gl_pathv) { g->gl_pathv = calloc(g->gl_offs + 16, sizeof(char *)); cap = g->gl_offs + 16; }
    start = g->gl_pathc;
    if (flags & GLOB_BRACE) {
        const char *o = strchr(pat, '{');
        if (o) {
            const char *p = o + 1, *c = NULL;
            int depth = 1;
            for (; *p; p++) { if (*p == '{') depth++; else if (*p == '}' && !--depth) { c = p; break; } }
            if (c) {
                const char *a = o + 1, *q;
                int any = 0;
                depth = 0;
                for (q = a; q <= c; q++) {
                    if (*q == '{') depth++;
                    else if ((*q == ',' && !depth) || q == c) {
                        char *np = malloc(strlen(pat) + (q - a) + 1);
                        memcpy(np, pat, o - pat);
                        memcpy(np + (o - pat), a, q - a);
                        strcpy(np + (o - pat) + (q - a), c + 1);
                        r = glob(np, (flags & ~GLOB_NOCHECK) | GLOB_APPEND, err, g);
                        free(np);
                        if (r && r != GLOB_NOMATCH) return r;
                        if (!r) any = 1;
                        a = q + 1;
                    } else if (*q == '}') depth--;
                }
                if (!any && (flags & GLOB_NOCHECK)) { c_glob_add(g, &cap, pat); return 0; }
                return any ? 0 : GLOB_NOMATCH;
            }
        }
    }
    r = pat[0] == '/' ? c_glob_walk("/", pat, flags, g, &cap) : c_glob_walk("", pat, flags, g, &cap);
    if (r == -2) return GLOB_ABORTED;
    if (r < 0) return GLOB_NOSPACE;
    if (g->gl_pathc == start) {
        if (flags & GLOB_NOCHECK) { c_glob_add(g, &cap, pat); return 0; }
        return GLOB_NOMATCH;
    }
    if (!(flags & GLOB_NOSORT)) qsort(g->gl_pathv + g->gl_offs + start, g->gl_pathc - start, sizeof(char *), c_cmp_str);
    if (flags & GLOB_MARK) {
        size_t i;
        for (i = start; i < g->gl_pathc; i++) {
            struct stat st;
            char *s = g->gl_pathv[g->gl_offs + i];
            if (stat(s, &st) == 0 && S_ISDIR(st.st_mode) && s[strlen(s) - 1] != '/') { char *n = malloc(strlen(s) + 2); strcpy(n, s); strcat(n, "/"); free(s); g->gl_pathv[g->gl_offs + i] = n; }
        }
    }
    return 0;
}
#endif
void globfree(glob_t *g)
#ifdef C_DECLS_ONLY
;
#else
{ size_t i; for (i = 0; i < g->gl_pathc; i++) free(g->gl_pathv[g->gl_offs + i]); free(g->gl_pathv); g->gl_pathv = NULL; g->gl_pathc = 0; }
#endif

char *basename(char *path)
#ifdef C_DECLS_ONLY
;
#else
{
    char *s;
    size_t l;
    if (!path || !*path) return ".";
    l = strlen(path);
    while (l > 1 && path[l - 1] == '/') path[--l] = 0;
    if (l == 1 && *path == '/') return path;
    s = strrchr(path, '/');
    return s ? s + 1 : path;
}
#endif
char *dirname(char *path)
#ifdef C_DECLS_ONLY
;
#else
{
    size_t l;
    if (!path || !*path) return ".";
    l = strlen(path);
    while (l > 1 && path[l - 1] == '/') l--;
    while (l > 0 && path[l - 1] != '/') l--;
    if (!l) return ".";
    while (l > 1 && path[l - 1] == '/') l--;
    path[l] = 0;
    return path;
}
#endif

#define FTW_F 0
#define FTW_D 1
#define FTW_DNR 2
#define FTW_NS 3
#define FTW_SL 4
#define FTW_DP 5
#define FTW_SLN 6
#define FTW_PHYS 1
#define FTW_MOUNT 2
#define FTW_CHDIR 4
#define FTW_DEPTH 8
struct FTW { int base, level; };
#ifndef C_DECLS_ONLY
static int c_nftw_rec(char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int depth, int flags, int level, int maxfd)
{
    struct stat st;
    struct FTW ftw;
    int type, r;
    size_t l = strlen(path);
    char *b = strrchr(path, '/');
    ftw.base = b ? b - path + 1 : 0; ftw.level = level;
    if ((flags & FTW_PHYS ? lstat(path, &st) : stat(path, &st)) < 0) {
        if (!(flags & FTW_PHYS) && lstat(path, &st) == 0) return fn(path, &st, FTW_SLN, &ftw);
        return fn(path, &st, FTW_NS, &ftw);
    }
    type = S_ISDIR(st.st_mode) ? FTW_D : S_ISLNK(st.st_mode) ? FTW_SL : FTW_F;
    if (type != FTW_D) return fn(path, &st, type, &ftw);
    if (!(flags & FTW_DEPTH) && (r = fn(path, &st, FTW_D, &ftw))) return r;
    {
        DIR *d = opendir(path);
        struct dirent *e;
        if (!d) { if (flags & FTW_DEPTH) return fn(path, &st, FTW_DNR, &ftw); return fn(path, &st, FTW_DNR, &ftw); }
        while ((e = readdir(d))) {
            char *child;
            if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
            child = malloc(l + strlen(e->d_name) + 2);
            sprintf(child, "%s%s%s", path, l && path[l - 1] == '/' ? "" : "/", e->d_name);
            r = c_nftw_rec(child, fn, depth, flags, level + 1, maxfd);
            free(child);
            if (r) { closedir(d); return r; }
        }
        closedir(d);
    }
    if (flags & FTW_DEPTH) return fn(path, &st, FTW_DP, &ftw);
    return 0;
}
#endif
int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd, int flags)
#ifdef C_DECLS_ONLY
;
#else
{
    char *p = strdup(path);
    int r = c_nftw_rec(p, fn, fd, flags, 0, fd);
    free(p);
    return r;
}
#endif
#ifndef C_DECLS_ONLY
static int (*c_ftw_fn)(const char *, const struct stat *, int);
#endif
#ifndef C_DECLS_ONLY
static int c_ftw_adapt(const char *p, const struct stat *s, int t, struct FTW *f) { (void)f; return c_ftw_fn(p, s, t); }
#endif
int ftw(const char *path, int (*fn)(const char *, const struct stat *, int), int fd)
#ifdef C_DECLS_ONLY
;
#else
{ c_ftw_fn = fn; return nftw(path, c_ftw_adapt, fd, 0); }
#endif

char *get_current_dir_name(void)
#ifdef C_DECLS_ONLY
;
#else
{ return getcwd(NULL, 0); }
#endif
char *canonicalize_file_name(const char *p)
#ifdef C_DECLS_ONLY
;
#else
{ return realpath(p, NULL); }
#endif

/* regular expressions: backtracking matcher over a parsed tree. basic and extended, with the usual GNU-ish extras (\w \s \b \< \>) */
#define REG_EXTENDED 1
#define REG_ICASE 2
#define REG_NOSUB 4
#define REG_NEWLINE 8
#define REG_NOTBOL 1
#define REG_NOTEOL 2
#define REG_STARTEND 4
#define REG_NOMATCH 1
#define REG_BADPAT 2
#define REG_ECOLLATE 3
#define REG_ECTYPE 4
#define REG_EESCAPE 5
#define REG_ESUBREG 6
#define REG_EBRACK 7
#define REG_EPAREN 8
#define REG_EBRACE 9
#define REG_BADBR 10
#define REG_ERANGE 11
#define REG_ESPACE 12
#define REG_BADRPT 13
typedef long regoff_t;
typedef struct { regoff_t rm_so, rm_eo; } regmatch_t;
enum { RX_CHAR, RX_ANY, RX_SET, RX_BOL, RX_EOL, RX_WORDB, RX_NWORDB, RX_WORDS, RX_WORDE, RX_GROUP, RX_BACKREF, RX_ALT };
struct rx_node {
    int type, min, max, group, c;
    char *set;
    struct rx_node *sub, *next, *alt;
};
struct rx_inst;
typedef struct { size_t re_nsub; struct rx_inst *prog; int flags; int nregs, len; } regex_t;
struct rx_parse { const char *p; int ext, icase, ngroups, err; };
#ifndef C_DECLS_ONLY
static struct rx_node *rx_parse_alt(struct rx_parse *ps, int depth);
#endif
#ifndef C_DECLS_ONLY
static struct rx_node *rx_new(int type) { struct rx_node *n = calloc(1, sizeof *n); n->type = type; n->min = n->max = 1; return n; }
#endif
#ifndef C_DECLS_ONLY
static void rx_free(struct rx_node *n)
{
    while (n) { struct rx_node *nx = n->next; rx_free(n->sub); rx_free(n->alt); free(n->set); free(n); n = nx; }
}
#endif
#ifndef C_DECLS_ONLY
static struct rx_node *rx_parse_set(struct rx_parse *ps)
{
    struct rx_node *n = rx_new(RX_SET);
    const char *p = ps->p;
    int neg = 0, first = 1, c;
    n->set = calloc(1, 256);
    if (*p == '^') { neg = 1; p++; }
    while (*p && (*p != ']' || first)) {
        first = 0;
        if (p[0] == '[' && p[1] == ':') {
            const char *e = strstr(p + 2, ":]");
            if (e) {
                char nm[16]; size_t l = e - p - 2;
                if (l > 8) { ps->err = REG_ECTYPE; return n; }
                memcpy(nm, p + 2, l); nm[l] = ':'; nm[l + 1] = 0;
                for (c = 0; c < 256; c++) if (c_fn_class(nm, c)) n->set[c] = 1;
                p = e + 2;
                continue;
            }
        }
        c = (unsigned char)*p++;
        if (*p == '-' && p[1] && p[1] != ']') {
            int hi = (unsigned char)p[1], i;
            p += 2;
            if (hi < c) { ps->err = REG_ERANGE; return n; }
            for (i = c; i <= hi; i++) n->set[i] = 1;
        } else n->set[c] = 1;
    }
    if (*p != ']') { ps->err = REG_EBRACK; return n; }
    p++;
    if (ps->icase) for (c = 0; c < 256; c++) if (n->set[c]) { n->set[tolower(c)] = 1; n->set[toupper(c)] = 1; }
    if (neg) for (c = 0; c < 256; c++) n->set[c] = !n->set[c];
    ps->p = p;
    return n;
}
#endif
#ifndef C_DECLS_ONLY
static struct rx_node *rx_parse_atom(struct rx_parse *ps, int depth, int *bol_ok)
{
    const char *p = ps->p;
    struct rx_node *n;
    int ext = ps->ext;
    (void)bol_ok;
    if (*p == '(' && ext) {
        int g = ++ps->ngroups;
        ps->p = p + 1;
        n = rx_new(RX_GROUP); n->group = g;
        n->sub = rx_parse_alt(ps, depth + 1);
        if (*ps->p != ')') { if (!ps->err) ps->err = REG_EPAREN; return n; }
        ps->p++;
        return n;
    }
    if (*p == '\\' && !ext && p[1] == '(') {
        int g = ++ps->ngroups;
        ps->p = p + 2;
        n = rx_new(RX_GROUP); n->group = g;
        n->sub = rx_parse_alt(ps, depth + 1);
        if (ps->p[0] != '\\' || ps->p[1] != ')') { if (!ps->err) ps->err = REG_EPAREN; return n; }
        ps->p += 2;
        return n;
    }
    if (*p == '.') { ps->p++; return rx_new(RX_ANY); }
    if (*p == '[') { ps->p++; return rx_parse_set(ps); }
    if (*p == '^' && (ext || p == ps->p)) { ps->p++; return rx_new(RX_BOL); }
    if (*p == '$') { ps->p++; return rx_new(RX_EOL); }
    if (*p == '\\') {
        int c = p[1];
        ps->p += 2;
        if (!c) { ps->err = REG_EESCAPE; return rx_new(RX_CHAR); }
        if (c >= '1' && c <= '9') { n = rx_new(RX_BACKREF); n->group = c - '0'; return n; }
        if (c == 'b') return rx_new(RX_WORDB);
        if (c == 'B') return rx_new(RX_NWORDB);
        if (c == '<') return rx_new(RX_WORDS);
        if (c == '>') return rx_new(RX_WORDE);
        if (c == 'w' || c == 'W' || c == 's' || c == 'S' || c == 'd' || c == 'D') {
            int i;
            n = rx_new(RX_SET); n->set = calloc(1, 256);
            for (i = 0; i < 256; i++) {
                int in = (c == 'w' || c == 'W') ? (isalnum(i) || i == '_') : (c == 's' || c == 'S') ? isspace(i) : isdigit(i);
                n->set[i] = isupper(c) ? !in : in;
            }
            return n;
        }
        n = rx_new(RX_CHAR); n->c = c == 'n' ? '\n' : c == 't' ? '\t' : c; return n;
    }
    ps->p++;
    n = rx_new(RX_CHAR); n->c = (unsigned char)*p;
    if (*p == '*' && !ext) { /* a leading star in a basic expression is a plain one */ }
    return n;
}
#endif
#ifndef C_DECLS_ONLY
static struct rx_node *rx_parse_seq(struct rx_parse *ps, int depth)
{
    struct rx_node *head = NULL, **tail = &head;
    while (*ps->p && !ps->err) {
        const char *p = ps->p;
        struct rx_node *a;
        int ext = ps->ext;
        if (ext && (*p == '|' || (*p == ')' && depth > 0))) break;
        if (!ext && p[0] == '\\' && (p[1] == '|' || (p[1] == ')' && depth > 0))) break;
        a = rx_parse_atom(ps, depth, NULL);
        if (ps->err) { rx_free(a); break; }
        for (;;) {
            p = ps->p;
            if (*p == '*' && !(a->type == RX_BOL && !ext)) { a->min = 0; a->max = -1; ps->p++; }
            else if (ext && *p == '+') { a->min = 1; a->max = -1; ps->p++; }
            else if (ext && *p == '?') { a->min = 0; a->max = 1; ps->p++; }
            else if (!ext && p[0] == '\\' && (p[1] == '+' || p[1] == '?')) { a->min = p[1] == '+'; a->max = p[1] == '+' ? -1 : 1; ps->p += 2; }
            else if ((ext && *p == '{') || (!ext && p[0] == '\\' && p[1] == '{')) {
                char *e;
                long lo, hi;
                p += ext ? 1 : 2;
                lo = strtol(p, &e, 10);
                if (e == p) { ps->err = REG_BADBR; break; }
                hi = lo;
                if (*e == ',') { p = e + 1; if (*p == '}' || *p == '\\') { hi = -1; e = (char *)p; } else { hi = strtol(p, &e, 10); } }
                if (ext ? *e != '}' : (e[0] != '\\' || e[1] != '}')) { ps->err = REG_EBRACE; break; }
                ps->p = e + (ext ? 1 : 2);
                if (hi >= 0 && hi < lo) { ps->err = REG_BADBR; break; }
                a->min = lo; a->max = hi;
            } else break;
            if (a->type == RX_BOL || a->type == RX_EOL) break;
            {
                /* a repeat on a repeat: wrap what we have */
                if ((ext && (*ps->p == '*' || *ps->p == '+' || *ps->p == '?'))) {
                    struct rx_node *w = rx_new(RX_GROUP);
                    w->group = 0; w->sub = a; a = w;
                } else break;
            }
        }
        *tail = a; tail = &a->next;
    }
    return head;
}
#endif
#ifndef C_DECLS_ONLY
static struct rx_node *rx_parse_alt(struct rx_parse *ps, int depth)
{
    struct rx_node *left = rx_parse_seq(ps, depth), *n;
    int ext = ps->ext;
    if ((ext && *ps->p == '|') || (!ext && ps->p[0] == '\\' && ps->p[1] == '|')) {
        ps->p += ext ? 1 : 2;
        n = rx_new(RX_ALT);
        n->sub = left;
        n->alt = rx_parse_alt(ps, depth);
        return n;
    }
    return left;
}
#endif
enum { I_CHAR, I_ANY, I_SET, I_SPLIT, I_JMP, I_SAVE, I_BOL, I_EOL, I_WORDB, I_NWORDB, I_WORDS, I_WORDE, I_BACKREF, I_MARK, I_CHK, I_MATCH };
struct rx_inst { int op, x, y; char *set; };
struct rx_gen { struct rx_inst *p; int n, cap, nregs, err; int icase; };
#ifndef C_DECLS_ONLY
static int rx_emit(struct rx_gen *g, int op, int x, int y, char *set)
{
    if (g->n == g->cap) {
        struct rx_inst *np;
        if (g->cap > 200000) { g->err = REG_ESPACE; return 0; }
        g->cap = g->cap * 2 + 32;
        np = realloc(g->p, g->cap * sizeof *np);
        if (!np) { g->err = REG_ESPACE; return 0; }
        g->p = np;
    }
    g->p[g->n].op = op; g->p[g->n].x = x; g->p[g->n].y = y; g->p[g->n].set = set;
    return g->n++;
}
#endif
#ifndef C_DECLS_ONLY
static void rx_gen_list(struct rx_gen *g, struct rx_node *n);
#endif
#ifndef C_DECLS_ONLY
static void rx_gen_one(struct rx_gen *g, struct rx_node *n)
{
    switch (n->type) {
    case RX_CHAR: rx_emit(g, I_CHAR, n->c, 0, NULL); break;
    case RX_ANY: rx_emit(g, I_ANY, 0, 0, NULL); break;
    case RX_SET: rx_emit(g, I_SET, 0, 0, n->set); break;
    case RX_BOL: rx_emit(g, I_BOL, 0, 0, NULL); break;
    case RX_EOL: rx_emit(g, I_EOL, 0, 0, NULL); break;
    case RX_WORDB: rx_emit(g, I_WORDB, 0, 0, NULL); break;
    case RX_NWORDB: rx_emit(g, I_NWORDB, 0, 0, NULL); break;
    case RX_WORDS: rx_emit(g, I_WORDS, 0, 0, NULL); break;
    case RX_WORDE: rx_emit(g, I_WORDE, 0, 0, NULL); break;
    case RX_BACKREF: rx_emit(g, I_BACKREF, n->group, 0, NULL); break;
    case RX_GROUP:
        if (n->group) rx_emit(g, I_SAVE, 2 * n->group, 0, NULL);
        rx_gen_list(g, n->sub);
        if (n->group) rx_emit(g, I_SAVE, 2 * n->group + 1, 0, NULL);
        break;
    case RX_ALT: {
        int sp = rx_emit(g, I_SPLIT, 0, 0, NULL), j;
        if (g->err) return;
        g->p[sp].x = g->n;
        rx_gen_list(g, n->sub);
        j = rx_emit(g, I_JMP, 0, 0, NULL);
        if (g->err) return;
        g->p[sp].y = g->n;
        rx_gen_list(g, n->alt);
        g->p[j].x = g->n;
        break;
    }
    }
}
#endif
#ifndef C_DECLS_ONLY
static void rx_gen_rep(struct rx_gen *g, struct rx_node *n)
{
    int i, ends[256], ne = 0;
    struct rx_node one = *n;
    one.next = NULL;
    if (n->type == RX_ALT) { one.min = one.max = 1; }
    for (i = 0; i < n->min && !g->err; i++) rx_gen_one(g, &one);
    if (n->max < 0) {
        int l1 = g->n, sp = rx_emit(g, I_SPLIT, 0, 0, NULL), reg = g->nregs++;
        if (g->err) return;
        g->p[sp].x = g->n;
        rx_emit(g, I_MARK, reg, 0, NULL);
        rx_gen_one(g, &one);
        rx_emit(g, I_CHK, reg, 0, NULL);
        rx_emit(g, I_JMP, l1, 0, NULL);
        g->p[sp].y = g->n;
    } else {
        for (i = n->min; i < n->max && !g->err; i++) {
            int sp = rx_emit(g, I_SPLIT, 0, 0, NULL);
            if (g->err) return;
            g->p[sp].x = g->n;
            if (ne < 256) ends[ne++] = sp;
            rx_gen_one(g, &one);
        }
        for (i = 0; i < ne; i++) g->p[ends[i]].y = g->n;
    }
}
#endif
#ifndef C_DECLS_ONLY
static void rx_gen_list(struct rx_gen *g, struct rx_node *n)
{
    for (; n && !g->err; n = n->next) {
        if (n->min == 1 && n->max == 1) rx_gen_one(g, n); else rx_gen_rep(g, n);
    }
}
#endif
#ifndef C_DECLS_ONLY
static int rx_nopt(struct rx_node *n) { (void)n; return 0; }
#endif
int regcomp(regex_t *re, const char *pat, int flags)
#ifdef C_DECLS_ONLY
;
#else
{
    struct rx_parse ps = { pat, flags & REG_EXTENDED, flags & REG_ICASE, 0, 0 };
    struct rx_gen g = { NULL, 0, 0, 0, 0, flags & REG_ICASE };
    struct rx_node *tree;
    (void)rx_nopt;
    tree = rx_parse_alt(&ps, 0);
    if (!ps.err && *ps.p) ps.err = REG_EPAREN;
    if (ps.err) { rx_free(tree); return ps.err; }
    rx_emit(&g, I_SAVE, 0, 0, NULL);
    rx_gen_list(&g, tree);
    rx_emit(&g, I_SAVE, 1, 0, NULL);
    rx_emit(&g, I_MATCH, 0, 0, NULL);
    if (g.err) { rx_free(tree); free(g.p); return g.err; }
    /* sets are owned by the program from here on; give the tree's away without freeing them */
    {
        struct rx_inst *pi;
        for (pi = g.p; pi < g.p + g.n; pi++) if (pi->op == I_SET) { char *c = malloc(256); memcpy(c, pi->set, 256); pi->set = c; }
    }
    rx_free(tree);
    re->prog = g.p; re->len = g.n; re->nregs = g.nregs; re->re_nsub = ps.ngroups; re->flags = flags;
    return 0;
}
#endif
struct rx_m { const char *s, *end; const struct rx_inst *p; long *cap, *reg; int ncap, icase, newline, notbol, noteol; long steps; };
#ifndef C_DECLS_ONLY
static int rx_word(int c) { return isalnum(c) || c == '_'; }
#endif
#ifndef C_DECLS_ONLY
static int rx_exec(struct rx_m *m, int pc, const char *s)
{
    for (;;) {
        const struct rx_inst *i = &m->p[pc];
        if (++m->steps > 20000000) return 0;
        switch (i->op) {
        case I_CHAR: if (s < m->end && (m->icase ? tolower((unsigned char)*s) == tolower(i->x) : (unsigned char)*s == i->x)) { s++; pc++; continue; } return 0;
        case I_ANY: if (s < m->end && !(m->newline && *s == '\n')) { s++; pc++; continue; } return 0;
        case I_SET: if (s < m->end && i->set[(unsigned char)*s]) { s++; pc++; continue; } return 0;
        case I_JMP: pc = i->x; continue;
        case I_SPLIT: if (rx_exec(m, i->x, s)) return 1; pc = i->y; continue;
        case I_SAVE: {
            long old;
            if (i->x >= m->ncap) { pc++; continue; }
            old = m->cap[i->x]; m->cap[i->x] = s - m->s;
            if (rx_exec(m, pc + 1, s)) return 1;
            m->cap[i->x] = old;
            return 0;
        }
        case I_MARK: {
            long old = m->reg[i->x];
            m->reg[i->x] = s - m->s;
            if (rx_exec(m, pc + 1, s)) return 1;
            m->reg[i->x] = old;
            return 0;
        }
        case I_CHK: if (m->reg[i->x] == s - m->s) return 0; pc++; continue;
        case I_BOL: if ((s == m->s && !m->notbol) || (m->newline && s > m->s && s[-1] == '\n')) { pc++; continue; } return 0;
        case I_EOL: if ((s == m->end && !m->noteol) || (m->newline && s < m->end && *s == '\n')) { pc++; continue; } return 0;
        case I_WORDB: case I_NWORDB: case I_WORDS: case I_WORDE: {
            int a = s > m->s && rx_word((unsigned char)s[-1]), b = s < m->end && rx_word((unsigned char)*s), ok;
            ok = i->op == I_WORDB ? a != b : i->op == I_NWORDB ? a == b : i->op == I_WORDS ? !a && b : a && !b;
            if (!ok) return 0;
            pc++; continue;
        }
        case I_BACKREF: {
            long so, eo;
            if (2 * i->x + 1 >= m->ncap) return 0;
            so = m->cap[2 * i->x]; eo = m->cap[2 * i->x + 1];
            if (so < 0 || eo < 0) return 0;
            if (s + (eo - so) > m->end) return 0;
            if (m->icase ? strncasecmp(s, m->s + so, eo - so) : memcmp(s, m->s + so, eo - so)) return 0;
            s += eo - so; pc++; continue;
        }
        case I_MATCH: m->cap[1] = s - m->s; return 1;
        }
        return 0;
    }
}
#endif
int regexec(const regex_t *re, const char *str, size_t nmatch, regmatch_t pmatch[], int eflags)
#ifdef C_DECLS_ONLY
;
#else
{
    struct rx_m m;
    const char *s = str, *end = str + strlen(str);
    int ncap = 2 * (re->re_nsub + 1), i, found = 0;
    long *cap = malloc((ncap + re->nregs + 1) * sizeof *cap);
    if (!cap) return REG_ESPACE;
    if (eflags & REG_STARTEND) { s = str + pmatch[0].rm_so; end = str + pmatch[0].rm_eo; }
    m.s = str; m.end = end; m.p = re->prog; m.cap = cap; m.reg = cap + ncap; m.ncap = ncap;
    m.icase = re->flags & REG_ICASE; m.newline = re->flags & REG_NEWLINE; m.notbol = eflags & REG_NOTBOL; m.noteol = eflags & REG_NOTEOL; m.steps = 0;
    for (; s <= end; s++) {
        for (i = 0; i < ncap + re->nregs; i++) cap[i] = -1;
        if (rx_exec(&m, 0, s)) { found = 1; break; }
        if (m.steps > 20000000) break;
    }
    if (found && !(re->flags & REG_NOSUB) && pmatch) {
        size_t k;
        for (k = 0; k < nmatch; k++) {
            if ((int)(2 * k + 1) < ncap && cap[2 * k] >= 0 && cap[2 * k + 1] >= 0) { pmatch[k].rm_so = cap[2 * k]; pmatch[k].rm_eo = cap[2 * k + 1]; }
            else { pmatch[k].rm_so = -1; pmatch[k].rm_eo = -1; }
        }
    }
    free(cap);
    return found ? 0 : REG_NOMATCH;
}
#endif
size_t regerror(int code, const regex_t *re, char *buf, size_t n)
#ifdef C_DECLS_ONLY
;
#else
{
    static const char *const msg[] = { "Success", "No match", "Invalid regular expression", "Invalid collation character", "Invalid character class name", "Trailing backslash", "Invalid back reference", "Unmatched [, [^, [:, [., or [=", "Unmatched ( or \\(", "Unmatched \\{", "Invalid content of \\{\\}", "Invalid range end", "Memory exhausted", "Invalid preceding regular expression" };
    const char *m = code >= 0 && code <= REG_BADRPT ? msg[code] : "Unknown error";
    (void)re;
    if (n) strlcpy(buf, m, n);
    return strlen(m) + 1;
}
#endif
void regfree(regex_t *re)
#ifdef C_DECLS_ONLY
;
#else
{
    int i;
    if (!re->prog) return;
    for (i = 0; i < re->len; i++) if (re->prog[i].op == I_SET) free(re->prog[i].set);
    free(re->prog);
    re->prog = NULL;
}
#endif

#endif
