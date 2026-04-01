#if !defined(ATRAIN_H)
#pragma once
// #include <stdint.h>
//
#define internal static
#define local_persist static
#define global_variable static
//
#define PI32 3.14159265359f
//
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
//
typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
//
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
//
typedef float real32;
typedef double real64;
typedef int bool32;
typedef float f32;
typedef double f64;
// LL ?
#define KiloBytes(Value) ((Value) * 1024LL)
#define MegaBytes(Value) (KiloBytes(Value) * 1024LL)
#define GigaBytes(Value) (MegaBytes(Value) * 1024LL)
// volatile ?
#define atn_Assert(Expression)  \
    if (!(Expression))          \
    {                           \
        *(volatile int *)0 = 0; \
    }
//
// inline uint32 SafeTruncateUInt64(uint64 Value)
// {
//     Assert(Value <= 0xFFFFFFFFFFFFFFFF);
//     uint32 Result = (uint32)Value;
//     return (Result);
// }
//
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define len(Array) (sizeof(Array) / sizeof((Array)[0]))
#define len2(Array) (sizeof(Array) / sizeof((Array)[0][0]))
#define len3(Array) (sizeof(Array) / sizeof((Array)[0][0][0]))
// Probably not a good idea
#define newline printf("\n") // specifically a ";" so it can be on the same line
//
// To edit, reverse the comments on the ifdefs and ifndefs.
#ifdef ATN_MEMORY
// #ifndef ATN_MEMORY
typedef struct atn_Memory
{
    bool IsInitialized;
    u64 PermanentStorageSize;
    void *PermanentStorage;
    u64 TransientStorageSize;
    void *TransientStorage;
    u64 offset;

} Memory;
static inline void initMemory(Memory *M, u64 PermanentStorageSize,
                              u64 TransientStorageSize);
//
#if defined(_WIN32)
// #ifndef ATN_MEMORY
#define _AMD64_
#include <memoryapi.h>
//  Transient Big Permanent Small
void initMemory(Memory *M, u64 PermanentStorageSize, u64 TransientStorageSize)
{
    void *BaseAddress = 0;
    M->PermanentStorageSize = (PermanentStorageSize);
    M->TransientStorageSize = (TransientStorageSize);
    u64 TotalSize = M->PermanentStorageSize + M->TransientStorageSize;
    M->PermanentStorage = VirtualAlloc(BaseAddress, TotalSize,
                                       MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    M->TransientStorage = ((u8 *)M->PermanentStorage + M->PermanentStorageSize);
    if (M->PermanentStorage == NULL)
    {
        M->IsInitialized = false;
        return;
    }
    M->IsInitialized = true;
}
#elif defined(__linux__)
// #ifndef LINUX
#include <sys/mman.h>
void initMemory(Memory *M, u64 PermanentStorageSize, u64 TransientStorageSize)
{
    void *BaseAddress = 0;
    M->PermanentStorageSize = (PermanentStorageSize);
    M->TransientStorageSize = (TransientStorageSize);
    u64 TotalSize = M->PermanentStorageSize + M->TransientStorageSize;
    M->PermanentStorage = mmap(NULL, TotalSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    M->TransientStorage = ((u8 *)M->PermanentStorage + M->PermanentStorageSize);
    if (M->PermanentStorage == MAP_FAILED)
    {
        M->IsInitialized = false;
        return;
    }
    M->IsInitialized = true;
}
#endif
#endif
#endif
