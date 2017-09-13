/*
 * universal.h
 *
 *  Created on: Feb 13, 2016
 *      Author: root
 */

#ifndef UNIVERSAL_H_
#define UNIVERSAL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "typesdef.h"

VOID CopyMemory(PBYTE pDest, PBYTE pSource, BYTE nLength);
char* StrDup(const char* string);

#ifdef __cplusplus
}
#endif
}
#endif /* UNIVERSAL_H_ */
