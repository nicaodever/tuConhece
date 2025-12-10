#ifndef UTILS_H
#define UTILS_H

// Cores ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

void titulo(const char *t);
void linha();
void pausa();
void trim_newline(char *str);

#endif

