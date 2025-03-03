/*
** Copyright (c) 2018 Arm Limited. All rights reserved.
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_device_headers.h"
#include "startup_cat1d.h"
#include "partition_ARMCM33.h"
CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.6', 3, \
'Checked manually. The definition is a part of linker script or application.')
CY_MISRA_DEVIATE_BLOCK_START('ARRAY_VS_SINGLETON', 1, \
'Checked manually. Using pointer as an array will not corrupt or misinterpret adjacent memory locations.')
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.1', 3, \
'Checked manually. Dereferencing a pointer to one beyond the end of an array will not result in undefined behaviour.')
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.3', 1, \
'Checked manually. Attempting to make comparisons between pointers will not result in undefined behaviour.')

// Initial Setup
//----------------------------------------------------------------

extern unsigned int __INITIAL_SP;
extern unsigned int __STACK_LIMIT;

void SysLib_FaultHandler(uint32_t const *faultStackAddr);
void S_NMIException_Handler(void);
void S_HardFault_Handler(void);
void S_MemManage_Handler(void);
void S_BusFault_Handler(void);
void S_UsageFault_Handler(void);
void S_SecureFault_Handler(void);
void S_SVC_Handler(void);
void S_DebugMon_Handler(void);
void S_PendSV_Handler(void);
void S_SysTick_Handler(void);
void S_InterruptHandler(void);


#if defined(__ARMCC_VERSION)
    extern void __main(void);
    ExecFuncPtrRw __s_vector_table_rw[VECTORTABLE_SIZE] __attribute__( ( section(".bss.noinit.RESET_RAM"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__GNUC__)
    ExecFuncPtrRw __s_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".ram_vectors"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__ICCARM__)
    extern void  __cmain();
    ExecFuncPtrRw __s_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".intvec_ram"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#else
    #error "An unsupported toolchain"
#endif  /* (__ARMCC_VERSION) */


extern void Cy_MpuInit_cm33_s_0(void);


__WEAK void Cy_MpuInit_cm33_s_0(void)
{

}

#if defined (__ARMCC_VERSION)
void __attribute__((optnone)) Cy_RuntimeInit(void);
#else
void Cy_RuntimeInit(void);
#endif

void Cy_RuntimeInit(void)
{
/* ARMCC runtime require FPU to be enabled */
#if defined (__FPU_USED) && (__FPU_USED == 1U) && \
          defined (TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)
    FPU->FPCCR = FPU->FPCCR & ~(FPU_FPCCR_ASPEN_Msk | FPU_FPCCR_LSPEN_Msk);
    SCB->CPACR |= SCB_NS_CPACR_CP10_CP11_ENABLE;
#endif
    __PROGRAM_START();
}

void SysLib_FaultHandler(uint32_t const *faultStackAddr)
{
    Cy_SysLib_FaultHandler(faultStackAddr);
}
// Exception Vector Table & Handlers
//----------------------------------------------------------------
void S_Reset_Handler(void);
void S_NMIException_Handler(void) {while(true){}}
void S_HardFault_Handler(void)
{
    __asm (
        "TST LR, #0x40\n"
        "BEQ from_nonsecure\n"
        "from_secure:\n"
        "TST LR, #0x04\n"
        "ITE EQ\n"
        "MRSEQ R0, MSP\n"
        "MRSNE R0, PSP\n"
        "B SysLib_FaultHandler \n"
        "from_nonsecure:\n"
        "MRS R0, CONTROL_NS\n"
        "TST R0, #2\n"
        "ITE EQ\n"
        "MRSEQ R0, MSP_NS\n"
        "MRSNE R0, PSP_NS\n"
        "B SysLib_FaultHandler\n"
    );
}

void S_MemManage_Handler(void)         {Cy_SysLib_ProcessingFault();}
void S_BusFault_Handler(void)          {Cy_SysLib_ProcessingFault();}
void S_UsageFault_Handler(void)        {Cy_SysLib_ProcessingFault();}
void S_SecureFault_Handler(void)       {Cy_SysLib_ProcessingFault();}
__WEAK void S_SVC_Handler(void)        {Cy_SysLib_ProcessingFault();}
void S_DebugMon_Handler(void)          {Cy_SysLib_ProcessingFault();}
void S_PendSV_Handler(void)            {Cy_SysLib_ProcessingFault();}
void S_SysTick_Handler(void)           {Cy_SysLib_ProcessingFault();}
void S_InterruptHandler(void)          {Cy_SysLib_ProcessingFault();}

ExecFuncPtr __s_vector_table[] __VECTOR_TABLE_ATTRIBUTE = {
    (ExecFuncPtr)&__INITIAL_SP,            // initial SP
    (ExecFuncPtr)S_Reset_Handler,          // initial PC/Reset
    (ExecFuncPtr)S_NMIException_Handler,
    (ExecFuncPtr)S_HardFault_Handler,
    (ExecFuncPtr)S_MemManage_Handler,      // Memory Manage Fault
    (ExecFuncPtr)S_BusFault_Handler,       // Bus Fault
    (ExecFuncPtr)S_UsageFault_Handler,     // Usage Fault
    (ExecFuncPtr)S_SecureFault_Handler,    // RESERVED
    (ExecFuncPtr)0,                        // RESERVED
    (ExecFuncPtr)0,                        // RESERVED
    (ExecFuncPtr)0,                        // RESERVED
    (ExecFuncPtr)S_SVC_Handler,
    (ExecFuncPtr)S_DebugMon_Handler,       // RESERVED for debug
    (ExecFuncPtr)0,                        // RESERVED
    (ExecFuncPtr)S_PendSV_Handler,
    (ExecFuncPtr)S_SysTick_Handler,

    /* External interrupts */
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler,
    (ExecFuncPtr)S_InterruptHandler
};

// Reset Handler
void S_Reset_Handler(void)
{

#if 0
    /* invalidate the cache */
    ICACHE0->CMD = ICACHE0->CMD | ICACHE_CMD_INV_Msk;
    /*wait for invalidation complete */
    while(ICACHE0->CMD & ICACHE_CMD_INV_Msk);
#endif

    /* Disable I cache */
    ICACHE0->CTL = ICACHE0->CTL & (~ICACHE_CTL_CA_EN_Msk);

#if defined(ICACHE_ECC_PRESENT) && (ICACHE_ECC_PRESENT == 1u)
    /* Enable ECC */
    ICACHE0->CTL = ICACHE0->CTL | ICACHE_CTL_ECC_EN_Msk;
#endif

    /* Enable I cache */
    ICACHE0->CTL = ICACHE0->CTL | ICACHE_CTL_CA_EN_Msk;

    __disable_irq();

    for (uint32_t count = 0; count < VECTORTABLE_SIZE; count++)
    {
        __s_vector_table_rw[count] =__s_vector_table[count];
    }

    SCB->VTOR = (uint32_t)__s_vector_table_rw;
    __DMB();

    __set_MSPLIM((uint32_t)(&__STACK_LIMIT));

    SystemInit();

    Cy_RuntimeInit();
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.3')
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.1')
CY_MISRA_BLOCK_END('ARRAY_VS_SINGLETON')
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.6')
