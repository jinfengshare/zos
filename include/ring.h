// jinfeng, program this file at 2014/7/25

/* 
 * Ring Buffer, just implement the algorithm, all the state has been store in ringbuf_t
 * structure. :)
 *
 * RING_OVERWRITE	: for write, if len+datalen > buflen, throw it
 * RING_REALTIME	: for read, if user picked one, the ring will be cleared
 */

#ifndef _RING_H
#define _RING_H

enum
{
	RING_NONE = 0x00,
	RING_OVERWRITE = 0x01,
	RING_REALTIME = 0x02,
};

typedef struct
{
	unsigned char *buffer;
	unsigned short buflen;
	unsigned char attr;
	unsigned short datalen;
	unsigned short head;
	unsigned short tail;
} ringbuf_t;

int ringbuf_init(ringbuf_t*);
// return how many bytes added to this ring
int ringbuf_put(ringbuf_t*, unsigned char*, unsigned short);
int ringbuf_pick(ringbuf_t*, unsigned char*, unsigned short);

#endif

