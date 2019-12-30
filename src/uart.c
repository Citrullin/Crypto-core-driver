#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <config.h>
#include <stdbool.h>
#include <jansson.h>
#include <stdint.h>

extern int uart_fd;
char uart_buffer[UART_BUFFER_SIZE];

int uart_set_interface_attribs(int fd, int speed, int parity){
    struct termios tty;
    if (tcgetattr (fd, &tty) != 0)
    {
        //error_message ("error %d from tcgetattr", errno);
        return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = ICANON;
    tty.c_oflag = 0;

    tty.c_cc[VINTR]    = 0;     /* Ctrl−c */
    tty.c_cc[VQUIT]    = 0;     /* Ctrl−\ */ 
    tty.c_cc[VERASE]   = 0;     /* del */
    tty.c_cc[VKILL]    = 0;     /* @ */
    tty.c_cc[VEOF]     = 4;     /* Ctrl−d */
    tty.c_cc[VTIME]    = 0;     /* inter−character timer unused */
    tty.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
    tty.c_cc[VSWTC]    = 0;     /* '\0' */
    tty.c_cc[VSTART]   = 0;     /* Ctrl−q */
    tty.c_cc[VSTOP]    = 0;     /* Ctrl−s */
    tty.c_cc[VSUSP]    = 0;     /* Ctrl−z */
    tty.c_cc[VEOL]     = 0;     /* '\0' */ 
    tty.c_cc[VREPRINT] = 0;     /* Ctrl−r */ 
    tty.c_cc[VDISCARD] = 0;     /* Ctrl−u */
    tty.c_cc[VWERASE]  = 0;     /* Ctrl−w */
    tty.c_cc[VLNEXT]   = 0;     /* Ctrl−v */ 
    tty.c_cc[VEOL2]    = 0;     /* '\0' */
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tcflush(fd, TCIFLUSH);
    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        printf("error %d from tcsetattr", errno);
        return -1;
    }
    return 0;
}

int uart_open(void){
    char *portname = UART_PORT;

    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        printf("error %d opening %s: %s", errno, portname, strerror (errno));
        return -1;
    }

    return fd;
}

char * uart_read(void){
    memset(uart_buffer, 0, UART_BUFFER_SIZE);
    int res;
    bool stop = false;
    uint32_t size = 0;

    while(!stop){
        if(size >= UART_BUFFER_SIZE){
            puts("Error: UART buffer size exceeded!");
        }else{
            res = read(uart_fd,uart_buffer,UART_BUFFER_SIZE);
            uart_buffer[res] = '\0';
            stop = true;
        }
    }

    return uart_buffer;
}

void uart_write(json_t * json_ptr){
    memset(uart_buffer, 0, UART_BUFFER_SIZE);
    size_t used_size = json_dumpb(json_ptr, uart_buffer, UART_BUFFER_SIZE, JSON_ENSURE_ASCII);

    printf("Send %li bytes to uart. Message: %s\n", used_size, uart_buffer);
    write(uart_fd, uart_buffer, used_size);
    write(uart_fd, "\n", 1);
}

int uart_init(void){
    int uart_fd = uart_open();
    uart_set_interface_attribs(uart_fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    return uart_fd;
}
