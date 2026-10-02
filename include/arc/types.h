#ifndef ARC_TYPES_H
#define ARC_TYPES_H

#ifndef NULL
#define NULL ((void*)0)
#endif

enum
{
    arc_false = 0,
    arc_true = 1
};

#undef true
#undef false
#define true arc_true
#define false arc_false

#ifndef size_t
#define size_t unsigned int
#endif

#ifndef offsetof
#define offsetof(st, m) \
    ((size_t)((char*)&((st*)0)->m - (char*)0))
#endif

#endif /* ARC_TYPES_H */