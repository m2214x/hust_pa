#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

void add_string(char *s, char *str, int *len) {
  while (*str) {
    s[(*len)++] = *str++;
  }
}

void add_char(char *s, char c, int *len) {
  s[(*len)++] = c;
}

void add_number(char *s, int num, int *len) {
  if (num == 0) {
    add_char(s, '0', len);
    return;
  }
  char buf[100];
  int i = 0;
  while (num) {
    buf[i++] = num % 10 + '0';
    num /= 10;
  }
  for (int j = i - 1; j >= 0; j--) {
    add_char(s, buf[j], len);
  }
}

int is_digit(char c) {
  return c >= '0' && c <= '9';
}

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  char buf[1000];
  int length=vsprintf(buf,fmt,ap);
  buf[length]='\0';
  for(int i=0;i<length;i++){
    _putc(buf[i]);
  }
  va_end(ap);
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *s = out;
  int len = 0;
  while(*fmt) {
    if (*fmt == '%') {
      fmt++;
      if (*fmt == 's') {
        char *str = va_arg(ap, char *);
        add_string(s, str, &len);
      } else if (*fmt == 'c') {
        char c = va_arg(ap, int);
        add_char(s, c, &len);
      } else if (*fmt == 'd') {
        int num = va_arg(ap, int);
        add_number(s, num, &len);
      }
    } else {
      add_char(s, *fmt, &len);
    }
    fmt++;
  }
  return len;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  int length=vsprintf(out,fmt,ap);
  va_end(ap);
  return length;
  return 0;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif