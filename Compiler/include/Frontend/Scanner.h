#ifndef _SCANNER_H
#define _SCANNER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <Frontend/Common.h>
#include <Frontend/Token.h>

void init_keywords_table();
Token *scan(const char *filename, uint64 *token_count_out);

#ifdef __cplusplus
}
#endif

#endif /* _SCANNER_H */