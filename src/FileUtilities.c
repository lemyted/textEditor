#include "../includes/Main.h"

// Operations
int createNewFile(char *path) 
{
  if (fileExists(path)) 
  {
    logShortFileError(FILE_ALREADY_EXISTS, path);
    return -1;
  }

  int fd = open(path, O_CREAT | O_RDWR);

  if (fd == -1) 
  {
    logLongFileError(UNABLE_TO_CREATE_FILE, path);
    return -1;
  }
  
  close(fd);
  return 0;
}

char *readFile(char *path) 
{
  struct stat *info = getFileInfo(path);

  if (info == NULL) 
  {
    return NULL;
  } 

  if (isDir(info)) 
  {
    logShortFileError(FILE_IS_DIRECTORY, path);
    free(info);
    return NULL;
  }

  ssize_t nBytesRead;
  int fileSize = getSize(info);
  int fd = open(path, O_RDONLY);
  char *buffer = (char*)malloc(sizeof (char) * (fileSize + 1));

  nBytesRead = read(fd, buffer, fileSize);
  
  if (nBytesRead == -1) 
  {
    logLongFileError(CANNOT_READ_FILE, path);
    free(info);
    return NULL;
  }

  if (nBytesRead != (ssize_t)fileSize) 
  {
    logShortFileError(FILE_NOT_READ_ENTIRELY, path);
  }
  
  buffer[fileSize] = '\0';
  free(info);
  close(fd);
  return buffer;
}

int updateFile(char *path, char *content) 
{
  struct stat *info = getFileInfo(path);

  if (info == NULL) 
  {
    return -1;
  } 

  if (isDir(info)) 
  {
    logShortFileError(FILE_IS_DIRECTORY, path);
    free(info);
    return -1;
  }

  ssize_t nBytesWritten;
  int contentSize = strlen(content);
  int fd = open(path, O_WRONLY);

  nBytesWritten = write(fd, content, contentSize);
  fsync(fd);

  if (nBytesWritten != (ssize_t)contentSize) 
  {
    logShortFileError(FILE_NOT_WRITTEN_ENTIRELY, path);
  }

  close(fd);
  return 0;
}

// Utilities
void logLongFileError(char *msg, char *path) 
{
  fprintf(stderr, msg, __LINE__, __FILE__, path, strerror(errno));
}

void logShortFileError(char *msg, char *path) 
{
  fprintf(stderr, msg, __LINE__, __FILE__, path);
}

int fileExists(char *path) 
{
  if (access(path, F_OK) == -1) 
  {
    return 0;
  }

  return 1;
}

struct stat *getFileInfo(char *path) 
{
  if (fileExists(path)) 
  {
    struct stat *info = (struct stat*)malloc(sizeof (struct stat));

    if (stat(path, info) != -1) 
    {
      return info;
    }

    logLongFileError(UNABLE_TO_GET_FILE_INFO, path);
  }

  logShortFileError(FILE_NOT_FOUND, path);
  return NULL;
}

int isDir(struct stat *info) 
{
  return S_ISDIR(info->st_mode);
}

off_t getSize(struct stat *info) 
{
  return info->st_size;
}
