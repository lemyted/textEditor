#include "../includes/Main.h"

// Operations
int createNewFile(char *path) 
{
  if (fileExists(path)) 
  {
    logShortFileError(FILE_ALREADY_EXISTS, path, __LINE__, __FILE__);
    return -1;
  }

  int fd = open(path, O_CREAT | O_RDWR);

  if (fd == -1) 
  {
    logLongFileError(UNABLE_TO_CREATE_FILE, path, __LINE__, __FILE__);
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
    logShortFileError(FILE_IS_DIRECTORY, path, __LINE__, __FILE__);
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
    logLongFileError(CANNOT_READ_FILE, path, __LINE__, __FILE__);
    free(info);
    return NULL;
  }

  if (nBytesRead != (ssize_t)fileSize) 
  {
    logShortFileError(FILE_NOT_READ_ENTIRELY, path, __LINE__, __FILE__);
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
    logShortFileError(FILE_IS_DIRECTORY, path, __LINE__, __FILE__);
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
    logShortFileError(FILE_NOT_WRITTEN_ENTIRELY, path, __LINE__, __FILE__);
  }

  free(info);
  close(fd);
  return 0;
}

int deleteFile(char *path) 
{
  if (!fileExists(path)) 
  {
    logShortFileError(FILE_NOT_FOUND, path, __LINE__, __FILE__);
    return -1;
  }

  int fd = open(path, O_RDWR);

  if (fd == -1) 
  {
    logLongFileError(UNABLE_TO_CREATE_FILE, path, __LINE__, __FILE__);
    return -1;
  }

  if (unlink(path) == -1) 
  {
    logLongFileError(UNABLE_TO_DELETE_FILE, path, __LINE__, __FILE__);
  }
  
  close(fd);
  return 0;
}

int copyFile(char *originalPath, char *copyPath) 
{
  char *content = readFile(originalPath);

  if (content == NULL) { return -1; }

  if (createNewFile(copyPath) == -1) { return -1; }

  if (updateFile(copyPath, content) == -1) { return -1; }

  return 0;
}

int moveFile(char *srcPath, char *destPath) 
{
  if (copyFile(srcPath, destPath) == -1) { return -1; }
  if (deleteFile(srcPath) == -1) { return -1; }
  return 0;
}

// Utilities
void logLongFileError(char *msg, char *path, int line, char *file) 
{
  fprintf(stderr, msg, line, file, path, strerror(errno));
}

void logShortFileError(char *msg, char *path, int line, char *file) 
{
  fprintf(stderr, msg, line, file, path);
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

    logLongFileError(UNABLE_TO_GET_FILE_INFO, path, __LINE__, __FILE__);
  }

  logShortFileError(FILE_NOT_FOUND, path, __LINE__, __FILE__);
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
