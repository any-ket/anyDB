#ifndef COMMON_H
#define COMMON_H

#include <_types/_uint8_t.h>
#include <string>
#include <ctype.h>
#include <cctype>

#define SERVER_PORT 8081

typedef struct {
  char tableName[];
} CreateTableReq;

typedef struct {
  uint8_t opcode;
  char data[];
} ClientRequest;


#define hexdump(ptr, buflen) do { \
  unsigned char *buf = (unsigned char*)(ptr); \
  int i, j; \
  for (i = 0; i < (buflen); i += 16) { \
    printf("%06x: ", i); \
    for (j = 0; j < 16; j++) { \
      if (i + j < (buflen)) \
        printf("%02x ", buf[i + j]); \
      else \
        printf("   "); \
    } \
    printf(" "); \
    for (j = 0; j < 16; j++) { \
      if (i + j < (buflen)) \
        printf("%c", isprint(buf[i + j]) ? buf[i + j] : '.'); \
    } \
    printf("\n"); \
  } \
} while (0);

#endif