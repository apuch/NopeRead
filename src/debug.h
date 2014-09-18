#ifndef DEBUG_H
#define DEBUG_H

/** \brief Generic error return code */
enum DebugCode_t {
    /** \brief all okay, nothing happened */
    E_OK = 0,
    /** \brief generic error, dont try to use it to often */
    E_ERROR = -1,
    /** \brief invalid argument .. NULL-pointer and such */
    E_ARGUMENT = -2,
    /** \brief out of range */
    E_RANGE = -3,
    /** \brief alignment is wrong */
    E_ALIGNMENT = -4,
};

void _debug_tr_log(const char* file, int line, int level, const char* msg, ...);

#define LOG_LEVEL_NONE  0
#define LOG_LEVEL_CRIT  1
#define LOG_LEVEL_ERR   2
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_DEBUG 4
#define LOG_LEVEL_SPAM  5

#ifndef LOG_LEVEL
    #ifndef LOG_LEVEL_DEF
    #define LOG_LEVEL LOG_LEVEL_INFO
    #else
    #define LOG_LEVEL LOG_LEVEL_DEF
    #endif
#endif

#define __TRACE(lvl, ...) \
    _debug_tr_log( __FILE__, __LINE__, lvl, __VA_ARGS__)

#if LOG_LEVEL >= 1
#define TR_CRIT(...) __TRACE(1, __VA_ARGS__)
#else 
#define TR_CRIT(...)
#endif

#if LOG_LEVEL >= 2
#define TR_ERR(...) __TRACE(2, __VA_ARGS__)
#else 
#define TR_ERR(...)
#endif

#if LOG_LEVEL >= 3
#define TR_INFO(...) __TRACE(3, __VA_ARGS__)
#else 
#define TR_INFO(...)
#endif

#if LOG_LEVEL >= 4
#define TR_DEBUG(...) __TRACE(4, __VA_ARGS__)
#else 
#define TR_DEBUG(...)
#endif

#if LOG_LEVEL >= 5
#define TR_SPAM(...) __TRACE(5, __VA_ARGS__)
#else 
#define TR_SPAM(...)
#endif


#endif

