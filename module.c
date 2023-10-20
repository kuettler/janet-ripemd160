#include <janet.h>

#include "rmd160.h"

JANET_FN(cfun_ripemd160,
         "(ripemd160/ripemd160 message)",
         "Calc ripemd160 hash of the given message.") {
    janet_fixarity(argc, 1);
    const uint8_t* message = janet_getstring(argv, 0);

    dword MDbuf[5]; // contains (A, B, C, D, E)
    dword X[16];    // current 16-word chunk

    // initialize
    MDinit(MDbuf);
    dword length = (dword)janet_string_length(message);

    // process message in 16-word chunks
    for (dword nbytes=length; nbytes > 63; nbytes-=64) {
        for (int i=0; i<16; i++) {
            X[i] = BYTES_TO_DWORD(message);
            message += 4;
        }
        compress(MDbuf, X);
    }

    // finish:
    MDfinish(MDbuf, (char*)message, length, 0);

    int outputlen = 20;
    uint8_t* hashcode = janet_string_begin(outputlen);

    for (int i=0; i<outputlen; i+=4) {
        hashcode[i]   =  MDbuf[i>>2];
        hashcode[i+1] = (MDbuf[i>>2] >>  8);
        hashcode[i+2] = (MDbuf[i>>2] >> 16);
        hashcode[i+3] = (MDbuf[i>>2] >> 24);
    }

    janet_string_end(hashcode);
    return janet_wrap_string(hashcode);
}

JANET_MODULE_ENTRY(JanetTable *env) {
    JanetRegExt cfuns[] = {
        JANET_REG("ripemd160", cfun_ripemd160),
        JANET_REG_END
    };
    janet_cfuns_ext(env, "ripemd160", cfuns);
}
