#ifndef cstring_h
#define cstring_h

#include <stdint.h>
#include <stddef.h>

#define CSTRING_PERMANENT 1
#define CSTRING_INTERNING 2
#define CSTRING_ONSTACK 4

#define CSTRING_INTERNING_SIZE 32
#define CSTRING_STACK_SIZE 128

struct cstring_data {
	char * cstr;
	uint32_t hash_size;
	uint16_t type;
	uint16_t ref;
};

typedef struct _cstring_buffer {
	struct cstring_data * str;
} cstring_buffer[1];

typedef struct cstring_data * cstring;

#define CSTRING_BUFFER(var) \
	char var##_cstring [CSTRING_STACK_SIZE] = { '\0' };	\
	struct cstring_data var##_cstring_data = { var##_cstring , 0, CSTRING_ONSTACK, 0 };	\
	cstring_buffer var;	\
	var->str = &var##_cstring_data;

#define CSTRING_LITERAL(var, cstr)	\
	static cstring var = NULL;	\
	if (var) {} else {	\
		cstring tmp = cstring_persist(""cstr, (sizeof(cstr)/sizeof(char))-1);	\
		if (!__sync_bool_compare_and_swap(&var, NULL, tmp)) {	\
			cstring_free_persist(tmp);	\
		}	\
	}

#define CSTRING(s) ((s)->str)

#define CSTRING_CLOSE(var) \
	if ((var)->str->type != 0) {} else \
		cstring_release((var)->str);

/* low level api, don't use directly */
cstring cstring_persist(const char * cstr, size_t sz);
void cstring_free_persist(cstring s);

/* public api */
cstring cstring_grab(cstring s);
void cstring_release(cstring s);
cstring cstring_cat(cstring_buffer sb, const char * str);
cstring cstring_printf(cstring_buffer sb, const char * format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;
int cstring_equal(cstring a, cstring b);
uint32_t cstring_hash(cstring s);

#endif


