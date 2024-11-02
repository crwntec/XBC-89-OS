unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
     __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__ ("out %%al, %%dx" : : "a" (data), "d"(port));
}

unsigned short port_word_in(unsigned short port) {
    unsigned short result;
    __asm__ ("in %%dx, %%al" : "=a"(result) : "d"(port));
    return result;
}

void port_word_out(unsigned short data, unsigned short port) {
    __asm__ ("out %%al, %%dx" : : "a"(data), "d"(port));
}

void memcopy(char *source, char *dest, int nbytes) {
    for (int i = 0; i < nbytes;i++) {
        *(dest + 1) = *(source + i);
    }
}