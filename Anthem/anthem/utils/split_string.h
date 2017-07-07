#pragma once

#define ANTHEM_STRING_SPLIT_1(str, i) \
    (sizeof(str) > (i) ? str[(i)] : 0)

#define ANTHEM_STRING_SPLIT_4(str, i) \
    ANTHEM_STRING_SPLIT_1(str, i+0),  \
    ANTHEM_STRING_SPLIT_1(str, i+1),  \
    ANTHEM_STRING_SPLIT_1(str, i+2),  \
    ANTHEM_STRING_SPLIT_1(str, i+3)

#define ANTHEM_STRING_SPLIT_16(str, i) \
    ANTHEM_STRING_SPLIT_4(str, i+0),   \
    ANTHEM_STRING_SPLIT_4(str, i+4),   \
    ANTHEM_STRING_SPLIT_4(str, i+8),   \
    ANTHEM_STRING_SPLIT_4(str, i+12)

#define ANTHEM_STRING_SPLIT_64(str, i) \
    ANTHEM_STRING_SPLIT_16(str, i+0),  \
    ANTHEM_STRING_SPLIT_16(str, i+16), \
    ANTHEM_STRING_SPLIT_16(str, i+32), \
    ANTHEM_STRING_SPLIT_16(str, i+48)

#define ANTHEM_STRING_SPLIT(str) ANTHEM_STRING_SPLIT_64(str, 0), 0