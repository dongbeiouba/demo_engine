#include <stdio.h>
#include <openssl/engine.h>

static const char *engine_id = "demo";
static const char *engine_name = "A demo engine";

static int bind(ENGINE *e, const char *id)
{
    int ret = 0;

    if (!ENGINE_set_id(e, engine_id)) {
        fprintf(stderr, "ENGINE_set_id failed\n");
        goto end;
    }

    if (!ENGINE_set_name(e, engine_name)) {
        printf("ENGINE_set_name failed\n");
        goto end;
    }

    ret = 1;
end:
    return ret;
}

IMPLEMENT_DYNAMIC_BIND_FN(bind)
IMPLEMENT_DYNAMIC_CHECK_FN()

/*
gcc -fPIC -o e_demo.o -c e_demo.c -I/usr/local/babassl-share/include
gcc -shared -o e_demo.so -L/usr/local/babassl-share/lib/ -lcrypto e_demo.o

/usr/local/babassl-share/bin/openssl engine -t -c `pwd`/e_demo.so
 */