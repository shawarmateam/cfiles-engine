#ifndef FE_SETTINGS_H
#define FE_SETTINGS_H

#include <iostream>

// settings for fe-kernel
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define LOG_LEVEL_INFO



#define RED "\033[31m"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define logftl(msg) std::cerr << RED "FE_FATAL: " << msg << RESET << std::endl
#define logerr(msg) std::cerr << RED "FE_ERROR: " << RESET << msg << std::endl

// define log function, if LOG_LEVEL_INFO is defined, it will be a normal log, otherwise it will be a no-op
#ifdef LOG_LEVEL_INFO
#define log(msg) std::cout << BLUE "INFO: " << msg << RESET << std::endl
#else
#define log(msg)
#endif

#endif // FE_SETTINGS_H