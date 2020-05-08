#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON/cJSON.h"

int main(int argc, char* argv[]) {
  cJSON *root = cJSON_CreateObject(), *arr, *item; 

  // cJSON_AddNumberToObject(root, "count", 1);
  // cJSON_AddItemToObject(root, "items", arr = cJSON_CreateArray());
  // cJSON_AddItemToArray(arr, cJSON_CreateString("こんにちわ世界"));
  // cJSON_AddItemToArray(arr, cJSON_CreateFalse());
  // cJSON_AddItemToArray(arr, cJSON_CreateNull());
  // puts(cJSON_PrintUnformatted(root));
  // cJSON_free(root);
  
  char *plaintext = "{\"v\":1,\"ts\":1584418939,\"mn\":[{\"id\":\"17458217\",\"na\":\"mornin' 1\",\"ic\":113,\"ak\":\"63d295423dca65f549150aa86b8548c9\",\"re\":false},{\"id\":\"8340e903\",\"na\":\"mornin' 2\",\"ic\":114,\"ak\":\"0b6df901c7f1edc87ec3052c90282cb0\",\"re\":false}]}";
  root = cJSON_Parse(plaintext);
  arr = cJSON_GetArrayItem(root, "mn");
  printf("%s", arr->valuestring);
  cJSON_ReplaceItemInArray(arr, 0, cJSON_CreateString("こんにちわ日本"));
  cJSON_ArrayForEach(item, arr) {
    puts(cJSON_Print(item));
  }
  cJSON_free(root);
  return 0;
}