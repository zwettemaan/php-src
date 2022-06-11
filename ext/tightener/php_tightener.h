/* tightener extension for PHP */

#ifndef PHP_TIGHTENER_H
# define PHP_TIGHTENER_H

#ifdef PHP_WIN32
#define IS_WINDOWS   1
#define IS_BSD       0
#define IS_MACINTOSH 0
#define IS_SOLARIS   0
#define IS_LINUX     0
#elif defined(BSD) || defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#define IS_WINDOWS   0
#define IS_BSD       1
#define IS_MACINTOSH 0
#define IS_SOLARIS   0
#define IS_LINUX     0
#elif defined(__APPLE__) || defined(__MACH__)
#define IS_WINDOWS   0
#define IS_BSD       0
#define IS_MACINTOSH 1
#define IS_SOLARIS   0
#define IS_LINUX     0
#elif defined(__sun__)
#define IS_WINDOWS   0
#define IS_BSD       0
#define IS_MACINTOSH 0
#define IS_SOLARIS   1
#define IS_LINUX     0
#elif defined(__linux__)
#define IS_WINDOWS   0
#define IS_BSD       0
#define IS_MACINTOSH 0
#define IS_SOLARIS   0
#define IS_LINUX     1
#else
#error Unknown
#endif

extern zend_module_entry tightener_module_entry;
# define phpext_tightener_ptr &tightener_module_entry

# define PHP_TIGHTENER_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_TIGHTENER)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_TIGHTENER_H */
