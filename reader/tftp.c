#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include "tftp.h"

//extern int h_errno;

#define TFTP_TYPE_GET 0
#define TFTP_TYPE_PUT 1

/* Should cover most needs */
#define MSGBUF_SIZE (TFTP_DATA_HDR_LEN + BLOCK_SIZE)

/* Record last transmited data and its length in case of packet loss */
char* lastTransferData;
int lastTransferDataLength;

/*
 * NOTE:
 * In tftp.h you will find definitions for headers and constants. Make
 * sure these are used throughout your code.
 */

/* A connection handle */
struct tftp_conn {
	int type; /* Are we putting or getting? */
	FILE *fp; /* The file we are reading or writing */
	int sock; /* Socket to communicate with server */
	int blocknr; /* The current block number */
	char *fname; /* The file name of the file we are putting or getting */
	char *mode; /* TFTP mode */
	struct sockaddr_in peer_addr; /* Remote peer address */
	socklen_t addrlen; /* The remote address length */
	char msgbuf[MSGBUF_SIZE]; /* Buffer for messages being sent or received */
};

/* Close the connection handle, i.e., delete our local state. */
static void tftp_close(struct tftp_conn *tc) {
	if (!tc)
		return;
	fclose(tc->fp);
	close(tc->sock);
	free(tc);
}

/* Connect to a remote TFTP server. */
static struct tftp_conn *tftp_connect(int type, char *fname, char *mode,const char *hostname) 
{
	struct addrinfo hints;
	struct addrinfo * res = NULL;
	struct tftp_conn *tc;

	if (!fname || !mode || !hostname)
		return NULL ;

	tc = malloc(sizeof(struct tftp_conn));

	if (!tc)
		return NULL ;

	/* Create a socket.
	 * Check return value. */
	 
    /* Specify communication domain (protocol family) and communication semantics (socket type) */
	if ((tc->sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "Unable to create socket...\n");
		free(tc);
		return NULL ;
	}
    /* Check the type = read or write file */
	if (type == TFTP_TYPE_PUT)
		tc->fp = fopen(fname, "rb");
	else if (type == TFTP_TYPE_GET)
		tc->fp = fopen(fname, "wb");
	else {
		fprintf(stderr, "Invalid TFTP mode, must be put or get\n");
		return NULL ;
	}

	if (tc->fp == NULL ) {
		fprintf(stderr, "File I/O error!\n");
		close(tc->sock);
		free(tc);
		return NULL ;
	}

	/* initial settings for getaddrinfo function */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	char port_str[5];
	sprintf(port_str, "%d", 20069);

	/* get address from host name.
	 * If error, gracefully clean up.*/
    
	/* host address information is stored in the varible res */
	int errorcode = getaddrinfo(hostname, port_str, &hints, &res);
	if (errorcode != 0) {
		fprintf(stderr, "Unable to get host address...\n");
		close(tc->sock);
		free(tc);
		return NULL ;
	}

	/* Assign address to the connection handle.
	 * You can assume that the first address in the hostent
	 * struct is the correct one */

	/* initial settings for varible tc which will be used in the later transmition */
	memcpy(&tc->peer_addr, res->ai_addr, res->ai_addrlen);
	tc->addrlen = sizeof(struct sockaddr_in);
	tc->type = type;
	tc->mode = mode;
	tc->fname = fname;
	tc->blocknr = 0;
	memset(tc->msgbuf, 0, MSGBUF_SIZE);
	return tc;
}

/*
 Send a read request to the server.
 1. Format message.
 2. Send the request using the connection handle.
 3. Return the number of bytes sent, or negative on error.
 */
static int tftp_send_rrq(struct tftp_conn *tc) {	
	/* struct tftp_rrq *rrq; */
	struct tftp_rrq* pTftp_rrq = malloc(TFTP_RRQ_LEN((*tc).fname,(*tc).mode));
	memset(pTftp_rrq, 0, TFTP_RRQ_LEN((*tc).fname,(*tc).mode));
	pTftp_rrq->opcode = htons(OPCODE_RRQ);//transform host ascii to net ascii
	memcpy(pTftp_rrq->req, (*tc).fname, strlen((*tc).fname));
	memcpy(pTftp_rrq->req + strlen((*tc).fname) + 1, (*tc).mode,
			strlen((*tc).mode));
	/* send read request to the server */
	int rqtResult = sendto(tc->sock, pTftp_rrq,
			TFTP_RRQ_LEN((*tc).fname,(*tc).mode), 0,
			(struct sockaddr*) (&(tc->peer_addr)), (*tc).addrlen);
	free(pTftp_rrq);
	return rqtResult;
}
/*
 Send a write request to the server.
 1. Format message.
 2. Send the request using the connection handle.
 3. Return the number of bytes sent, or negative on error.
 */
static int tftp_send_wrq(struct tftp_conn *tc) {
	/* struct tftp_wrq *wrq; */
	struct tftp_wrq* pTftp_wrq = malloc(TFTP_WRQ_LEN(tc->fname, tc->mode));
	memset(pTftp_wrq, 0, TFTP_WRQ_LEN(tc->fname, tc->mode));
	pTftp_wrq->opcode = htons(OPCODE_WRQ);//transform host ascii to net ascii
	memcpy(pTftp_wrq->req, tc->fname, strlen(tc->fname));
	memcpy(pTftp_wrq->req + strlen(tc->fname) + 1, tc->mode, strlen(tc->mode));
	/* send write request to the server */
	int rqtResult = sendto(tc->sock, pTftp_wrq,
			TFTP_WRQ_LEN(tc->fname, tc->mode), 0,
			(struct sockaddr*) (&(tc->peer_addr)), (*tc).addrlen);
	free(pTftp_wrq);
	return rqtResult;
}

/*
 Acknowledge reception of a block.
 1. Format message.
 2. Send the acknowledgement using the connection handle.
 3. Return the number of bytes sent, or negative on error.
 */
static int tftp_send_ack(struct tftp_conn *tc) {
	/* struct tftp_ack *ack; */
	struct tftp_ack* pTftp_ack = (struct tftp_ack*) malloc(TFTP_ACK_HDR_LEN);
	pTftp_ack->opcode = htons(OPCODE_ACK);//transform host ascii to net ascii
	/* Get receiving data block number from tc->msgbuf and ack to the server */
	tc->blocknr = ntohs(((struct tftp_data*) tc->msgbuf)->blocknr);
	pTftp_ack->blocknr = htons(tc->blocknr);
	int result = sendto(tc->sock, pTftp_ack,TFTP_ACK_HDR_LEN, 0,
			(struct sockaddr*)(&(tc->peer_addr)), (*tc).addrlen);
	free(pTftp_ack);
	return result;
}

/*
 Send a data block to the other side.
 1. Format message.
 2. Add data block to message according to length argument.
 3. Send the data block message using the connection handle.
 4. Return the number of bytes sent, or negative on error.

 TIP: You need to be able to resend data in case of a timeout. When
 resending, the old message should be sent again and therefore no
 new message should be created. This can, for example, be handled by
 passing a negative length indicating that the creation of a new
 message should be skipped.
 */
static int tftp_send_data(struct tftp_conn *tc, int length) {
	/* struct tftp_data *tdata; */
	struct tftp_data* pTftp_data = malloc(TFTP_DATA_HDR_LEN+BLOCK_SIZE);
	memset(pTftp_data,0,TFTP_DATA_HDR_LEN+length);
	pTftp_data->opcode=htons(OPCODE_DATA);
	/* Get receiving ack number from tc->msgbuf and send data to the server */
	/* Retransmit old block in case of packet loss */
    if(tc->blocknr==1+ntohs(((struct tftp_ack*)tc->msgbuf)->blocknr)) {
		pTftp_data->blocknr=htons(tc->blocknr);
		memcpy(pTftp_data->data,lastTransferData,lastTransferDataLength);
		/* transmit last transfered data */
		int result=sendto(tc->sock, pTftp_data, TFTP_DATA_HDR_LEN+lastTransferDataLength, 
		                 0,(struct sockaddr*)(&(tc->peer_addr)), (*tc).addrlen);
        return result;
    } else {
    //************Transmit new block**********************//
		tc->blocknr=ntohs(((struct tftp_ack*)tc->msgbuf)->blocknr)+1;
		pTftp_data->blocknr=htons(tc->blocknr);
		/* read data from local file system and send it to the server */
		if(!feof(tc->fp)) {
			int dataLength=fread(pTftp_data->data,1,length,tc->fp);
			int result=sendto(tc->sock, pTftp_data, TFTP_DATA_HDR_LEN+dataLength, 0,
						(struct sockaddr*)(&(tc->peer_addr)), (*tc).addrlen);
			/* record data as lastTranserData in case of packet loss */
			lastTransferData=malloc(dataLength);
			memset(lastTransferData,0,dataLength);
			memcpy(lastTransferData,pTftp_data->data,dataLength);
			lastTransferDataLength=dataLength;
			return result;
		}
    }
    return -1;
}

	/*
	 Transfer a file to or from the server.
	 */
static int tftp_transfer(struct tftp_conn *tc) {
	int retval = 0; //Transfer result
	int totlen = 0; //Transfer total length
	int recvResult; //Length of reveiving data
	int sendResult; //Length of sending data
	struct timeval timeout; //Time out setting
	fd_set fdst;    //File descriptor for select function
	u_int16_t errorCode; //Error code
	int isEnd=0;    //Transfer is end or not: 0-not, 1-end

	/* Sanity check */
	if (!tc)
		return -1;

	/* After the connection request we should start receiving data
	 * immediately */
	/* Check if we are putting a file or getting a file and send
	 * the corresponding request. */
	if (TFTP_TYPE_GET == tc->type) {
		tftp_send_rrq(tc);
	} else if (TFTP_TYPE_PUT == tc->type) {
		tftp_send_wrq(tc);
	} else {
		return -1;
	}
	
	/*
	 Put or get the file, block by block, in a loop.
	 */
	do {
		/* 1. Wait for something from the server (using
		 * 'select'). If a timeout occurs, resend last block
		 * or ack depending on whether we are in put or get
		 * mode. */

		/* ... */
		while (1) {
		/* Set a timeout for resending data. */
			timeout.tv_sec = TFTP_TIMEOUT;
			timeout.tv_usec = 0;

			FD_ZERO(&fdst);//Clear file descriptor set to enable status checking
			FD_SET(tc->sock, &fdst);//add fiel descriptor to the set
			/* Check status of values in the fdst to see if any fd is ready for reading or writing */
			int sltRlt = select(tc->sock + 1, &fdst, NULL, NULL, &timeout);
			if (sltRlt < 0) { //Error in the select function
				return -1;
			} else if (sltRlt == 0) { //Time out in the selection function, no readable, writable or error fds
				//******Retransmit********//
				if (TFTP_TYPE_GET == tc->type) {
				    /* Retransmit read request */
					if(0==tc->blocknr) {
						tftp_send_rrq(tc);
					} else {
					/* Retransmit ack packet */
						printf("%s,%d\n", "Retransmit Ack", tc->blocknr);
						tftp_send_ack(tc);
					}

				} else if (TFTP_TYPE_PUT == tc->type) {
				    /* Retransmit write request */
					if(0==tc->blocknr) {
						tftp_send_wrq(tc);
					} else {
					/* Retransmit data packet */

						printf("%s,%d\n", "Retransmit Data", tc->blocknr);
						sendResult=tftp_send_data(tc,BLOCK_SIZE);
					}
				} else {
						return -1;
				}
				continue;//Continue to wait for receiving data
			} else {//readable, writable or error fds exist
			    /* receive data */
				recvResult = recvfrom(tc->sock, tc->msgbuf,
				sizeof(tc->msgbuf), 0,(struct sockaddr*) (&(tc->peer_addr)),&tc->addrlen);
				break;
			}
		}
		u_int16_t msgType = ntohs(((struct tftp_msg*) (tc->msgbuf))->opcode);//Msg type
		int serverSendBlkNr=0; //receiving data block number sent by server
		int serverAckBlkNr=0;  //receiving ack block number sent by server
		
		/* 2. Check the message type and take the necessary action. */
		switch (msgType) {

		case OPCODE_DATA:
			/* Received data block, send ack */
			serverSendBlkNr=ntohs(((struct tftp_data*) tc->msgbuf)->blocknr);
			/* receive correct data packet and discard duplicated dat packets */
			if(tc->blocknr == serverSendBlkNr-1)
			{
			    /* write correct data to file */
				fwrite(tc->msgbuf+ TFTP_DATA_HDR_LEN, 1, recvResult-TFTP_DATA_HDR_LEN, tc->fp);
				totlen += recvResult - TFTP_DATA_HDR_LEN;
				printf("%s,%d,%d,%d\n","Get",serverSendBlkNr,recvResult - TFTP_DATA_HDR_LEN,totlen);
			}
			/* Send ack packet to server */
		    tftp_send_ack(tc);
			/* if length of receiving data packet is less than 516(512+4) bytes, 
			then the connection should be terminated */
		    if(recvResult < 516) {
				isEnd=1;
				printf("%s\n", "End of receiving data");
		    }
			break;

			case OPCODE_ACK:
			/* Received ACK, send next block */
			serverAckBlkNr = ntohs(((struct tftp_ack*)tc->msgbuf)->blocknr);
			/* receive correct ack packet and discard duplicated ack packets */
			if(tc->blocknr == serverAckBlkNr && serverAckBlkNr>0) {
				totlen+=sendResult-TFTP_DATA_HDR_LEN;
				printf("%s,%d,%d,%d\n","Put",serverAckBlkNr,sendResult-TFTP_DATA_HDR_LEN,totlen);
				/* if length of sending data packet is less than 516(512+4) bytes, 
			then the connection should be terminated */
				if(sendResult<516 && serverAckBlkNr>0) {
					isEnd=1;
					printf("%s\n", "End of sending data");
					break;
				}
			}
			/* Send data packet to server */
            sendResult=tftp_send_data(tc,BLOCK_SIZE);
			break;

			case OPCODE_ERR:
			/* Handle error... */
			errorCode=ntohs(((struct tftp_err*) (tc->msgbuf))->errcode);
			fprintf(stderr,"%s", err_codes[errorCode]);
			retval=-1;
			goto out;
			break;

			default:
			fprintf(stderr, "\nUnknown message type\n");
			goto out;
		}

	} while (isEnd==0);

	printf("\nTotal data bytes sent/received: %d.\n", totlen);
	out: return retval;
}

int tftp_recv_process(char *host, char *path)
{
	int ret = -1;
	struct tftp_conn *tc;

	/* Connect to the remote server */
	tc = tftp_connect(TFTP_TYPE_GET, path, MODE_OCTET, host);
	if (!tc) {
		fprintf(stderr, "Failed to connect!\n");
		return -1;
	}

	/* Transfer the file to or from the server */
	ret = tftp_transfer(tc);
	if (ret < 0) {
		fprintf(stderr, "File transfer failed!\n");
	}

	/* We are done. Cleanup our state. */
	tftp_close(tc);

	return ret;
}
