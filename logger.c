#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// File handle to log file
FILE *log_file;

// log_flag is used to ensure the succesful creation of logfile before attempting to 
// log info or clean up the logger
int log_flag = -1;

// Initialize the logger
int init_log()
{
	// Get user's $PWD value
	char* current_path;
	current_path = getenv("PWD");
	// To get current time stamp
	time_t now;
   	time(&now);
	
	// If $HOME was fetched start logging else inform about the failure in log file
	if(current_path != NULL)
	{
		// Log to the same directory where crawler exists
		char* log_file_path = "/.log";
		strcat(current_path, log_file_path);
		log_file = fopen(current_path, "a");

		// If log_file was not created issue a warning to the user else begin logging
		if(log_file)
		{
   			fprintf(log_file, "%s[%s]: %s", ctime(&now), INFO_TAG, "Logging into ");
			fprintf(log_file, "%s", current_path);
			fprintf(log_file, "%s", "...\n");
			log_flag = 0;
			return 0;
		}
		else
		{
			printf("[WARN] Log file can't be created, check file path\n\n");
			log_flag = 1;
			return 1;
		}
	}
	log_flag = 1;
   	logger(ERROR_TAG, "`$PWD` returned NULL, Can't log");
	fclose(log_file);
	return 1;
}

void logger(char* tag, char* message)
{
	// If log_flag is 0, log file was succesfully created
	if(log_flag == 0)
	{
   		fprintf(log_file, "[%s]: %s\n", tag, message);
	}
	else if(log_flag == -1)
	{
		printf("[WARN] Please initialize the log file using init_log()\n\n");
	}
}

void cleanup_log()
{
	// If log_flag is 0, log file was succesfully created
	// Separate logs by --- and close the file handle
	if(log_flag == 0)
	{
		fprintf(log_file, "\n\n%s\n\n", "-------------------------------------------------------------------\n");
		fclose(log_file);
	}
}
