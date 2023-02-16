#include "../includes/Main.h"

// Only for the tests
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <time.h>

#define FILE_1 "resources/testFile1.txt"
#define FAKE_FILE_1 "resources/nonExistantTestFile1.txt"

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

// void test_whenFileExist_createNewFile_error(void) 
// {
//   CU_ASSERT_EQUAL(createNewFile("resources/testFile1.txt"), -1);
// }

// void test_whenFileDoesntExist_createNewFile_noError(void) 
// {
//   char path[50];
//   sprintf(path, "resources/newTestFile%ld.txt", time(NULL));
//   CU_ASSERT_EQUAL(createNewFile(path), 0);
// }

// void test_whenFileIsDir_isDir_true(void) 
// {
//   struct stat *info = getFileInfo("resources/");
//   CU_ASSERT_TRUE(isDir(info));
//   free(info);
// }

// void test_whenFileIsNotDir_isDir_false(void) 
// {
//   struct stat *info = getFileInfo("resources/");
//   CU_ASSERT_FALSE(isDir(info));
//   free(info);
// }

int main(void) 
{
  CU_initialize_registry();

  // Utilities
  CU_pSuite suite_fileExists = CU_add_suite("fileExists", NULL, NULL);
  CU_add_test(suite_fileExists, "test_ifFileExists_fileExists_true", test_ifFileExists_fileExists_true);
  CU_add_test(suite_fileExists, "test_ifNotFileExists_fileExists_false", test_ifNotFileExists_fileExists_false); 

  CU_pSuite suite_getFileInfo = CU_add_suite("getFileInfo", NULL, NULL);
  CU_add_test(suite_getFileInfo, "test_whenFileDoesntExist_getFileInfo_error", test_whenFileDoesntExist_getFileInfo_error);
  CU_add_test(suite_getFileInfo, "test_whenFileExist_getFileInfo_noError", test_whenFileExist_getFileInfo_noError);

  // CU_pSuite suite_createNewFile = CU_add_suite("createNewFile", NULL, NULL);
  // CU_add_test(suite_createNewFile, "test_whenFileExist_createNewFile_error", test_whenFileExist_createNewFile_error);
  // CU_add_test(suite_createNewFile, "test_whenFileDoesntExist_createNewFile_noError", test_whenFileDoesntExist_createNewFile_noError);

  // CU_pSuite suite_isDir = CU_add_suite("isDir", NULL, NULL);
  // CU_add_test(suite_isDir, "test_whenFileIsDir_isDir_true", test_whenFileIsDir_isDir_true);
  // CU_add_test(suite_isDir, "test_whenFileIsDir_isDir_true", test_whenFileIsNotDir_isDir_false);

  CU_basic_run_tests();
  CU_cleanup_registry();
}