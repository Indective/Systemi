#include "parser.h"

char* read_file_to_string(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file) 
    {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // +1 for null-terminator
    char *buffer = malloc(length + 1);

    if (!buffer) 
    {
        printf("Error: Memory allocation failed\n");
        
        fclose(file);
        free(buffer);
        return NULL;
    }

    // Read the file into the buffer
    size_t read_bytes = fread(buffer, 1, length, file);

    if(feof(file))
    {
        buffer[read_bytes] = '\0';
        
        fclose(file);
        return buffer;
    }
    else if (ferror(file)) 
    {
        perror("An error occurred while reading the file");
        
        fclose(file);
        free(buffer);
        return NULL;
    }

    fclose(file);
    return buffer;
}

cJSON *Parse_json(const char *filename)
{
    char *string_data = read_file_to_string(filename);

    if (!string_data) 
    {
        printf("Error : JSON file empty\n");
        
        free(string_data);
        return NULL;
    }

    // 2. Parse the string into a cJSON object structure
    cJSON *json_data = cJSON_Parse(string_data);

    if (!json_data) 
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) 
        {
            printf("Error before: %s\n", error_ptr);
        }

        free(string_data);
        return NULL;
    }

    return json_data;
}


