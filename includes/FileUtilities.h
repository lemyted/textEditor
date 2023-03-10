// logLongFileError
#define UNABLE_TO_CREATE_FILE "[%d][%s] Unable to create file : %s\n%s\n"
#define CANNOT_ACCESS_FILE "[%d][%s] Cannot access file : %s\n%s\n"
#define UNABLE_TO_GET_FILE_INFO "[%d][%s] Unable to get file info of : %s\n%s\n"
#define CANNOT_READ_FILE "[%d][%s] Cannot read file : %s\n%s\n"
#define UNABLE_TO_DELETE_FILE "[%d][%s] Unable to create file : %s\n%s\n"

// logShortFileError
#define FILE_NOT_FOUND "[%d][%s] File not found : %s\n"
#define FILE_ALREADY_EXISTS "[%d][%s] File already exists : %s\n"
#define FILE_IS_DIRECTORY "[%d][%s] File is directory : %s\n"
#define FILE_NOT_READ_ENTIRELY "[%d][%s] File not read entirely : %s\n"
#define FILE_NOT_WRITTEN_ENTIRELY "[%d][%s] File not written entirely : %s\n"
#define PATH_IS_NOT_DIRECTORY "[%d][%s] Path is not directory : %s\n"

// Operations
int createNewFile(char *path);

char *readFile(char *path);

int updateFile(char *path, char *content);

int deleteFile(char *path);

int copyFile(char *originalPath, char *copyPath);

int moveFile(char *srcPath, char *destPath);

// Utilities
void logLongFileError(char *msg, char *path, int line, char *file);

void logShortFileError(char *msg, char *path, int line, char *file);

int fileExists(char *path);

struct stat *getFileInfo(char *path);

int isDir(struct stat *info);

off_t getSize(struct stat *info);
