#include "../includes/Main.h"

// Only for the tests
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <time.h>

#define FILE_1 "resources/testFile1.txt"
#define FILE_2 "resources/testFile2.txt"
#define FILE_3 "resources/testFile3.txt"
#define FILE_4 "resources/testFile4.txt"
#define FILE_5 "resources/testFile5.txt"

#define COPY_FILE_1 "resources/testFile1_copy.txt"
#define MOVE_FILE_1 "resources/testFolder1/testFile1.txt"

#define NEW_FILE "resources/newTestFile%ld.txt2"
#define FAKE_FILE_1 "resources/nonExistantTestFile1.txt"

#define DIRECTORY_1 "resources"
#define FAKE_DIRECTORY_1 "nonExistantResources/"


// Operations

void test_whenFileExists_createNewFile_error(void) 
{
  CU_ASSERT_EQUAL(createNewFile(FILE_1), -1);
}
void test_whenFileDoesntExist_createNewFile_noError(void) 
{
  char path[50];
  sprintf(path, NEW_FILE, time(NULL));
  CU_ASSERT_EQUAL(createNewFile(path), 0);
}

//

void test_whenFileExists_readFile_returnsContent(void) 
{
  char *content = readFile(FILE_2);
  char expected[] = "123 5\0";
  CU_ASSERT_STRING_EQUAL(content, expected);
  free(content);
}
void test_whenFileWithNewLineExists_readFile_returnsContent(void) 
{
  char *content = readFile(FILE_3);
  char expected[] = "123 5\n7 9\0";
  CU_ASSERT_STRING_EQUAL(content, expected);
  free(content);
}
void test_whenFileDoesntExist_readFile_returnsNull(void) 
{
  CU_ASSERT_PTR_NULL(readFile(FAKE_FILE_1));
}
void test_whenDirectoryExists_readFile_returnsNull(void) 
{
  CU_ASSERT_PTR_NULL(readFile(DIRECTORY_1));
}
void test_whenDirectoryDoesntExist_readFile_returnsNull(void) 
{
  CU_ASSERT_PTR_NULL(readFile(FAKE_DIRECTORY_1));
}

//

void test_whenFileExists_updateFile_fileUpdated(void) 
{
  char content1[] = "content1\0";
  char content2[] = "content2\0";
  char *res1, *res2;
  CU_ASSERT_EQUAL(updateFile(FILE_4, content1), 0);
  res1 = readFile(FILE_4);
  CU_ASSERT_STRING_EQUAL(res1, content1);
  CU_ASSERT_EQUAL(updateFile(FILE_4, content2), 0);
  res2 = readFile(FILE_4);
  CU_ASSERT_STRING_EQUAL(res2, content2);
  free(res1);
  free(res2);
}
void test_whenFileDoesntExist_updateFile_error(void) 
{
  char content1[] = "content1\0";
  CU_ASSERT_EQUAL(updateFile(FAKE_FILE_1, content1), -1);
}
void test_whenDirectoryExists_updateFile_error(void) 
{
  char content1[] = "content1\0";
  CU_ASSERT_EQUAL(updateFile(DIRECTORY_1, content1), -1);
}
void test_whenDirectoryDoesntExist_updateFile_error(void) 
{
  char content1[] = "content1\0";
  CU_ASSERT_EQUAL(updateFile(FAKE_DIRECTORY_1, content1), -1);
}

//

void test_whenFileExists_deleteFile_fileDeleted(void) 
{
  CU_ASSERT_EQUAL(createNewFile(FILE_5), 0);
  CU_ASSERT_EQUAL(deleteFile(FILE_5), 0);
  CU_ASSERT_PTR_NULL(readFile(FILE_5));
}
void test_whenFileDoesntExist_deleteFile_error(void) 
{
  CU_ASSERT_EQUAL(deleteFile(FAKE_FILE_1), -1);
}
void test_whenDirectoryExists_deleteFile_error(void) 
{
  CU_ASSERT_EQUAL(deleteFile(DIRECTORY_1), -1);
}
void test_whenDirectoryDoesntExist_deleteFile_error(void) 
{
  CU_ASSERT_EQUAL(deleteFile(FAKE_DIRECTORY_1), -1);
}

//

void test_whenOriginalFileExists_copyFile_fileCopied(void) 
{
  CU_ASSERT_EQUAL(copyFile(FILE_1, COPY_FILE_1), 0);
  CU_ASSERT_EQUAL(deleteFile(COPY_FILE_1), 0);
}
void test_whenOriginalFileDoesntExists_copyFile_error(void) 
{
  CU_ASSERT_EQUAL(copyFile(FAKE_FILE_1, COPY_FILE_1), -1);
}
void test_whenCopyFileExists_copyFile_error(void) 
{
  CU_ASSERT_EQUAL(copyFile(FILE_1, FILE_2), -1);
}

//

void test_whenOriginalFileExists_moveFile_fileMoved(void) 
{
  char *content;
  CU_ASSERT_EQUAL(moveFile(FILE_1, MOVE_FILE_1), 0);
  content = readFile(MOVE_FILE_1);
  CU_ASSERT_PTR_NOT_NULL(content);
  CU_ASSERT_PTR_NULL(readFile(FILE_1));
  CU_ASSERT_EQUAL(moveFile(MOVE_FILE_1, FILE_1), 0);
  content = readFile(FILE_1);
  CU_ASSERT_PTR_NOT_NULL(content);
  CU_ASSERT_PTR_NULL(readFile(MOVE_FILE_1));
  free(content);
}

// Utilities

void test_ifFileExists_fileExists_true(void) 
{
  CU_ASSERT_TRUE(fileExists(FILE_1));
}
void test_ifNotFileExists_fileExists_false(void) 
{
  CU_ASSERT_FALSE(fileExists(FAKE_FILE_1));
}

void test_whenFileDoesntExist_getFileInfo_error(void)
{
  struct stat *info = getFileInfo(FAKE_FILE_1);
  CU_ASSERT_EQUAL(info, NULL);
  free(info);
}
void test_whenFileExist_getFileInfo_noError(void)
{
  struct stat *info = getFileInfo(FILE_1);
  CU_ASSERT_NOT_EQUAL(info, NULL);
  free(info);
}

void test_whenFileIsDirectory_isDir_true(void) 
{
  struct stat *info = getFileInfo(DIRECTORY_1);
  CU_ASSERT_TRUE(isDir(info));
  free(info);
}
void test_whenFileIsNotDirectory_isDir_false(void) 
{
  struct stat *info = getFileInfo(FILE_1);
  CU_ASSERT_FALSE(isDir(info));
  free(info);
}

void test_whenFile_getSize_returnSize(void) 
{
  struct stat *info = getFileInfo(FILE_2);
  CU_ASSERT_EQUAL(getSize(info), 5);
  free(info);
}

int main(void) 
{
  CU_initialize_registry();
  
  // Operations
  CU_pSuite suite_createNewFile = CU_add_suite("createNewFile", NULL, NULL);
  CU_add_test(suite_createNewFile, "test_whenFileExists_createNewFile_error", test_whenFileExists_createNewFile_error);
  CU_add_test(suite_createNewFile, "test_whenFileDoesntExist_createNewFile_noError", test_whenFileDoesntExist_createNewFile_noError);

  CU_pSuite suite_readFile = CU_add_suite("readFile", NULL, NULL);
  CU_add_test(suite_readFile, "test_whenFileExists_readFile_returnsContent", test_whenFileExists_readFile_returnsContent);
  CU_add_test(suite_readFile, "test_whenFileWithNewLineExists_readFile_returnsContent", test_whenFileWithNewLineExists_readFile_returnsContent);
  CU_add_test(suite_readFile, "test_whenFileDoesntExist_readFile_returnsNull", test_whenFileDoesntExist_readFile_returnsNull);
  CU_add_test(suite_readFile, "test_whenDirectoryExists_readFile_returnsNull", test_whenDirectoryExists_readFile_returnsNull);
  CU_add_test(suite_readFile, "test_whenDirectoryDoesntExist_readFile_returnsNull", test_whenDirectoryDoesntExist_readFile_returnsNull);

  CU_pSuite suite_updateFile = CU_add_suite("updateFile", NULL, NULL);
  CU_add_test(suite_updateFile, "test_whenFileExists_updateFile_fileUpdated", test_whenFileExists_updateFile_fileUpdated);
  CU_add_test(suite_updateFile, "test_whenFileDoesntExist_updateFile_error", test_whenFileDoesntExist_updateFile_error);
  CU_add_test(suite_updateFile, "test_whenDirectoryExists_updateFile_error", test_whenDirectoryExists_updateFile_error);
  CU_add_test(suite_updateFile, "test_whenDirectoryDoesntExist_updateFile_error", test_whenDirectoryDoesntExist_updateFile_error);
  
  CU_pSuite suite_deleteFile = CU_add_suite("deleteFile", NULL, NULL);
  CU_add_test(suite_deleteFile, "test_whenFileExists_deleteFile_fileDeleted", test_whenFileExists_deleteFile_fileDeleted);
  CU_add_test(suite_deleteFile, "test_whenFileDoesntExist_deleteFile_error", test_whenFileDoesntExist_deleteFile_error);
  CU_add_test(suite_deleteFile, "test_whenDirectoryExists_deleteFile_error", test_whenDirectoryExists_deleteFile_error);
  CU_add_test(suite_deleteFile, "test_whenDirectoryDoesntExist_deleteFile_error", test_whenDirectoryDoesntExist_deleteFile_error);

  CU_pSuite suite_copyFile = CU_add_suite("copyFile", NULL, NULL);
  CU_add_test(suite_copyFile, "test_whenOriginalFileExists_copyFile_fileCopied", test_whenOriginalFileExists_copyFile_fileCopied);
  CU_add_test(suite_copyFile, "test_whenOriginalFileDoesntExists_copyFile_error", test_whenOriginalFileDoesntExists_copyFile_error);
  CU_add_test(suite_copyFile, "test_whenCopyFileExists_copyFile_error", test_whenCopyFileExists_copyFile_error);

  CU_pSuite suite_moveFile = CU_add_suite("moveFile", NULL, NULL);
  CU_add_test(suite_moveFile, "test_whenOriginalFileExists_moveFile_fileMoved", test_whenOriginalFileExists_moveFile_fileMoved);

  // Utilities
  CU_pSuite suite_fileExists = CU_add_suite("fileExists", NULL, NULL);
  CU_add_test(suite_fileExists, "test_ifFileExists_fileExists_true", test_ifFileExists_fileExists_true);
  CU_add_test(suite_fileExists, "test_ifNotFileExists_fileExists_false", test_ifNotFileExists_fileExists_false); 

  CU_pSuite suite_getFileInfo = CU_add_suite("getFileInfo", NULL, NULL);
  CU_add_test(suite_getFileInfo, "test_whenFileDoesntExist_getFileInfo_error", test_whenFileDoesntExist_getFileInfo_error);
  CU_add_test(suite_getFileInfo, "test_whenFileExist_getFileInfo_noError", test_whenFileExist_getFileInfo_noError);

  CU_pSuite suite_isDir = CU_add_suite("isDir", NULL, NULL);
  CU_add_test(suite_isDir, "test_whenFileIsDirectory_isDir_true", test_whenFileIsDirectory_isDir_true);
  CU_add_test(suite_isDir, "test_whenFileIsNotDirectory_isDir_false", test_whenFileIsNotDirectory_isDir_false);

  CU_pSuite suite_getSize = CU_add_suite("getSize", NULL, NULL);
  CU_add_test(suite_getSize, "test_whenFile_getSize_returnSize", test_whenFile_getSize_returnSize);

  CU_basic_run_tests();
  CU_cleanup_registry();
}