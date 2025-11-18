#if !defined(ATRAIN_H)
#include <stdint.h>
//
#define internal static
#define local_persist static
#define global_variable static
//
#define PI32 3.14159265359f
//
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
//
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
//
typedef float real32;
typedef double real64;
typedef float f32;
typedef double f64;
typedef int32_t bool32;
// LL ?
#define KiloBytes(Value) ((Value) * 1024LL)
#define MegaBytes(Value) (KiloBytes(Value) * 1024LL)
#define GigaBytes(Value) (MegaBytes(Value) * 1024LL)
// volatile ?
#define Assert(Expression)      \
    if (!(Expression))          \
    {                           \
        *(volatile int *)0 = 0; \
    }
//
inline uint32 SafeTruncateUInt64(uint64 Value)
{
    Assert(Value <= 0xFFFFFFFFFFFFFFFF);
    uint32 Result = (uint32)Value;
    return (Result);
}
//
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
// len
#define len(Array) (sizeof(Array) / sizeof((Array)[0]))
#define len2(Array) (sizeof(Array) / sizeof((Array)[0][0]))
#define len3(Array) (sizeof(Array) / sizeof((Array)[0][0]))
//
#if !DEBUG
#else
#endif

#endif
