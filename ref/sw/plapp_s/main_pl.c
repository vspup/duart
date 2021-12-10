/* simple application of communication IPC */

// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include <sys/poll.h>

int open_com(int baud);
int read_com(int fd, int len , int timeout, char * buff);
int serial_port;
int baud_rate = B921600;

// Allocate memory for read buffer & send buffer
#define BUF_SIZES 16
char read_buf [BUF_SIZES];
char send_buf [BUF_SIZES];

unsigned char msg[] = { '<', 'r', 'e', 'a', 'd', 'y', ':', '0', '1', '/', '5', '5', '5','>' };
unsigned char msg1[] = { '<', 'o', 'n', '/', '1','>' };
int counter = 0;

int f_send = 1;
char R[1];
int ReceivedCount = 0;
int f_new = 0;
int f_cmd = 0;

int main()
{
	// open serial port
	serial_port = open_com(baud_rate);
	if (serial_port < 0) {
		printf("[APU] Error %i open port: %s\n", errno, strerror(errno));

	}

	// Transmit operation
	while(1){

		// send command
		if (f_send == 1) {
			sleep(5);
			// send cmd
			int m = write(serial_port, msg, sizeof(msg));
			printf("[APU] Send >>> : %d\n", m);
			f_send =0;
		}
		else if (f_send == 2) {
			sleep(9);
			// send cmd
			int m = write(serial_port, msg1, sizeof(msg1));
			printf("[APU] Send >>> : %d\n", m);
			f_send =0;
		}



		// read answer
		while (read_com(serial_port, 1, 5, R) > 0){
			if (R[0] =='<'){
				ReceivedCount = 0;
				f_new = 1;
			}
			else if (R[0] == '>'){
				if (f_new == 1){
					f_cmd = 1;
					f_new = 0;
					//ReceivedCount--;
					printf("[APU] <<< read answer size [%d] = ", ReceivedCount);
					break;
				}
			}
			else {
				if (f_new == 1){
					read_buf[ReceivedCount] = R[0];
					ReceivedCount++;
				}
			}
		}


		if (f_cmd ==1) {
			f_cmd = 0;
			counter++;
			if (counter%2 == 0){
				f_send = 1;
			}
			else {
				f_send = 2;
			}

			for (int j=0; j < ReceivedCount; j++){
				printf("[%c]", read_buf[j]);
			}
			printf("\r\n");
		}
	}

	close(serial_port);

    return 0;
}


/*   */
int open_com(int baud){
	struct termios tty;
	int _port = open("/dev/ttyS1", O_RDWR);
	if (_port < 0) {
		printf("[APU] Error %i open port: %s\n", errno, strerror(errno));
		return _port;
	}

	printf("[APU] open port: %d\n", _port);

	printf("[APU] configure ttyS1\n");
	if(tcgetattr(_port, &tty) != 0) {
		printf("[APU] Error %i from tcgetattr: %s\n", errno, strerror(errno));
	}
		/* set parameters tty */
		/* baud_rate baud, 8 bits data length, 1 stop bit and no parity */
	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication
	tty.c_cflag |= CS8; // 8 bits per byte
	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	tty.c_cc[VTIME] = 1;    // Wait for up to 0.1s (1 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;
	cfsetispeed(&tty, baud);
	cfsetospeed(&tty, baud);
	// Save tty settings, also checking for error
	if (tcsetattr(_port, TCSANOW, &tty) != 0) {
		printf("[APU] Error configure tty %i from tcsetattr: %s\n", errno, strerror(errno));
	}
	printf("[APU] configure tty OK set baud rate %d\n", baud_rate);
	return _port;
}


int read_com(int fd, int len , int timeout, char * buff){
        int ret = 0;

        struct pollfd fds;
        fds.fd=fd;
        fds.events = POLLIN;
        poll(&fds, 1, timeout);
        if(fds.revents & POLLIN) {
                ret = read(fd, buff, len);
        }
        if(ret<0){
                ret = 0;
        }
        return ret;
}

