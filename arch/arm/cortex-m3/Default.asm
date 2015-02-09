
; jinfeng, 2014/7/29

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

Default_Handler PROC

	EXPORT  WWDG_IRQHandler                   [WEAK]                                        
	EXPORT  PVD_IRQHandler                    [WEAK]                      
	EXPORT  TAMP_STAMP_IRQHandler             [WEAK]         
	EXPORT  RTC_WKUP_IRQHandler               [WEAK]                     
	EXPORT  FLASH_IRQHandler                  [WEAK]                                         
	EXPORT  RCC_IRQHandler                    [WEAK]                                            
	EXPORT  EXTI0_IRQHandler                  [WEAK]                                            
	EXPORT  EXTI1_IRQHandler                  [WEAK]                                             
	EXPORT  EXTI2_IRQHandler                  [WEAK]                                            
	EXPORT  EXTI3_IRQHandler                  [WEAK]                                           
	EXPORT  EXTI4_IRQHandler                  [WEAK]                                            
	EXPORT  DMA1_Stream0_IRQHandler           [WEAK]                                
	EXPORT  DMA1_Stream1_IRQHandler           [WEAK]                                   
	EXPORT  DMA1_Stream2_IRQHandler           [WEAK]                                   
	EXPORT  DMA1_Stream3_IRQHandler           [WEAK]                                   
	EXPORT  DMA1_Stream4_IRQHandler           [WEAK]                                   
	EXPORT  DMA1_Stream5_IRQHandler           [WEAK]                                   
	EXPORT  DMA1_Stream6_IRQHandler           [WEAK]                                   
	EXPORT  ADC_IRQHandler                    [WEAK]                         
	EXPORT  CAN1_TX_IRQHandler                [WEAK]                                                
	EXPORT  CAN1_RX0_IRQHandler               [WEAK]                                               
	EXPORT  CAN1_RX1_IRQHandler               [WEAK]                                                
	EXPORT  CAN1_SCE_IRQHandler               [WEAK]                                                
	EXPORT  EXTI9_5_IRQHandler                [WEAK]                                    
	EXPORT  TIM1_BRK_TIM9_IRQHandler          [WEAK]                  
	EXPORT  TIM1_UP_TIM10_IRQHandler          [WEAK]                
	EXPORT  TIM1_TRG_COM_TIM11_IRQHandler     [WEAK] 
	EXPORT  TIM1_CC_IRQHandler                [WEAK]                                   
	EXPORT  TIM2_IRQHandler                   [WEAK]                                            
	EXPORT  TIM3_IRQHandler                   [WEAK]                                            
	EXPORT  TIM4_IRQHandler                   [WEAK]                                            
	EXPORT  I2C1_EV_IRQHandler                [WEAK]                                             
	EXPORT  I2C1_ER_IRQHandler                [WEAK]                                             
	EXPORT  I2C2_EV_IRQHandler                [WEAK]                                            
	EXPORT  I2C2_ER_IRQHandler                [WEAK]                                               
	EXPORT  SPI1_IRQHandler                   [WEAK]                                           
	EXPORT  SPI2_IRQHandler                   [WEAK]                                            
	EXPORT  USART1_IRQHandler                 [WEAK]                                          
	EXPORT  USART2_IRQHandler                 [WEAK]                                          
	EXPORT  USART3_IRQHandler                 [WEAK]                                         
	EXPORT  EXTI15_10_IRQHandler              [WEAK]                                  
	EXPORT  RTC_Alarm_IRQHandler              [WEAK]                  
	EXPORT  OTG_FS_WKUP_IRQHandler            [WEAK]                        
	EXPORT  TIM8_BRK_TIM12_IRQHandler         [WEAK]                 
	EXPORT  TIM8_UP_TIM13_IRQHandler          [WEAK]                 
	EXPORT  TIM8_TRG_COM_TIM14_IRQHandler     [WEAK] 
	EXPORT  TIM8_CC_IRQHandler                [WEAK]                                   
	EXPORT  DMA1_Stream7_IRQHandler           [WEAK]                                          
	EXPORT  FSMC_IRQHandler                   [WEAK]                                             
	EXPORT  SDIO_IRQHandler                   [WEAK]                                             
	EXPORT  TIM5_IRQHandler                   [WEAK]                                             
	EXPORT  SPI3_IRQHandler                   [WEAK]                                             
	EXPORT  UART4_IRQHandler                  [WEAK]                                            
	EXPORT  UART5_IRQHandler                  [WEAK]                                            
	EXPORT  TIM6_DAC_IRQHandler               [WEAK]                   
	EXPORT  TIM7_IRQHandler                   [WEAK]                    
	EXPORT  DMA2_Stream0_IRQHandler           [WEAK]                                  
	EXPORT  DMA2_Stream1_IRQHandler           [WEAK]                                   
	EXPORT  DMA2_Stream2_IRQHandler           [WEAK]                                    
	EXPORT  DMA2_Stream3_IRQHandler           [WEAK]                                    
	EXPORT  DMA2_Stream4_IRQHandler           [WEAK]                                 
	EXPORT  ETH_IRQHandler                    [WEAK]                                         
	EXPORT  ETH_WKUP_IRQHandler               [WEAK]                     
	EXPORT  CAN2_TX_IRQHandler                [WEAK]                                               
	EXPORT  CAN2_RX0_IRQHandler               [WEAK]                                               
	EXPORT  CAN2_RX1_IRQHandler               [WEAK]                                               
	EXPORT  CAN2_SCE_IRQHandler               [WEAK]                                               
	EXPORT  OTG_FS_IRQHandler                 [WEAK]                                       
	EXPORT  DMA2_Stream5_IRQHandler           [WEAK]                                   
	EXPORT  DMA2_Stream6_IRQHandler           [WEAK]                                   
	EXPORT  DMA2_Stream7_IRQHandler           [WEAK]                                   
	EXPORT  USART6_IRQHandler                 [WEAK]                                           
	EXPORT  I2C3_EV_IRQHandler                [WEAK]                                              
	EXPORT  I2C3_ER_IRQHandler                [WEAK]                                              
	EXPORT  OTG_HS_EP1_OUT_IRQHandler         [WEAK]                      
	EXPORT  OTG_HS_EP1_IN_IRQHandler          [WEAK]                      
	EXPORT  OTG_HS_WKUP_IRQHandler            [WEAK]                        
	EXPORT  OTG_HS_IRQHandler                 [WEAK]                                      
	EXPORT  DCMI_IRQHandler                   [WEAK]                                             
	EXPORT  CRYP_IRQHandler                   [WEAK]                                     
	EXPORT  HASH_RNG_IRQHandler               [WEAK]

WWDG_IRQHandler                                                       
PVD_IRQHandler                                      
TAMP_STAMP_IRQHandler                  
RTC_WKUP_IRQHandler                                
FLASH_IRQHandler                                                       
RCC_IRQHandler                                                            
EXTI0_IRQHandler                                                          
EXTI1_IRQHandler                                                           
EXTI2_IRQHandler                                                          
EXTI3_IRQHandler                                                         
EXTI4_IRQHandler                                                          
DMA1_Stream0_IRQHandler                                       
DMA1_Stream1_IRQHandler                                          
DMA1_Stream2_IRQHandler                                          
DMA1_Stream3_IRQHandler                                          
DMA1_Stream4_IRQHandler                                          
DMA1_Stream5_IRQHandler                                          
DMA1_Stream6_IRQHandler                                          
ADC_IRQHandler                                         
CAN1_TX_IRQHandler                                                            
CAN1_RX0_IRQHandler                                                          
CAN1_RX1_IRQHandler                                                           
CAN1_SCE_IRQHandler                                                           
EXTI9_5_IRQHandler                                                
TIM1_BRK_TIM9_IRQHandler                        
TIM1_UP_TIM10_IRQHandler                      
TIM1_TRG_COM_TIM11_IRQHandler  
TIM1_CC_IRQHandler                                               
TIM2_IRQHandler                                                           
TIM3_IRQHandler                                                           
TIM4_IRQHandler                                                           
I2C1_EV_IRQHandler                                                         
I2C1_ER_IRQHandler                                                         
I2C2_EV_IRQHandler                                                        
I2C2_ER_IRQHandler                                                           
SPI1_IRQHandler                                                          
SPI2_IRQHandler                                                           
USART1_IRQHandler                                                       
USART2_IRQHandler                                                       
USART3_IRQHandler                                                      
EXTI15_10_IRQHandler                                            
RTC_Alarm_IRQHandler                            
OTG_FS_WKUP_IRQHandler                                
TIM8_BRK_TIM12_IRQHandler                      
TIM8_UP_TIM13_IRQHandler                       
TIM8_TRG_COM_TIM14_IRQHandler  
TIM8_CC_IRQHandler                                               
DMA1_Stream7_IRQHandler                                                 
FSMC_IRQHandler                                                            
SDIO_IRQHandler                                                            
TIM5_IRQHandler                                                            
SPI3_IRQHandler                                                            
UART4_IRQHandler                                                          
UART5_IRQHandler                                                          
TIM6_DAC_IRQHandler                            
TIM7_IRQHandler                              
DMA2_Stream0_IRQHandler                                         
DMA2_Stream1_IRQHandler                                          
DMA2_Stream2_IRQHandler                                           
DMA2_Stream3_IRQHandler                                           
DMA2_Stream4_IRQHandler                                        
ETH_IRQHandler                                                         
ETH_WKUP_IRQHandler                                
CAN2_TX_IRQHandler                                                           
CAN2_RX0_IRQHandler                                                          
CAN2_RX1_IRQHandler                                                          
CAN2_SCE_IRQHandler                                                          
OTG_FS_IRQHandler                                                    
DMA2_Stream5_IRQHandler                                          
DMA2_Stream6_IRQHandler                                          
DMA2_Stream7_IRQHandler                                          
USART6_IRQHandler                                                        
I2C3_EV_IRQHandler                                                          
I2C3_ER_IRQHandler                                                          
OTG_HS_EP1_OUT_IRQHandler                           
OTG_HS_EP1_IN_IRQHandler                            
OTG_HS_WKUP_IRQHandler                                
OTG_HS_IRQHandler                                                   
DCMI_IRQHandler                                                            
CRYP_IRQHandler                                                    
HASH_RNG_IRQHandler                                               

	B       .

	ENDP
		
	ALIGN
	
	END
	