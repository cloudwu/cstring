#include "cstring.h"

#include <stdio.h>

static cstring
foo(cstring t) {
	CSTRING_LITERAL(hello, "hello");
	CSTRING_BUFFER(ret);
	if (cstring_equal(hello,t)) {
		cstring_cat(ret, "equal");
	} else {
		cstring_cat(ret, "not equal");
	}
	return cstring_grab(CSTRING(ret));
}

static void
test() {
	CSTRING_BUFFER(a);
	cstring_printf(a, "%s", "hello");
	cstring b = foo(CSTRING(a));
	printf("%s\n", b->cstr);
	cstring_printf(a, "very long string %01024d",0);
	printf("%s\n", CSTRING(a)->cstr);
	CSTRING_CLOSE(a);
	cstring_release(b);
}

int
main() {
	test();
	return 0;
}
