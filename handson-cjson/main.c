#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON/cJSON.h"

int main(int argc, char* argv[]) {
  cJSON *root = cJSON_CreateObject(), *arr, *item; 

  cJSON_AddNumberToObject(root, "count", 1);
  cJSON_AddItemToObject(root, "items", arr = cJSON_CreateArray());
  cJSON_AddItemToArray(arr, cJSON_CreateString("こんにちわ世界"));
  cJSON_AddItemToArray(arr, cJSON_CreateFalse());
  cJSON_AddItemToArray(arr, cJSON_CreateNull());
  puts(cJSON_PrintUnformatted(root));
  cJSON_free(root);
  
  root = cJSON_Parse("{\"count\":1, \"items\":[\"こんにちわ世界\",false,null]}");
  arr = cJSON_GetObjectItem(root, "items");
  cJSON_ReplaceItemInArray(arr, 0, cJSON_CreateString("こんにちわ日本"));
  cJSON_ArrayForEach(item, arr) {
    puts(cJSON_Print(item));
  }
  cJSON_free(root);
  return 0;
}