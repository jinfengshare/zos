#include <fs/file.h>
#include <lib/types.h>
#include <stdio.h>

file_t _filedesc[FILEDESC_MAX];

void fs_init(void)
{
  memset(_filedesc, 0, sizeof(_filedesc));
}

static file_t * get_filedesc(int fd)
{
  if((fd>=0) && (fd<FILEDESC_MAX))
  {
    return &_filedesc[fd];
  }
  
  return NULL;
}

void fs_dump(void)
{
  int i;
  file_t *file;
  
  for(i=0; i<FILEDESC_MAX; i++)
  {
    file = get_filedesc(i);
    if(NULL != file)
    {
      printf("%s\n", file->filename);
    }
  }
}

int Create(file_t *filedesc)
{
  int i;
  int ret;
  file_t *file;
  
  if(NULL == filedesc)
  {
    return -1;
  }
  
  for(i=0; i<FILEDESC_MAX; i++)
  {
    file = get_filedesc(i);
    if(NULL != file)
    {
      if(0 == file->filename[0])
      {
        continue;
      }
      ret = memcmp(file->filename, filedesc->filename, strlen(filedesc->filename));
      if(0 == ret)
      {
        return i;
      }
    }
  }
    
  for(i=0; i<FILEDESC_MAX; i++)
  {
    file = get_filedesc(i);
    if(NULL != file)
    {
      if(0 == file->filename[0])
      {
        memcpy(file, filedesc, sizeof(file_t));
        return i;
      }
    }
  }
  
  return -1;
}

int Open(char *filename)
{
  int i;
  int ret;
  file_t *file;
  
  if((NULL == filename) || (strlen(filename) >= FILENAME_MAX))
  {
    return -1;
  }
  
  for(i=0; i<FILEDESC_MAX; i++)
  {
    file = get_filedesc(i);
    if(NULL != file)
    {
      ret = memcmp(file->filename, filename, strlen(filename));
      if(0 == ret)
      {
        break;
      }
    }
  }
  
  if(i == FILEDESC_MAX)
  {
    return -1;
  }
  else
  {
    if(NULL != file->open)
    {
      ret = file->open();
      if(0 == ret)
      {
        // dm ok, driver ok
        return i;
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
}

int Close(int fd)
{
  int ret;
  
  file_t *file = get_filedesc(fd);
  if(NULL == file)
  {
    return -1;
  }
  
  if(NULL != file->close)
  {
    ret = file->close();
    return ret;
  }
  
  return -1;
}
int IOCtrl(int fd, int option, void *value, unsigned char len)
{
  int ret;
  
  file_t *file = get_filedesc(fd);
  if(NULL == file)
  {
    return -1;
  }
  
  if(NULL != file->ioctrl)
  {
    ret = file->ioctrl(option, value, len);
    return ret;
  }
  
  return -1;
}
int Read(int fd, unsigned char *buffer, unsigned int len)
{
  int ret;
  
  file_t *file = get_filedesc(fd);
  if(NULL == file)
  {
    return -1;
  }
  
  if(NULL != file->read)
  {
    ret = file->read(buffer, len);
    return ret;
  }
  
  return -1;
}

int Write(int fd, unsigned char *buffer, unsigned int len)
{
  int ret;
  
  file_t *file = get_filedesc(fd);
  if(NULL == file)
  {
    return -1;
  }
  
  if(NULL != file->write)
  {
    ret = file->write(buffer, len);
    return ret;
  }
  
  return -1;
}
