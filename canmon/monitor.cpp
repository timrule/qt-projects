#include <QDebug>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include "monitor.h"

Monitor::Monitor()
{
	running = 0;
}

void Monitor::start()
{
	int rc;
	int s;
	fd_set rdfs;
	int nbytes;
	struct sockaddr_can addr;
	struct canfd_frame frame;
	struct iovec iov;
	char ctrlmsg[CMSG_SPACE(sizeof(struct timeval)) + CMSG_SPACE(sizeof(__u32))];
	struct msghdr msg;
	struct ifreq ifr;
	char* ifname = "can0";

	running = 1;

	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (s < 0)
	{
		qDebug() << "Error opening socket: " << s;
		stop();
		return;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	rc = bind(s, (struct sockaddr*)&addr, sizeof(addr));
	if (rc < 0)
	{
		qDebug() << "Error binding to interface: " << rc;
		stop();
		return;
	}

	iov.iov_base = &frame;
	msg.msg_name = &addr;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = &ctrlmsg;

	while (running)
	{
		FD_ZERO(&rdfs);
		FD_SET(s, &rdfs);
		rc = select(s, &rdfs, NULL, NULL, NULL);
		if (rc < 0)
		{
			qDebug() << "Error calling select" << rc;
			stop();
			continue;
		}

		if (FD_ISSET(s, &rdfs))
		{
			int maxdlen;

			// These can apparently get changed, so set before each read
			iov.iov_len = sizeof(frame);
			msg.msg_namelen = sizeof(addr);
			msg.msg_controllen = sizeof(ctrlmsg);
			msg.msg_flags = 0;

			nbytes = recvmsg(s, &msg, 0);
			if (nbytes < 0)
			{
				qDebug() << "Error calling recvmsg : " << nbytes;
				stop();
				continue;
			}

			if ((size_t)nbytes == CAN_MTU)
				maxdlen = CAN_MAX_DLEN;
			else if ((size_t)nbytes == CANFD_MTU)
				maxdlen = CANFD_MAX_DLEN;
			else
			{
				qDebug() << "Warning: read incomplete CAN frame : " << nbytes;
				continue;
			}
			// TODO get timestamp from message

			sendMsg(&frame, maxdlen);
		}
	}
}

void Monitor::stop()
{
	running = 0;
}

void Monitor::sendMsg(struct canfd_frame *frame, int maxdlen)
{
	canMessage msg;
	char buf[200];
	int pBuf = 0;
	int i;
	int len = (frame->len > maxdlen) ? maxdlen : frame->len;

	msg.interface = 1; // TODO set in constructor at some point
	msg.identifier = QString("%1:%03X")
						.arg(msg.interface)
						.arg(frame->can_id & CAN_SFF_MASK);
	msg.time = QTime::currentTime();

	pBuf += sprintf(buf + pBuf, "[%d]", frame->len);
	if (frame->can_id & CAN_RTR_FLAG)
	{
		pBuf += sprintf(buf + pBuf, " remote request");
		emit messageInBuffer(&msg);
		return;
	}
	for (i = 0; i < len; i++)
	{
		pBuf += sprintf(buf + pBuf, " [%02X]", frame->data[i]);
	}
	msg.content = QString("%1").arg(buf);

	emit messageInBuffer(&msg);
}

