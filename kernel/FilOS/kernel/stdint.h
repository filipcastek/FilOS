#ifndef STDINT_H
#define STDINT_H

#include <stddef.h>

// Definice celých čísel s pevným počtem bitů
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

// Definice velikostí (v bytech)
typedef unsigned long size_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;

#endif // STDINT_H
