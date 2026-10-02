#ifndef ARC_CONTAINER_OF_H
#define ARC_CONTAINER_OF_H

#include <arc/types.h>

#define CONTAINER_OF(ptr, Type, member) ({ \
                const typeof(((Type*)0)->member) *__mptr = (ptr); \
                (Type*)((char*)__mptr - offsetof(Type, member)); })
                
#endif /* ARC_CONTAINER_OF_H */