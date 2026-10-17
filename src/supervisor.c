#include "signals.h"
#include "types.h"
#include "supervisor.h"
#include "process.h"
#include "parser.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool should_stop(void)
{
    // terminate or not
    if (shutdown_req) 
    {
        shutdown_req = 0;
        return true;
    }
    
    return false;
}

bool create_processes(const cJSON *json_data, process *p, size_t *count)
{
    cJSON *processes = cJSON_GetObjectItemCaseSensitive(json_data, "processes");

    if (cJSON_IsArray(processes)) 
    {
        int total = cJSON_GetArraySize(processes);

        if (total < 0 || total > MAX_PROCESSES) 
        {
            printf("Error: number of processes exceeds limit\n");
            return false;
        }

        *count = 0;

        cJSON *json_process = NULL;

        cJSON_ArrayForEach(json_process, processes) 
        {
            // add process name
            cJSON *name = cJSON_GetObjectItemCaseSensitive(json_process, "name");
            if (cJSON_IsString(name) && (name->valuestring != NULL)) 
            {
                p[*count].name = strdup(name->valuestring);

                if(p[*count].name == NULL)
                {
                    printf("Error : strdup failed");

                    free(p[*count].argv);
                    p[*count].name = NULL;
                    return false;
                }
            }
            else
            {
                printf("Error : Process name must be of type stirng, check json config\n");
                return false;
            }

            // add process max restarts
            cJSON *max_restart = cJSON_GetObjectItemCaseSensitive(json_process, "max_restarts");
            if (cJSON_IsNumber(max_restart) && max_restart->valueint > 0) 
            {
                p[*count].max_restart = max_restart->valueint;
            }
            else
            {  
                printf("Error : max_restarts must be a positive integer, check json conifg\n");
                return false;
            }

            // add process arguments
            cJSON *argv = cJSON_GetObjectItemCaseSensitive(json_process, "argv");
            if(cJSON_IsArray(argv))
            {
                cJSON *arg = NULL;

                size_t size = cJSON_GetArraySize(argv);

                p[*count].argv = calloc((size + 1), sizeof(*p[*count].argv)); // size + 1 for null termination

                // check if calloc succeeded 
                if (p[*count].argv == NULL) 
                {
                    printf("Error: calloc allocation failed\n");
                    return false;
                }

                int j = 0;

                cJSON_ArrayForEach(arg, argv)
                {
                    if(!cJSON_IsString(arg) || arg->valuestring == NULL) 
                    {
                        printf("Error : All arguments in argv must be of type string, check json config\n");

                        for(int k = 0; k < j; k++)
                        {
                            free(p[*count].argv[k]);
                        }

                        free(p[*count].argv);
                        return false;
                    }

                    p[*count].argv[j] = strdup(arg->valuestring);

                    if(p[*count].argv[j] == NULL)
                    {
                        printf("Error : strdup failed");

                        // clean up argv
                        for(int k = 0; k < j; k++)
                        {
                            free(p[*count].argv[k]);
                        }

                        free(p[*count].argv);
                        p[*count].argv = NULL;

                        return false;
                    }

                    j++;
                }
            }
            else
            {
                printf("Error : A process must have and argv, check json config");
                return false;
            }

            (*count)++;
        }
        
    }
    else
    {
        printf("Error : Invalid json syntax\n");
        return false;
    }

    return true;
}

int sup_init(char* argv[], process *p)
{
    printf("%d \n", getpid());

    install_sigterm();

    const char *filename = argv[1];

    cJSON *json_data = Parse_json(filename);

    if(json_data == NULL)
    {
        printf("Error : json parsing failed\n");
        return -1;
    }

    size_t p_size = 0;

    if(!create_processes(json_data, p, &p_size))
    {
        printf("Error : process creation failed");
        cJSON_Delete(json_data);
        exit_cleanup(p, p_size);
        return -1;
    }

    cJSON_Delete(json_data);

    return (int)p_size;
}

void exit_cleanup(process *p, int p_size)
{
    for(int i = 0; i < p_size; i++)
    {
        int j = 0;
        while(p[i].argv[j] != NULL)
        {
            free(p[i].argv[j]);
            j++;
        }

        free(p[i].argv);
        free(p[i].name);

        p[i].argv = NULL;
        p[i].name = NULL;

    }

    
}
