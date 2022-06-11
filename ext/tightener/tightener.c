/* tightener extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../../Zend/zend_API.h"

#include "php.h"
#include "ext/standard/info.h"
#include "php_tightener.h"
#include "tightener_arginfo.h"

#if IS_LINUX
#include "dlfcn.h"
#else
#error Not yet supported
#endif

#define OP_CODE_NONE                        0
#define OP_CODE_ADVANCE_HOST_MESSAGE_QUEUE  1
#define OP_CODE_ADVANCE_LOG_MESSAGE_QUEUE   2
#define OP_CODE_GET_HOST_NAME               3
#define OP_CODE_GET_HOST_MESSAGE            4
#define OP_CODE_GET_HOST_MESSAGE_QUEUE_SIZE 5
#define OP_CODE_GET_LOG_MESSAGE             6
#define OP_CODE_GET_LOG_MESSAGE_QUEUE_SIZE  7
#define OP_CODE_REGISTER_LOCAL_HOST_NAME    8
#define OP_CODE_RELAY_HOST_MESSAGE          9
#define OP_CODE_INIT                       10
#define OP_CODE_TIMESLICE                  11

typedef struct APIData {
    const char *fString;
    size_t fSize;
} APIData;

#define FILEPATH_DLL "TightenerDLL/Linux_x64/libTightenerDLL.so"

typedef void DLLEntryPoint(char opCode, APIData *apiData, APIData *apiData2);

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void test1() */
PHP_FUNCTION(test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "tightener");
}
/* }}} */

/* {{{ string test2( [ string $var ] ) */
PHP_FUNCTION(test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(tightener)
{
#if defined(ZTS) && defined(COMPILE_DL_TIGHTENER)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

#if _WINDLL
    HINSTANCE hDLLEntryPoint = LoadLibraryA(FILEPATH_DLL);
#else
    void* hDLLEntryPoint = dlopen(FILEPATH_DLL, RTLD_LAZY);
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(tightener)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tightener support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ tightener_module_entry */
zend_module_entry tightener_module_entry = {
	STANDARD_MODULE_HEADER,
	"tightener",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(tightener),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(tightener),			/* PHP_MINFO - Module info */
	PHP_TIGHTENER_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TIGHTENER
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(tightener)
#endif
