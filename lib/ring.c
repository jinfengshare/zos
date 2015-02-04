#include <lib/ring.h>
#include <string.h>

// tail = 3
// buffer[tail] = []; // to fill into
// buffer[tail-1] = [x];
// but if tail = 0, 


// --- Key ---
// if buffer len = 5, and you have put 5 bytes, then, tail = 5, which cause overflow!
// why? as this pointer always point to the new position, even if there is no space!
// so, at the end, we should stop move forward!

int ringbuf_init(ringbuf_t* rb)
{
	rb->datalen = 0;
	rb->head = 0;
	rb->tail = 0;
	
	memset(rb->buffer, 0, rb->buflen);
	
	return 0;
}

int ringbuf_reset(ringbuf_t* rb)
{
	rb->datalen = 0;
	rb->head = 0;
	rb->tail = 0;
	
	memset(rb->buffer, 0, rb->buflen);
	
	return 0;
}


// return how many bytes added to this ring
int ringbuf_put(ringbuf_t* rb, unsigned char* data, unsigned short len)
{
	unsigned short byteslast;
	unsigned short bytes2put;
	unsigned short bytesputted;
	
	// parameter check
	if((NULL==rb)||(NULL==data)||(0==len))
	{
		return 0;
	}

	// ring entry check
	// if data too big, suggest to check if input module error!
	// if we stored it, the data is not valid.
	if(len > rb->buflen)
	{
		return 0;
	}

	// algorithm check
	if(0 == (rb->attr & RING_OVERWRITE))
	{
		if(rb->datalen + len > rb->buflen)
		{
			// throw this data!
			return 0;
		}
	}

	// add it at tail offset, normally byteslast >= 0
	byteslast = rb->buflen - rb->datalen;
	
	// as type of byteslast is uint16_t, so if byteslast > BUFLEN
	// Ring Error!reset it!
	if(byteslast > rb->buflen)
	{
		ringbuf_reset(rb);
	}
	
	// enough space to hold the data
	if(byteslast >= len)
	{
		// tail count from 1
		// buffer start from offset 0
		if(rb->tail + len < rb->buflen)
		{
			memcpy(&rb->buffer[rb->tail], data, len);
			rb->tail += len;
			rb->datalen += len;
		}
		// deal with buffer-end-overflow question
		else if(rb->tail + len == rb->buflen)
		{
			memcpy(&rb->buffer[rb->tail], data, len);
			rb->tail = 0;
			rb->datalen += len;
		}
		else
		{
			bytes2put = len - (rb->buflen - rb->tail);
			memcpy(&rb->buffer[rb->tail], data, bytes2put);
			bytesputted = bytes2put;
			bytes2put = len - bytesputted;
			memcpy(rb->buffer, &data[bytesputted], bytes2put);
			rb->tail = bytes2put;
			rb->datalen += len;
		}
	}
	// not enough, the ring buffer just keep 2-3 frames
	else
	{
		ringbuf_reset(rb);
		// enough now!
		memcpy(rb->buffer, data, len);
		rb->datalen = len;
		rb->tail = len;
	}
	
	return len;
}

int ringbuf_pick(ringbuf_t *rb, unsigned char *buf, unsigned short len)
{
	unsigned short bytes2pick;
	unsigned short minlen;
	
	// parameter check
	if((NULL==rb)||(NULL==buf)||(0==len))
	{
		return 0;
	}

#if 0
	// for test
	/*
	 * rb->datalen == 0 >>> OK
	 *
	 * Enter DMA interrupt
	 * rb->datalen = 1; rb->head += 1;
	 * rb->head != rb->tail >>> OK
	 * Exit DMA interrupt
	 *
	 * then the break point
	 */
	if((rb->datalen == 0) && (rb->head != rb->tail))
	{
		rb->head = rb->tail;
	}
#endif
	
	if(0 == rb->datalen)
	{
		return 0;
	}

	// pick data, attention, real data len >= minlen
	minlen = (len <= rb->datalen) ? len : rb->datalen;
	if(minlen > (rb->buflen - rb->head))
	{
		bytes2pick = rb->buflen - rb->tail;
		memcpy(buf, &rb->buffer[rb->head], bytes2pick);
		memcpy(&buf[bytes2pick], rb->buffer, (minlen - bytes2pick));
		rb->head = bytes2pick;
		rb->datalen -= minlen;
	}
	else if(minlen < (rb->buflen - rb->head))
	{
		memcpy(buf, &rb->buffer[rb->head], minlen);
		rb->head += minlen;
		rb->datalen -= minlen;
	}
	else
	{
		memcpy(buf, &rb->buffer[rb->head], minlen);
		rb->head = 0;
		rb->datalen -= minlen;
	}
	
	// algorithm check
	if(rb->attr & RING_REALTIME)
	{
		ringbuf_reset(rb);
	}

	return minlen;
}

