// Operations
int createNewFile(char *path);

char *readFile(char *path);

int updateFile(char *path, char *content);

int deleteFile(char *path);

int copyFile(char *originalPath, char *copyPath);


// Utilities
int fileExists(char *path);

struct stat *getFileInfo(char *path);

int isDir(struct stat *info);

int getSize(struct stat *info);
