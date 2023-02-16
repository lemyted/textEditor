#include "../includes/Main.h"

// Utilities
int fileExists(char *path) 
{
  int status = access(path, F_OK);

  if (status == -1) 
  {
    fprintf(stderr, "[%d][%s] Cannot access file : %s\n%s\n", __LINE__, __FILE__, path, strerror(errno));
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

    fprintf(stderr, "[%d] Unable to get file info of : %s\n%s\n", __LINE__, path, strerror(errno));
  }

  return NULL;
}

