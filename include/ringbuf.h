#ifndef RINGBUF_H
#define RINGBUF_H

typedef struct
{
    unsigned int size;
    unsigned char *head;
    unsigned char *tail;
    unsigned int datalen;
    unsigned char *buffer;
} ringbuf_t;

void ringbuf_init(ringbuf_t *ringbuf, unsigned char *buf, unsigned int len);
int ringbuf_add(ringbuf_t *ringbuf, unsigned char *buf, unsigned int len);
int ringbuf_get_data(ringbuf_t *ringbuf, unsigned char *buf, unsigned int len);
int ringbuf_get_datalen(ringbuf_t *ringbuf);

#endif
