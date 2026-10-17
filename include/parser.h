#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cJSON.h>
#include <unistd.h>

char* read_file_to_string(const char *filename);
cJSON *Parse_json(const char *filename);

