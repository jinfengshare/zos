#include "ringbuf.h"

static int _is_head_follow_tail(ringbuf_t *ringbuf)
{

    return (ringbuf->head < ringbuf->tail) ? 1 : 0;
}

static int _is_space_enough(ringbuf_t *ringbuf, unsigned int len)
{
    return (ringbuf->size - ringbuf->datalen > len) ? 1 : 0;
}

static int _tail2end(ringbuf_t *ringbuf)
{
    return ringbuf->size - (ringbuf->tail - ringbuf->buffer);
}

void ringbuf_init(ringbuf_t *ringbuf, unsigned char *buf, unsigned int len)
{
    ringbuf->buffer = buf;
    ringbuf->size = len;
    ringbuf->datalen = 0;
    ringbuf->head = buf;
    ringbuf->tail = buf;
}

int ringbuf_add(ringbuf_t *ringbuf, unsigned char *buf, unsigned int len)
{
    int ret;

    if (_is_space_enough(ringbuf, len))
    {
        ringbuf->datalen += len;

        if (_is_head_follow_tail(ringbuf))
        {
            ret = _tail2end(ringbuf);

            if (ret > len)
            {
                memcpy(ringbuf->tail, buf, len);
                ringbuf->tail += len;
                return len;
            }
            else if (ret == len)
            {
                memcpy(ringbuf->tail, buf, len);
                ringbuf->tail = ringbuf->buffer;
                return len;
            }
            else
            {
                memcpy(ringbuf->tail, buf, ret);
                memcpy(ringbuf->buffer, &buf[len - ret], (len - ret));
                ringbuf->tail = ringbuf->buffer + (len - ret);
                return len;
            }
        }
        else
        {
            memcpy(ringbuf->tail, buf, len);
            ringbuf->tail += len;
            return len;
        }
    }
    else
    {
        return -1;
    }
}

int ringbuf_get_data(ringbuf_t *ringbuf, unsigned char *buf, unsigned int len)
{
    int ret;
    int tmp;

    if (_is_head_follow_tail(ringbuf))
    {
        if (ringbuf->datalen <= len)
        {
            tmp = ringbuf->datalen;
            memcpy(buf, ringbuf->head, tmp);
            ringbuf->head = ringbuf->tail;
            ringbuf->datalen = 0;
            return tmp;
        }
        else
        {
            memcpy(buf, ringbuf->head, len);
            ringbuf->head += len;
            ringbuf->datalen -= len;
            return len;
        }
    }
    else
    {
        ret = _tail2end(ringbuf);

        if (len < ret)
        {
            memcpy(buf, ringbuf->head, len);
            ringbuf->head += len;
            ringbuf->datalen -= len;
            return len;
        }
        else if (len < ringbuf->datalen)
        {
            memcpy(buf, ringbuf->head, ret);
            memcpy(&buf[ret], ringbuf->buffer, len - ret);
            ringbuf->head = ringbuf->buffer + (len - ret);
            ringbuf->datalen -= len;
            return len;
        }
        else
        {
            memcpy(buf, ringbuf->head, ret);
            memcpy(&buf[ret], ringbuf->buffer, ringbuf->datalen - ret);
            ringbuf->head = ringbuf->tail;
            ringbuf->datalen = 0;
            return ringbuf->datalen;
        }
    }
}

int ringbuf_get_datalen(ringbuf_t *ringbuf)
{
    return ringbuf->datalen;
}

