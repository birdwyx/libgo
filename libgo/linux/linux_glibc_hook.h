#pragma once
#include <unistd.h>
#include <resolv.h>
#include <netdb.h>

extern "C" {

typedef int(*connect_t)(int, const struct sockaddr *, socklen_t);
extern connect_t connect_f;

typedef ssize_t(*read_t)(int, void *, size_t);
extern read_t read_f;

typedef ssize_t(*readv_t)(int, const struct iovec *, int);
extern readv_t readv_f;

typedef ssize_t(*recv_t)(int sockfd, void *buf, size_t len, int flags);
extern recv_t recv_f;

typedef ssize_t(*recvfrom_t)(int sockfd, void *buf, size_t len, int flags,
        struct sockaddr *src_addr, socklen_t *addrlen);
extern recvfrom_t recvfrom_f;

typedef ssize_t(*recvmsg_t)(int sockfd, struct msghdr *msg, int flags);
extern recvmsg_t recvmsg_f;

typedef ssize_t(*write_t)(int, const void *, size_t);
extern write_t write_f;

typedef ssize_t(*writev_t)(int, const struct iovec *, int);
extern writev_t writev_f;

typedef ssize_t(*send_t)(int sockfd, const void *buf, size_t len, int flags);
extern send_t send_f;

typedef ssize_t(*sendto_t)(int sockfd, const void *buf, size_t len, int flags,
        const struct sockaddr *dest_addr, socklen_t addrlen);
extern sendto_t sendto_f;

typedef ssize_t(*sendmsg_t)(int sockfd, const struct msghdr *msg, int flags);
extern sendmsg_t sendmsg_f;

typedef int(*poll_t)(struct pollfd *fds, nfds_t nfds, int timeout);
extern poll_t poll_f;

typedef int (*epoll_wait_t)(int epfd, struct epoll_event *events,
        int maxevents, int timeout);
extern epoll_wait_t epoll_wait_f;

typedef int(*select_t)(int nfds, fd_set *readfds, fd_set *writefds,
        fd_set *exceptfds, struct timeval *timeout);
extern select_t select_f;

typedef int(*accept_t)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
extern accept_t accept_f;

typedef unsigned int(*sleep_t)(unsigned int seconds);
extern sleep_t sleep_f;

typedef int (*usleep_t)(useconds_t usec);
extern usleep_t usleep_f;

typedef int(*nanosleep_t)(const struct timespec *req, struct timespec *rem);
extern nanosleep_t nanosleep_f;

// new-syscall
typedef int(*close_t)(int);
extern close_t close_f;

typedef int(*fcntl_t)(int __fd, int __cmd, ...);
extern fcntl_t fcntl_f;

typedef int(*ioctl_t)(int fd, unsigned long int request, ...);
extern ioctl_t ioctl_f;

typedef int (*getsockopt_t)(int sockfd, int level, int optname,
        void *optval, socklen_t *optlen);
extern getsockopt_t getsockopt_f;

typedef int (*setsockopt_t)(int sockfd, int level, int optname,
        const void *optval, socklen_t optlen);
extern setsockopt_t setsockopt_f;

typedef int(*dup_t)(int);
extern dup_t dup_f;

typedef int(*dup2_t)(int, int);
extern dup2_t dup2_f;

typedef int(*dup3_t)(int, int, int);
extern dup3_t dup3_f;

typedef int (*fclose_t)(FILE *fp);
extern fclose_t fclose_f;

// DNS by libcares
// gethostent

// gethostbyname
// gethostbyname_r
typedef int (*gethostbyname_r_t) (const char *__restrict __name,
			    struct hostent *__restrict __result_buf,
			    char *__restrict __buf, size_t __buflen,
			    struct hostent **__restrict __result,
			    int *__restrict __h_errnop);
extern gethostbyname_r_t gethostbyname_r_f;
// gethostbyname2
// gethostbyname2_r
typedef int (*gethostbyname2_r_t) (const char *name, int af,
        struct hostent *ret, char *buf, size_t buflen,
        struct hostent **result, int *h_errnop);
extern gethostbyname2_r_t gethostbyname2_r_f;
// gethostbyaddr
// gethostbyaddr_r
typedef int (*gethostbyaddr_r_t) (const void *addr, socklen_t len, int type,
        struct hostent *ret, char *buf, size_t buflen,
        struct hostent **result, int *h_errnop);
extern gethostbyaddr_r_t gethostbyaddr_r_f;

// getaddrinfo
// getaddrinfo_r
typedef int (*getaddrinfo_t) (const char *__restrict host,
                const char *__restrict service,
                const struct addrinfo *__restrict hint,
                struct addrinfo **__restrict res);
extern getaddrinfo_t getaddrinfo_f;

} //extern "C"

namespace co {
    extern void set_connect_timeout(int milliseconds);
    extern void initialize_socket_async_methods(int socketfd);

    // libgo提供的协程版epoll_wait接口
    extern int libgo_epoll_wait(int epfd, struct epoll_event *events,
            int maxevents, int timeout);

    // 设置ET模式
    extern void set_et_mode(int fd);

    // 重置可读/写事件状态
    // * 绕过hook机制直接使用底层系统调用时, 可能会导致记录的可读/写事件不准确,
    // * 需要调用相应的清理事件状态的接口.
    extern void reset_readable(int fd);
    extern void reset_writable(int fd);

    extern void coroutine_hook_init();
} //namespace co
