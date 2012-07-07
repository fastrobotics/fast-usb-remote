/*
 * serial-link.c: simple program to send and recieve MAVlink heartbeat messages
 * Copyright (C) 2012  Michael Welling / FAST Robotics
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mavlink.h>

#define BAUDRATE B115200
char SERIALDEVICE[40] = "/dev/ttyUSB0";

volatile int STOP=0; 

int main(int argc, char **argv)
{
	int fd,c,res,i;
	int timeout = 0;
	struct termios oldtio,newtio;
	char buf[255];

	mavlink_message_t msg;
	mavlink_status_t status;

	if(argv[1])
		strcpy(SERIALDEVICE, argv[1]);

	fd = open(SERIALDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd <0) 
	{
		perror(SERIALDEVICE); 
		exit(-1); 
	}

	tcgetattr(fd,&oldtio);

	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VTIME]    = 0;
	newtio.c_cc[VMIN]     = 1;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);


	while (STOP==0) 
	{
		mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_HELICOPTER,
			MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, 
			MAV_STATE_ACTIVE);

		res = mavlink_msg_to_send_buffer(buf, &msg);
		res = write(fd,buf,res);
		printf("Heartbeat Message Sent\n");

		res = read(fd,buf,255);
		if(res > 0) 
		{
			for(i = 0; i < res; i++)
			{
				if(mavlink_parse_char(MAVLINK_COMM_0,buf[i], &msg, &status))
				{
                                        printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
					
					timeout = 0;
					switch(msg.msgid)
					{
						case MAVLINK_MSG_ID_HEARTBEAT:
							printf("Heartbeat Message Recieved\n");
							break;
						default:
							break;
					}
				}
			}
		}

		sleep(1);

		if(timeout++ == 20)
		{
			printf("No link detected.\n");
			STOP = 1;
		}
	}

	tcsetattr(fd,TCSANOW,&oldtio);
	return 0;
}
