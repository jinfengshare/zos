#ifndef _FILE_H_
#define _FILE_H_

#define FILEDESC_MAX  20
#define FILENAME_MAX  20

typedef struct
{
  char filename[FILENAME_MAX];
  int (*open)(void);
  int (*close)(void);
  int (*ioctrl)(int option, void *value, unsigned int len);
  int (*read)(unsigned char *buffer, unsigned int len);
  int (*write)(unsigned char *buffer, unsigned int len);
}file_t;

int Create(file_t*);
int Open(char *filename);
int Close(int fd);
int IOCtrl(int fd, int option, void *value, unsigned char len);
int Read(int fd, unsigned char *buffer, unsigned int len);
int Write(int fd, unsigned char *buffer, unsigned int len);

#endif
