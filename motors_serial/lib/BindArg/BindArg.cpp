#include "BindArg.h"

#if defined(ESP_PLATFORM) || defined(ESP32)
#include "Arduino.h"
#if !defined(bindArgStaticVoidFuncAttr)
#define bindArgStaticVoidFuncAttr IRAM_ATTR
#endif
#else
#if !defined(bindArgStaticVoidFuncAttr)
#define bindArgStaticVoidFuncAttr
#endif
#endif

#if !defined(bindArgStaticData)
#define bindArgStaticData                 static
#endif

#if !defined(bindArgStaticVoidFuncDecl)
#define bindArgStaticVoidFuncDecl         static
#endif

#if !defined(bindArgStaticVoidFuncBody)
#define bindArgStaticVoidFuncBody         static
#endif

#define bindArgVoidFuncBlock(bindArgVoidFuncBlockItem) \
  bindArgVoidFuncBlockItem( 0) bindArgVoidFuncBlockItem( 1) bindArgVoidFuncBlockItem( 2) bindArgVoidFuncBlockItem( 3) bindArgVoidFuncBlockItem( 4) \
  bindArgVoidFuncBlockItem( 5) bindArgVoidFuncBlockItem( 6) bindArgVoidFuncBlockItem( 7) bindArgVoidFuncBlockItem( 8) bindArgVoidFuncBlockItem( 9) \
  bindArgVoidFuncBlockItem(10) bindArgVoidFuncBlockItem(11) bindArgVoidFuncBlockItem(12) bindArgVoidFuncBlockItem(13) bindArgVoidFuncBlockItem(14) \
  bindArgVoidFuncBlockItem(15) bindArgVoidFuncBlockItem(16) bindArgVoidFuncBlockItem(17) bindArgVoidFuncBlockItem(18) bindArgVoidFuncBlockItem(19) \
  bindArgVoidFuncBlockItem(20) bindArgVoidFuncBlockItem(21) bindArgVoidFuncBlockItem(22) bindArgVoidFuncBlockItem(23) bindArgVoidFuncBlockItem(24) \
  bindArgVoidFuncBlockItem(25) bindArgVoidFuncBlockItem(26) bindArgVoidFuncBlockItem(27) bindArgVoidFuncBlockItem(28) bindArgVoidFuncBlockItem(29) \


#define bindArgProcArgArrayBody(size)     bindArgStaticData bindArgProcArg_t   bindArgProcArgArray[size];
#define bindArgProcFuncArrayBody(size)    bindArgStaticData bindArgProcFunc_t  bindArgProcFuncArray[size];
#define bindArgVoidFuncName(num)          bindArgVoidFunc##num
#define bindArgVoidFuncDecl(num)          bindArgStaticVoidFuncDecl void bindArgVoidFuncName(num)(void);
#define bindArgVoidFuncBody(num)          bindArgStaticVoidFuncBody void bindArgStaticVoidFuncAttr bindArgVoidFuncName(num)(void) { if(bindArgProcFuncArray[num] != nullptr) { bindArgProcFuncArray[num](bindArgProcArgArray[num]); } }
#define bindArgVoidFuncArrayBodyBegin()   bindArgStaticData bindArgVoidFunc_t bindArgVoidFuncArray[] = {
#define bindArgVoidFuncArrayBodyItem(num) &bindArgVoidFuncName(num),
#define bindArgVoidFuncArrayBodyEnd()     };
#define bindArgVoidFuncArraySize()        (sizeof(bindArgVoidFuncArray)/sizeof(bindArgVoidFuncArray[0]))

bindArgVoidFuncBlock(bindArgVoidFuncDecl)

bindArgVoidFuncArrayBodyBegin()
                bindArgVoidFuncBlock(bindArgVoidFuncArrayBodyItem)
bindArgVoidFuncArrayBodyEnd();

bindArgProcFuncArrayBody(bindArgVoidFuncArraySize());
bindArgProcArgArrayBody(bindArgVoidFuncArraySize());

bindArgVoidFuncBlock(bindArgVoidFuncBody)

bindArgVoidFunc_t bindArgGateVoidAllocate(bindArgProcFunc_t func, bindArgProcArg_t arg)
{
    for (int i = 0; i < bindArgVoidFuncArraySize(); i++)
    {
        if (bindArgProcFuncArray[i] == nullptr)
        {
            bindArgProcFuncArray[i] = func;
            bindArgProcArgArray[i] = arg;
            return bindArgVoidFuncArray[i];
        }
    }

    return nullptr;
}

void bindArgGateFree(bindArgVoidFunc_t gate)
{
    if (gate == nullptr) { return; }
    for (int i = 0; i < bindArgVoidFuncArraySize(); i++)
    {
        if (bindArgVoidFuncArray[i] == gate)
        {
            bindArgProcFuncArray[i] = nullptr;
            bindArgProcArgArray[i] = nullptr;
            return;
        }
    }
}
