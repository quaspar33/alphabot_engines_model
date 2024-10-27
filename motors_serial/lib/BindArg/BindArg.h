#pragma once

#ifndef LAB3_BINDARG_H
#define LAB3_BINDARG_H


typedef void  (*bindArgVoidFunc_t)(void);

typedef void* bindArgProcArg_t;
typedef void  (*bindArgProcFunc_t)(bindArgProcArg_t arg);

extern
bindArgVoidFunc_t bindArgGateVoidAllocate(bindArgProcFunc_t func, bindArgProcArg_t arg);

template<typename T>
bindArgVoidFunc_t bindArgGateFuncAllocate(void (*func)(T*), T* arg)
{
    return bindArgGateVoidAllocate(*((bindArgProcFunc_t*)((void*)(&func))), (bindArgProcArg_t)(arg));
}

template<typename T>
bindArgVoidFunc_t bindArgGateThisAllocate(void (T::*method)(), T* objPtr)
{
    return bindArgGateVoidAllocate(*((bindArgProcFunc_t*)((void*)(&method))), (bindArgProcArg_t)(objPtr));
}

extern
void bindArgGateFree(bindArgVoidFunc_t gate);


#endif
