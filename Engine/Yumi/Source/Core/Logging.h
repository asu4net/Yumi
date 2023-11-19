#pragma once
#include <iostream>
#include <cstdio>

//TODO: Add date/time at the log beginning
//TODO: Add final config without logs and stats
//TODO: Set logging levels

#define YLOG(...) \
    printf("Yumi Engine: "); \
    printf(__VA_ARGS__)

#define YLOG_TRACE(...) \
    printf("\x1B[96m"); \
    YLOG(__VA_ARGS__); \
    printf("\033[0m")

#define YLOG_WARN(...) \
    printf("\x1B[93m"); \
    YLOG(__VA_ARGS__); \
    printf("\033[0m")

#define YLOG_ERR(...) \
    printf("\x1B[91m"); \
    YLOG(__VA_ARGS__); \
    printf("\033[0m")

#define YCHECK(_CONDITION, ...) \
    if (!_CONDITION) { YLOG_ERR(__VA_ARGS__); __debugbreak(); }