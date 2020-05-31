#ifndef LOGGER
#define LOGGER

#define INFO_TAG "INFO"
#define ERROR_TAG "ERROR"
#define WARNING_TAG "WARN"
int init_log();
void logger(char*, char*);
void cleanup_log();

#endif
