;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     TIMER0_Handler            ; 0
                DCD     WDT_Handler               ; 1
                DCD     GPIO0_Handler             ; 2
                DCD     I2C0_Handler              ; 3 
                DCD     SPI0_Handler              ; 4 
                DCD     UART0_Handler             ; 5 
                DCD     SYSCTRL_Handler           ; 6 
                DCD     TIMER1_Handler            ; 7 
                DCD     GPIO1_Handler             ; 8 
                DCD     I2C1_Handler              ; 9 
                DCD     SPI1_Handler              ; 10 
                DCD     UART1_Handler             ; 11 
				DCD     I2C2_Handler              ; 12 
				DCD     UART2_Handler             ; 13 
                DCD     SPI2_Handler              ; 14
				DCD     QSPI_Handler			  ; 15 
				DCD     DMAC_Handler			  ; 16
				DCD     FP0_IRQHandler            ; 17 FP0
				DCD     FP1_IRQHandler			  ; 18 FP1 
				DCD     FP2_IRQHandler			  ; 19 FP2 
				DCD     FP3_IRQHandler			  ; 20 FP3 
				DCD     FP4_IRQHandler			  ; 21 FP4 
				DCD     FP5_IRQHandler			  ; 22 FP5 
				DCD     FP6_IRQHandler			  ; 23 FP6 
				DCD     FP7_IRQHandler 			  ; 24 FP7
				DCD     FP8_IRQHandler            ; 25 FP0
				DCD     FP9_IRQHandler			  ; 26 FP1 
				DCD     FP10_IRQHandler			  ; 27 FP2 
				DCD     FP11_IRQHandler			  ; 28 FP3 
				DCD     FP12_IRQHandler			  ; 29 FP4 
				DCD     FP13_IRQHandler			  ; 30 FP5 
				DCD     FP14_IRQHandler			  ; 31 FP6 
				DCD     FP15_IRQHandler 		  ; 32 FP7
				DCD     FP16_IRQHandler 		  ; 33 FP7
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT	   TIMER0_Handler         [WEAK]
                EXPORT     WDT_Handler            [WEAK]
                EXPORT     GPIO0_Handler          [WEAK]
                EXPORT     I2C0_Handler           [WEAK]
                EXPORT     SPI0_Handler           [WEAK]
                EXPORT     UART0_Handler          [WEAK]
                EXPORT     SYSCTRL_Handler        [WEAK]
                EXPORT     TIMER1_Handler         [WEAK]
                EXPORT     GPIO1_Handler          [WEAK]
                EXPORT     I2C1_Handler           [WEAK]
                EXPORT     SPI1_Handler           [WEAK]
                EXPORT     UART1_Handler          [WEAK]
				EXPORT     I2C2_Handler           [WEAK]
				EXPORT     UART2_Handler          [WEAK]
                EXPORT     SPI2_Handler           [WEAK]
				EXPORT     QSPI_Handler			  [WEAK]
				EXPORT     DMAC_Handler			  [WEAK]
				EXPORT     FP0_IRQHandler         [WEAK]
				EXPORT     FP1_IRQHandler		  [WEAK]
				EXPORT     FP2_IRQHandler		  [WEAK]
				EXPORT     FP3_IRQHandler		  [WEAK] 
				EXPORT     FP4_IRQHandler		  [WEAK] 
				EXPORT     FP5_IRQHandler		  [WEAK]
				EXPORT     FP6_IRQHandler		  [WEAK] 
				EXPORT     FP7_IRQHandler 		  [WEAK]
				EXPORT     FP8_IRQHandler         [WEAK]
				EXPORT     FP9_IRQHandler		  [WEAK]
				EXPORT     FP10_IRQHandler        [WEAK]
				EXPORT     FP11_IRQHandler		  [WEAK]
				EXPORT     FP12_IRQHandler		  [WEAK]
				EXPORT     FP13_IRQHandler		  [WEAK] 
				EXPORT     FP14_IRQHandler		  [WEAK] 
				EXPORT     FP15_IRQHandler		  [WEAK]
				EXPORT     FP16_IRQHandler		  [WEAK] 
					
							
TIMER0_Handler   					
WDT_Handler      					
GPIO0_Handler    					
I2C0_Handler     					
SPI0_Handler     					
UART0_Handler    					
SYSCTRL_Handler  					
TIMER1_Handler   					
GPIO1_Handler    					
I2C1_Handler     					
SPI1_Handler     					
UART1_Handler    					
I2C2_Handler  
UART2_Handler 
SPI2_Handler     										
QSPI_Handler							
DMAC_Handler							
FP0_IRQHandler 
FP1_IRQHandler
FP2_IRQHandler
FP3_IRQHandler
FP4_IRQHandler
FP5_IRQHandler
FP6_IRQHandler
FP7_IRQHandler 
FP8_IRQHandler 
FP9_IRQHandler
FP10_IRQHandler
FP11_IRQHandler
FP12_IRQHandler
FP13_IRQHandler
FP14_IRQHandler
FP15_IRQHandler
FP16_IRQHandler

                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
