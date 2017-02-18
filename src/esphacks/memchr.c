/*
 * string::find_last_of requires memchr and it's implemented in libc.
 * libc is too big to be loaded in ESP RAM thus one of solutions is to just 
 * copypaste it here.
 * 
 * More details here:
 * https://github.com/pfalcon/esp-open-sdk/issues/213
 */

void* memchr(const void* s, unsigned char c, int n) {
    if (n != 0) {
        const unsigned char *p = s;

        do {
            if (*p++ == c)
                return ((void *)(p - 1));
        } while (--n != 0);
    }
    return 0;
}