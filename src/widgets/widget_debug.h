#pragma once

#define WDBG_NONE 0
#define WDBG_ERROR 1
#define WDBG_INFO 2
#define WDBG_DEBUG 3

#ifndef WDBG_LEVEL
    #define WDBG_LEVEL WDBG_NONE
#endif 

#if WDBG_LEVEL >= INFO
    #define dbg(...) printf("%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n");
#else
    #define dbg(...) 
#endif

#if WDBG_LEVEL >= DEBUG
    #define dbg_d(...) printf("%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n");
#else
    #define dbg_d(...) 
#endif

#if WDBG_LEVEL >= ERROR
    #define dbg_e(...) printf("%s:%d ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n");
#else
    #define dbg_e(...) 
#endif
    