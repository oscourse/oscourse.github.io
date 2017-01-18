/* 
 * Author: Kartik Gopalan
 *
 * Below is a test code that I wrote which demonstrates all the three methods
 * of invoking the same system call. Note that the kernel implementation of
 * the system calls does not change. Only there are two different ways of
 * invoking the system calls -- faster-newer method (sysenter/sysexit) and
 * slower-older method (int 0x80). The syscall(...) library function
 * apparently hides the architecture dependent differences in making the system calls.
 *
 * WARNING: This is just an example: don't use it directly, but learn from
 * this example and write your own code. It most likely won't work as it is
 * with what you are doing.
 *
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/syscall.h>

// define the new syscall numbers. Standard syscalls are defined in linux/unistd.h
#define __NR_foo 325
//#define __NR_foo1 325

// user-level stubs

int foo(void)
{
        long __res;
        __asm__ volatile ("int $0x80"
                : "=a" (__res)
                : "0" (__NR_foo));
        if (__res >= 0)
                return (int) __res;
        errno = -__res;
        return -1;
}

int foo_ret;
int foo_sysenter_method(void)
{

        __asm__(
                "movl $325, %eax    \n"
                "call *%gs:0x10   \n"
                "movl %eax, foo_ret    \n"
        );

        return foo_ret;
}

#if 0
int foo1(int arg)
{
        long __res;
        __asm__ volatile ("int $0x80"
                : "=a" (__res)
                : "0" (__NR_foo1),
                  "b" ((long)(arg))
                );
        if (__res >= 0)
                return (int) __res;
        errno = -__res;
        return -1;
}
#endif

int main(void)
{
        int ret;
        int arg = 100;
        while(1) {
               // no-argument system call foo
               ret = foo();  // Method 1: Using wrapper above
               printf("0x80 ret = %d errno = %d\n", ret, errno);

               ret = syscall(__NR_foo); // Method 2: using syscall() library function from unistd.h
               printf("syscall ret = %d errno = %d\n", ret, errno);

               ret = foo_sysenter_method(); // Method 3: using sysenter/sysexit technique
               printf("sysenter ret = %d errno = %d\n", ret, errno);

#if 0
               // One-argument system call foo1
               ret = foo1(arg); // Method 1: Using wrapper above
		perror("");
               printf("ret = %d errno = %d\n", ret, errno);

               ret = syscall(__NR_foo1,arg); // Method 2: using syscall() library function from unistd.h
		perror("");
               printf("ret = %d errno = %d\n", ret, errno);
#endif

               // How about method 3?

               sleep(1);
        }

}
