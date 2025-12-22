/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is based on the GigaDevice GD32E23x standard firmware library.
 * It has been modified to be compatible with the GCC toolchain for RT-Thread
 * on a Cortex-M23 core, using maximum compatibility instructions.
 */

.syntax unified
.cpu cortex-m23
.fpu softvfp
.thumb

/* Vector Table */
.section .isr_vector, "a",%progbits
.global g_pfnVectors
.type g_pfnVectors, %object

g_pfnVectors:
    .word   _estack                         /* Top of Stack (defined in linker script) */
    .word   Reset_Handler                   /* Reset Handler */
    .word   NMI_Handler                     /* NMI Handler */
    .word   HardFault_Handler               /* Hard Fault Handler */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   SVC_Handler                     /* SVCall Handler */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   PendSV_Handler                  /* PendSV Handler */
    .word   SysTick_Handler                 /* SysTick Handler */

    /* External Interrupts */
    .word   WWDGT_IRQHandler                /* 16: Window Watchdog Timer */
    .word   LVD_IRQHandler                  /* 17: LVD through EXTI Line detect */
    .word   RTC_IRQHandler                  /* 18: RTC through EXTI Line */
    .word   FMC_IRQHandler                  /* 19: FMC */
    .word   RCU_IRQHandler                  /* 20: RCU */
    .word   EXTI0_1_IRQHandler              /* 21: EXTI Line 0 and EXTI Line 1 */
    .word   EXTI2_3_IRQHandler              /* 22: EXTI Line 2 and EXTI Line 3 */
    .word   EXTI4_15_IRQHandler             /* 23: EXTI Line 4 to EXTI Line 15 */
    .word   0                               /* Reserved */
    .word   DMA_Channel0_IRQHandler         /* 25: DMA Channel 0 */
    .word   DMA_Channel1_2_IRQHandler       /* 26: DMA Channel 1 and DMA Channel 2 */
    .word   DMA_Channel3_4_IRQHandler       /* 27: DMA Channel 3 and DMA Channel 4 */
    .word   ADC_CMP_IRQHandler              /* 28: ADC and Comparator */
    .word   TIMER0_BRK_UP_TRG_COM_IRQHandler /* 29: TIMER0 Break,Update,Trigger and Commutation */
    .word   TIMER0_Channel_IRQHandler       /* 30: TIMER0 Channel Capture Compare */
    .word   0                               /* Reserved */
    .word   TIMER2_IRQHandler               /* 32: TIMER2 */
    .word   TIMER5_IRQHandler               /* 33: TIMER5 */
    .word   0                               /* Reserved */
    .word   TIMER13_IRQHandler              /* 35: TIMER13 */
    .word   TIMER14_IRQHandler              /* 36: TIMER14 */
    .word   TIMER15_IRQHandler              /* 37: TIMER15 */
    .word   TIMER16_IRQHandler              /* 38: TIMER16 */
    .word   I2C0_EV_IRQHandler              /* 39: I2C0 Event */
    .word   I2C1_EV_IRQHandler              /* 40: I2C1 Event */
    .word   SPI0_IRQHandler                 /* 41: SPI0 */
    .word   SPI1_IRQHandler                 /* 42: SPI1 */
    .word   USART0_IRQHandler               /* 43: USART0 */
    .word   USART1_IRQHandler               /* 44: USART1 */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   0                               /* Reserved */
    .word   I2C0_ER_IRQHandler              /* 48: I2C0 Error */
    .word   0                               /* Reserved */
    .word   I2C1_ER_IRQHandler              /* 50: I2C1 Error */

.size g_pfnVectors, . - g_pfnVectors

/* Reset Handler */
.section .text.Reset_Handler
.global Reset_Handler
.type Reset_Handler, %function
.thumb_func
Reset_Handler:
    /* Call the system clock initialization function */
    bl  SystemInit

    /* Copy the .data segment initializers from flash to SRAM */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

LoopCopyDataInit:
    cmp r1, r2
    bhs LoopCopyDataEnd     /* Branch if r1 >= r2 (unsigned) */
    ldr r3, [r0]            /* Load from source */
    adds r0, r0, #4         /* Increment source pointer */
    str r3, [r1]            /* Store to destination */
    adds r1, r1, #4         /* Increment destination pointer */
    b LoopCopyDataInit
LoopCopyDataEnd:

    /* Zero-fill the .bss section */
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0

LoopFillZerobss:
    cmp r1, r2
    bhs LoopFillZerobssEnd  /* Branch if r1 >= r2 (unsigned) */
    str r3, [r1]            /* Store zero to destination */
    adds r1, r1, #4         /* Increment destination pointer */
    b LoopFillZerobss
LoopFillZerobssEnd:

    /* Call RT-Thread entry point */
    bl entry

    /* Should never reach here */
    b .

.size Reset_Handler, . - Reset_Handler


/* Default exception and interrupt handlers */
.section .text.Default_Handler, "ax", %progbits
.thumb_func
Default_Handler:
    b .
.size Default_Handler, . - Default_Handler


/* Macro to define default handlers */
.macro def_irq_handler handler_name
    .weak \handler_name
    .thumb_set \handler_name, Default_Handler
.endm

/* Weak definitions for all exception and interrupt handlers */
def_irq_handler NMI_Handler
def_irq_handler HardFault_Handler
def_irq_handler SVC_Handler
def_irq_handler PendSV_Handler
def_irq_handler SysTick_Handler
def_irq_handler WWDGT_IRQHandler
def_irq_handler LVD_IRQHandler
def_irq_handler RTC_IRQHandler
def_irq_handler FMC_IRQHandler
def_irq_handler RCU_IRQHandler
def_irq_handler EXTI0_1_IRQHandler
def_irq_handler EXTI2_3_IRQHandler
def_irq_handler EXTI4_15_IRQHandler
def_irq_handler DMA_Channel0_IRQHandler
def_irq_handler DMA_Channel1_2_IRQHandler
def_irq_handler DMA_Channel3_4_IRQHandler
def_irq_handler ADC_CMP_IRQHandler
def_irq_handler TIMER0_BRK_UP_TRG_COM_IRQHandler
def_irq_handler TIMER0_Channel_IRQHandler
def_irq_handler TIMER2_IRQHandler
def_irq_handler TIMER5_IRQHandler
def_irq_handler TIMER13_IRQHandler
def_irq_handler TIMER14_IRQHandler
def_irq_handler TIMER15_IRQHandler
def_irq_handler TIMER16_IRQHandler
def_irq_handler I2C0_EV_IRQHandler
def_irq_handler I2C1_EV_IRQHandler
def_irq_handler SPI0_IRQHandler
def_irq_handler SPI1_IRQHandler
def_irq_handler USART0_IRQHandler
def_irq_handler USART1_IRQHandler
def_irq_handler I2C0_ER_IRQHandler
def_irq_handler I2C1_ER_IRQHandler
