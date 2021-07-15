/**
 * \brief Peripheral I/O description for SAMC21N18A
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2018-11-30T04:44:36Z */
#ifndef _SAMC21N18A_GPIO_H_
#define _SAMC21N18A_GPIO_H_

/* ========== Peripheral I/O pin numbers ========== */
#define PIN_PA00                    (  0  )  /**< Pin Number for PA00 */
#define PIN_PA01                    (  1  )  /**< Pin Number for PA01 */
#define PIN_PA02                    (  2  )  /**< Pin Number for PA02 */
#define PIN_PA03                    (  3  )  /**< Pin Number for PA03 */
#define PIN_PA04                    (  4  )  /**< Pin Number for PA04 */
#define PIN_PA05                    (  5  )  /**< Pin Number for PA05 */
#define PIN_PA06                    (  6  )  /**< Pin Number for PA06 */
#define PIN_PA07                    (  7  )  /**< Pin Number for PA07 */
#define PIN_PA08                    (  8  )  /**< Pin Number for PA08 */
#define PIN_PA09                    (  9  )  /**< Pin Number for PA09 */
#define PIN_PA10                    ( 10  )  /**< Pin Number for PA10 */
#define PIN_PA11                    ( 11  )  /**< Pin Number for PA11 */
#define PIN_PA12                    ( 12  )  /**< Pin Number for PA12 */
#define PIN_PA13                    ( 13  )  /**< Pin Number for PA13 */
#define PIN_PA14                    ( 14  )  /**< Pin Number for PA14 */
#define PIN_PA15                    ( 15  )  /**< Pin Number for PA15 */
#define PIN_PA16                    ( 16  )  /**< Pin Number for PA16 */
#define PIN_PA17                    ( 17  )  /**< Pin Number for PA17 */
#define PIN_PA18                    ( 18  )  /**< Pin Number for PA18 */
#define PIN_PA19                    ( 19  )  /**< Pin Number for PA19 */
#define PIN_PA20                    ( 20  )  /**< Pin Number for PA20 */
#define PIN_PA21                    ( 21  )  /**< Pin Number for PA21 */
#define PIN_PA22                    ( 22  )  /**< Pin Number for PA22 */
#define PIN_PA23                    ( 23  )  /**< Pin Number for PA23 */
#define PIN_PA24                    ( 24  )  /**< Pin Number for PA24 */
#define PIN_PA25                    ( 25  )  /**< Pin Number for PA25 */
#define PIN_PA27                    ( 27  )  /**< Pin Number for PA27 */
#define PIN_PA28                    ( 28  )  /**< Pin Number for PA28 */
#define PIN_PA30                    ( 30  )  /**< Pin Number for PA30 */
#define PIN_PA31                    ( 31  )  /**< Pin Number for PA31 */
#define PIN_PB00                    ( 32  )  /**< Pin Number for PB00 */
#define PIN_PB01                    ( 33  )  /**< Pin Number for PB01 */
#define PIN_PB02                    ( 34  )  /**< Pin Number for PB02 */
#define PIN_PB03                    ( 35  )  /**< Pin Number for PB03 */
#define PIN_PB04                    ( 36  )  /**< Pin Number for PB04 */
#define PIN_PB05                    ( 37  )  /**< Pin Number for PB05 */
#define PIN_PB06                    ( 38  )  /**< Pin Number for PB06 */
#define PIN_PB07                    ( 39  )  /**< Pin Number for PB07 */
#define PIN_PB08                    ( 40  )  /**< Pin Number for PB08 */
#define PIN_PB09                    ( 41  )  /**< Pin Number for PB09 */
#define PIN_PB10                    ( 42  )  /**< Pin Number for PB10 */
#define PIN_PB11                    ( 43  )  /**< Pin Number for PB11 */
#define PIN_PB12                    ( 44  )  /**< Pin Number for PB12 */
#define PIN_PB13                    ( 45  )  /**< Pin Number for PB13 */
#define PIN_PB14                    ( 46  )  /**< Pin Number for PB14 */
#define PIN_PB15                    ( 47  )  /**< Pin Number for PB15 */
#define PIN_PB16                    ( 48  )  /**< Pin Number for PB16 */
#define PIN_PB17                    ( 49  )  /**< Pin Number for PB17 */
#define PIN_PB18                    ( 50  )  /**< Pin Number for PB18 */
#define PIN_PB19                    ( 51  )  /**< Pin Number for PB19 */
#define PIN_PB20                    ( 52  )  /**< Pin Number for PB20 */
#define PIN_PB21                    ( 53  )  /**< Pin Number for PB21 */
#define PIN_PB22                    ( 54  )  /**< Pin Number for PB22 */
#define PIN_PB23                    ( 55  )  /**< Pin Number for PB23 */
#define PIN_PB24                    ( 56  )  /**< Pin Number for PB24 */
#define PIN_PB25                    ( 57  )  /**< Pin Number for PB25 */
#define PIN_PB30                    ( 62  )  /**< Pin Number for PB30 */
#define PIN_PB31                    ( 63  )  /**< Pin Number for PB31 */
#define PIN_PC00                    ( 64  )  /**< Pin Number for PC00 */
#define PIN_PC01                    ( 65  )  /**< Pin Number for PC01 */
#define PIN_PC02                    ( 66  )  /**< Pin Number for PC02 */
#define PIN_PC03                    ( 67  )  /**< Pin Number for PC03 */
#define PIN_PC05                    ( 69  )  /**< Pin Number for PC05 */
#define PIN_PC06                    ( 70  )  /**< Pin Number for PC06 */
#define PIN_PC07                    ( 71  )  /**< Pin Number for PC07 */
#define PIN_PC08                    ( 72  )  /**< Pin Number for PC08 */
#define PIN_PC09                    ( 73  )  /**< Pin Number for PC09 */
#define PIN_PC10                    ( 74  )  /**< Pin Number for PC10 */
#define PIN_PC11                    ( 75  )  /**< Pin Number for PC11 */
#define PIN_PC12                    ( 76  )  /**< Pin Number for PC12 */
#define PIN_PC13                    ( 77  )  /**< Pin Number for PC13 */
#define PIN_PC14                    ( 78  )  /**< Pin Number for PC14 */
#define PIN_PC15                    ( 79  )  /**< Pin Number for PC15 */
#define PIN_PC16                    ( 80  )  /**< Pin Number for PC16 */
#define PIN_PC17                    ( 81  )  /**< Pin Number for PC17 */
#define PIN_PC18                    ( 82  )  /**< Pin Number for PC18 */
#define PIN_PC19                    ( 83  )  /**< Pin Number for PC19 */
#define PIN_PC20                    ( 84  )  /**< Pin Number for PC20 */
#define PIN_PC21                    ( 85  )  /**< Pin Number for PC21 */
#define PIN_PC24                    ( 88  )  /**< Pin Number for PC24 */
#define PIN_PC25                    ( 89  )  /**< Pin Number for PC25 */
#define PIN_PC26                    ( 90  )  /**< Pin Number for PC26 */
#define PIN_PC27                    ( 91  )  /**< Pin Number for PC27 */
#define PIN_PC28                    ( 92  )  /**< Pin Number for PC28 */

/* ========== Peripheral I/O masks ========== */
#define PORT_PA00                   _UL_(1 << 0)    /**< PORT mask for PA00 */
#define PORT_PA01                   _UL_(1 << 1)    /**< PORT mask for PA01 */
#define PORT_PA02                   _UL_(1 << 2)    /**< PORT mask for PA02 */
#define PORT_PA03                   _UL_(1 << 3)    /**< PORT mask for PA03 */
#define PORT_PA04                   _UL_(1 << 4)    /**< PORT mask for PA04 */
#define PORT_PA05                   _UL_(1 << 5)    /**< PORT mask for PA05 */
#define PORT_PA06                   _UL_(1 << 6)    /**< PORT mask for PA06 */
#define PORT_PA07                   _UL_(1 << 7)    /**< PORT mask for PA07 */
#define PORT_PA08                   _UL_(1 << 8)    /**< PORT mask for PA08 */
#define PORT_PA09                   _UL_(1 << 9)    /**< PORT mask for PA09 */
#define PORT_PA10                   _UL_(1 << 10)   /**< PORT mask for PA10 */
#define PORT_PA11                   _UL_(1 << 11)   /**< PORT mask for PA11 */
#define PORT_PA12                   _UL_(1 << 12)   /**< PORT mask for PA12 */
#define PORT_PA13                   _UL_(1 << 13)   /**< PORT mask for PA13 */
#define PORT_PA14                   _UL_(1 << 14)   /**< PORT mask for PA14 */
#define PORT_PA15                   _UL_(1 << 15)   /**< PORT mask for PA15 */
#define PORT_PA16                   _UL_(1 << 16)   /**< PORT mask for PA16 */
#define PORT_PA17                   _UL_(1 << 17)   /**< PORT mask for PA17 */
#define PORT_PA18                   _UL_(1 << 18)   /**< PORT mask for PA18 */
#define PORT_PA19                   _UL_(1 << 19)   /**< PORT mask for PA19 */
#define PORT_PA20                   _UL_(1 << 20)   /**< PORT mask for PA20 */
#define PORT_PA21                   _UL_(1 << 21)   /**< PORT mask for PA21 */
#define PORT_PA22                   _UL_(1 << 22)   /**< PORT mask for PA22 */
#define PORT_PA23                   _UL_(1 << 23)   /**< PORT mask for PA23 */
#define PORT_PA24                   _UL_(1 << 24)   /**< PORT mask for PA24 */
#define PORT_PA25                   _UL_(1 << 25)   /**< PORT mask for PA25 */
#define PORT_PA27                   _UL_(1 << 27)   /**< PORT mask for PA27 */
#define PORT_PA28                   _UL_(1 << 28)   /**< PORT mask for PA28 */
#define PORT_PA30                   _UL_(1 << 30)   /**< PORT mask for PA30 */
#define PORT_PA31                   _UL_(1 << 31)   /**< PORT mask for PA31 */
#define PORT_PB00                   _UL_(1 << 0)    /**< PORT mask for PB00 */
#define PORT_PB01                   _UL_(1 << 1)    /**< PORT mask for PB01 */
#define PORT_PB02                   _UL_(1 << 2)    /**< PORT mask for PB02 */
#define PORT_PB03                   _UL_(1 << 3)    /**< PORT mask for PB03 */
#define PORT_PB04                   _UL_(1 << 4)    /**< PORT mask for PB04 */
#define PORT_PB05                   _UL_(1 << 5)    /**< PORT mask for PB05 */
#define PORT_PB06                   _UL_(1 << 6)    /**< PORT mask for PB06 */
#define PORT_PB07                   _UL_(1 << 7)    /**< PORT mask for PB07 */
#define PORT_PB08                   _UL_(1 << 8)    /**< PORT mask for PB08 */
#define PORT_PB09                   _UL_(1 << 9)    /**< PORT mask for PB09 */
#define PORT_PB10                   _UL_(1 << 10)   /**< PORT mask for PB10 */
#define PORT_PB11                   _UL_(1 << 11)   /**< PORT mask for PB11 */
#define PORT_PB12                   _UL_(1 << 12)   /**< PORT mask for PB12 */
#define PORT_PB13                   _UL_(1 << 13)   /**< PORT mask for PB13 */
#define PORT_PB14                   _UL_(1 << 14)   /**< PORT mask for PB14 */
#define PORT_PB15                   _UL_(1 << 15)   /**< PORT mask for PB15 */
#define PORT_PB16                   _UL_(1 << 16)   /**< PORT mask for PB16 */
#define PORT_PB17                   _UL_(1 << 17)   /**< PORT mask for PB17 */
#define PORT_PB18                   _UL_(1 << 18)   /**< PORT mask for PB18 */
#define PORT_PB19                   _UL_(1 << 19)   /**< PORT mask for PB19 */
#define PORT_PB20                   _UL_(1 << 20)   /**< PORT mask for PB20 */
#define PORT_PB21                   _UL_(1 << 21)   /**< PORT mask for PB21 */
#define PORT_PB22                   _UL_(1 << 22)   /**< PORT mask for PB22 */
#define PORT_PB23                   _UL_(1 << 23)   /**< PORT mask for PB23 */
#define PORT_PB24                   _UL_(1 << 24)   /**< PORT mask for PB24 */
#define PORT_PB25                   _UL_(1 << 25)   /**< PORT mask for PB25 */
#define PORT_PB30                   _UL_(1 << 30)   /**< PORT mask for PB30 */
#define PORT_PB31                   _UL_(1 << 31)   /**< PORT mask for PB31 */
#define PORT_PC00                   _UL_(1 << 0)    /**< PORT mask for PC00 */
#define PORT_PC01                   _UL_(1 << 1)    /**< PORT mask for PC01 */
#define PORT_PC02                   _UL_(1 << 2)    /**< PORT mask for PC02 */
#define PORT_PC03                   _UL_(1 << 3)    /**< PORT mask for PC03 */
#define PORT_PC05                   _UL_(1 << 5)    /**< PORT mask for PC05 */
#define PORT_PC06                   _UL_(1 << 6)    /**< PORT mask for PC06 */
#define PORT_PC07                   _UL_(1 << 7)    /**< PORT mask for PC07 */
#define PORT_PC08                   _UL_(1 << 8)    /**< PORT mask for PC08 */
#define PORT_PC09                   _UL_(1 << 9)    /**< PORT mask for PC09 */
#define PORT_PC10                   _UL_(1 << 10)   /**< PORT mask for PC10 */
#define PORT_PC11                   _UL_(1 << 11)   /**< PORT mask for PC11 */
#define PORT_PC12                   _UL_(1 << 12)   /**< PORT mask for PC12 */
#define PORT_PC13                   _UL_(1 << 13)   /**< PORT mask for PC13 */
#define PORT_PC14                   _UL_(1 << 14)   /**< PORT mask for PC14 */
#define PORT_PC15                   _UL_(1 << 15)   /**< PORT mask for PC15 */
#define PORT_PC16                   _UL_(1 << 16)   /**< PORT mask for PC16 */
#define PORT_PC17                   _UL_(1 << 17)   /**< PORT mask for PC17 */
#define PORT_PC18                   _UL_(1 << 18)   /**< PORT mask for PC18 */
#define PORT_PC19                   _UL_(1 << 19)   /**< PORT mask for PC19 */
#define PORT_PC20                   _UL_(1 << 20)   /**< PORT mask for PC20 */
#define PORT_PC21                   _UL_(1 << 21)   /**< PORT mask for PC21 */
#define PORT_PC24                   _UL_(1 << 24)   /**< PORT mask for PC24 */
#define PORT_PC25                   _UL_(1 << 25)   /**< PORT mask for PC25 */
#define PORT_PC26                   _UL_(1 << 26)   /**< PORT mask for PC26 */
#define PORT_PC27                   _UL_(1 << 27)   /**< PORT mask for PC27 */
#define PORT_PC28                   _UL_(1 << 28)   /**< PORT mask for PC28 */

/* ========== PORT definition for AC peripheral ========== */
#define PIN_PA04B_AC_AIN0                          (4L)         
#define MUX_PA04B_AC_AIN0                          (1L)        
#define PINMUX_PA04B_AC_AIN0                       ((PIN_PA04B_AC_AIN0 << 16) | MUX_PA04B_AC_AIN0)
#define PORT_PA04B_AC_AIN0                         ((1UL) << 4)

#define PIN_PA05B_AC_AIN1                          (5L)         
#define MUX_PA05B_AC_AIN1                          (1L)        
#define PINMUX_PA05B_AC_AIN1                       ((PIN_PA05B_AC_AIN1 << 16) | MUX_PA05B_AC_AIN1)
#define PORT_PA05B_AC_AIN1                         ((1UL) << 5)

#define PIN_PA06B_AC_AIN2                          (6L)         
#define MUX_PA06B_AC_AIN2                          (1L)        
#define PINMUX_PA06B_AC_AIN2                       ((PIN_PA06B_AC_AIN2 << 16) | MUX_PA06B_AC_AIN2)
#define PORT_PA06B_AC_AIN2                         ((1UL) << 6)

#define PIN_PA07B_AC_AIN3                          (7L)         
#define MUX_PA07B_AC_AIN3                          (1L)        
#define PINMUX_PA07B_AC_AIN3                       ((PIN_PA07B_AC_AIN3 << 16) | MUX_PA07B_AC_AIN3)
#define PORT_PA07B_AC_AIN3                         ((1UL) << 7)

#define PIN_PA02B_AC_AIN4                          (2L)         
#define MUX_PA02B_AC_AIN4                          (1L)        
#define PINMUX_PA02B_AC_AIN4                       ((PIN_PA02B_AC_AIN4 << 16) | MUX_PA02B_AC_AIN4)
#define PORT_PA02B_AC_AIN4                         ((1UL) << 2)

#define PIN_PB04B_AC_AIN5                          (36L)        
#define MUX_PB04B_AC_AIN5                          (1L)        
#define PINMUX_PB04B_AC_AIN5                       ((PIN_PB04B_AC_AIN5 << 16) | MUX_PB04B_AC_AIN5)
#define PORT_PB04B_AC_AIN5                         ((1UL) << 4)

#define PIN_PB05B_AC_AIN6                          (37L)        
#define MUX_PB05B_AC_AIN6                          (1L)        
#define PINMUX_PB05B_AC_AIN6                       ((PIN_PB05B_AC_AIN6 << 16) | MUX_PB05B_AC_AIN6)
#define PORT_PB05B_AC_AIN6                         ((1UL) << 5)

#define PIN_PB06B_AC_AIN7                          (38L)        
#define MUX_PB06B_AC_AIN7                          (1L)        
#define PINMUX_PB06B_AC_AIN7                       ((PIN_PB06B_AC_AIN7 << 16) | MUX_PB06B_AC_AIN7)
#define PORT_PB06B_AC_AIN7                         ((1UL) << 6)

#define PIN_PA12H_AC_CMP0                          (12L)        
#define MUX_PA12H_AC_CMP0                          (7L)        
#define PINMUX_PA12H_AC_CMP0                       ((PIN_PA12H_AC_CMP0 << 16) | MUX_PA12H_AC_CMP0)
#define PORT_PA12H_AC_CMP0                         ((1UL) << 12)

#define PIN_PA18H_AC_CMP0                          (18L)        
#define MUX_PA18H_AC_CMP0                          (7L)        
#define PINMUX_PA18H_AC_CMP0                       ((PIN_PA18H_AC_CMP0 << 16) | MUX_PA18H_AC_CMP0)
#define PORT_PA18H_AC_CMP0                         ((1UL) << 18)

#define PIN_PB24H_AC_CMP0                          (56L)        
#define MUX_PB24H_AC_CMP0                          (7L)        
#define PINMUX_PB24H_AC_CMP0                       ((PIN_PB24H_AC_CMP0 << 16) | MUX_PB24H_AC_CMP0)
#define PORT_PB24H_AC_CMP0                         ((1UL) << 24)

#define PIN_PA13H_AC_CMP1                          (13L)        
#define MUX_PA13H_AC_CMP1                          (7L)        
#define PINMUX_PA13H_AC_CMP1                       ((PIN_PA13H_AC_CMP1 << 16) | MUX_PA13H_AC_CMP1)
#define PORT_PA13H_AC_CMP1                         ((1UL) << 13)

#define PIN_PA19H_AC_CMP1                          (19L)        
#define MUX_PA19H_AC_CMP1                          (7L)        
#define PINMUX_PA19H_AC_CMP1                       ((PIN_PA19H_AC_CMP1 << 16) | MUX_PA19H_AC_CMP1)
#define PORT_PA19H_AC_CMP1                         ((1UL) << 19)

#define PIN_PB25H_AC_CMP1                          (57L)        
#define MUX_PB25H_AC_CMP1                          (7L)        
#define PINMUX_PB25H_AC_CMP1                       ((PIN_PB25H_AC_CMP1 << 16) | MUX_PB25H_AC_CMP1)
#define PORT_PB25H_AC_CMP1                         ((1UL) << 25)

#define PIN_PA00H_AC_CMP2                          (0L)         
#define MUX_PA00H_AC_CMP2                          (7L)        
#define PINMUX_PA00H_AC_CMP2                       ((PIN_PA00H_AC_CMP2 << 16) | MUX_PA00H_AC_CMP2)
#define PORT_PA00H_AC_CMP2                         ((1UL) << 0)

#define PIN_PA24H_AC_CMP2                          (24L)        
#define MUX_PA24H_AC_CMP2                          (7L)        
#define PINMUX_PA24H_AC_CMP2                       ((PIN_PA24H_AC_CMP2 << 16) | MUX_PA24H_AC_CMP2)
#define PORT_PA24H_AC_CMP2                         ((1UL) << 24)

#define PIN_PB30H_AC_CMP2                          (62L)        
#define MUX_PB30H_AC_CMP2                          (7L)        
#define PINMUX_PB30H_AC_CMP2                       ((PIN_PB30H_AC_CMP2 << 16) | MUX_PB30H_AC_CMP2)
#define PORT_PB30H_AC_CMP2                         ((1UL) << 30)

#define PIN_PA01H_AC_CMP3                          (1L)         
#define MUX_PA01H_AC_CMP3                          (7L)        
#define PINMUX_PA01H_AC_CMP3                       ((PIN_PA01H_AC_CMP3 << 16) | MUX_PA01H_AC_CMP3)
#define PORT_PA01H_AC_CMP3                         ((1UL) << 1)

#define PIN_PA25H_AC_CMP3                          (25L)        
#define MUX_PA25H_AC_CMP3                          (7L)        
#define PINMUX_PA25H_AC_CMP3                       ((PIN_PA25H_AC_CMP3 << 16) | MUX_PA25H_AC_CMP3)
#define PORT_PA25H_AC_CMP3                         ((1UL) << 25)

#define PIN_PB31H_AC_CMP3                          (63L)        
#define MUX_PB31H_AC_CMP3                          (7L)        
#define PINMUX_PB31H_AC_CMP3                       ((PIN_PB31H_AC_CMP3 << 16) | MUX_PB31H_AC_CMP3)
#define PORT_PB31H_AC_CMP3                         ((1UL) << 31)

/* ========== PORT definition for ADC0 peripheral ========== */
#define PIN_PA02B_ADC0_AIN0                        (2L)         
#define MUX_PA02B_ADC0_AIN0                        (1L)        
#define PINMUX_PA02B_ADC0_AIN0                     ((PIN_PA02B_ADC0_AIN0 << 16) | MUX_PA02B_ADC0_AIN0)
#define PORT_PA02B_ADC0_AIN0                       ((1UL) << 2)

#define PIN_PA03B_ADC0_AIN1                        (3L)         
#define MUX_PA03B_ADC0_AIN1                        (1L)        
#define PINMUX_PA03B_ADC0_AIN1                     ((PIN_PA03B_ADC0_AIN1 << 16) | MUX_PA03B_ADC0_AIN1)
#define PORT_PA03B_ADC0_AIN1                       ((1UL) << 3)

#define PIN_PB08B_ADC0_AIN2                        (40L)        
#define MUX_PB08B_ADC0_AIN2                        (1L)        
#define PINMUX_PB08B_ADC0_AIN2                     ((PIN_PB08B_ADC0_AIN2 << 16) | MUX_PB08B_ADC0_AIN2)
#define PORT_PB08B_ADC0_AIN2                       ((1UL) << 8)

#define PIN_PB09B_ADC0_AIN3                        (41L)        
#define MUX_PB09B_ADC0_AIN3                        (1L)        
#define PINMUX_PB09B_ADC0_AIN3                     ((PIN_PB09B_ADC0_AIN3 << 16) | MUX_PB09B_ADC0_AIN3)
#define PORT_PB09B_ADC0_AIN3                       ((1UL) << 9)

#define PIN_PA04B_ADC0_AIN4                        (4L)         
#define MUX_PA04B_ADC0_AIN4                        (1L)        
#define PINMUX_PA04B_ADC0_AIN4                     ((PIN_PA04B_ADC0_AIN4 << 16) | MUX_PA04B_ADC0_AIN4)
#define PORT_PA04B_ADC0_AIN4                       ((1UL) << 4)

#define PIN_PA05B_ADC0_AIN5                        (5L)         
#define MUX_PA05B_ADC0_AIN5                        (1L)        
#define PINMUX_PA05B_ADC0_AIN5                     ((PIN_PA05B_ADC0_AIN5 << 16) | MUX_PA05B_ADC0_AIN5)
#define PORT_PA05B_ADC0_AIN5                       ((1UL) << 5)

#define PIN_PA06B_ADC0_AIN6                        (6L)         
#define MUX_PA06B_ADC0_AIN6                        (1L)        
#define PINMUX_PA06B_ADC0_AIN6                     ((PIN_PA06B_ADC0_AIN6 << 16) | MUX_PA06B_ADC0_AIN6)
#define PORT_PA06B_ADC0_AIN6                       ((1UL) << 6)

#define PIN_PA07B_ADC0_AIN7                        (7L)         
#define MUX_PA07B_ADC0_AIN7                        (1L)        
#define PINMUX_PA07B_ADC0_AIN7                     ((PIN_PA07B_ADC0_AIN7 << 16) | MUX_PA07B_ADC0_AIN7)
#define PORT_PA07B_ADC0_AIN7                       ((1UL) << 7)

#define PIN_PC00B_ADC0_AIN8                        (64L)        
#define MUX_PC00B_ADC0_AIN8                        (1L)        
#define PINMUX_PC00B_ADC0_AIN8                     ((PIN_PC00B_ADC0_AIN8 << 16) | MUX_PC00B_ADC0_AIN8)
#define PORT_PC00B_ADC0_AIN8                       ((1UL) << 0)

#define PIN_PC01B_ADC0_AIN9                        (65L)        
#define MUX_PC01B_ADC0_AIN9                        (1L)        
#define PINMUX_PC01B_ADC0_AIN9                     ((PIN_PC01B_ADC0_AIN9 << 16) | MUX_PC01B_ADC0_AIN9)
#define PORT_PC01B_ADC0_AIN9                       ((1UL) << 1)

#define PIN_PC02B_ADC0_AIN10                       (66L)        
#define MUX_PC02B_ADC0_AIN10                       (1L)        
#define PINMUX_PC02B_ADC0_AIN10                    ((PIN_PC02B_ADC0_AIN10 << 16) | MUX_PC02B_ADC0_AIN10)
#define PORT_PC02B_ADC0_AIN10                      ((1UL) << 2)

#define PIN_PC03B_ADC0_AIN11                       (67L)        
#define MUX_PC03B_ADC0_AIN11                       (1L)        
#define PINMUX_PC03B_ADC0_AIN11                    ((PIN_PC03B_ADC0_AIN11 << 16) | MUX_PC03B_ADC0_AIN11)
#define PORT_PC03B_ADC0_AIN11                      ((1UL) << 3)

#define PIN_PA03B_ADC0_VREFP                       (3L)         
#define MUX_PA03B_ADC0_VREFP                       (1L)        
#define PINMUX_PA03B_ADC0_VREFP                    ((PIN_PA03B_ADC0_VREFP << 16) | MUX_PA03B_ADC0_VREFP)
#define PORT_PA03B_ADC0_VREFP                      ((1UL) << 3)

/* ========== PORT definition for ADC1 peripheral ========== */
#define PIN_PB00B_ADC1_AIN0                        (32L)        
#define MUX_PB00B_ADC1_AIN0                        (1L)        
#define PINMUX_PB00B_ADC1_AIN0                     ((PIN_PB00B_ADC1_AIN0 << 16) | MUX_PB00B_ADC1_AIN0)
#define PORT_PB00B_ADC1_AIN0                       ((1UL) << 0)

#define PIN_PB01B_ADC1_AIN1                        (33L)        
#define MUX_PB01B_ADC1_AIN1                        (1L)        
#define PINMUX_PB01B_ADC1_AIN1                     ((PIN_PB01B_ADC1_AIN1 << 16) | MUX_PB01B_ADC1_AIN1)
#define PORT_PB01B_ADC1_AIN1                       ((1UL) << 1)

#define PIN_PB02B_ADC1_AIN2                        (34L)        
#define MUX_PB02B_ADC1_AIN2                        (1L)        
#define PINMUX_PB02B_ADC1_AIN2                     ((PIN_PB02B_ADC1_AIN2 << 16) | MUX_PB02B_ADC1_AIN2)
#define PORT_PB02B_ADC1_AIN2                       ((1UL) << 2)

#define PIN_PB03B_ADC1_AIN3                        (35L)        
#define MUX_PB03B_ADC1_AIN3                        (1L)        
#define PINMUX_PB03B_ADC1_AIN3                     ((PIN_PB03B_ADC1_AIN3 << 16) | MUX_PB03B_ADC1_AIN3)
#define PORT_PB03B_ADC1_AIN3                       ((1UL) << 3)

#define PIN_PB08B_ADC1_AIN4                        (40L)        
#define MUX_PB08B_ADC1_AIN4                        (1L)        
#define PINMUX_PB08B_ADC1_AIN4                     ((PIN_PB08B_ADC1_AIN4 << 16) | MUX_PB08B_ADC1_AIN4)
#define PORT_PB08B_ADC1_AIN4                       ((1UL) << 8)

#define PIN_PB09B_ADC1_AIN5                        (41L)        
#define MUX_PB09B_ADC1_AIN5                        (1L)        
#define PINMUX_PB09B_ADC1_AIN5                     ((PIN_PB09B_ADC1_AIN5 << 16) | MUX_PB09B_ADC1_AIN5)
#define PORT_PB09B_ADC1_AIN5                       ((1UL) << 9)

#define PIN_PB04B_ADC1_AIN6                        (36L)        
#define MUX_PB04B_ADC1_AIN6                        (1L)        
#define PINMUX_PB04B_ADC1_AIN6                     ((PIN_PB04B_ADC1_AIN6 << 16) | MUX_PB04B_ADC1_AIN6)
#define PORT_PB04B_ADC1_AIN6                       ((1UL) << 4)

#define PIN_PB05B_ADC1_AIN7                        (37L)        
#define MUX_PB05B_ADC1_AIN7                        (1L)        
#define PINMUX_PB05B_ADC1_AIN7                     ((PIN_PB05B_ADC1_AIN7 << 16) | MUX_PB05B_ADC1_AIN7)
#define PORT_PB05B_ADC1_AIN7                       ((1UL) << 5)

#define PIN_PB06B_ADC1_AIN8                        (38L)        
#define MUX_PB06B_ADC1_AIN8                        (1L)        
#define PINMUX_PB06B_ADC1_AIN8                     ((PIN_PB06B_ADC1_AIN8 << 16) | MUX_PB06B_ADC1_AIN8)
#define PORT_PB06B_ADC1_AIN8                       ((1UL) << 6)

#define PIN_PB07B_ADC1_AIN9                        (39L)        
#define MUX_PB07B_ADC1_AIN9                        (1L)        
#define PINMUX_PB07B_ADC1_AIN9                     ((PIN_PB07B_ADC1_AIN9 << 16) | MUX_PB07B_ADC1_AIN9)
#define PORT_PB07B_ADC1_AIN9                       ((1UL) << 7)

#define PIN_PA08B_ADC1_AIN10                       (8L)         
#define MUX_PA08B_ADC1_AIN10                       (1L)        
#define PINMUX_PA08B_ADC1_AIN10                    ((PIN_PA08B_ADC1_AIN10 << 16) | MUX_PA08B_ADC1_AIN10)
#define PORT_PA08B_ADC1_AIN10                      ((1UL) << 8)

#define PIN_PA09B_ADC1_AIN11                       (9L)         
#define MUX_PA09B_ADC1_AIN11                       (1L)        
#define PINMUX_PA09B_ADC1_AIN11                    ((PIN_PA09B_ADC1_AIN11 << 16) | MUX_PA09B_ADC1_AIN11)
#define PORT_PA09B_ADC1_AIN11                      ((1UL) << 9)

/* ========== PORT definition for CAN0 peripheral ========== */
#define PIN_PA23G_CAN0_RX                          (23L)        
#define MUX_PA23G_CAN0_RX                          (6L)        
#define PINMUX_PA23G_CAN0_RX                       ((PIN_PA23G_CAN0_RX << 16) | MUX_PA23G_CAN0_RX)
#define PORT_PA23G_CAN0_RX                         ((1UL) << 23)

#define PIN_PA25G_CAN0_RX                          (25L)        
#define MUX_PA25G_CAN0_RX                          (6L)        
#define PINMUX_PA25G_CAN0_RX                       ((PIN_PA25G_CAN0_RX << 16) | MUX_PA25G_CAN0_RX)
#define PORT_PA25G_CAN0_RX                         ((1UL) << 25)

#define PIN_PA22G_CAN0_TX                          (22L)        
#define MUX_PA22G_CAN0_TX                          (6L)        
#define PINMUX_PA22G_CAN0_TX                       ((PIN_PA22G_CAN0_TX << 16) | MUX_PA22G_CAN0_TX)
#define PORT_PA22G_CAN0_TX                         ((1UL) << 22)

#define PIN_PA24G_CAN0_TX                          (24L)        
#define MUX_PA24G_CAN0_TX                          (6L)        
#define PINMUX_PA24G_CAN0_TX                       ((PIN_PA24G_CAN0_TX << 16) | MUX_PA24G_CAN0_TX)
#define PORT_PA24G_CAN0_TX                         ((1UL) << 24)

/* ========== PORT definition for CAN1 peripheral ========== */
#define PIN_PB13G_CAN1_RX                          (45L)        
#define MUX_PB13G_CAN1_RX                          (6L)        
#define PINMUX_PB13G_CAN1_RX                       ((PIN_PB13G_CAN1_RX << 16) | MUX_PB13G_CAN1_RX)
#define PORT_PB13G_CAN1_RX                         ((1UL) << 13)

#define PIN_PB15G_CAN1_RX                          (47L)        
#define MUX_PB15G_CAN1_RX                          (6L)        
#define PINMUX_PB15G_CAN1_RX                       ((PIN_PB15G_CAN1_RX << 16) | MUX_PB15G_CAN1_RX)
#define PORT_PB15G_CAN1_RX                         ((1UL) << 15)

#define PIN_PB12G_CAN1_TX                          (44L)        
#define MUX_PB12G_CAN1_TX                          (6L)        
#define PINMUX_PB12G_CAN1_TX                       ((PIN_PB12G_CAN1_TX << 16) | MUX_PB12G_CAN1_TX)
#define PORT_PB12G_CAN1_TX                         ((1UL) << 12)

#define PIN_PB14G_CAN1_TX                          (46L)        
#define MUX_PB14G_CAN1_TX                          (6L)        
#define PINMUX_PB14G_CAN1_TX                       ((PIN_PB14G_CAN1_TX << 16) | MUX_PB14G_CAN1_TX)
#define PORT_PB14G_CAN1_TX                         ((1UL) << 14)

/* ========== PORT definition for CCL peripheral ========== */
#define PIN_PA04I_CCL_IN0                          (4L)         
#define MUX_PA04I_CCL_IN0                          (8L)        
#define PINMUX_PA04I_CCL_IN0                       ((PIN_PA04I_CCL_IN0 << 16) | MUX_PA04I_CCL_IN0)
#define PORT_PA04I_CCL_IN0                         ((1UL) << 4)

#define PIN_PA16I_CCL_IN0                          (16L)        
#define MUX_PA16I_CCL_IN0                          (8L)        
#define PINMUX_PA16I_CCL_IN0                       ((PIN_PA16I_CCL_IN0 << 16) | MUX_PA16I_CCL_IN0)
#define PORT_PA16I_CCL_IN0                         ((1UL) << 16)

#define PIN_PB22I_CCL_IN0                          (54L)        
#define MUX_PB22I_CCL_IN0                          (8L)        
#define PINMUX_PB22I_CCL_IN0                       ((PIN_PB22I_CCL_IN0 << 16) | MUX_PB22I_CCL_IN0)
#define PORT_PB22I_CCL_IN0                         ((1UL) << 22)

#define PIN_PA05I_CCL_IN1                          (5L)         
#define MUX_PA05I_CCL_IN1                          (8L)        
#define PINMUX_PA05I_CCL_IN1                       ((PIN_PA05I_CCL_IN1 << 16) | MUX_PA05I_CCL_IN1)
#define PORT_PA05I_CCL_IN1                         ((1UL) << 5)

#define PIN_PA17I_CCL_IN1                          (17L)        
#define MUX_PA17I_CCL_IN1                          (8L)        
#define PINMUX_PA17I_CCL_IN1                       ((PIN_PA17I_CCL_IN1 << 16) | MUX_PA17I_CCL_IN1)
#define PORT_PA17I_CCL_IN1                         ((1UL) << 17)

#define PIN_PB00I_CCL_IN1                          (32L)        
#define MUX_PB00I_CCL_IN1                          (8L)        
#define PINMUX_PB00I_CCL_IN1                       ((PIN_PB00I_CCL_IN1 << 16) | MUX_PB00I_CCL_IN1)
#define PORT_PB00I_CCL_IN1                         ((1UL) << 0)

#define PIN_PA06I_CCL_IN2                          (6L)         
#define MUX_PA06I_CCL_IN2                          (8L)        
#define PINMUX_PA06I_CCL_IN2                       ((PIN_PA06I_CCL_IN2 << 16) | MUX_PA06I_CCL_IN2)
#define PORT_PA06I_CCL_IN2                         ((1UL) << 6)

#define PIN_PA18I_CCL_IN2                          (18L)        
#define MUX_PA18I_CCL_IN2                          (8L)        
#define PINMUX_PA18I_CCL_IN2                       ((PIN_PA18I_CCL_IN2 << 16) | MUX_PA18I_CCL_IN2)
#define PORT_PA18I_CCL_IN2                         ((1UL) << 18)

#define PIN_PB01I_CCL_IN2                          (33L)        
#define MUX_PB01I_CCL_IN2                          (8L)        
#define PINMUX_PB01I_CCL_IN2                       ((PIN_PB01I_CCL_IN2 << 16) | MUX_PB01I_CCL_IN2)
#define PORT_PB01I_CCL_IN2                         ((1UL) << 1)

#define PIN_PA08I_CCL_IN3                          (8L)         
#define MUX_PA08I_CCL_IN3                          (8L)        
#define PINMUX_PA08I_CCL_IN3                       ((PIN_PA08I_CCL_IN3 << 16) | MUX_PA08I_CCL_IN3)
#define PORT_PA08I_CCL_IN3                         ((1UL) << 8)

#define PIN_PA30I_CCL_IN3                          (30L)        
#define MUX_PA30I_CCL_IN3                          (8L)        
#define PINMUX_PA30I_CCL_IN3                       ((PIN_PA30I_CCL_IN3 << 16) | MUX_PA30I_CCL_IN3)
#define PORT_PA30I_CCL_IN3                         ((1UL) << 30)

#define PIN_PA09I_CCL_IN4                          (9L)         
#define MUX_PA09I_CCL_IN4                          (8L)        
#define PINMUX_PA09I_CCL_IN4                       ((PIN_PA09I_CCL_IN4 << 16) | MUX_PA09I_CCL_IN4)
#define PORT_PA09I_CCL_IN4                         ((1UL) << 9)

#define PIN_PC27I_CCL_IN4                          (91L)        
#define MUX_PC27I_CCL_IN4                          (8L)        
#define PINMUX_PC27I_CCL_IN4                       ((PIN_PC27I_CCL_IN4 << 16) | MUX_PC27I_CCL_IN4)
#define PORT_PC27I_CCL_IN4                         ((1UL) << 27)

#define PIN_PA10I_CCL_IN5                          (10L)        
#define MUX_PA10I_CCL_IN5                          (8L)        
#define PINMUX_PA10I_CCL_IN5                       ((PIN_PA10I_CCL_IN5 << 16) | MUX_PA10I_CCL_IN5)
#define PORT_PA10I_CCL_IN5                         ((1UL) << 10)

#define PIN_PB10I_CCL_IN5                          (42L)        
#define MUX_PB10I_CCL_IN5                          (8L)        
#define PINMUX_PB10I_CCL_IN5                       ((PIN_PB10I_CCL_IN5 << 16) | MUX_PB10I_CCL_IN5)
#define PORT_PB10I_CCL_IN5                         ((1UL) << 10)

#define PIN_PC28I_CCL_IN5                          (92L)        
#define MUX_PC28I_CCL_IN5                          (8L)        
#define PINMUX_PC28I_CCL_IN5                       ((PIN_PC28I_CCL_IN5 << 16) | MUX_PC28I_CCL_IN5)
#define PORT_PC28I_CCL_IN5                         ((1UL) << 28)

#define PIN_PA22I_CCL_IN6                          (22L)        
#define MUX_PA22I_CCL_IN6                          (8L)        
#define PINMUX_PA22I_CCL_IN6                       ((PIN_PA22I_CCL_IN6 << 16) | MUX_PA22I_CCL_IN6)
#define PORT_PA22I_CCL_IN6                         ((1UL) << 22)

#define PIN_PB06I_CCL_IN6                          (38L)        
#define MUX_PB06I_CCL_IN6                          (8L)        
#define PINMUX_PB06I_CCL_IN6                       ((PIN_PB06I_CCL_IN6 << 16) | MUX_PB06I_CCL_IN6)
#define PORT_PB06I_CCL_IN6                         ((1UL) << 6)

#define PIN_PB07I_CCL_IN7                          (39L)        
#define MUX_PB07I_CCL_IN7                          (8L)        
#define PINMUX_PB07I_CCL_IN7                       ((PIN_PB07I_CCL_IN7 << 16) | MUX_PB07I_CCL_IN7)
#define PORT_PB07I_CCL_IN7                         ((1UL) << 7)

#define PIN_PA23I_CCL_IN7                          (23L)        
#define MUX_PA23I_CCL_IN7                          (8L)        
#define PINMUX_PA23I_CCL_IN7                       ((PIN_PA23I_CCL_IN7 << 16) | MUX_PA23I_CCL_IN7)
#define PORT_PA23I_CCL_IN7                         ((1UL) << 23)

#define PIN_PB08I_CCL_IN8                          (40L)        
#define MUX_PB08I_CCL_IN8                          (8L)        
#define PINMUX_PB08I_CCL_IN8                       ((PIN_PB08I_CCL_IN8 << 16) | MUX_PB08I_CCL_IN8)
#define PORT_PB08I_CCL_IN8                         ((1UL) << 8)

#define PIN_PA24I_CCL_IN8                          (24L)        
#define MUX_PA24I_CCL_IN8                          (8L)        
#define PINMUX_PA24I_CCL_IN8                       ((PIN_PA24I_CCL_IN8 << 16) | MUX_PA24I_CCL_IN8)
#define PORT_PA24I_CCL_IN8                         ((1UL) << 24)

#define PIN_PB14I_CCL_IN9                          (46L)        
#define MUX_PB14I_CCL_IN9                          (8L)        
#define PINMUX_PB14I_CCL_IN9                       ((PIN_PB14I_CCL_IN9 << 16) | MUX_PB14I_CCL_IN9)
#define PORT_PB14I_CCL_IN9                         ((1UL) << 14)

#define PIN_PC20I_CCL_IN9                          (84L)        
#define MUX_PC20I_CCL_IN9                          (8L)        
#define PINMUX_PC20I_CCL_IN9                       ((PIN_PC20I_CCL_IN9 << 16) | MUX_PC20I_CCL_IN9)
#define PORT_PC20I_CCL_IN9                         ((1UL) << 20)

#define PIN_PB15I_CCL_IN10                         (47L)        
#define MUX_PB15I_CCL_IN10                         (8L)        
#define PINMUX_PB15I_CCL_IN10                      ((PIN_PB15I_CCL_IN10 << 16) | MUX_PB15I_CCL_IN10)
#define PORT_PB15I_CCL_IN10                        ((1UL) << 15)

#define PIN_PC21I_CCL_IN10                         (85L)        
#define MUX_PC21I_CCL_IN10                         (8L)        
#define PINMUX_PC21I_CCL_IN10                      ((PIN_PC21I_CCL_IN10 << 16) | MUX_PC21I_CCL_IN10)
#define PORT_PC21I_CCL_IN10                        ((1UL) << 21)

#define PIN_PB16I_CCL_IN11                         (48L)        
#define MUX_PB16I_CCL_IN11                         (8L)        
#define PINMUX_PB16I_CCL_IN11                      ((PIN_PB16I_CCL_IN11 << 16) | MUX_PB16I_CCL_IN11)
#define PORT_PB16I_CCL_IN11                        ((1UL) << 16)

#define PIN_PA07I_CCL_OUT0                         (7L)         
#define MUX_PA07I_CCL_OUT0                         (8L)        
#define PINMUX_PA07I_CCL_OUT0                      ((PIN_PA07I_CCL_OUT0 << 16) | MUX_PA07I_CCL_OUT0)
#define PORT_PA07I_CCL_OUT0                        ((1UL) << 7)

#define PIN_PA19I_CCL_OUT0                         (19L)        
#define MUX_PA19I_CCL_OUT0                         (8L)        
#define PINMUX_PA19I_CCL_OUT0                      ((PIN_PA19I_CCL_OUT0 << 16) | MUX_PA19I_CCL_OUT0)
#define PORT_PA19I_CCL_OUT0                        ((1UL) << 19)

#define PIN_PB02I_CCL_OUT0                         (34L)        
#define MUX_PB02I_CCL_OUT0                         (8L)        
#define PINMUX_PB02I_CCL_OUT0                      ((PIN_PB02I_CCL_OUT0 << 16) | MUX_PB02I_CCL_OUT0)
#define PORT_PB02I_CCL_OUT0                        ((1UL) << 2)

#define PIN_PB23I_CCL_OUT0                         (55L)        
#define MUX_PB23I_CCL_OUT0                         (8L)        
#define PINMUX_PB23I_CCL_OUT0                      ((PIN_PB23I_CCL_OUT0 << 16) | MUX_PB23I_CCL_OUT0)
#define PORT_PB23I_CCL_OUT0                        ((1UL) << 23)

#define PIN_PA11I_CCL_OUT1                         (11L)        
#define MUX_PA11I_CCL_OUT1                         (8L)        
#define PINMUX_PA11I_CCL_OUT1                      ((PIN_PA11I_CCL_OUT1 << 16) | MUX_PA11I_CCL_OUT1)
#define PORT_PA11I_CCL_OUT1                        ((1UL) << 11)

#define PIN_PA31I_CCL_OUT1                         (31L)        
#define MUX_PA31I_CCL_OUT1                         (8L)        
#define PINMUX_PA31I_CCL_OUT1                      ((PIN_PA31I_CCL_OUT1 << 16) | MUX_PA31I_CCL_OUT1)
#define PORT_PA31I_CCL_OUT1                        ((1UL) << 31)

#define PIN_PB11I_CCL_OUT1                         (43L)        
#define MUX_PB11I_CCL_OUT1                         (8L)        
#define PINMUX_PB11I_CCL_OUT1                      ((PIN_PB11I_CCL_OUT1 << 16) | MUX_PB11I_CCL_OUT1)
#define PORT_PB11I_CCL_OUT1                        ((1UL) << 11)

#define PIN_PA25I_CCL_OUT2                         (25L)        
#define MUX_PA25I_CCL_OUT2                         (8L)        
#define PINMUX_PA25I_CCL_OUT2                      ((PIN_PA25I_CCL_OUT2 << 16) | MUX_PA25I_CCL_OUT2)
#define PORT_PA25I_CCL_OUT2                        ((1UL) << 25)

#define PIN_PB09I_CCL_OUT2                         (41L)        
#define MUX_PB09I_CCL_OUT2                         (8L)        
#define PINMUX_PB09I_CCL_OUT2                      ((PIN_PB09I_CCL_OUT2 << 16) | MUX_PB09I_CCL_OUT2)
#define PORT_PB09I_CCL_OUT2                        ((1UL) << 9)

#define PIN_PB17I_CCL_OUT3                         (49L)        
#define MUX_PB17I_CCL_OUT3                         (8L)        
#define PINMUX_PB17I_CCL_OUT3                      ((PIN_PB17I_CCL_OUT3 << 16) | MUX_PB17I_CCL_OUT3)
#define PORT_PB17I_CCL_OUT3                        ((1UL) << 17)

/* ========== PORT definition for DAC peripheral ========== */
#define PIN_PA02B_DAC_VOUT                         (2L)         
#define MUX_PA02B_DAC_VOUT                         (1L)        
#define PINMUX_PA02B_DAC_VOUT                      ((PIN_PA02B_DAC_VOUT << 16) | MUX_PA02B_DAC_VOUT)
#define PORT_PA02B_DAC_VOUT                        ((1UL) << 2)

#define PIN_PA03B_DAC_VREFP                        (3L)         
#define MUX_PA03B_DAC_VREFP                        (1L)        
#define PINMUX_PA03B_DAC_VREFP                     ((PIN_PA03B_DAC_VREFP << 16) | MUX_PA03B_DAC_VREFP)
#define PORT_PA03B_DAC_VREFP                       ((1UL) << 3)

/* ========== PORT definition for EIC peripheral ========== */
#define PIN_PA16A_EIC_EXTINT0                      (16L)        
#define MUX_PA16A_EIC_EXTINT0                      (0L)        
#define PINMUX_PA16A_EIC_EXTINT0                   ((PIN_PA16A_EIC_EXTINT0 << 16) | MUX_PA16A_EIC_EXTINT0)
#define PORT_PA16A_EIC_EXTINT0                     ((1UL) << 16)
#define PIN_PA16A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PA16 External Interrupt Line */

#define PIN_PB00A_EIC_EXTINT0                      (32L)        
#define MUX_PB00A_EIC_EXTINT0                      (0L)        
#define PINMUX_PB00A_EIC_EXTINT0                   ((PIN_PB00A_EIC_EXTINT0 << 16) | MUX_PB00A_EIC_EXTINT0)
#define PORT_PB00A_EIC_EXTINT0                     ((1UL) << 0)
#define PIN_PB00A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PB00 External Interrupt Line */

#define PIN_PB16A_EIC_EXTINT0                      (48L)        
#define MUX_PB16A_EIC_EXTINT0                      (0L)        
#define PINMUX_PB16A_EIC_EXTINT0                   ((PIN_PB16A_EIC_EXTINT0 << 16) | MUX_PB16A_EIC_EXTINT0)
#define PORT_PB16A_EIC_EXTINT0                     ((1UL) << 16)
#define PIN_PB16A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PB16 External Interrupt Line */

#define PIN_PC08A_EIC_EXTINT0                      (72L)        
#define MUX_PC08A_EIC_EXTINT0                      (0L)        
#define PINMUX_PC08A_EIC_EXTINT0                   ((PIN_PC08A_EIC_EXTINT0 << 16) | MUX_PC08A_EIC_EXTINT0)
#define PORT_PC08A_EIC_EXTINT0                     ((1UL) << 8)
#define PIN_PC08A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PC08 External Interrupt Line */

#define PIN_PC24A_EIC_EXTINT0                      (88L)        
#define MUX_PC24A_EIC_EXTINT0                      (0L)        
#define PINMUX_PC24A_EIC_EXTINT0                   ((PIN_PC24A_EIC_EXTINT0 << 16) | MUX_PC24A_EIC_EXTINT0)
#define PORT_PC24A_EIC_EXTINT0                     ((1UL) << 24)
#define PIN_PC24A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PC24 External Interrupt Line */

#define PIN_PA00A_EIC_EXTINT0                      (0L)         
#define MUX_PA00A_EIC_EXTINT0                      (0L)        
#define PINMUX_PA00A_EIC_EXTINT0                   ((PIN_PA00A_EIC_EXTINT0 << 16) | MUX_PA00A_EIC_EXTINT0)
#define PORT_PA00A_EIC_EXTINT0                     ((1UL) << 0)
#define PIN_PA00A_EIC_EXTINT_NUM                   _L_(0)       /**< EIC signal: PIN_PA00 External Interrupt Line */

#define PIN_PA17A_EIC_EXTINT1                      (17L)        
#define MUX_PA17A_EIC_EXTINT1                      (0L)        
#define PINMUX_PA17A_EIC_EXTINT1                   ((PIN_PA17A_EIC_EXTINT1 << 16) | MUX_PA17A_EIC_EXTINT1)
#define PORT_PA17A_EIC_EXTINT1                     ((1UL) << 17)
#define PIN_PA17A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PA17 External Interrupt Line */

#define PIN_PB01A_EIC_EXTINT1                      (33L)        
#define MUX_PB01A_EIC_EXTINT1                      (0L)        
#define PINMUX_PB01A_EIC_EXTINT1                   ((PIN_PB01A_EIC_EXTINT1 << 16) | MUX_PB01A_EIC_EXTINT1)
#define PORT_PB01A_EIC_EXTINT1                     ((1UL) << 1)
#define PIN_PB01A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PB01 External Interrupt Line */

#define PIN_PB17A_EIC_EXTINT1                      (49L)        
#define MUX_PB17A_EIC_EXTINT1                      (0L)        
#define PINMUX_PB17A_EIC_EXTINT1                   ((PIN_PB17A_EIC_EXTINT1 << 16) | MUX_PB17A_EIC_EXTINT1)
#define PORT_PB17A_EIC_EXTINT1                     ((1UL) << 17)
#define PIN_PB17A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PB17 External Interrupt Line */

#define PIN_PC09A_EIC_EXTINT1                      (73L)        
#define MUX_PC09A_EIC_EXTINT1                      (0L)        
#define PINMUX_PC09A_EIC_EXTINT1                   ((PIN_PC09A_EIC_EXTINT1 << 16) | MUX_PC09A_EIC_EXTINT1)
#define PORT_PC09A_EIC_EXTINT1                     ((1UL) << 9)
#define PIN_PC09A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PC09 External Interrupt Line */

#define PIN_PC25A_EIC_EXTINT1                      (89L)        
#define MUX_PC25A_EIC_EXTINT1                      (0L)        
#define PINMUX_PC25A_EIC_EXTINT1                   ((PIN_PC25A_EIC_EXTINT1 << 16) | MUX_PC25A_EIC_EXTINT1)
#define PORT_PC25A_EIC_EXTINT1                     ((1UL) << 25)
#define PIN_PC25A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PC25 External Interrupt Line */

#define PIN_PA01A_EIC_EXTINT1                      (1L)         
#define MUX_PA01A_EIC_EXTINT1                      (0L)        
#define PINMUX_PA01A_EIC_EXTINT1                   ((PIN_PA01A_EIC_EXTINT1 << 16) | MUX_PA01A_EIC_EXTINT1)
#define PORT_PA01A_EIC_EXTINT1                     ((1UL) << 1)
#define PIN_PA01A_EIC_EXTINT_NUM                   _L_(1)       /**< EIC signal: PIN_PA01 External Interrupt Line */

#define PIN_PA02A_EIC_EXTINT2                      (2L)         
#define MUX_PA02A_EIC_EXTINT2                      (0L)        
#define PINMUX_PA02A_EIC_EXTINT2                   ((PIN_PA02A_EIC_EXTINT2 << 16) | MUX_PA02A_EIC_EXTINT2)
#define PORT_PA02A_EIC_EXTINT2                     ((1UL) << 2)
#define PIN_PA02A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PA02 External Interrupt Line */

#define PIN_PA18A_EIC_EXTINT2                      (18L)        
#define MUX_PA18A_EIC_EXTINT2                      (0L)        
#define PINMUX_PA18A_EIC_EXTINT2                   ((PIN_PA18A_EIC_EXTINT2 << 16) | MUX_PA18A_EIC_EXTINT2)
#define PORT_PA18A_EIC_EXTINT2                     ((1UL) << 18)
#define PIN_PA18A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PA18 External Interrupt Line */

#define PIN_PB02A_EIC_EXTINT2                      (34L)        
#define MUX_PB02A_EIC_EXTINT2                      (0L)        
#define PINMUX_PB02A_EIC_EXTINT2                   ((PIN_PB02A_EIC_EXTINT2 << 16) | MUX_PB02A_EIC_EXTINT2)
#define PORT_PB02A_EIC_EXTINT2                     ((1UL) << 2)
#define PIN_PB02A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PB02 External Interrupt Line */

#define PIN_PB18A_EIC_EXTINT2                      (50L)        
#define MUX_PB18A_EIC_EXTINT2                      (0L)        
#define PINMUX_PB18A_EIC_EXTINT2                   ((PIN_PB18A_EIC_EXTINT2 << 16) | MUX_PB18A_EIC_EXTINT2)
#define PORT_PB18A_EIC_EXTINT2                     ((1UL) << 18)
#define PIN_PB18A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PB18 External Interrupt Line */

#define PIN_PC10A_EIC_EXTINT2                      (74L)        
#define MUX_PC10A_EIC_EXTINT2                      (0L)        
#define PINMUX_PC10A_EIC_EXTINT2                   ((PIN_PC10A_EIC_EXTINT2 << 16) | MUX_PC10A_EIC_EXTINT2)
#define PORT_PC10A_EIC_EXTINT2                     ((1UL) << 10)
#define PIN_PC10A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PC10 External Interrupt Line */

#define PIN_PC26A_EIC_EXTINT2                      (90L)        
#define MUX_PC26A_EIC_EXTINT2                      (0L)        
#define PINMUX_PC26A_EIC_EXTINT2                   ((PIN_PC26A_EIC_EXTINT2 << 16) | MUX_PC26A_EIC_EXTINT2)
#define PORT_PC26A_EIC_EXTINT2                     ((1UL) << 26)
#define PIN_PC26A_EIC_EXTINT_NUM                   _L_(2)       /**< EIC signal: PIN_PC26 External Interrupt Line */

#define PIN_PA03A_EIC_EXTINT3                      (3L)         
#define MUX_PA03A_EIC_EXTINT3                      (0L)        
#define PINMUX_PA03A_EIC_EXTINT3                   ((PIN_PA03A_EIC_EXTINT3 << 16) | MUX_PA03A_EIC_EXTINT3)
#define PORT_PA03A_EIC_EXTINT3                     ((1UL) << 3)
#define PIN_PA03A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PA03 External Interrupt Line */

#define PIN_PA19A_EIC_EXTINT3                      (19L)        
#define MUX_PA19A_EIC_EXTINT3                      (0L)        
#define PINMUX_PA19A_EIC_EXTINT3                   ((PIN_PA19A_EIC_EXTINT3 << 16) | MUX_PA19A_EIC_EXTINT3)
#define PORT_PA19A_EIC_EXTINT3                     ((1UL) << 19)
#define PIN_PA19A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PA19 External Interrupt Line */

#define PIN_PB03A_EIC_EXTINT3                      (35L)        
#define MUX_PB03A_EIC_EXTINT3                      (0L)        
#define PINMUX_PB03A_EIC_EXTINT3                   ((PIN_PB03A_EIC_EXTINT3 << 16) | MUX_PB03A_EIC_EXTINT3)
#define PORT_PB03A_EIC_EXTINT3                     ((1UL) << 3)
#define PIN_PB03A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PB03 External Interrupt Line */

#define PIN_PB19A_EIC_EXTINT3                      (51L)        
#define MUX_PB19A_EIC_EXTINT3                      (0L)        
#define PINMUX_PB19A_EIC_EXTINT3                   ((PIN_PB19A_EIC_EXTINT3 << 16) | MUX_PB19A_EIC_EXTINT3)
#define PORT_PB19A_EIC_EXTINT3                     ((1UL) << 19)
#define PIN_PB19A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PB19 External Interrupt Line */

#define PIN_PC11A_EIC_EXTINT3                      (75L)        
#define MUX_PC11A_EIC_EXTINT3                      (0L)        
#define PINMUX_PC11A_EIC_EXTINT3                   ((PIN_PC11A_EIC_EXTINT3 << 16) | MUX_PC11A_EIC_EXTINT3)
#define PORT_PC11A_EIC_EXTINT3                     ((1UL) << 11)
#define PIN_PC11A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PC11 External Interrupt Line */

#define PIN_PC27A_EIC_EXTINT3                      (91L)        
#define MUX_PC27A_EIC_EXTINT3                      (0L)        
#define PINMUX_PC27A_EIC_EXTINT3                   ((PIN_PC27A_EIC_EXTINT3 << 16) | MUX_PC27A_EIC_EXTINT3)
#define PORT_PC27A_EIC_EXTINT3                     ((1UL) << 27)
#define PIN_PC27A_EIC_EXTINT_NUM                   _L_(3)       /**< EIC signal: PIN_PC27 External Interrupt Line */

#define PIN_PA04A_EIC_EXTINT4                      (4L)         
#define MUX_PA04A_EIC_EXTINT4                      (0L)        
#define PINMUX_PA04A_EIC_EXTINT4                   ((PIN_PA04A_EIC_EXTINT4 << 16) | MUX_PA04A_EIC_EXTINT4)
#define PORT_PA04A_EIC_EXTINT4                     ((1UL) << 4)
#define PIN_PA04A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PA04 External Interrupt Line */

#define PIN_PA20A_EIC_EXTINT4                      (20L)        
#define MUX_PA20A_EIC_EXTINT4                      (0L)        
#define PINMUX_PA20A_EIC_EXTINT4                   ((PIN_PA20A_EIC_EXTINT4 << 16) | MUX_PA20A_EIC_EXTINT4)
#define PORT_PA20A_EIC_EXTINT4                     ((1UL) << 20)
#define PIN_PA20A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PA20 External Interrupt Line */

#define PIN_PB04A_EIC_EXTINT4                      (36L)        
#define MUX_PB04A_EIC_EXTINT4                      (0L)        
#define PINMUX_PB04A_EIC_EXTINT4                   ((PIN_PB04A_EIC_EXTINT4 << 16) | MUX_PB04A_EIC_EXTINT4)
#define PORT_PB04A_EIC_EXTINT4                     ((1UL) << 4)
#define PIN_PB04A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PB04 External Interrupt Line */

#define PIN_PB20A_EIC_EXTINT4                      (52L)        
#define MUX_PB20A_EIC_EXTINT4                      (0L)        
#define PINMUX_PB20A_EIC_EXTINT4                   ((PIN_PB20A_EIC_EXTINT4 << 16) | MUX_PB20A_EIC_EXTINT4)
#define PORT_PB20A_EIC_EXTINT4                     ((1UL) << 20)
#define PIN_PB20A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PB20 External Interrupt Line */

#define PIN_PC12A_EIC_EXTINT4                      (76L)        
#define MUX_PC12A_EIC_EXTINT4                      (0L)        
#define PINMUX_PC12A_EIC_EXTINT4                   ((PIN_PC12A_EIC_EXTINT4 << 16) | MUX_PC12A_EIC_EXTINT4)
#define PORT_PC12A_EIC_EXTINT4                     ((1UL) << 12)
#define PIN_PC12A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PC12 External Interrupt Line */

#define PIN_PC28A_EIC_EXTINT4                      (92L)        
#define MUX_PC28A_EIC_EXTINT4                      (0L)        
#define PINMUX_PC28A_EIC_EXTINT4                   ((PIN_PC28A_EIC_EXTINT4 << 16) | MUX_PC28A_EIC_EXTINT4)
#define PORT_PC28A_EIC_EXTINT4                     ((1UL) << 28)
#define PIN_PC28A_EIC_EXTINT_NUM                   _L_(4)       /**< EIC signal: PIN_PC28 External Interrupt Line */

#define PIN_PA05A_EIC_EXTINT5                      (5L)         
#define MUX_PA05A_EIC_EXTINT5                      (0L)        
#define PINMUX_PA05A_EIC_EXTINT5                   ((PIN_PA05A_EIC_EXTINT5 << 16) | MUX_PA05A_EIC_EXTINT5)
#define PORT_PA05A_EIC_EXTINT5                     ((1UL) << 5)
#define PIN_PA05A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PA05 External Interrupt Line */

#define PIN_PA21A_EIC_EXTINT5                      (21L)        
#define MUX_PA21A_EIC_EXTINT5                      (0L)        
#define PINMUX_PA21A_EIC_EXTINT5                   ((PIN_PA21A_EIC_EXTINT5 << 16) | MUX_PA21A_EIC_EXTINT5)
#define PORT_PA21A_EIC_EXTINT5                     ((1UL) << 21)
#define PIN_PA21A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PA21 External Interrupt Line */

#define PIN_PB05A_EIC_EXTINT5                      (37L)        
#define MUX_PB05A_EIC_EXTINT5                      (0L)        
#define PINMUX_PB05A_EIC_EXTINT5                   ((PIN_PB05A_EIC_EXTINT5 << 16) | MUX_PB05A_EIC_EXTINT5)
#define PORT_PB05A_EIC_EXTINT5                     ((1UL) << 5)
#define PIN_PB05A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PB05 External Interrupt Line */

#define PIN_PB21A_EIC_EXTINT5                      (53L)        
#define MUX_PB21A_EIC_EXTINT5                      (0L)        
#define PINMUX_PB21A_EIC_EXTINT5                   ((PIN_PB21A_EIC_EXTINT5 << 16) | MUX_PB21A_EIC_EXTINT5)
#define PORT_PB21A_EIC_EXTINT5                     ((1UL) << 21)
#define PIN_PB21A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PB21 External Interrupt Line */

#define PIN_PC13A_EIC_EXTINT5                      (77L)        
#define MUX_PC13A_EIC_EXTINT5                      (0L)        
#define PINMUX_PC13A_EIC_EXTINT5                   ((PIN_PC13A_EIC_EXTINT5 << 16) | MUX_PC13A_EIC_EXTINT5)
#define PORT_PC13A_EIC_EXTINT5                     ((1UL) << 13)
#define PIN_PC13A_EIC_EXTINT_NUM                   _L_(5)       /**< EIC signal: PIN_PC13 External Interrupt Line */

#define PIN_PA06A_EIC_EXTINT6                      (6L)         
#define MUX_PA06A_EIC_EXTINT6                      (0L)        
#define PINMUX_PA06A_EIC_EXTINT6                   ((PIN_PA06A_EIC_EXTINT6 << 16) | MUX_PA06A_EIC_EXTINT6)
#define PORT_PA06A_EIC_EXTINT6                     ((1UL) << 6)
#define PIN_PA06A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PA06 External Interrupt Line */

#define PIN_PA22A_EIC_EXTINT6                      (22L)        
#define MUX_PA22A_EIC_EXTINT6                      (0L)        
#define PINMUX_PA22A_EIC_EXTINT6                   ((PIN_PA22A_EIC_EXTINT6 << 16) | MUX_PA22A_EIC_EXTINT6)
#define PORT_PA22A_EIC_EXTINT6                     ((1UL) << 22)
#define PIN_PA22A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PA22 External Interrupt Line */

#define PIN_PB06A_EIC_EXTINT6                      (38L)        
#define MUX_PB06A_EIC_EXTINT6                      (0L)        
#define PINMUX_PB06A_EIC_EXTINT6                   ((PIN_PB06A_EIC_EXTINT6 << 16) | MUX_PB06A_EIC_EXTINT6)
#define PORT_PB06A_EIC_EXTINT6                     ((1UL) << 6)
#define PIN_PB06A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PB06 External Interrupt Line */

#define PIN_PB22A_EIC_EXTINT6                      (54L)        
#define MUX_PB22A_EIC_EXTINT6                      (0L)        
#define PINMUX_PB22A_EIC_EXTINT6                   ((PIN_PB22A_EIC_EXTINT6 << 16) | MUX_PB22A_EIC_EXTINT6)
#define PORT_PB22A_EIC_EXTINT6                     ((1UL) << 22)
#define PIN_PB22A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PB22 External Interrupt Line */

#define PIN_PC14A_EIC_EXTINT6                      (78L)        
#define MUX_PC14A_EIC_EXTINT6                      (0L)        
#define PINMUX_PC14A_EIC_EXTINT6                   ((PIN_PC14A_EIC_EXTINT6 << 16) | MUX_PC14A_EIC_EXTINT6)
#define PORT_PC14A_EIC_EXTINT6                     ((1UL) << 14)
#define PIN_PC14A_EIC_EXTINT_NUM                   _L_(6)       /**< EIC signal: PIN_PC14 External Interrupt Line */

#define PIN_PA07A_EIC_EXTINT7                      (7L)         
#define MUX_PA07A_EIC_EXTINT7                      (0L)        
#define PINMUX_PA07A_EIC_EXTINT7                   ((PIN_PA07A_EIC_EXTINT7 << 16) | MUX_PA07A_EIC_EXTINT7)
#define PORT_PA07A_EIC_EXTINT7                     ((1UL) << 7)
#define PIN_PA07A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PA07 External Interrupt Line */

#define PIN_PA23A_EIC_EXTINT7                      (23L)        
#define MUX_PA23A_EIC_EXTINT7                      (0L)        
#define PINMUX_PA23A_EIC_EXTINT7                   ((PIN_PA23A_EIC_EXTINT7 << 16) | MUX_PA23A_EIC_EXTINT7)
#define PORT_PA23A_EIC_EXTINT7                     ((1UL) << 23)
#define PIN_PA23A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PA23 External Interrupt Line */

#define PIN_PB07A_EIC_EXTINT7                      (39L)        
#define MUX_PB07A_EIC_EXTINT7                      (0L)        
#define PINMUX_PB07A_EIC_EXTINT7                   ((PIN_PB07A_EIC_EXTINT7 << 16) | MUX_PB07A_EIC_EXTINT7)
#define PORT_PB07A_EIC_EXTINT7                     ((1UL) << 7)
#define PIN_PB07A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PB07 External Interrupt Line */

#define PIN_PB23A_EIC_EXTINT7                      (55L)        
#define MUX_PB23A_EIC_EXTINT7                      (0L)        
#define PINMUX_PB23A_EIC_EXTINT7                   ((PIN_PB23A_EIC_EXTINT7 << 16) | MUX_PB23A_EIC_EXTINT7)
#define PORT_PB23A_EIC_EXTINT7                     ((1UL) << 23)
#define PIN_PB23A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PB23 External Interrupt Line */

#define PIN_PC15A_EIC_EXTINT7                      (79L)        
#define MUX_PC15A_EIC_EXTINT7                      (0L)        
#define PINMUX_PC15A_EIC_EXTINT7                   ((PIN_PC15A_EIC_EXTINT7 << 16) | MUX_PC15A_EIC_EXTINT7)
#define PORT_PC15A_EIC_EXTINT7                     ((1UL) << 15)
#define PIN_PC15A_EIC_EXTINT_NUM                   _L_(7)       /**< EIC signal: PIN_PC15 External Interrupt Line */

#define PIN_PB08A_EIC_EXTINT8                      (40L)        
#define MUX_PB08A_EIC_EXTINT8                      (0L)        
#define PINMUX_PB08A_EIC_EXTINT8                   ((PIN_PB08A_EIC_EXTINT8 << 16) | MUX_PB08A_EIC_EXTINT8)
#define PORT_PB08A_EIC_EXTINT8                     ((1UL) << 8)
#define PIN_PB08A_EIC_EXTINT_NUM                   _L_(8)       /**< EIC signal: PIN_PB08 External Interrupt Line */

#define PIN_PB24A_EIC_EXTINT8                      (56L)        
#define MUX_PB24A_EIC_EXTINT8                      (0L)        
#define PINMUX_PB24A_EIC_EXTINT8                   ((PIN_PB24A_EIC_EXTINT8 << 16) | MUX_PB24A_EIC_EXTINT8)
#define PORT_PB24A_EIC_EXTINT8                     ((1UL) << 24)
#define PIN_PB24A_EIC_EXTINT_NUM                   _L_(8)       /**< EIC signal: PIN_PB24 External Interrupt Line */

#define PIN_PC00A_EIC_EXTINT8                      (64L)        
#define MUX_PC00A_EIC_EXTINT8                      (0L)        
#define PINMUX_PC00A_EIC_EXTINT8                   ((PIN_PC00A_EIC_EXTINT8 << 16) | MUX_PC00A_EIC_EXTINT8)
#define PORT_PC00A_EIC_EXTINT8                     ((1UL) << 0)
#define PIN_PC00A_EIC_EXTINT_NUM                   _L_(8)       /**< EIC signal: PIN_PC00 External Interrupt Line */

#define PIN_PC16A_EIC_EXTINT8                      (80L)        
#define MUX_PC16A_EIC_EXTINT8                      (0L)        
#define PINMUX_PC16A_EIC_EXTINT8                   ((PIN_PC16A_EIC_EXTINT8 << 16) | MUX_PC16A_EIC_EXTINT8)
#define PORT_PC16A_EIC_EXTINT8                     ((1UL) << 16)
#define PIN_PC16A_EIC_EXTINT_NUM                   _L_(8)       /**< EIC signal: PIN_PC16 External Interrupt Line */

#define PIN_PA28A_EIC_EXTINT8                      (28L)        
#define MUX_PA28A_EIC_EXTINT8                      (0L)        
#define PINMUX_PA28A_EIC_EXTINT8                   ((PIN_PA28A_EIC_EXTINT8 << 16) | MUX_PA28A_EIC_EXTINT8)
#define PORT_PA28A_EIC_EXTINT8                     ((1UL) << 28)
#define PIN_PA28A_EIC_EXTINT_NUM                   _L_(8)       /**< EIC signal: PIN_PA28 External Interrupt Line */

#define PIN_PA09A_EIC_EXTINT9                      (9L)         
#define MUX_PA09A_EIC_EXTINT9                      (0L)        
#define PINMUX_PA09A_EIC_EXTINT9                   ((PIN_PA09A_EIC_EXTINT9 << 16) | MUX_PA09A_EIC_EXTINT9)
#define PORT_PA09A_EIC_EXTINT9                     ((1UL) << 9)
#define PIN_PA09A_EIC_EXTINT_NUM                   _L_(9)       /**< EIC signal: PIN_PA09 External Interrupt Line */

#define PIN_PB09A_EIC_EXTINT9                      (41L)        
#define MUX_PB09A_EIC_EXTINT9                      (0L)        
#define PINMUX_PB09A_EIC_EXTINT9                   ((PIN_PB09A_EIC_EXTINT9 << 16) | MUX_PB09A_EIC_EXTINT9)
#define PORT_PB09A_EIC_EXTINT9                     ((1UL) << 9)
#define PIN_PB09A_EIC_EXTINT_NUM                   _L_(9)       /**< EIC signal: PIN_PB09 External Interrupt Line */

#define PIN_PB25A_EIC_EXTINT9                      (57L)        
#define MUX_PB25A_EIC_EXTINT9                      (0L)        
#define PINMUX_PB25A_EIC_EXTINT9                   ((PIN_PB25A_EIC_EXTINT9 << 16) | MUX_PB25A_EIC_EXTINT9)
#define PORT_PB25A_EIC_EXTINT9                     ((1UL) << 25)
#define PIN_PB25A_EIC_EXTINT_NUM                   _L_(9)       /**< EIC signal: PIN_PB25 External Interrupt Line */

#define PIN_PC01A_EIC_EXTINT9                      (65L)        
#define MUX_PC01A_EIC_EXTINT9                      (0L)        
#define PINMUX_PC01A_EIC_EXTINT9                   ((PIN_PC01A_EIC_EXTINT9 << 16) | MUX_PC01A_EIC_EXTINT9)
#define PORT_PC01A_EIC_EXTINT9                     ((1UL) << 1)
#define PIN_PC01A_EIC_EXTINT_NUM                   _L_(9)       /**< EIC signal: PIN_PC01 External Interrupt Line */

#define PIN_PC17A_EIC_EXTINT9                      (81L)        
#define MUX_PC17A_EIC_EXTINT9                      (0L)        
#define PINMUX_PC17A_EIC_EXTINT9                   ((PIN_PC17A_EIC_EXTINT9 << 16) | MUX_PC17A_EIC_EXTINT9)
#define PORT_PC17A_EIC_EXTINT9                     ((1UL) << 17)
#define PIN_PC17A_EIC_EXTINT_NUM                   _L_(9)       /**< EIC signal: PIN_PC17 External Interrupt Line */

#define PIN_PA10A_EIC_EXTINT10                     (10L)        
#define MUX_PA10A_EIC_EXTINT10                     (0L)        
#define PINMUX_PA10A_EIC_EXTINT10                  ((PIN_PA10A_EIC_EXTINT10 << 16) | MUX_PA10A_EIC_EXTINT10)
#define PORT_PA10A_EIC_EXTINT10                    ((1UL) << 10)
#define PIN_PA10A_EIC_EXTINT_NUM                   _L_(10)      /**< EIC signal: PIN_PA10 External Interrupt Line */

#define PIN_PA30A_EIC_EXTINT10                     (30L)        
#define MUX_PA30A_EIC_EXTINT10                     (0L)        
#define PINMUX_PA30A_EIC_EXTINT10                  ((PIN_PA30A_EIC_EXTINT10 << 16) | MUX_PA30A_EIC_EXTINT10)
#define PORT_PA30A_EIC_EXTINT10                    ((1UL) << 30)
#define PIN_PA30A_EIC_EXTINT_NUM                   _L_(10)      /**< EIC signal: PIN_PA30 External Interrupt Line */

#define PIN_PB10A_EIC_EXTINT10                     (42L)        
#define MUX_PB10A_EIC_EXTINT10                     (0L)        
#define PINMUX_PB10A_EIC_EXTINT10                  ((PIN_PB10A_EIC_EXTINT10 << 16) | MUX_PB10A_EIC_EXTINT10)
#define PORT_PB10A_EIC_EXTINT10                    ((1UL) << 10)
#define PIN_PB10A_EIC_EXTINT_NUM                   _L_(10)      /**< EIC signal: PIN_PB10 External Interrupt Line */

#define PIN_PC02A_EIC_EXTINT10                     (66L)        
#define MUX_PC02A_EIC_EXTINT10                     (0L)        
#define PINMUX_PC02A_EIC_EXTINT10                  ((PIN_PC02A_EIC_EXTINT10 << 16) | MUX_PC02A_EIC_EXTINT10)
#define PORT_PC02A_EIC_EXTINT10                    ((1UL) << 2)
#define PIN_PC02A_EIC_EXTINT_NUM                   _L_(10)      /**< EIC signal: PIN_PC02 External Interrupt Line */

#define PIN_PC18A_EIC_EXTINT10                     (82L)        
#define MUX_PC18A_EIC_EXTINT10                     (0L)        
#define PINMUX_PC18A_EIC_EXTINT10                  ((PIN_PC18A_EIC_EXTINT10 << 16) | MUX_PC18A_EIC_EXTINT10)
#define PORT_PC18A_EIC_EXTINT10                    ((1UL) << 18)
#define PIN_PC18A_EIC_EXTINT_NUM                   _L_(10)      /**< EIC signal: PIN_PC18 External Interrupt Line */

#define PIN_PA11A_EIC_EXTINT11                     (11L)        
#define MUX_PA11A_EIC_EXTINT11                     (0L)        
#define PINMUX_PA11A_EIC_EXTINT11                  ((PIN_PA11A_EIC_EXTINT11 << 16) | MUX_PA11A_EIC_EXTINT11)
#define PORT_PA11A_EIC_EXTINT11                    ((1UL) << 11)
#define PIN_PA11A_EIC_EXTINT_NUM                   _L_(11)      /**< EIC signal: PIN_PA11 External Interrupt Line */

#define PIN_PA31A_EIC_EXTINT11                     (31L)        
#define MUX_PA31A_EIC_EXTINT11                     (0L)        
#define PINMUX_PA31A_EIC_EXTINT11                  ((PIN_PA31A_EIC_EXTINT11 << 16) | MUX_PA31A_EIC_EXTINT11)
#define PORT_PA31A_EIC_EXTINT11                    ((1UL) << 31)
#define PIN_PA31A_EIC_EXTINT_NUM                   _L_(11)      /**< EIC signal: PIN_PA31 External Interrupt Line */

#define PIN_PB11A_EIC_EXTINT11                     (43L)        
#define MUX_PB11A_EIC_EXTINT11                     (0L)        
#define PINMUX_PB11A_EIC_EXTINT11                  ((PIN_PB11A_EIC_EXTINT11 << 16) | MUX_PB11A_EIC_EXTINT11)
#define PORT_PB11A_EIC_EXTINT11                    ((1UL) << 11)
#define PIN_PB11A_EIC_EXTINT_NUM                   _L_(11)      /**< EIC signal: PIN_PB11 External Interrupt Line */

#define PIN_PC03A_EIC_EXTINT11                     (67L)        
#define MUX_PC03A_EIC_EXTINT11                     (0L)        
#define PINMUX_PC03A_EIC_EXTINT11                  ((PIN_PC03A_EIC_EXTINT11 << 16) | MUX_PC03A_EIC_EXTINT11)
#define PORT_PC03A_EIC_EXTINT11                    ((1UL) << 3)
#define PIN_PC03A_EIC_EXTINT_NUM                   _L_(11)      /**< EIC signal: PIN_PC03 External Interrupt Line */

#define PIN_PC19A_EIC_EXTINT11                     (83L)        
#define MUX_PC19A_EIC_EXTINT11                     (0L)        
#define PINMUX_PC19A_EIC_EXTINT11                  ((PIN_PC19A_EIC_EXTINT11 << 16) | MUX_PC19A_EIC_EXTINT11)
#define PORT_PC19A_EIC_EXTINT11                    ((1UL) << 19)
#define PIN_PC19A_EIC_EXTINT_NUM                   _L_(11)      /**< EIC signal: PIN_PC19 External Interrupt Line */

#define PIN_PA12A_EIC_EXTINT12                     (12L)        
#define MUX_PA12A_EIC_EXTINT12                     (0L)        
#define PINMUX_PA12A_EIC_EXTINT12                  ((PIN_PA12A_EIC_EXTINT12 << 16) | MUX_PA12A_EIC_EXTINT12)
#define PORT_PA12A_EIC_EXTINT12                    ((1UL) << 12)
#define PIN_PA12A_EIC_EXTINT_NUM                   _L_(12)      /**< EIC signal: PIN_PA12 External Interrupt Line */

#define PIN_PA24A_EIC_EXTINT12                     (24L)        
#define MUX_PA24A_EIC_EXTINT12                     (0L)        
#define PINMUX_PA24A_EIC_EXTINT12                  ((PIN_PA24A_EIC_EXTINT12 << 16) | MUX_PA24A_EIC_EXTINT12)
#define PORT_PA24A_EIC_EXTINT12                    ((1UL) << 24)
#define PIN_PA24A_EIC_EXTINT_NUM                   _L_(12)      /**< EIC signal: PIN_PA24 External Interrupt Line */

#define PIN_PB12A_EIC_EXTINT12                     (44L)        
#define MUX_PB12A_EIC_EXTINT12                     (0L)        
#define PINMUX_PB12A_EIC_EXTINT12                  ((PIN_PB12A_EIC_EXTINT12 << 16) | MUX_PB12A_EIC_EXTINT12)
#define PORT_PB12A_EIC_EXTINT12                    ((1UL) << 12)
#define PIN_PB12A_EIC_EXTINT_NUM                   _L_(12)      /**< EIC signal: PIN_PB12 External Interrupt Line */

#define PIN_PC20A_EIC_EXTINT12                     (84L)        
#define MUX_PC20A_EIC_EXTINT12                     (0L)        
#define PINMUX_PC20A_EIC_EXTINT12                  ((PIN_PC20A_EIC_EXTINT12 << 16) | MUX_PC20A_EIC_EXTINT12)
#define PORT_PC20A_EIC_EXTINT12                    ((1UL) << 20)
#define PIN_PC20A_EIC_EXTINT_NUM                   _L_(12)      /**< EIC signal: PIN_PC20 External Interrupt Line */

#define PIN_PA13A_EIC_EXTINT13                     (13L)        
#define MUX_PA13A_EIC_EXTINT13                     (0L)        
#define PINMUX_PA13A_EIC_EXTINT13                  ((PIN_PA13A_EIC_EXTINT13 << 16) | MUX_PA13A_EIC_EXTINT13)
#define PORT_PA13A_EIC_EXTINT13                    ((1UL) << 13)
#define PIN_PA13A_EIC_EXTINT_NUM                   _L_(13)      /**< EIC signal: PIN_PA13 External Interrupt Line */

#define PIN_PA25A_EIC_EXTINT13                     (25L)        
#define MUX_PA25A_EIC_EXTINT13                     (0L)        
#define PINMUX_PA25A_EIC_EXTINT13                  ((PIN_PA25A_EIC_EXTINT13 << 16) | MUX_PA25A_EIC_EXTINT13)
#define PORT_PA25A_EIC_EXTINT13                    ((1UL) << 25)
#define PIN_PA25A_EIC_EXTINT_NUM                   _L_(13)      /**< EIC signal: PIN_PA25 External Interrupt Line */

#define PIN_PB13A_EIC_EXTINT13                     (45L)        
#define MUX_PB13A_EIC_EXTINT13                     (0L)        
#define PINMUX_PB13A_EIC_EXTINT13                  ((PIN_PB13A_EIC_EXTINT13 << 16) | MUX_PB13A_EIC_EXTINT13)
#define PORT_PB13A_EIC_EXTINT13                    ((1UL) << 13)
#define PIN_PB13A_EIC_EXTINT_NUM                   _L_(13)      /**< EIC signal: PIN_PB13 External Interrupt Line */

#define PIN_PC05A_EIC_EXTINT13                     (69L)        
#define MUX_PC05A_EIC_EXTINT13                     (0L)        
#define PINMUX_PC05A_EIC_EXTINT13                  ((PIN_PC05A_EIC_EXTINT13 << 16) | MUX_PC05A_EIC_EXTINT13)
#define PORT_PC05A_EIC_EXTINT13                    ((1UL) << 5)
#define PIN_PC05A_EIC_EXTINT_NUM                   _L_(13)      /**< EIC signal: PIN_PC05 External Interrupt Line */

#define PIN_PC21A_EIC_EXTINT13                     (85L)        
#define MUX_PC21A_EIC_EXTINT13                     (0L)        
#define PINMUX_PC21A_EIC_EXTINT13                  ((PIN_PC21A_EIC_EXTINT13 << 16) | MUX_PC21A_EIC_EXTINT13)
#define PORT_PC21A_EIC_EXTINT13                    ((1UL) << 21)
#define PIN_PC21A_EIC_EXTINT_NUM                   _L_(13)      /**< EIC signal: PIN_PC21 External Interrupt Line */

#define PIN_PB14A_EIC_EXTINT14                     (46L)        
#define MUX_PB14A_EIC_EXTINT14                     (0L)        
#define PINMUX_PB14A_EIC_EXTINT14                  ((PIN_PB14A_EIC_EXTINT14 << 16) | MUX_PB14A_EIC_EXTINT14)
#define PORT_PB14A_EIC_EXTINT14                    ((1UL) << 14)
#define PIN_PB14A_EIC_EXTINT_NUM                   _L_(14)      /**< EIC signal: PIN_PB14 External Interrupt Line */

#define PIN_PB30A_EIC_EXTINT14                     (62L)        
#define MUX_PB30A_EIC_EXTINT14                     (0L)        
#define PINMUX_PB30A_EIC_EXTINT14                  ((PIN_PB30A_EIC_EXTINT14 << 16) | MUX_PB30A_EIC_EXTINT14)
#define PORT_PB30A_EIC_EXTINT14                    ((1UL) << 30)
#define PIN_PB30A_EIC_EXTINT_NUM                   _L_(14)      /**< EIC signal: PIN_PB30 External Interrupt Line */

#define PIN_PC06A_EIC_EXTINT14                     (70L)        
#define MUX_PC06A_EIC_EXTINT14                     (0L)        
#define PINMUX_PC06A_EIC_EXTINT14                  ((PIN_PC06A_EIC_EXTINT14 << 16) | MUX_PC06A_EIC_EXTINT14)
#define PORT_PC06A_EIC_EXTINT14                    ((1UL) << 6)
#define PIN_PC06A_EIC_EXTINT_NUM                   _L_(14)      /**< EIC signal: PIN_PC06 External Interrupt Line */

#define PIN_PA14A_EIC_EXTINT14                     (14L)        
#define MUX_PA14A_EIC_EXTINT14                     (0L)        
#define PINMUX_PA14A_EIC_EXTINT14                  ((PIN_PA14A_EIC_EXTINT14 << 16) | MUX_PA14A_EIC_EXTINT14)
#define PORT_PA14A_EIC_EXTINT14                    ((1UL) << 14)
#define PIN_PA14A_EIC_EXTINT_NUM                   _L_(14)      /**< EIC signal: PIN_PA14 External Interrupt Line */

#define PIN_PA27A_EIC_EXTINT15                     (27L)        
#define MUX_PA27A_EIC_EXTINT15                     (0L)        
#define PINMUX_PA27A_EIC_EXTINT15                  ((PIN_PA27A_EIC_EXTINT15 << 16) | MUX_PA27A_EIC_EXTINT15)
#define PORT_PA27A_EIC_EXTINT15                    ((1UL) << 27)
#define PIN_PA27A_EIC_EXTINT_NUM                   _L_(15)      /**< EIC signal: PIN_PA27 External Interrupt Line */

#define PIN_PB15A_EIC_EXTINT15                     (47L)        
#define MUX_PB15A_EIC_EXTINT15                     (0L)        
#define PINMUX_PB15A_EIC_EXTINT15                  ((PIN_PB15A_EIC_EXTINT15 << 16) | MUX_PB15A_EIC_EXTINT15)
#define PORT_PB15A_EIC_EXTINT15                    ((1UL) << 15)
#define PIN_PB15A_EIC_EXTINT_NUM                   _L_(15)      /**< EIC signal: PIN_PB15 External Interrupt Line */

#define PIN_PB31A_EIC_EXTINT15                     (63L)        
#define MUX_PB31A_EIC_EXTINT15                     (0L)        
#define PINMUX_PB31A_EIC_EXTINT15                  ((PIN_PB31A_EIC_EXTINT15 << 16) | MUX_PB31A_EIC_EXTINT15)
#define PORT_PB31A_EIC_EXTINT15                    ((1UL) << 31)
#define PIN_PB31A_EIC_EXTINT_NUM                   _L_(15)      /**< EIC signal: PIN_PB31 External Interrupt Line */

#define PIN_PC07A_EIC_EXTINT15                     (71L)        
#define MUX_PC07A_EIC_EXTINT15                     (0L)        
#define PINMUX_PC07A_EIC_EXTINT15                  ((PIN_PC07A_EIC_EXTINT15 << 16) | MUX_PC07A_EIC_EXTINT15)
#define PORT_PC07A_EIC_EXTINT15                    ((1UL) << 7)
#define PIN_PC07A_EIC_EXTINT_NUM                   _L_(15)      /**< EIC signal: PIN_PC07 External Interrupt Line */

#define PIN_PA15A_EIC_EXTINT15                     (15L)        
#define MUX_PA15A_EIC_EXTINT15                     (0L)        
#define PINMUX_PA15A_EIC_EXTINT15                  ((PIN_PA15A_EIC_EXTINT15 << 16) | MUX_PA15A_EIC_EXTINT15)
#define PORT_PA15A_EIC_EXTINT15                    ((1UL) << 15)
#define PIN_PA15A_EIC_EXTINT_NUM                   _L_(15)      /**< EIC signal: PIN_PA15 External Interrupt Line */

#define PIN_PA08A_EIC_NMI                          (8L)         
#define MUX_PA08A_EIC_NMI                          (0L)        
#define PINMUX_PA08A_EIC_NMI                       ((PIN_PA08A_EIC_NMI << 16) | MUX_PA08A_EIC_NMI)
#define PORT_PA08A_EIC_NMI                         ((1UL) << 8)

/* ========== PORT definition for GCLK peripheral ========== */
#define PIN_PB14H_GCLK_IO0                         (46L)        
#define MUX_PB14H_GCLK_IO0                         (7L)        
#define PINMUX_PB14H_GCLK_IO0                      ((PIN_PB14H_GCLK_IO0 << 16) | MUX_PB14H_GCLK_IO0)
#define PORT_PB14H_GCLK_IO0                        ((1UL) << 14)

#define PIN_PB22H_GCLK_IO0                         (54L)        
#define MUX_PB22H_GCLK_IO0                         (7L)        
#define PINMUX_PB22H_GCLK_IO0                      ((PIN_PB22H_GCLK_IO0 << 16) | MUX_PB22H_GCLK_IO0)
#define PORT_PB22H_GCLK_IO0                        ((1UL) << 22)

#define PIN_PA14H_GCLK_IO0                         (14L)        
#define MUX_PA14H_GCLK_IO0                         (7L)        
#define PINMUX_PA14H_GCLK_IO0                      ((PIN_PA14H_GCLK_IO0 << 16) | MUX_PA14H_GCLK_IO0)
#define PORT_PA14H_GCLK_IO0                        ((1UL) << 14)

#define PIN_PA27H_GCLK_IO0                         (27L)        
#define MUX_PA27H_GCLK_IO0                         (7L)        
#define PINMUX_PA27H_GCLK_IO0                      ((PIN_PA27H_GCLK_IO0 << 16) | MUX_PA27H_GCLK_IO0)
#define PORT_PA27H_GCLK_IO0                        ((1UL) << 27)

#define PIN_PA28H_GCLK_IO0                         (28L)        
#define MUX_PA28H_GCLK_IO0                         (7L)        
#define PINMUX_PA28H_GCLK_IO0                      ((PIN_PA28H_GCLK_IO0 << 16) | MUX_PA28H_GCLK_IO0)
#define PORT_PA28H_GCLK_IO0                        ((1UL) << 28)

#define PIN_PA30H_GCLK_IO0                         (30L)        
#define MUX_PA30H_GCLK_IO0                         (7L)        
#define PINMUX_PA30H_GCLK_IO0                      ((PIN_PA30H_GCLK_IO0 << 16) | MUX_PA30H_GCLK_IO0)
#define PORT_PA30H_GCLK_IO0                        ((1UL) << 30)

#define PIN_PB23H_GCLK_IO1                         (55L)        
#define MUX_PB23H_GCLK_IO1                         (7L)        
#define PINMUX_PB23H_GCLK_IO1                      ((PIN_PB23H_GCLK_IO1 << 16) | MUX_PB23H_GCLK_IO1)
#define PORT_PB23H_GCLK_IO1                        ((1UL) << 23)

#define PIN_PA15H_GCLK_IO1                         (15L)        
#define MUX_PA15H_GCLK_IO1                         (7L)        
#define PINMUX_PA15H_GCLK_IO1                      ((PIN_PA15H_GCLK_IO1 << 16) | MUX_PA15H_GCLK_IO1)
#define PORT_PA15H_GCLK_IO1                        ((1UL) << 15)

#define PIN_PB15H_GCLK_IO1                         (47L)        
#define MUX_PB15H_GCLK_IO1                         (7L)        
#define PINMUX_PB15H_GCLK_IO1                      ((PIN_PB15H_GCLK_IO1 << 16) | MUX_PB15H_GCLK_IO1)
#define PORT_PB15H_GCLK_IO1                        ((1UL) << 15)

#define PIN_PB16H_GCLK_IO2                         (48L)        
#define MUX_PB16H_GCLK_IO2                         (7L)        
#define PINMUX_PB16H_GCLK_IO2                      ((PIN_PB16H_GCLK_IO2 << 16) | MUX_PB16H_GCLK_IO2)
#define PORT_PB16H_GCLK_IO2                        ((1UL) << 16)

#define PIN_PA16H_GCLK_IO2                         (16L)        
#define MUX_PA16H_GCLK_IO2                         (7L)        
#define PINMUX_PA16H_GCLK_IO2                      ((PIN_PA16H_GCLK_IO2 << 16) | MUX_PA16H_GCLK_IO2)
#define PORT_PA16H_GCLK_IO2                        ((1UL) << 16)

#define PIN_PA17H_GCLK_IO3                         (17L)        
#define MUX_PA17H_GCLK_IO3                         (7L)        
#define PINMUX_PA17H_GCLK_IO3                      ((PIN_PA17H_GCLK_IO3 << 16) | MUX_PA17H_GCLK_IO3)
#define PORT_PA17H_GCLK_IO3                        ((1UL) << 17)

#define PIN_PB17H_GCLK_IO3                         (49L)        
#define MUX_PB17H_GCLK_IO3                         (7L)        
#define PINMUX_PB17H_GCLK_IO3                      ((PIN_PB17H_GCLK_IO3 << 16) | MUX_PB17H_GCLK_IO3)
#define PORT_PB17H_GCLK_IO3                        ((1UL) << 17)

#define PIN_PA10H_GCLK_IO4                         (10L)        
#define MUX_PA10H_GCLK_IO4                         (7L)        
#define PINMUX_PA10H_GCLK_IO4                      ((PIN_PA10H_GCLK_IO4 << 16) | MUX_PA10H_GCLK_IO4)
#define PORT_PA10H_GCLK_IO4                        ((1UL) << 10)

#define PIN_PB10H_GCLK_IO4                         (42L)        
#define MUX_PB10H_GCLK_IO4                         (7L)        
#define PINMUX_PB10H_GCLK_IO4                      ((PIN_PB10H_GCLK_IO4 << 16) | MUX_PB10H_GCLK_IO4)
#define PORT_PB10H_GCLK_IO4                        ((1UL) << 10)

#define PIN_PB18H_GCLK_IO4                         (50L)        
#define MUX_PB18H_GCLK_IO4                         (7L)        
#define PINMUX_PB18H_GCLK_IO4                      ((PIN_PB18H_GCLK_IO4 << 16) | MUX_PB18H_GCLK_IO4)
#define PORT_PB18H_GCLK_IO4                        ((1UL) << 18)

#define PIN_PA20H_GCLK_IO4                         (20L)        
#define MUX_PA20H_GCLK_IO4                         (7L)        
#define PINMUX_PA20H_GCLK_IO4                      ((PIN_PA20H_GCLK_IO4 << 16) | MUX_PA20H_GCLK_IO4)
#define PORT_PA20H_GCLK_IO4                        ((1UL) << 20)

#define PIN_PA11H_GCLK_IO5                         (11L)        
#define MUX_PA11H_GCLK_IO5                         (7L)        
#define PINMUX_PA11H_GCLK_IO5                      ((PIN_PA11H_GCLK_IO5 << 16) | MUX_PA11H_GCLK_IO5)
#define PORT_PA11H_GCLK_IO5                        ((1UL) << 11)

#define PIN_PA21H_GCLK_IO5                         (21L)        
#define MUX_PA21H_GCLK_IO5                         (7L)        
#define PINMUX_PA21H_GCLK_IO5                      ((PIN_PA21H_GCLK_IO5 << 16) | MUX_PA21H_GCLK_IO5)
#define PORT_PA21H_GCLK_IO5                        ((1UL) << 21)

#define PIN_PB11H_GCLK_IO5                         (43L)        
#define MUX_PB11H_GCLK_IO5                         (7L)        
#define PINMUX_PB11H_GCLK_IO5                      ((PIN_PB11H_GCLK_IO5 << 16) | MUX_PB11H_GCLK_IO5)
#define PORT_PB11H_GCLK_IO5                        ((1UL) << 11)

#define PIN_PB19H_GCLK_IO5                         (51L)        
#define MUX_PB19H_GCLK_IO5                         (7L)        
#define PINMUX_PB19H_GCLK_IO5                      ((PIN_PB19H_GCLK_IO5 << 16) | MUX_PB19H_GCLK_IO5)
#define PORT_PB19H_GCLK_IO5                        ((1UL) << 19)

#define PIN_PA22H_GCLK_IO6                         (22L)        
#define MUX_PA22H_GCLK_IO6                         (7L)        
#define PINMUX_PA22H_GCLK_IO6                      ((PIN_PA22H_GCLK_IO6 << 16) | MUX_PA22H_GCLK_IO6)
#define PORT_PA22H_GCLK_IO6                        ((1UL) << 22)

#define PIN_PB12H_GCLK_IO6                         (44L)        
#define MUX_PB12H_GCLK_IO6                         (7L)        
#define PINMUX_PB12H_GCLK_IO6                      ((PIN_PB12H_GCLK_IO6 << 16) | MUX_PB12H_GCLK_IO6)
#define PORT_PB12H_GCLK_IO6                        ((1UL) << 12)

#define PIN_PB20H_GCLK_IO6                         (52L)        
#define MUX_PB20H_GCLK_IO6                         (7L)        
#define PINMUX_PB20H_GCLK_IO6                      ((PIN_PB20H_GCLK_IO6 << 16) | MUX_PB20H_GCLK_IO6)
#define PORT_PB20H_GCLK_IO6                        ((1UL) << 20)

#define PIN_PB13H_GCLK_IO7                         (45L)        
#define MUX_PB13H_GCLK_IO7                         (7L)        
#define PINMUX_PB13H_GCLK_IO7                      ((PIN_PB13H_GCLK_IO7 << 16) | MUX_PB13H_GCLK_IO7)
#define PORT_PB13H_GCLK_IO7                        ((1UL) << 13)

#define PIN_PA23H_GCLK_IO7                         (23L)        
#define MUX_PA23H_GCLK_IO7                         (7L)        
#define PINMUX_PA23H_GCLK_IO7                      ((PIN_PA23H_GCLK_IO7 << 16) | MUX_PA23H_GCLK_IO7)
#define PORT_PA23H_GCLK_IO7                        ((1UL) << 23)

#define PIN_PB21H_GCLK_IO7                         (53L)        
#define MUX_PB21H_GCLK_IO7                         (7L)        
#define PINMUX_PB21H_GCLK_IO7                      ((PIN_PB21H_GCLK_IO7 << 16) | MUX_PB21H_GCLK_IO7)
#define PORT_PB21H_GCLK_IO7                        ((1UL) << 21)

/* ========== PORT definition for PTC peripheral ========== */
#define PIN_PA08B_PTC_X0                           (8L)         
#define MUX_PA08B_PTC_X0                           (1L)        
#define PINMUX_PA08B_PTC_X0                        ((PIN_PA08B_PTC_X0 << 16) | MUX_PA08B_PTC_X0)
#define PORT_PA08B_PTC_X0                          ((1UL) << 8)

#define PIN_PA09B_PTC_X1                           (9L)         
#define MUX_PA09B_PTC_X1                           (1L)        
#define PINMUX_PA09B_PTC_X1                        ((PIN_PA09B_PTC_X1 << 16) | MUX_PA09B_PTC_X1)
#define PORT_PA09B_PTC_X1                          ((1UL) << 9)

#define PIN_PA10B_PTC_X2                           (10L)        
#define MUX_PA10B_PTC_X2                           (1L)        
#define PINMUX_PA10B_PTC_X2                        ((PIN_PA10B_PTC_X2 << 16) | MUX_PA10B_PTC_X2)
#define PORT_PA10B_PTC_X2                          ((1UL) << 10)

#define PIN_PA11B_PTC_X3                           (11L)        
#define MUX_PA11B_PTC_X3                           (1L)        
#define PINMUX_PA11B_PTC_X3                        ((PIN_PA11B_PTC_X3 << 16) | MUX_PA11B_PTC_X3)
#define PORT_PA11B_PTC_X3                          ((1UL) << 11)

#define PIN_PA16B_PTC_X4                           (16L)        
#define MUX_PA16B_PTC_X4                           (1L)        
#define PINMUX_PA16B_PTC_X4                        ((PIN_PA16B_PTC_X4 << 16) | MUX_PA16B_PTC_X4)
#define PORT_PA16B_PTC_X4                          ((1UL) << 16)

#define PIN_PA17B_PTC_X5                           (17L)        
#define MUX_PA17B_PTC_X5                           (1L)        
#define PINMUX_PA17B_PTC_X5                        ((PIN_PA17B_PTC_X5 << 16) | MUX_PA17B_PTC_X5)
#define PORT_PA17B_PTC_X5                          ((1UL) << 17)

#define PIN_PA18B_PTC_X6                           (18L)        
#define MUX_PA18B_PTC_X6                           (1L)        
#define PINMUX_PA18B_PTC_X6                        ((PIN_PA18B_PTC_X6 << 16) | MUX_PA18B_PTC_X6)
#define PORT_PA18B_PTC_X6                          ((1UL) << 18)

#define PIN_PA19B_PTC_X7                           (19L)        
#define MUX_PA19B_PTC_X7                           (1L)        
#define PINMUX_PA19B_PTC_X7                        ((PIN_PA19B_PTC_X7 << 16) | MUX_PA19B_PTC_X7)
#define PORT_PA19B_PTC_X7                          ((1UL) << 19)

#define PIN_PA20B_PTC_X8                           (20L)        
#define MUX_PA20B_PTC_X8                           (1L)        
#define PINMUX_PA20B_PTC_X8                        ((PIN_PA20B_PTC_X8 << 16) | MUX_PA20B_PTC_X8)
#define PORT_PA20B_PTC_X8                          ((1UL) << 20)

#define PIN_PA21B_PTC_X9                           (21L)        
#define MUX_PA21B_PTC_X9                           (1L)        
#define PINMUX_PA21B_PTC_X9                        ((PIN_PA21B_PTC_X9 << 16) | MUX_PA21B_PTC_X9)
#define PORT_PA21B_PTC_X9                          ((1UL) << 21)

#define PIN_PA22B_PTC_X10                          (22L)        
#define MUX_PA22B_PTC_X10                          (1L)        
#define PINMUX_PA22B_PTC_X10                       ((PIN_PA22B_PTC_X10 << 16) | MUX_PA22B_PTC_X10)
#define PORT_PA22B_PTC_X10                         ((1UL) << 22)

#define PIN_PA23B_PTC_X11                          (23L)        
#define MUX_PA23B_PTC_X11                          (1L)        
#define PINMUX_PA23B_PTC_X11                       ((PIN_PA23B_PTC_X11 << 16) | MUX_PA23B_PTC_X11)
#define PORT_PA23B_PTC_X11                         ((1UL) << 23)

#define PIN_PB12B_PTC_X12                          (44L)        
#define MUX_PB12B_PTC_X12                          (1L)        
#define PINMUX_PB12B_PTC_X12                       ((PIN_PB12B_PTC_X12 << 16) | MUX_PB12B_PTC_X12)
#define PORT_PB12B_PTC_X12                         ((1UL) << 12)

#define PIN_PB13B_PTC_X13                          (45L)        
#define MUX_PB13B_PTC_X13                          (1L)        
#define PINMUX_PB13B_PTC_X13                       ((PIN_PB13B_PTC_X13 << 16) | MUX_PB13B_PTC_X13)
#define PORT_PB13B_PTC_X13                         ((1UL) << 13)

#define PIN_PB14B_PTC_X14                          (46L)        
#define MUX_PB14B_PTC_X14                          (1L)        
#define PINMUX_PB14B_PTC_X14                       ((PIN_PB14B_PTC_X14 << 16) | MUX_PB14B_PTC_X14)
#define PORT_PB14B_PTC_X14                         ((1UL) << 14)

#define PIN_PB15B_PTC_X15                          (47L)        
#define MUX_PB15B_PTC_X15                          (1L)        
#define PINMUX_PB15B_PTC_X15                       ((PIN_PB15B_PTC_X15 << 16) | MUX_PB15B_PTC_X15)
#define PORT_PB15B_PTC_X15                         ((1UL) << 15)

#define PIN_PA02B_PTC_Y0                           (2L)         
#define MUX_PA02B_PTC_Y0                           (1L)        
#define PINMUX_PA02B_PTC_Y0                        ((PIN_PA02B_PTC_Y0 << 16) | MUX_PA02B_PTC_Y0)
#define PORT_PA02B_PTC_Y0                          ((1UL) << 2)

#define PIN_PA03B_PTC_Y1                           (3L)         
#define MUX_PA03B_PTC_Y1                           (1L)        
#define PINMUX_PA03B_PTC_Y1                        ((PIN_PA03B_PTC_Y1 << 16) | MUX_PA03B_PTC_Y1)
#define PORT_PA03B_PTC_Y1                          ((1UL) << 3)

#define PIN_PA04B_PTC_Y2                           (4L)         
#define MUX_PA04B_PTC_Y2                           (1L)        
#define PINMUX_PA04B_PTC_Y2                        ((PIN_PA04B_PTC_Y2 << 16) | MUX_PA04B_PTC_Y2)
#define PORT_PA04B_PTC_Y2                          ((1UL) << 4)

#define PIN_PA05B_PTC_Y3                           (5L)         
#define MUX_PA05B_PTC_Y3                           (1L)        
#define PINMUX_PA05B_PTC_Y3                        ((PIN_PA05B_PTC_Y3 << 16) | MUX_PA05B_PTC_Y3)
#define PORT_PA05B_PTC_Y3                          ((1UL) << 5)

#define PIN_PA06B_PTC_Y4                           (6L)         
#define MUX_PA06B_PTC_Y4                           (1L)        
#define PINMUX_PA06B_PTC_Y4                        ((PIN_PA06B_PTC_Y4 << 16) | MUX_PA06B_PTC_Y4)
#define PORT_PA06B_PTC_Y4                          ((1UL) << 6)

#define PIN_PA07B_PTC_Y5                           (7L)         
#define MUX_PA07B_PTC_Y5                           (1L)        
#define PINMUX_PA07B_PTC_Y5                        ((PIN_PA07B_PTC_Y5 << 16) | MUX_PA07B_PTC_Y5)
#define PORT_PA07B_PTC_Y5                          ((1UL) << 7)

#define PIN_PB00B_PTC_Y6                           (32L)        
#define MUX_PB00B_PTC_Y6                           (1L)        
#define PINMUX_PB00B_PTC_Y6                        ((PIN_PB00B_PTC_Y6 << 16) | MUX_PB00B_PTC_Y6)
#define PORT_PB00B_PTC_Y6                          ((1UL) << 0)

#define PIN_PB01B_PTC_Y7                           (33L)        
#define MUX_PB01B_PTC_Y7                           (1L)        
#define PINMUX_PB01B_PTC_Y7                        ((PIN_PB01B_PTC_Y7 << 16) | MUX_PB01B_PTC_Y7)
#define PORT_PB01B_PTC_Y7                          ((1UL) << 1)

#define PIN_PB02B_PTC_Y8                           (34L)        
#define MUX_PB02B_PTC_Y8                           (1L)        
#define PINMUX_PB02B_PTC_Y8                        ((PIN_PB02B_PTC_Y8 << 16) | MUX_PB02B_PTC_Y8)
#define PORT_PB02B_PTC_Y8                          ((1UL) << 2)

#define PIN_PB03B_PTC_Y9                           (35L)        
#define MUX_PB03B_PTC_Y9                           (1L)        
#define PINMUX_PB03B_PTC_Y9                        ((PIN_PB03B_PTC_Y9 << 16) | MUX_PB03B_PTC_Y9)
#define PORT_PB03B_PTC_Y9                          ((1UL) << 3)

#define PIN_PB04B_PTC_Y10                          (36L)        
#define MUX_PB04B_PTC_Y10                          (1L)        
#define PINMUX_PB04B_PTC_Y10                       ((PIN_PB04B_PTC_Y10 << 16) | MUX_PB04B_PTC_Y10)
#define PORT_PB04B_PTC_Y10                         ((1UL) << 4)

#define PIN_PB05B_PTC_Y11                          (37L)        
#define MUX_PB05B_PTC_Y11                          (1L)        
#define PINMUX_PB05B_PTC_Y11                       ((PIN_PB05B_PTC_Y11 << 16) | MUX_PB05B_PTC_Y11)
#define PORT_PB05B_PTC_Y11                         ((1UL) << 5)

#define PIN_PB06B_PTC_Y12                          (38L)        
#define MUX_PB06B_PTC_Y12                          (1L)        
#define PINMUX_PB06B_PTC_Y12                       ((PIN_PB06B_PTC_Y12 << 16) | MUX_PB06B_PTC_Y12)
#define PORT_PB06B_PTC_Y12                         ((1UL) << 6)

#define PIN_PB07B_PTC_Y13                          (39L)        
#define MUX_PB07B_PTC_Y13                          (1L)        
#define PINMUX_PB07B_PTC_Y13                       ((PIN_PB07B_PTC_Y13 << 16) | MUX_PB07B_PTC_Y13)
#define PORT_PB07B_PTC_Y13                         ((1UL) << 7)

#define PIN_PB08B_PTC_Y14                          (40L)        
#define MUX_PB08B_PTC_Y14                          (1L)        
#define PINMUX_PB08B_PTC_Y14                       ((PIN_PB08B_PTC_Y14 << 16) | MUX_PB08B_PTC_Y14)
#define PORT_PB08B_PTC_Y14                         ((1UL) << 8)

#define PIN_PB09B_PTC_Y15                          (41L)        
#define MUX_PB09B_PTC_Y15                          (1L)        
#define PINMUX_PB09B_PTC_Y15                       ((PIN_PB09B_PTC_Y15 << 16) | MUX_PB09B_PTC_Y15)
#define PORT_PB09B_PTC_Y15                         ((1UL) << 9)

#define PIN_PA08B_PTC_Y16                          (8L)         
#define MUX_PA08B_PTC_Y16                          (1L)        
#define PINMUX_PA08B_PTC_Y16                       ((PIN_PA08B_PTC_Y16 << 16) | MUX_PA08B_PTC_Y16)
#define PORT_PA08B_PTC_Y16                         ((1UL) << 8)

#define PIN_PA09B_PTC_Y17                          (9L)         
#define MUX_PA09B_PTC_Y17                          (1L)        
#define PINMUX_PA09B_PTC_Y17                       ((PIN_PA09B_PTC_Y17 << 16) | MUX_PA09B_PTC_Y17)
#define PORT_PA09B_PTC_Y17                         ((1UL) << 9)

#define PIN_PA10B_PTC_Y18                          (10L)        
#define MUX_PA10B_PTC_Y18                          (1L)        
#define PINMUX_PA10B_PTC_Y18                       ((PIN_PA10B_PTC_Y18 << 16) | MUX_PA10B_PTC_Y18)
#define PORT_PA10B_PTC_Y18                         ((1UL) << 10)

#define PIN_PA11B_PTC_Y19                          (11L)        
#define MUX_PA11B_PTC_Y19                          (1L)        
#define PINMUX_PA11B_PTC_Y19                       ((PIN_PA11B_PTC_Y19 << 16) | MUX_PA11B_PTC_Y19)
#define PORT_PA11B_PTC_Y19                         ((1UL) << 11)

#define PIN_PA16B_PTC_Y20                          (16L)        
#define MUX_PA16B_PTC_Y20                          (1L)        
#define PINMUX_PA16B_PTC_Y20                       ((PIN_PA16B_PTC_Y20 << 16) | MUX_PA16B_PTC_Y20)
#define PORT_PA16B_PTC_Y20                         ((1UL) << 16)

#define PIN_PA17B_PTC_Y21                          (17L)        
#define MUX_PA17B_PTC_Y21                          (1L)        
#define PINMUX_PA17B_PTC_Y21                       ((PIN_PA17B_PTC_Y21 << 16) | MUX_PA17B_PTC_Y21)
#define PORT_PA17B_PTC_Y21                         ((1UL) << 17)

#define PIN_PA18B_PTC_Y22                          (18L)        
#define MUX_PA18B_PTC_Y22                          (1L)        
#define PINMUX_PA18B_PTC_Y22                       ((PIN_PA18B_PTC_Y22 << 16) | MUX_PA18B_PTC_Y22)
#define PORT_PA18B_PTC_Y22                         ((1UL) << 18)

#define PIN_PA19B_PTC_Y23                          (19L)        
#define MUX_PA19B_PTC_Y23                          (1L)        
#define PINMUX_PA19B_PTC_Y23                       ((PIN_PA19B_PTC_Y23 << 16) | MUX_PA19B_PTC_Y23)
#define PORT_PA19B_PTC_Y23                         ((1UL) << 19)

#define PIN_PA20B_PTC_Y24                          (20L)        
#define MUX_PA20B_PTC_Y24                          (1L)        
#define PINMUX_PA20B_PTC_Y24                       ((PIN_PA20B_PTC_Y24 << 16) | MUX_PA20B_PTC_Y24)
#define PORT_PA20B_PTC_Y24                         ((1UL) << 20)

#define PIN_PA21B_PTC_Y25                          (21L)        
#define MUX_PA21B_PTC_Y25                          (1L)        
#define PINMUX_PA21B_PTC_Y25                       ((PIN_PA21B_PTC_Y25 << 16) | MUX_PA21B_PTC_Y25)
#define PORT_PA21B_PTC_Y25                         ((1UL) << 21)

#define PIN_PA22B_PTC_Y26                          (22L)        
#define MUX_PA22B_PTC_Y26                          (1L)        
#define PINMUX_PA22B_PTC_Y26                       ((PIN_PA22B_PTC_Y26 << 16) | MUX_PA22B_PTC_Y26)
#define PORT_PA22B_PTC_Y26                         ((1UL) << 22)

#define PIN_PA23B_PTC_Y27                          (23L)        
#define MUX_PA23B_PTC_Y27                          (1L)        
#define PINMUX_PA23B_PTC_Y27                       ((PIN_PA23B_PTC_Y27 << 16) | MUX_PA23B_PTC_Y27)
#define PORT_PA23B_PTC_Y27                         ((1UL) << 23)

#define PIN_PB12B_PTC_Y28                          (44L)        
#define MUX_PB12B_PTC_Y28                          (1L)        
#define PINMUX_PB12B_PTC_Y28                       ((PIN_PB12B_PTC_Y28 << 16) | MUX_PB12B_PTC_Y28)
#define PORT_PB12B_PTC_Y28                         ((1UL) << 12)

#define PIN_PB13B_PTC_Y29                          (45L)        
#define MUX_PB13B_PTC_Y29                          (1L)        
#define PINMUX_PB13B_PTC_Y29                       ((PIN_PB13B_PTC_Y29 << 16) | MUX_PB13B_PTC_Y29)
#define PORT_PB13B_PTC_Y29                         ((1UL) << 13)

#define PIN_PB14B_PTC_Y30                          (46L)        
#define MUX_PB14B_PTC_Y30                          (1L)        
#define PINMUX_PB14B_PTC_Y30                       ((PIN_PB14B_PTC_Y30 << 16) | MUX_PB14B_PTC_Y30)
#define PORT_PB14B_PTC_Y30                         ((1UL) << 14)

#define PIN_PB15B_PTC_Y31                          (47L)        
#define MUX_PB15B_PTC_Y31                          (1L)        
#define PINMUX_PB15B_PTC_Y31                       ((PIN_PB15B_PTC_Y31 << 16) | MUX_PB15B_PTC_Y31)
#define PORT_PB15B_PTC_Y31                         ((1UL) << 15)

/* ========== PORT definition for RSTC peripheral ========== */
#define PIN_PA00A_RSTC_EXTWAKE0                    (0L)         
#define MUX_PA00A_RSTC_EXTWAKE0                    (0L)        
#define PINMUX_PA00A_RSTC_EXTWAKE0                 ((PIN_PA00A_RSTC_EXTWAKE0 << 16) | MUX_PA00A_RSTC_EXTWAKE0)
#define PORT_PA00A_RSTC_EXTWAKE0                   ((1UL) << 0)

#define PIN_PA01A_RSTC_EXTWAKE1                    (1L)         
#define MUX_PA01A_RSTC_EXTWAKE1                    (0L)        
#define PINMUX_PA01A_RSTC_EXTWAKE1                 ((PIN_PA01A_RSTC_EXTWAKE1 << 16) | MUX_PA01A_RSTC_EXTWAKE1)
#define PORT_PA01A_RSTC_EXTWAKE1                   ((1UL) << 1)

#define PIN_PA02A_RSTC_EXTWAKE2                    (2L)         
#define MUX_PA02A_RSTC_EXTWAKE2                    (0L)        
#define PINMUX_PA02A_RSTC_EXTWAKE2                 ((PIN_PA02A_RSTC_EXTWAKE2 << 16) | MUX_PA02A_RSTC_EXTWAKE2)
#define PORT_PA02A_RSTC_EXTWAKE2                   ((1UL) << 2)

#define PIN_PA03A_RSTC_EXTWAKE3                    (3L)         
#define MUX_PA03A_RSTC_EXTWAKE3                    (0L)        
#define PINMUX_PA03A_RSTC_EXTWAKE3                 ((PIN_PA03A_RSTC_EXTWAKE3 << 16) | MUX_PA03A_RSTC_EXTWAKE3)
#define PORT_PA03A_RSTC_EXTWAKE3                   ((1UL) << 3)

#define PIN_PA04A_RSTC_EXTWAKE4                    (4L)         
#define MUX_PA04A_RSTC_EXTWAKE4                    (0L)        
#define PINMUX_PA04A_RSTC_EXTWAKE4                 ((PIN_PA04A_RSTC_EXTWAKE4 << 16) | MUX_PA04A_RSTC_EXTWAKE4)
#define PORT_PA04A_RSTC_EXTWAKE4                   ((1UL) << 4)

#define PIN_PA05A_RSTC_EXTWAKE5                    (5L)         
#define MUX_PA05A_RSTC_EXTWAKE5                    (0L)        
#define PINMUX_PA05A_RSTC_EXTWAKE5                 ((PIN_PA05A_RSTC_EXTWAKE5 << 16) | MUX_PA05A_RSTC_EXTWAKE5)
#define PORT_PA05A_RSTC_EXTWAKE5                   ((1UL) << 5)

#define PIN_PA06A_RSTC_EXTWAKE6                    (6L)         
#define MUX_PA06A_RSTC_EXTWAKE6                    (0L)        
#define PINMUX_PA06A_RSTC_EXTWAKE6                 ((PIN_PA06A_RSTC_EXTWAKE6 << 16) | MUX_PA06A_RSTC_EXTWAKE6)
#define PORT_PA06A_RSTC_EXTWAKE6                   ((1UL) << 6)

#define PIN_PA07A_RSTC_EXTWAKE7                    (7L)         
#define MUX_PA07A_RSTC_EXTWAKE7                    (0L)        
#define PINMUX_PA07A_RSTC_EXTWAKE7                 ((PIN_PA07A_RSTC_EXTWAKE7 << 16) | MUX_PA07A_RSTC_EXTWAKE7)
#define PORT_PA07A_RSTC_EXTWAKE7                   ((1UL) << 7)

#define PIN_PA08A_RSTC_EXTWAKE8                    (8L)         
#define MUX_PA08A_RSTC_EXTWAKE8                    (0L)        
#define PINMUX_PA08A_RSTC_EXTWAKE8                 ((PIN_PA08A_RSTC_EXTWAKE8 << 16) | MUX_PA08A_RSTC_EXTWAKE8)
#define PORT_PA08A_RSTC_EXTWAKE8                   ((1UL) << 8)

#define PIN_PA09A_RSTC_EXTWAKE9                    (9L)         
#define MUX_PA09A_RSTC_EXTWAKE9                    (0L)        
#define PINMUX_PA09A_RSTC_EXTWAKE9                 ((PIN_PA09A_RSTC_EXTWAKE9 << 16) | MUX_PA09A_RSTC_EXTWAKE9)
#define PORT_PA09A_RSTC_EXTWAKE9                   ((1UL) << 9)

#define PIN_PA10A_RSTC_EXTWAKE10                   (10L)        
#define MUX_PA10A_RSTC_EXTWAKE10                   (0L)        
#define PINMUX_PA10A_RSTC_EXTWAKE10                ((PIN_PA10A_RSTC_EXTWAKE10 << 16) | MUX_PA10A_RSTC_EXTWAKE10)
#define PORT_PA10A_RSTC_EXTWAKE10                  ((1UL) << 10)

#define PIN_PA11A_RSTC_EXTWAKE11                   (11L)        
#define MUX_PA11A_RSTC_EXTWAKE11                   (0L)        
#define PINMUX_PA11A_RSTC_EXTWAKE11                ((PIN_PA11A_RSTC_EXTWAKE11 << 16) | MUX_PA11A_RSTC_EXTWAKE11)
#define PORT_PA11A_RSTC_EXTWAKE11                  ((1UL) << 11)

#define PIN_PA12A_RSTC_EXTWAKE12                   (12L)        
#define MUX_PA12A_RSTC_EXTWAKE12                   (0L)        
#define PINMUX_PA12A_RSTC_EXTWAKE12                ((PIN_PA12A_RSTC_EXTWAKE12 << 16) | MUX_PA12A_RSTC_EXTWAKE12)
#define PORT_PA12A_RSTC_EXTWAKE12                  ((1UL) << 12)

#define PIN_PA13A_RSTC_EXTWAKE13                   (13L)        
#define MUX_PA13A_RSTC_EXTWAKE13                   (0L)        
#define PINMUX_PA13A_RSTC_EXTWAKE13                ((PIN_PA13A_RSTC_EXTWAKE13 << 16) | MUX_PA13A_RSTC_EXTWAKE13)
#define PORT_PA13A_RSTC_EXTWAKE13                  ((1UL) << 13)

#define PIN_PA14A_RSTC_EXTWAKE14                   (14L)        
#define MUX_PA14A_RSTC_EXTWAKE14                   (0L)        
#define PINMUX_PA14A_RSTC_EXTWAKE14                ((PIN_PA14A_RSTC_EXTWAKE14 << 16) | MUX_PA14A_RSTC_EXTWAKE14)
#define PORT_PA14A_RSTC_EXTWAKE14                  ((1UL) << 14)

#define PIN_PA15A_RSTC_EXTWAKE15                   (15L)        
#define MUX_PA15A_RSTC_EXTWAKE15                   (0L)        
#define PINMUX_PA15A_RSTC_EXTWAKE15                ((PIN_PA15A_RSTC_EXTWAKE15 << 16) | MUX_PA15A_RSTC_EXTWAKE15)
#define PORT_PA15A_RSTC_EXTWAKE15                  ((1UL) << 15)

/* ========== PORT definition for SDADC peripheral ========== */
#define PIN_PA06B_SDADC_INN0                       (6L)         
#define MUX_PA06B_SDADC_INN0                       (1L)        
#define PINMUX_PA06B_SDADC_INN0                    ((PIN_PA06B_SDADC_INN0 << 16) | MUX_PA06B_SDADC_INN0)
#define PORT_PA06B_SDADC_INN0                      ((1UL) << 6)

#define PIN_PB08B_SDADC_INN1                       (40L)        
#define MUX_PB08B_SDADC_INN1                       (1L)        
#define PINMUX_PB08B_SDADC_INN1                    ((PIN_PB08B_SDADC_INN1 << 16) | MUX_PB08B_SDADC_INN1)
#define PORT_PB08B_SDADC_INN1                      ((1UL) << 8)

#define PIN_PB06B_SDADC_INN2                       (38L)        
#define MUX_PB06B_SDADC_INN2                       (1L)        
#define PINMUX_PB06B_SDADC_INN2                    ((PIN_PB06B_SDADC_INN2 << 16) | MUX_PB06B_SDADC_INN2)
#define PORT_PB06B_SDADC_INN2                      ((1UL) << 6)

#define PIN_PA07B_SDADC_INP0                       (7L)         
#define MUX_PA07B_SDADC_INP0                       (1L)        
#define PINMUX_PA07B_SDADC_INP0                    ((PIN_PA07B_SDADC_INP0 << 16) | MUX_PA07B_SDADC_INP0)
#define PORT_PA07B_SDADC_INP0                      ((1UL) << 7)

#define PIN_PB09B_SDADC_INP1                       (41L)        
#define MUX_PB09B_SDADC_INP1                       (1L)        
#define PINMUX_PB09B_SDADC_INP1                    ((PIN_PB09B_SDADC_INP1 << 16) | MUX_PB09B_SDADC_INP1)
#define PORT_PB09B_SDADC_INP1                      ((1UL) << 9)

#define PIN_PB07B_SDADC_INP2                       (39L)        
#define MUX_PB07B_SDADC_INP2                       (1L)        
#define PINMUX_PB07B_SDADC_INP2                    ((PIN_PB07B_SDADC_INP2 << 16) | MUX_PB07B_SDADC_INP2)
#define PORT_PB07B_SDADC_INP2                      ((1UL) << 7)

#define PIN_PA04B_SDADC_VREFP                      (4L)         
#define MUX_PA04B_SDADC_VREFP                      (1L)        
#define PINMUX_PA04B_SDADC_VREFP                   ((PIN_PA04B_SDADC_VREFP << 16) | MUX_PA04B_SDADC_VREFP)
#define PORT_PA04B_SDADC_VREFP                     ((1UL) << 4)

/* ========== PORT definition for SERCOM0 peripheral ========== */
#define PIN_PA04D_SERCOM0_PAD0                     (4L)         
#define MUX_PA04D_SERCOM0_PAD0                     (3L)        
#define PINMUX_PA04D_SERCOM0_PAD0                  ((PIN_PA04D_SERCOM0_PAD0 << 16) | MUX_PA04D_SERCOM0_PAD0)
#define PORT_PA04D_SERCOM0_PAD0                    ((1UL) << 4)

#define PIN_PA08C_SERCOM0_PAD0                     (8L)         
#define MUX_PA08C_SERCOM0_PAD0                     (2L)        
#define PINMUX_PA08C_SERCOM0_PAD0                  ((PIN_PA08C_SERCOM0_PAD0 << 16) | MUX_PA08C_SERCOM0_PAD0)
#define PORT_PA08C_SERCOM0_PAD0                    ((1UL) << 8)

#define PIN_PB24C_SERCOM0_PAD0                     (56L)        
#define MUX_PB24C_SERCOM0_PAD0                     (2L)        
#define PINMUX_PB24C_SERCOM0_PAD0                  ((PIN_PB24C_SERCOM0_PAD0 << 16) | MUX_PB24C_SERCOM0_PAD0)
#define PORT_PB24C_SERCOM0_PAD0                    ((1UL) << 24)

#define PIN_PA05D_SERCOM0_PAD1                     (5L)         
#define MUX_PA05D_SERCOM0_PAD1                     (3L)        
#define PINMUX_PA05D_SERCOM0_PAD1                  ((PIN_PA05D_SERCOM0_PAD1 << 16) | MUX_PA05D_SERCOM0_PAD1)
#define PORT_PA05D_SERCOM0_PAD1                    ((1UL) << 5)

#define PIN_PA09C_SERCOM0_PAD1                     (9L)         
#define MUX_PA09C_SERCOM0_PAD1                     (2L)        
#define PINMUX_PA09C_SERCOM0_PAD1                  ((PIN_PA09C_SERCOM0_PAD1 << 16) | MUX_PA09C_SERCOM0_PAD1)
#define PORT_PA09C_SERCOM0_PAD1                    ((1UL) << 9)

#define PIN_PB25C_SERCOM0_PAD1                     (57L)        
#define MUX_PB25C_SERCOM0_PAD1                     (2L)        
#define PINMUX_PB25C_SERCOM0_PAD1                  ((PIN_PB25C_SERCOM0_PAD1 << 16) | MUX_PB25C_SERCOM0_PAD1)
#define PORT_PB25C_SERCOM0_PAD1                    ((1UL) << 25)

#define PIN_PA06D_SERCOM0_PAD2                     (6L)         
#define MUX_PA06D_SERCOM0_PAD2                     (3L)        
#define PINMUX_PA06D_SERCOM0_PAD2                  ((PIN_PA06D_SERCOM0_PAD2 << 16) | MUX_PA06D_SERCOM0_PAD2)
#define PORT_PA06D_SERCOM0_PAD2                    ((1UL) << 6)

#define PIN_PB22C_SERCOM0_PAD2                     (54L)        
#define MUX_PB22C_SERCOM0_PAD2                     (2L)        
#define PINMUX_PB22C_SERCOM0_PAD2                  ((PIN_PB22C_SERCOM0_PAD2 << 16) | MUX_PB22C_SERCOM0_PAD2)
#define PORT_PB22C_SERCOM0_PAD2                    ((1UL) << 22)

#define PIN_PA10C_SERCOM0_PAD2                     (10L)        
#define MUX_PA10C_SERCOM0_PAD2                     (2L)        
#define PINMUX_PA10C_SERCOM0_PAD2                  ((PIN_PA10C_SERCOM0_PAD2 << 16) | MUX_PA10C_SERCOM0_PAD2)
#define PORT_PA10C_SERCOM0_PAD2                    ((1UL) << 10)

#define PIN_PC24C_SERCOM0_PAD2                     (88L)        
#define MUX_PC24C_SERCOM0_PAD2                     (2L)        
#define PINMUX_PC24C_SERCOM0_PAD2                  ((PIN_PC24C_SERCOM0_PAD2 << 16) | MUX_PC24C_SERCOM0_PAD2)
#define PORT_PC24C_SERCOM0_PAD2                    ((1UL) << 24)

#define PIN_PA07D_SERCOM0_PAD3                     (7L)         
#define MUX_PA07D_SERCOM0_PAD3                     (3L)        
#define PINMUX_PA07D_SERCOM0_PAD3                  ((PIN_PA07D_SERCOM0_PAD3 << 16) | MUX_PA07D_SERCOM0_PAD3)
#define PORT_PA07D_SERCOM0_PAD3                    ((1UL) << 7)

#define PIN_PA11C_SERCOM0_PAD3                     (11L)        
#define MUX_PA11C_SERCOM0_PAD3                     (2L)        
#define PINMUX_PA11C_SERCOM0_PAD3                  ((PIN_PA11C_SERCOM0_PAD3 << 16) | MUX_PA11C_SERCOM0_PAD3)
#define PORT_PA11C_SERCOM0_PAD3                    ((1UL) << 11)

#define PIN_PB23C_SERCOM0_PAD3                     (55L)        
#define MUX_PB23C_SERCOM0_PAD3                     (2L)        
#define PINMUX_PB23C_SERCOM0_PAD3                  ((PIN_PB23C_SERCOM0_PAD3 << 16) | MUX_PB23C_SERCOM0_PAD3)
#define PORT_PB23C_SERCOM0_PAD3                    ((1UL) << 23)

#define PIN_PC25C_SERCOM0_PAD3                     (89L)        
#define MUX_PC25C_SERCOM0_PAD3                     (2L)        
#define PINMUX_PC25C_SERCOM0_PAD3                  ((PIN_PC25C_SERCOM0_PAD3 << 16) | MUX_PC25C_SERCOM0_PAD3)
#define PORT_PC25C_SERCOM0_PAD3                    ((1UL) << 25)

/* ========== PORT definition for SERCOM1 peripheral ========== */
#define PIN_PC27D_SERCOM1_PAD0                     (91L)        
#define MUX_PC27D_SERCOM1_PAD0                     (3L)        
#define PINMUX_PC27D_SERCOM1_PAD0                  ((PIN_PC27D_SERCOM1_PAD0 << 16) | MUX_PC27D_SERCOM1_PAD0)
#define PORT_PC27D_SERCOM1_PAD0                    ((1UL) << 27)

#define PIN_PA16C_SERCOM1_PAD0                     (16L)        
#define MUX_PA16C_SERCOM1_PAD0                     (2L)        
#define PINMUX_PA16C_SERCOM1_PAD0                  ((PIN_PA16C_SERCOM1_PAD0 << 16) | MUX_PA16C_SERCOM1_PAD0)
#define PORT_PA16C_SERCOM1_PAD0                    ((1UL) << 16)

#define PIN_PB30C_SERCOM1_PAD0                     (62L)        
#define MUX_PB30C_SERCOM1_PAD0                     (2L)        
#define PINMUX_PB30C_SERCOM1_PAD0                  ((PIN_PB30C_SERCOM1_PAD0 << 16) | MUX_PB30C_SERCOM1_PAD0)
#define PORT_PB30C_SERCOM1_PAD0                    ((1UL) << 30)

#define PIN_PA00D_SERCOM1_PAD0                     (0L)         
#define MUX_PA00D_SERCOM1_PAD0                     (3L)        
#define PINMUX_PA00D_SERCOM1_PAD0                  ((PIN_PA00D_SERCOM1_PAD0 << 16) | MUX_PA00D_SERCOM1_PAD0)
#define PORT_PA00D_SERCOM1_PAD0                    ((1UL) << 0)

#define PIN_PC28D_SERCOM1_PAD1                     (92L)        
#define MUX_PC28D_SERCOM1_PAD1                     (3L)        
#define PINMUX_PC28D_SERCOM1_PAD1                  ((PIN_PC28D_SERCOM1_PAD1 << 16) | MUX_PC28D_SERCOM1_PAD1)
#define PORT_PC28D_SERCOM1_PAD1                    ((1UL) << 28)

#define PIN_PA17C_SERCOM1_PAD1                     (17L)        
#define MUX_PA17C_SERCOM1_PAD1                     (2L)        
#define PINMUX_PA17C_SERCOM1_PAD1                  ((PIN_PA17C_SERCOM1_PAD1 << 16) | MUX_PA17C_SERCOM1_PAD1)
#define PORT_PA17C_SERCOM1_PAD1                    ((1UL) << 17)

#define PIN_PB31C_SERCOM1_PAD1                     (63L)        
#define MUX_PB31C_SERCOM1_PAD1                     (2L)        
#define PINMUX_PB31C_SERCOM1_PAD1                  ((PIN_PB31C_SERCOM1_PAD1 << 16) | MUX_PB31C_SERCOM1_PAD1)
#define PORT_PB31C_SERCOM1_PAD1                    ((1UL) << 31)

#define PIN_PA01D_SERCOM1_PAD1                     (1L)         
#define MUX_PA01D_SERCOM1_PAD1                     (3L)        
#define PINMUX_PA01D_SERCOM1_PAD1                  ((PIN_PA01D_SERCOM1_PAD1 << 16) | MUX_PA01D_SERCOM1_PAD1)
#define PORT_PA01D_SERCOM1_PAD1                    ((1UL) << 1)

#define PIN_PA30D_SERCOM1_PAD2                     (30L)        
#define MUX_PA30D_SERCOM1_PAD2                     (3L)        
#define PINMUX_PA30D_SERCOM1_PAD2                  ((PIN_PA30D_SERCOM1_PAD2 << 16) | MUX_PA30D_SERCOM1_PAD2)
#define PORT_PA30D_SERCOM1_PAD2                    ((1UL) << 30)

#define PIN_PA18C_SERCOM1_PAD2                     (18L)        
#define MUX_PA18C_SERCOM1_PAD2                     (2L)        
#define PINMUX_PA18C_SERCOM1_PAD2                  ((PIN_PA18C_SERCOM1_PAD2 << 16) | MUX_PA18C_SERCOM1_PAD2)
#define PORT_PA18C_SERCOM1_PAD2                    ((1UL) << 18)

#define PIN_PA31D_SERCOM1_PAD3                     (31L)        
#define MUX_PA31D_SERCOM1_PAD3                     (3L)        
#define PINMUX_PA31D_SERCOM1_PAD3                  ((PIN_PA31D_SERCOM1_PAD3 << 16) | MUX_PA31D_SERCOM1_PAD3)
#define PORT_PA31D_SERCOM1_PAD3                    ((1UL) << 31)

#define PIN_PA19C_SERCOM1_PAD3                     (19L)        
#define MUX_PA19C_SERCOM1_PAD3                     (2L)        
#define PINMUX_PA19C_SERCOM1_PAD3                  ((PIN_PA19C_SERCOM1_PAD3 << 16) | MUX_PA19C_SERCOM1_PAD3)
#define PORT_PA19C_SERCOM1_PAD3                    ((1UL) << 19)

/* ========== PORT definition for SERCOM2 peripheral ========== */
#define PIN_PA08D_SERCOM2_PAD0                     (8L)         
#define MUX_PA08D_SERCOM2_PAD0                     (3L)        
#define PINMUX_PA08D_SERCOM2_PAD0                  ((PIN_PA08D_SERCOM2_PAD0 << 16) | MUX_PA08D_SERCOM2_PAD0)
#define PORT_PA08D_SERCOM2_PAD0                    ((1UL) << 8)

#define PIN_PB20D_SERCOM2_PAD0                     (52L)        
#define MUX_PB20D_SERCOM2_PAD0                     (3L)        
#define PINMUX_PB20D_SERCOM2_PAD0                  ((PIN_PB20D_SERCOM2_PAD0 << 16) | MUX_PB20D_SERCOM2_PAD0)
#define PORT_PB20D_SERCOM2_PAD0                    ((1UL) << 20)

#define PIN_PA12C_SERCOM2_PAD0                     (12L)        
#define MUX_PA12C_SERCOM2_PAD0                     (2L)        
#define PINMUX_PA12C_SERCOM2_PAD0                  ((PIN_PA12C_SERCOM2_PAD0 << 16) | MUX_PA12C_SERCOM2_PAD0)
#define PORT_PA12C_SERCOM2_PAD0                    ((1UL) << 12)

#define PIN_PA09D_SERCOM2_PAD1                     (9L)         
#define MUX_PA09D_SERCOM2_PAD1                     (3L)        
#define PINMUX_PA09D_SERCOM2_PAD1                  ((PIN_PA09D_SERCOM2_PAD1 << 16) | MUX_PA09D_SERCOM2_PAD1)
#define PORT_PA09D_SERCOM2_PAD1                    ((1UL) << 9)

#define PIN_PB21D_SERCOM2_PAD1                     (53L)        
#define MUX_PB21D_SERCOM2_PAD1                     (3L)        
#define PINMUX_PB21D_SERCOM2_PAD1                  ((PIN_PB21D_SERCOM2_PAD1 << 16) | MUX_PB21D_SERCOM2_PAD1)
#define PORT_PB21D_SERCOM2_PAD1                    ((1UL) << 21)

#define PIN_PA13C_SERCOM2_PAD1                     (13L)        
#define MUX_PA13C_SERCOM2_PAD1                     (2L)        
#define PINMUX_PA13C_SERCOM2_PAD1                  ((PIN_PA13C_SERCOM2_PAD1 << 16) | MUX_PA13C_SERCOM2_PAD1)
#define PORT_PA13C_SERCOM2_PAD1                    ((1UL) << 13)

#define PIN_PA10D_SERCOM2_PAD2                     (10L)        
#define MUX_PA10D_SERCOM2_PAD2                     (3L)        
#define PINMUX_PA10D_SERCOM2_PAD2                  ((PIN_PA10D_SERCOM2_PAD2 << 16) | MUX_PA10D_SERCOM2_PAD2)
#define PORT_PA10D_SERCOM2_PAD2                    ((1UL) << 10)

#define PIN_PA14C_SERCOM2_PAD2                     (14L)        
#define MUX_PA14C_SERCOM2_PAD2                     (2L)        
#define PINMUX_PA14C_SERCOM2_PAD2                  ((PIN_PA14C_SERCOM2_PAD2 << 16) | MUX_PA14C_SERCOM2_PAD2)
#define PORT_PA14C_SERCOM2_PAD2                    ((1UL) << 14)

#define PIN_PA11D_SERCOM2_PAD3                     (11L)        
#define MUX_PA11D_SERCOM2_PAD3                     (3L)        
#define PINMUX_PA11D_SERCOM2_PAD3                  ((PIN_PA11D_SERCOM2_PAD3 << 16) | MUX_PA11D_SERCOM2_PAD3)
#define PORT_PA11D_SERCOM2_PAD3                    ((1UL) << 11)

#define PIN_PA15C_SERCOM2_PAD3                     (15L)        
#define MUX_PA15C_SERCOM2_PAD3                     (2L)        
#define PINMUX_PA15C_SERCOM2_PAD3                  ((PIN_PA15C_SERCOM2_PAD3 << 16) | MUX_PA15C_SERCOM2_PAD3)
#define PORT_PA15C_SERCOM2_PAD3                    ((1UL) << 15)

/* ========== PORT definition for SERCOM3 peripheral ========== */
#define PIN_PA16D_SERCOM3_PAD0                     (16L)        
#define MUX_PA16D_SERCOM3_PAD0                     (3L)        
#define PINMUX_PA16D_SERCOM3_PAD0                  ((PIN_PA16D_SERCOM3_PAD0 << 16) | MUX_PA16D_SERCOM3_PAD0)
#define PORT_PA16D_SERCOM3_PAD0                    ((1UL) << 16)

#define PIN_PA22C_SERCOM3_PAD0                     (22L)        
#define MUX_PA22C_SERCOM3_PAD0                     (2L)        
#define PINMUX_PA22C_SERCOM3_PAD0                  ((PIN_PA22C_SERCOM3_PAD0 << 16) | MUX_PA22C_SERCOM3_PAD0)
#define PORT_PA22C_SERCOM3_PAD0                    ((1UL) << 22)

#define PIN_PB20C_SERCOM3_PAD0                     (52L)        
#define MUX_PB20C_SERCOM3_PAD0                     (2L)        
#define PINMUX_PB20C_SERCOM3_PAD0                  ((PIN_PB20C_SERCOM3_PAD0 << 16) | MUX_PB20C_SERCOM3_PAD0)
#define PORT_PB20C_SERCOM3_PAD0                    ((1UL) << 20)

#define PIN_PA17D_SERCOM3_PAD1                     (17L)        
#define MUX_PA17D_SERCOM3_PAD1                     (3L)        
#define PINMUX_PA17D_SERCOM3_PAD1                  ((PIN_PA17D_SERCOM3_PAD1 << 16) | MUX_PA17D_SERCOM3_PAD1)
#define PORT_PA17D_SERCOM3_PAD1                    ((1UL) << 17)

#define PIN_PA23C_SERCOM3_PAD1                     (23L)        
#define MUX_PA23C_SERCOM3_PAD1                     (2L)        
#define PINMUX_PA23C_SERCOM3_PAD1                  ((PIN_PA23C_SERCOM3_PAD1 << 16) | MUX_PA23C_SERCOM3_PAD1)
#define PORT_PA23C_SERCOM3_PAD1                    ((1UL) << 23)

#define PIN_PB21C_SERCOM3_PAD1                     (53L)        
#define MUX_PB21C_SERCOM3_PAD1                     (2L)        
#define PINMUX_PB21C_SERCOM3_PAD1                  ((PIN_PB21C_SERCOM3_PAD1 << 16) | MUX_PB21C_SERCOM3_PAD1)
#define PORT_PB21C_SERCOM3_PAD1                    ((1UL) << 21)

#define PIN_PA18D_SERCOM3_PAD2                     (18L)        
#define MUX_PA18D_SERCOM3_PAD2                     (3L)        
#define PINMUX_PA18D_SERCOM3_PAD2                  ((PIN_PA18D_SERCOM3_PAD2 << 16) | MUX_PA18D_SERCOM3_PAD2)
#define PORT_PA18D_SERCOM3_PAD2                    ((1UL) << 18)

#define PIN_PB18D_SERCOM3_PAD2                     (50L)        
#define MUX_PB18D_SERCOM3_PAD2                     (3L)        
#define PINMUX_PB18D_SERCOM3_PAD2                  ((PIN_PB18D_SERCOM3_PAD2 << 16) | MUX_PB18D_SERCOM3_PAD2)
#define PORT_PB18D_SERCOM3_PAD2                    ((1UL) << 18)

#define PIN_PA20D_SERCOM3_PAD2                     (20L)        
#define MUX_PA20D_SERCOM3_PAD2                     (3L)        
#define PINMUX_PA20D_SERCOM3_PAD2                  ((PIN_PA20D_SERCOM3_PAD2 << 16) | MUX_PA20D_SERCOM3_PAD2)
#define PORT_PA20D_SERCOM3_PAD2                    ((1UL) << 20)

#define PIN_PA24C_SERCOM3_PAD2                     (24L)        
#define MUX_PA24C_SERCOM3_PAD2                     (2L)        
#define PINMUX_PA24C_SERCOM3_PAD2                  ((PIN_PA24C_SERCOM3_PAD2 << 16) | MUX_PA24C_SERCOM3_PAD2)
#define PORT_PA24C_SERCOM3_PAD2                    ((1UL) << 24)

#define PIN_PA19D_SERCOM3_PAD3                     (19L)        
#define MUX_PA19D_SERCOM3_PAD3                     (3L)        
#define PINMUX_PA19D_SERCOM3_PAD3                  ((PIN_PA19D_SERCOM3_PAD3 << 16) | MUX_PA19D_SERCOM3_PAD3)
#define PORT_PA19D_SERCOM3_PAD3                    ((1UL) << 19)

#define PIN_PA25C_SERCOM3_PAD3                     (25L)        
#define MUX_PA25C_SERCOM3_PAD3                     (2L)        
#define PINMUX_PA25C_SERCOM3_PAD3                  ((PIN_PA25C_SERCOM3_PAD3 << 16) | MUX_PA25C_SERCOM3_PAD3)
#define PORT_PA25C_SERCOM3_PAD3                    ((1UL) << 25)

#define PIN_PA21D_SERCOM3_PAD3                     (21L)        
#define MUX_PA21D_SERCOM3_PAD3                     (3L)        
#define PINMUX_PA21D_SERCOM3_PAD3                  ((PIN_PA21D_SERCOM3_PAD3 << 16) | MUX_PA21D_SERCOM3_PAD3)
#define PORT_PA21D_SERCOM3_PAD3                    ((1UL) << 21)

#define PIN_PB19D_SERCOM3_PAD3                     (51L)        
#define MUX_PB19D_SERCOM3_PAD3                     (3L)        
#define PINMUX_PB19D_SERCOM3_PAD3                  ((PIN_PB19D_SERCOM3_PAD3 << 16) | MUX_PB19D_SERCOM3_PAD3)
#define PORT_PB19D_SERCOM3_PAD3                    ((1UL) << 19)

/* ========== PORT definition for SERCOM4 peripheral ========== */
#define PIN_PA12D_SERCOM4_PAD0                     (12L)        
#define MUX_PA12D_SERCOM4_PAD0                     (3L)        
#define PINMUX_PA12D_SERCOM4_PAD0                  ((PIN_PA12D_SERCOM4_PAD0 << 16) | MUX_PA12D_SERCOM4_PAD0)
#define PORT_PA12D_SERCOM4_PAD0                    ((1UL) << 12)

#define PIN_PB24D_SERCOM4_PAD0                     (56L)        
#define MUX_PB24D_SERCOM4_PAD0                     (3L)        
#define PINMUX_PB24D_SERCOM4_PAD0                  ((PIN_PB24D_SERCOM4_PAD0 << 16) | MUX_PB24D_SERCOM4_PAD0)
#define PORT_PB24D_SERCOM4_PAD0                    ((1UL) << 24)

#define PIN_PB12C_SERCOM4_PAD0                     (44L)        
#define MUX_PB12C_SERCOM4_PAD0                     (2L)        
#define PINMUX_PB12C_SERCOM4_PAD0                  ((PIN_PB12C_SERCOM4_PAD0 << 16) | MUX_PB12C_SERCOM4_PAD0)
#define PORT_PB12C_SERCOM4_PAD0                    ((1UL) << 12)

#define PIN_PA13D_SERCOM4_PAD1                     (13L)        
#define MUX_PA13D_SERCOM4_PAD1                     (3L)        
#define PINMUX_PA13D_SERCOM4_PAD1                  ((PIN_PA13D_SERCOM4_PAD1 << 16) | MUX_PA13D_SERCOM4_PAD1)
#define PORT_PA13D_SERCOM4_PAD1                    ((1UL) << 13)

#define PIN_PB09D_SERCOM4_PAD1                     (41L)        
#define MUX_PB09D_SERCOM4_PAD1                     (3L)        
#define PINMUX_PB09D_SERCOM4_PAD1                  ((PIN_PB09D_SERCOM4_PAD1 << 16) | MUX_PB09D_SERCOM4_PAD1)
#define PORT_PB09D_SERCOM4_PAD1                    ((1UL) << 9)

#define PIN_PB25D_SERCOM4_PAD1                     (57L)        
#define MUX_PB25D_SERCOM4_PAD1                     (3L)        
#define PINMUX_PB25D_SERCOM4_PAD1                  ((PIN_PB25D_SERCOM4_PAD1 << 16) | MUX_PB25D_SERCOM4_PAD1)
#define PORT_PB25D_SERCOM4_PAD1                    ((1UL) << 25)

#define PIN_PB13C_SERCOM4_PAD1                     (45L)        
#define MUX_PB13C_SERCOM4_PAD1                     (2L)        
#define PINMUX_PB13C_SERCOM4_PAD1                  ((PIN_PB13C_SERCOM4_PAD1 << 16) | MUX_PB13C_SERCOM4_PAD1)
#define PORT_PB13C_SERCOM4_PAD1                    ((1UL) << 13)

#define PIN_PA14D_SERCOM4_PAD2                     (14L)        
#define MUX_PA14D_SERCOM4_PAD2                     (3L)        
#define PINMUX_PA14D_SERCOM4_PAD2                  ((PIN_PA14D_SERCOM4_PAD2 << 16) | MUX_PA14D_SERCOM4_PAD2)
#define PORT_PA14D_SERCOM4_PAD2                    ((1UL) << 14)

#define PIN_PB10D_SERCOM4_PAD2                     (42L)        
#define MUX_PB10D_SERCOM4_PAD2                     (3L)        
#define PINMUX_PB10D_SERCOM4_PAD2                  ((PIN_PB10D_SERCOM4_PAD2 << 16) | MUX_PB10D_SERCOM4_PAD2)
#define PORT_PB10D_SERCOM4_PAD2                    ((1UL) << 10)

#define PIN_PB14C_SERCOM4_PAD2                     (46L)        
#define MUX_PB14C_SERCOM4_PAD2                     (2L)        
#define PINMUX_PB14C_SERCOM4_PAD2                  ((PIN_PB14C_SERCOM4_PAD2 << 16) | MUX_PB14C_SERCOM4_PAD2)
#define PORT_PB14C_SERCOM4_PAD2                    ((1UL) << 14)

#define PIN_PC24D_SERCOM4_PAD2                     (88L)        
#define MUX_PC24D_SERCOM4_PAD2                     (3L)        
#define PINMUX_PC24D_SERCOM4_PAD2                  ((PIN_PC24D_SERCOM4_PAD2 << 16) | MUX_PC24D_SERCOM4_PAD2)
#define PORT_PC24D_SERCOM4_PAD2                    ((1UL) << 24)

#define PIN_PA15D_SERCOM4_PAD3                     (15L)        
#define MUX_PA15D_SERCOM4_PAD3                     (3L)        
#define PINMUX_PA15D_SERCOM4_PAD3                  ((PIN_PA15D_SERCOM4_PAD3 << 16) | MUX_PA15D_SERCOM4_PAD3)
#define PORT_PA15D_SERCOM4_PAD3                    ((1UL) << 15)

#define PIN_PB11D_SERCOM4_PAD3                     (43L)        
#define MUX_PB11D_SERCOM4_PAD3                     (3L)        
#define PINMUX_PB11D_SERCOM4_PAD3                  ((PIN_PB11D_SERCOM4_PAD3 << 16) | MUX_PB11D_SERCOM4_PAD3)
#define PORT_PB11D_SERCOM4_PAD3                    ((1UL) << 11)

#define PIN_PC25D_SERCOM4_PAD3                     (89L)        
#define MUX_PC25D_SERCOM4_PAD3                     (3L)        
#define PINMUX_PC25D_SERCOM4_PAD3                  ((PIN_PC25D_SERCOM4_PAD3 << 16) | MUX_PC25D_SERCOM4_PAD3)
#define PORT_PC25D_SERCOM4_PAD3                    ((1UL) << 25)

#define PIN_PB15C_SERCOM4_PAD3                     (47L)        
#define MUX_PB15C_SERCOM4_PAD3                     (2L)        
#define PINMUX_PB15C_SERCOM4_PAD3                  ((PIN_PB15C_SERCOM4_PAD3 << 16) | MUX_PB15C_SERCOM4_PAD3)
#define PORT_PB15C_SERCOM4_PAD3                    ((1UL) << 15)

/* ========== PORT definition for SERCOM5 peripheral ========== */
#define PIN_PA22D_SERCOM5_PAD0                     (22L)        
#define MUX_PA22D_SERCOM5_PAD0                     (3L)        
#define PINMUX_PA22D_SERCOM5_PAD0                  ((PIN_PA22D_SERCOM5_PAD0 << 16) | MUX_PA22D_SERCOM5_PAD0)
#define PORT_PA22D_SERCOM5_PAD0                    ((1UL) << 22)

#define PIN_PB02D_SERCOM5_PAD0                     (34L)        
#define MUX_PB02D_SERCOM5_PAD0                     (3L)        
#define PINMUX_PB02D_SERCOM5_PAD0                  ((PIN_PB02D_SERCOM5_PAD0 << 16) | MUX_PB02D_SERCOM5_PAD0)
#define PORT_PB02D_SERCOM5_PAD0                    ((1UL) << 2)

#define PIN_PB16C_SERCOM5_PAD0                     (48L)        
#define MUX_PB16C_SERCOM5_PAD0                     (2L)        
#define PINMUX_PB16C_SERCOM5_PAD0                  ((PIN_PB16C_SERCOM5_PAD0 << 16) | MUX_PB16C_SERCOM5_PAD0)
#define PORT_PB16C_SERCOM5_PAD0                    ((1UL) << 16)

#define PIN_PB30D_SERCOM5_PAD0                     (62L)        
#define MUX_PB30D_SERCOM5_PAD0                     (3L)        
#define PINMUX_PB30D_SERCOM5_PAD0                  ((PIN_PB30D_SERCOM5_PAD0 << 16) | MUX_PB30D_SERCOM5_PAD0)
#define PORT_PB30D_SERCOM5_PAD0                    ((1UL) << 30)

#define PIN_PB03D_SERCOM5_PAD1                     (35L)        
#define MUX_PB03D_SERCOM5_PAD1                     (3L)        
#define PINMUX_PB03D_SERCOM5_PAD1                  ((PIN_PB03D_SERCOM5_PAD1 << 16) | MUX_PB03D_SERCOM5_PAD1)
#define PORT_PB03D_SERCOM5_PAD1                    ((1UL) << 3)

#define PIN_PB31D_SERCOM5_PAD1                     (63L)        
#define MUX_PB31D_SERCOM5_PAD1                     (3L)        
#define PINMUX_PB31D_SERCOM5_PAD1                  ((PIN_PB31D_SERCOM5_PAD1 << 16) | MUX_PB31D_SERCOM5_PAD1)
#define PORT_PB31D_SERCOM5_PAD1                    ((1UL) << 31)

#define PIN_PB17C_SERCOM5_PAD1                     (49L)        
#define MUX_PB17C_SERCOM5_PAD1                     (2L)        
#define PINMUX_PB17C_SERCOM5_PAD1                  ((PIN_PB17C_SERCOM5_PAD1 << 16) | MUX_PB17C_SERCOM5_PAD1)
#define PORT_PB17C_SERCOM5_PAD1                    ((1UL) << 17)

#define PIN_PA23D_SERCOM5_PAD1                     (23L)        
#define MUX_PA23D_SERCOM5_PAD1                     (3L)        
#define PINMUX_PA23D_SERCOM5_PAD1                  ((PIN_PA23D_SERCOM5_PAD1 << 16) | MUX_PA23D_SERCOM5_PAD1)
#define PORT_PA23D_SERCOM5_PAD1                    ((1UL) << 23)

#define PIN_PB00D_SERCOM5_PAD2                     (32L)        
#define MUX_PB00D_SERCOM5_PAD2                     (3L)        
#define PINMUX_PB00D_SERCOM5_PAD2                  ((PIN_PB00D_SERCOM5_PAD2 << 16) | MUX_PB00D_SERCOM5_PAD2)
#define PORT_PB00D_SERCOM5_PAD2                    ((1UL) << 0)

#define PIN_PB22D_SERCOM5_PAD2                     (54L)        
#define MUX_PB22D_SERCOM5_PAD2                     (3L)        
#define PINMUX_PB22D_SERCOM5_PAD2                  ((PIN_PB22D_SERCOM5_PAD2 << 16) | MUX_PB22D_SERCOM5_PAD2)
#define PORT_PB22D_SERCOM5_PAD2                    ((1UL) << 22)

#define PIN_PB18C_SERCOM5_PAD2                     (50L)        
#define MUX_PB18C_SERCOM5_PAD2                     (2L)        
#define PINMUX_PB18C_SERCOM5_PAD2                  ((PIN_PB18C_SERCOM5_PAD2 << 16) | MUX_PB18C_SERCOM5_PAD2)
#define PORT_PB18C_SERCOM5_PAD2                    ((1UL) << 18)

#define PIN_PA24D_SERCOM5_PAD2                     (24L)        
#define MUX_PA24D_SERCOM5_PAD2                     (3L)        
#define PINMUX_PA24D_SERCOM5_PAD2                  ((PIN_PA24D_SERCOM5_PAD2 << 16) | MUX_PA24D_SERCOM5_PAD2)
#define PORT_PA24D_SERCOM5_PAD2                    ((1UL) << 24)

#define PIN_PA20C_SERCOM5_PAD2                     (20L)        
#define MUX_PA20C_SERCOM5_PAD2                     (2L)        
#define PINMUX_PA20C_SERCOM5_PAD2                  ((PIN_PA20C_SERCOM5_PAD2 << 16) | MUX_PA20C_SERCOM5_PAD2)
#define PORT_PA20C_SERCOM5_PAD2                    ((1UL) << 20)

#define PIN_PA25D_SERCOM5_PAD3                     (25L)        
#define MUX_PA25D_SERCOM5_PAD3                     (3L)        
#define PINMUX_PA25D_SERCOM5_PAD3                  ((PIN_PA25D_SERCOM5_PAD3 << 16) | MUX_PA25D_SERCOM5_PAD3)
#define PORT_PA25D_SERCOM5_PAD3                    ((1UL) << 25)

#define PIN_PB01D_SERCOM5_PAD3                     (33L)        
#define MUX_PB01D_SERCOM5_PAD3                     (3L)        
#define PINMUX_PB01D_SERCOM5_PAD3                  ((PIN_PB01D_SERCOM5_PAD3 << 16) | MUX_PB01D_SERCOM5_PAD3)
#define PORT_PB01D_SERCOM5_PAD3                    ((1UL) << 1)

#define PIN_PB23D_SERCOM5_PAD3                     (55L)        
#define MUX_PB23D_SERCOM5_PAD3                     (3L)        
#define PINMUX_PB23D_SERCOM5_PAD3                  ((PIN_PB23D_SERCOM5_PAD3 << 16) | MUX_PB23D_SERCOM5_PAD3)
#define PORT_PB23D_SERCOM5_PAD3                    ((1UL) << 23)

#define PIN_PA21C_SERCOM5_PAD3                     (21L)        
#define MUX_PA21C_SERCOM5_PAD3                     (2L)        
#define PINMUX_PA21C_SERCOM5_PAD3                  ((PIN_PA21C_SERCOM5_PAD3 << 16) | MUX_PA21C_SERCOM5_PAD3)
#define PORT_PA21C_SERCOM5_PAD3                    ((1UL) << 21)

#define PIN_PB19C_SERCOM5_PAD3                     (51L)        
#define MUX_PB19C_SERCOM5_PAD3                     (2L)        
#define PINMUX_PB19C_SERCOM5_PAD3                  ((PIN_PB19C_SERCOM5_PAD3 << 16) | MUX_PB19C_SERCOM5_PAD3)
#define PORT_PB19C_SERCOM5_PAD3                    ((1UL) << 19)

/* ========== PORT definition for SERCOM6 peripheral ========== */
#define PIN_PC06C_SERCOM6_PAD0                     (70L)        
#define MUX_PC06C_SERCOM6_PAD0                     (2L)        
#define PINMUX_PC06C_SERCOM6_PAD0                  ((PIN_PC06C_SERCOM6_PAD0 << 16) | MUX_PC06C_SERCOM6_PAD0)
#define PORT_PC06C_SERCOM6_PAD0                    ((1UL) << 6)

#define PIN_PC16C_SERCOM6_PAD0                     (80L)        
#define MUX_PC16C_SERCOM6_PAD0                     (2L)        
#define PINMUX_PC16C_SERCOM6_PAD0                  ((PIN_PC16C_SERCOM6_PAD0 << 16) | MUX_PC16C_SERCOM6_PAD0)
#define PORT_PC16C_SERCOM6_PAD0                    ((1UL) << 16)

#define PIN_PC08C_SERCOM6_PAD0                     (72L)        
#define MUX_PC08C_SERCOM6_PAD0                     (2L)        
#define PINMUX_PC08C_SERCOM6_PAD0                  ((PIN_PC08C_SERCOM6_PAD0 << 16) | MUX_PC08C_SERCOM6_PAD0)
#define PORT_PC08C_SERCOM6_PAD0                    ((1UL) << 8)

#define PIN_PC07C_SERCOM6_PAD1                     (71L)        
#define MUX_PC07C_SERCOM6_PAD1                     (2L)        
#define PINMUX_PC07C_SERCOM6_PAD1                  ((PIN_PC07C_SERCOM6_PAD1 << 16) | MUX_PC07C_SERCOM6_PAD1)
#define PORT_PC07C_SERCOM6_PAD1                    ((1UL) << 7)

#define PIN_PC17C_SERCOM6_PAD1                     (81L)        
#define MUX_PC17C_SERCOM6_PAD1                     (2L)        
#define PINMUX_PC17C_SERCOM6_PAD1                  ((PIN_PC17C_SERCOM6_PAD1 << 16) | MUX_PC17C_SERCOM6_PAD1)
#define PORT_PC17C_SERCOM6_PAD1                    ((1UL) << 17)

#define PIN_PC09C_SERCOM6_PAD1                     (73L)        
#define MUX_PC09C_SERCOM6_PAD1                     (2L)        
#define PINMUX_PC09C_SERCOM6_PAD1                  ((PIN_PC09C_SERCOM6_PAD1 << 16) | MUX_PC09C_SERCOM6_PAD1)
#define PORT_PC09C_SERCOM6_PAD1                    ((1UL) << 9)

#define PIN_PC18C_SERCOM6_PAD2                     (82L)        
#define MUX_PC18C_SERCOM6_PAD2                     (2L)        
#define PINMUX_PC18C_SERCOM6_PAD2                  ((PIN_PC18C_SERCOM6_PAD2 << 16) | MUX_PC18C_SERCOM6_PAD2)
#define PORT_PC18C_SERCOM6_PAD2                    ((1UL) << 18)

#define PIN_PC10C_SERCOM6_PAD2                     (74L)        
#define MUX_PC10C_SERCOM6_PAD2                     (2L)        
#define PINMUX_PC10C_SERCOM6_PAD2                  ((PIN_PC10C_SERCOM6_PAD2 << 16) | MUX_PC10C_SERCOM6_PAD2)
#define PORT_PC10C_SERCOM6_PAD2                    ((1UL) << 10)

#define PIN_PC05C_SERCOM6_PAD3                     (69L)        
#define MUX_PC05C_SERCOM6_PAD3                     (2L)        
#define PINMUX_PC05C_SERCOM6_PAD3                  ((PIN_PC05C_SERCOM6_PAD3 << 16) | MUX_PC05C_SERCOM6_PAD3)
#define PORT_PC05C_SERCOM6_PAD3                    ((1UL) << 5)

#define PIN_PC11C_SERCOM6_PAD3                     (75L)        
#define MUX_PC11C_SERCOM6_PAD3                     (2L)        
#define PINMUX_PC11C_SERCOM6_PAD3                  ((PIN_PC11C_SERCOM6_PAD3 << 16) | MUX_PC11C_SERCOM6_PAD3)
#define PORT_PC11C_SERCOM6_PAD3                    ((1UL) << 11)

#define PIN_PC19C_SERCOM6_PAD3                     (83L)        
#define MUX_PC19C_SERCOM6_PAD3                     (2L)        
#define PINMUX_PC19C_SERCOM6_PAD3                  ((PIN_PC19C_SERCOM6_PAD3 << 16) | MUX_PC19C_SERCOM6_PAD3)
#define PORT_PC19C_SERCOM6_PAD3                    ((1UL) << 19)

/* ========== PORT definition for SERCOM7 peripheral ========== */
#define PIN_PC08D_SERCOM7_PAD0                     (72L)        
#define MUX_PC08D_SERCOM7_PAD0                     (3L)        
#define PINMUX_PC08D_SERCOM7_PAD0                  ((PIN_PC08D_SERCOM7_PAD0 << 16) | MUX_PC08D_SERCOM7_PAD0)
#define PORT_PC08D_SERCOM7_PAD0                    ((1UL) << 8)

#define PIN_PC03C_SERCOM7_PAD0                     (67L)        
#define MUX_PC03C_SERCOM7_PAD0                     (2L)        
#define PINMUX_PC03C_SERCOM7_PAD0                  ((PIN_PC03C_SERCOM7_PAD0 << 16) | MUX_PC03C_SERCOM7_PAD0)
#define PORT_PC03C_SERCOM7_PAD0                    ((1UL) << 3)

#define PIN_PC12C_SERCOM7_PAD0                     (76L)        
#define MUX_PC12C_SERCOM7_PAD0                     (2L)        
#define PINMUX_PC12C_SERCOM7_PAD0                  ((PIN_PC12C_SERCOM7_PAD0 << 16) | MUX_PC12C_SERCOM7_PAD0)
#define PORT_PC12C_SERCOM7_PAD0                    ((1UL) << 12)

#define PIN_PC09D_SERCOM7_PAD1                     (73L)        
#define MUX_PC09D_SERCOM7_PAD1                     (3L)        
#define PINMUX_PC09D_SERCOM7_PAD1                  ((PIN_PC09D_SERCOM7_PAD1 << 16) | MUX_PC09D_SERCOM7_PAD1)
#define PORT_PC09D_SERCOM7_PAD1                    ((1UL) << 9)

#define PIN_PB06C_SERCOM7_PAD1                     (38L)        
#define MUX_PB06C_SERCOM7_PAD1                     (2L)        
#define PINMUX_PB06C_SERCOM7_PAD1                  ((PIN_PB06C_SERCOM7_PAD1 << 16) | MUX_PB06C_SERCOM7_PAD1)
#define PORT_PB06C_SERCOM7_PAD1                    ((1UL) << 6)

#define PIN_PC13C_SERCOM7_PAD1                     (77L)        
#define MUX_PC13C_SERCOM7_PAD1                     (2L)        
#define PINMUX_PC13C_SERCOM7_PAD1                  ((PIN_PC13C_SERCOM7_PAD1 << 16) | MUX_PC13C_SERCOM7_PAD1)
#define PORT_PC13C_SERCOM7_PAD1                    ((1UL) << 13)

#define PIN_PB07D_SERCOM7_PAD2                     (39L)        
#define MUX_PB07D_SERCOM7_PAD2                     (3L)        
#define PINMUX_PB07D_SERCOM7_PAD2                  ((PIN_PB07D_SERCOM7_PAD2 << 16) | MUX_PB07D_SERCOM7_PAD2)
#define PORT_PB07D_SERCOM7_PAD2                    ((1UL) << 7)

#define PIN_PC10D_SERCOM7_PAD2                     (74L)        
#define MUX_PC10D_SERCOM7_PAD2                     (3L)        
#define PINMUX_PC10D_SERCOM7_PAD2                  ((PIN_PC10D_SERCOM7_PAD2 << 16) | MUX_PC10D_SERCOM7_PAD2)
#define PORT_PC10D_SERCOM7_PAD2                    ((1UL) << 10)

#define PIN_PB08C_SERCOM7_PAD2                     (40L)        
#define MUX_PB08C_SERCOM7_PAD2                     (2L)        
#define PINMUX_PB08C_SERCOM7_PAD2                  ((PIN_PB08C_SERCOM7_PAD2 << 16) | MUX_PB08C_SERCOM7_PAD2)
#define PORT_PB08C_SERCOM7_PAD2                    ((1UL) << 8)

#define PIN_PC14C_SERCOM7_PAD2                     (78L)        
#define MUX_PC14C_SERCOM7_PAD2                     (2L)        
#define PINMUX_PC14C_SERCOM7_PAD2                  ((PIN_PC14C_SERCOM7_PAD2 << 16) | MUX_PC14C_SERCOM7_PAD2)
#define PORT_PC14C_SERCOM7_PAD2                    ((1UL) << 14)

#define PIN_PB08D_SERCOM7_PAD3                     (40L)        
#define MUX_PB08D_SERCOM7_PAD3                     (3L)        
#define PINMUX_PB08D_SERCOM7_PAD3                  ((PIN_PB08D_SERCOM7_PAD3 << 16) | MUX_PB08D_SERCOM7_PAD3)
#define PORT_PB08D_SERCOM7_PAD3                    ((1UL) << 8)

#define PIN_PC11D_SERCOM7_PAD3                     (75L)        
#define MUX_PC11D_SERCOM7_PAD3                     (3L)        
#define PINMUX_PC11D_SERCOM7_PAD3                  ((PIN_PC11D_SERCOM7_PAD3 << 16) | MUX_PC11D_SERCOM7_PAD3)
#define PORT_PC11D_SERCOM7_PAD3                    ((1UL) << 11)

#define PIN_PB07C_SERCOM7_PAD3                     (39L)        
#define MUX_PB07C_SERCOM7_PAD3                     (2L)        
#define PINMUX_PB07C_SERCOM7_PAD3                  ((PIN_PB07C_SERCOM7_PAD3 << 16) | MUX_PB07C_SERCOM7_PAD3)
#define PORT_PB07C_SERCOM7_PAD3                    ((1UL) << 7)

#define PIN_PC15C_SERCOM7_PAD3                     (79L)        
#define MUX_PC15C_SERCOM7_PAD3                     (2L)        
#define PINMUX_PC15C_SERCOM7_PAD3                  ((PIN_PC15C_SERCOM7_PAD3 << 16) | MUX_PC15C_SERCOM7_PAD3)
#define PORT_PC15C_SERCOM7_PAD3                    ((1UL) << 15)

/* ========== PORT definition for TC0 peripheral ========== */
#define PIN_PA08E_TC0_WO0                          (8L)         
#define MUX_PA08E_TC0_WO0                          (4L)        
#define PINMUX_PA08E_TC0_WO0                       ((PIN_PA08E_TC0_WO0 << 16) | MUX_PA08E_TC0_WO0)
#define PORT_PA08E_TC0_WO0                         ((1UL) << 8)

#define PIN_PA04E_TC0_WO0                          (4L)         
#define MUX_PA04E_TC0_WO0                          (4L)        
#define PINMUX_PA04E_TC0_WO0                       ((PIN_PA04E_TC0_WO0 << 16) | MUX_PA04E_TC0_WO0)
#define PORT_PA04E_TC0_WO0                         ((1UL) << 4)

#define PIN_PB30E_TC0_WO0                          (62L)        
#define MUX_PB30E_TC0_WO0                          (4L)        
#define PINMUX_PB30E_TC0_WO0                       ((PIN_PB30E_TC0_WO0 << 16) | MUX_PB30E_TC0_WO0)
#define PORT_PB30E_TC0_WO0                         ((1UL) << 30)

#define PIN_PA09E_TC0_WO1                          (9L)         
#define MUX_PA09E_TC0_WO1                          (4L)        
#define PINMUX_PA09E_TC0_WO1                       ((PIN_PA09E_TC0_WO1 << 16) | MUX_PA09E_TC0_WO1)
#define PORT_PA09E_TC0_WO1                         ((1UL) << 9)

#define PIN_PA05E_TC0_WO1                          (5L)         
#define MUX_PA05E_TC0_WO1                          (4L)        
#define PINMUX_PA05E_TC0_WO1                       ((PIN_PA05E_TC0_WO1 << 16) | MUX_PA05E_TC0_WO1)
#define PORT_PA05E_TC0_WO1                         ((1UL) << 5)

#define PIN_PB31E_TC0_WO1                          (63L)        
#define MUX_PB31E_TC0_WO1                          (4L)        
#define PINMUX_PB31E_TC0_WO1                       ((PIN_PB31E_TC0_WO1 << 16) | MUX_PB31E_TC0_WO1)
#define PORT_PB31E_TC0_WO1                         ((1UL) << 31)

/* ========== PORT definition for TC1 peripheral ========== */
#define PIN_PA10E_TC1_WO0                          (10L)        
#define MUX_PA10E_TC1_WO0                          (4L)        
#define PINMUX_PA10E_TC1_WO0                       ((PIN_PA10E_TC1_WO0 << 16) | MUX_PA10E_TC1_WO0)
#define PORT_PA10E_TC1_WO0                         ((1UL) << 10)

#define PIN_PA06E_TC1_WO0                          (6L)         
#define MUX_PA06E_TC1_WO0                          (4L)        
#define PINMUX_PA06E_TC1_WO0                       ((PIN_PA06E_TC1_WO0 << 16) | MUX_PA06E_TC1_WO0)
#define PORT_PA06E_TC1_WO0                         ((1UL) << 6)

#define PIN_PA30E_TC1_WO0                          (30L)        
#define MUX_PA30E_TC1_WO0                          (4L)        
#define PINMUX_PA30E_TC1_WO0                       ((PIN_PA30E_TC1_WO0 << 16) | MUX_PA30E_TC1_WO0)
#define PORT_PA30E_TC1_WO0                         ((1UL) << 30)

#define PIN_PA11E_TC1_WO1                          (11L)        
#define MUX_PA11E_TC1_WO1                          (4L)        
#define PINMUX_PA11E_TC1_WO1                       ((PIN_PA11E_TC1_WO1 << 16) | MUX_PA11E_TC1_WO1)
#define PORT_PA11E_TC1_WO1                         ((1UL) << 11)

#define PIN_PA07E_TC1_WO1                          (7L)         
#define MUX_PA07E_TC1_WO1                          (4L)        
#define PINMUX_PA07E_TC1_WO1                       ((PIN_PA07E_TC1_WO1 << 16) | MUX_PA07E_TC1_WO1)
#define PORT_PA07E_TC1_WO1                         ((1UL) << 7)

#define PIN_PA31E_TC1_WO1                          (31L)        
#define MUX_PA31E_TC1_WO1                          (4L)        
#define PINMUX_PA31E_TC1_WO1                       ((PIN_PA31E_TC1_WO1 << 16) | MUX_PA31E_TC1_WO1)
#define PORT_PA31E_TC1_WO1                         ((1UL) << 31)

/* ========== PORT definition for TC2 peripheral ========== */
#define PIN_PA12E_TC2_WO0                          (12L)        
#define MUX_PA12E_TC2_WO0                          (4L)        
#define PINMUX_PA12E_TC2_WO0                       ((PIN_PA12E_TC2_WO0 << 16) | MUX_PA12E_TC2_WO0)
#define PORT_PA12E_TC2_WO0                         ((1UL) << 12)

#define PIN_PA16E_TC2_WO0                          (16L)        
#define MUX_PA16E_TC2_WO0                          (4L)        
#define PINMUX_PA16E_TC2_WO0                       ((PIN_PA16E_TC2_WO0 << 16) | MUX_PA16E_TC2_WO0)
#define PORT_PA16E_TC2_WO0                         ((1UL) << 16)

#define PIN_PA00E_TC2_WO0                          (0L)         
#define MUX_PA00E_TC2_WO0                          (4L)        
#define PINMUX_PA00E_TC2_WO0                       ((PIN_PA00E_TC2_WO0 << 16) | MUX_PA00E_TC2_WO0)
#define PORT_PA00E_TC2_WO0                         ((1UL) << 0)

#define PIN_PA01E_TC2_WO1                          (1L)         
#define MUX_PA01E_TC2_WO1                          (4L)        
#define PINMUX_PA01E_TC2_WO1                       ((PIN_PA01E_TC2_WO1 << 16) | MUX_PA01E_TC2_WO1)
#define PORT_PA01E_TC2_WO1                         ((1UL) << 1)

#define PIN_PA13E_TC2_WO1                          (13L)        
#define MUX_PA13E_TC2_WO1                          (4L)        
#define PINMUX_PA13E_TC2_WO1                       ((PIN_PA13E_TC2_WO1 << 16) | MUX_PA13E_TC2_WO1)
#define PORT_PA13E_TC2_WO1                         ((1UL) << 13)

#define PIN_PA17E_TC2_WO1                          (17L)        
#define MUX_PA17E_TC2_WO1                          (4L)        
#define PINMUX_PA17E_TC2_WO1                       ((PIN_PA17E_TC2_WO1 << 16) | MUX_PA17E_TC2_WO1)
#define PORT_PA17E_TC2_WO1                         ((1UL) << 17)

/* ========== PORT definition for TC3 peripheral ========== */
#define PIN_PA18E_TC3_WO0                          (18L)        
#define MUX_PA18E_TC3_WO0                          (4L)        
#define PINMUX_PA18E_TC3_WO0                       ((PIN_PA18E_TC3_WO0 << 16) | MUX_PA18E_TC3_WO0)
#define PORT_PA18E_TC3_WO0                         ((1UL) << 18)

#define PIN_PA14E_TC3_WO0                          (14L)        
#define MUX_PA14E_TC3_WO0                          (4L)        
#define PINMUX_PA14E_TC3_WO0                       ((PIN_PA14E_TC3_WO0 << 16) | MUX_PA14E_TC3_WO0)
#define PORT_PA14E_TC3_WO0                         ((1UL) << 14)

#define PIN_PA15E_TC3_WO1                          (15L)        
#define MUX_PA15E_TC3_WO1                          (4L)        
#define PINMUX_PA15E_TC3_WO1                       ((PIN_PA15E_TC3_WO1 << 16) | MUX_PA15E_TC3_WO1)
#define PORT_PA15E_TC3_WO1                         ((1UL) << 15)

#define PIN_PA19E_TC3_WO1                          (19L)        
#define MUX_PA19E_TC3_WO1                          (4L)        
#define PINMUX_PA19E_TC3_WO1                       ((PIN_PA19E_TC3_WO1 << 16) | MUX_PA19E_TC3_WO1)
#define PORT_PA19E_TC3_WO1                         ((1UL) << 19)

/* ========== PORT definition for TC4 peripheral ========== */
#define PIN_PB12E_TC4_WO0                          (44L)        
#define MUX_PB12E_TC4_WO0                          (4L)        
#define PINMUX_PB12E_TC4_WO0                       ((PIN_PB12E_TC4_WO0 << 16) | MUX_PB12E_TC4_WO0)
#define PORT_PB12E_TC4_WO0                         ((1UL) << 12)

#define PIN_PA22E_TC4_WO0                          (22L)        
#define MUX_PA22E_TC4_WO0                          (4L)        
#define PINMUX_PA22E_TC4_WO0                       ((PIN_PA22E_TC4_WO0 << 16) | MUX_PA22E_TC4_WO0)
#define PORT_PA22E_TC4_WO0                         ((1UL) << 22)

#define PIN_PB08E_TC4_WO0                          (40L)        
#define MUX_PB08E_TC4_WO0                          (4L)        
#define PINMUX_PB08E_TC4_WO0                       ((PIN_PB08E_TC4_WO0 << 16) | MUX_PB08E_TC4_WO0)
#define PORT_PB08E_TC4_WO0                         ((1UL) << 8)

#define PIN_PB09E_TC4_WO1                          (41L)        
#define MUX_PB09E_TC4_WO1                          (4L)        
#define PINMUX_PB09E_TC4_WO1                       ((PIN_PB09E_TC4_WO1 << 16) | MUX_PB09E_TC4_WO1)
#define PORT_PB09E_TC4_WO1                         ((1UL) << 9)

#define PIN_PA23E_TC4_WO1                          (23L)        
#define MUX_PA23E_TC4_WO1                          (4L)        
#define PINMUX_PA23E_TC4_WO1                       ((PIN_PA23E_TC4_WO1 << 16) | MUX_PA23E_TC4_WO1)
#define PORT_PA23E_TC4_WO1                         ((1UL) << 23)

#define PIN_PB13E_TC4_WO1                          (45L)        
#define MUX_PB13E_TC4_WO1                          (4L)        
#define PINMUX_PB13E_TC4_WO1                       ((PIN_PB13E_TC4_WO1 << 16) | MUX_PB13E_TC4_WO1)
#define PORT_PB13E_TC4_WO1                         ((1UL) << 13)

/* ========== PORT definition for TC5 peripheral ========== */
#define PIN_PB14E_TC5_WO0                          (46L)        
#define MUX_PB14E_TC5_WO0                          (4L)        
#define PINMUX_PB14E_TC5_WO0                       ((PIN_PB14E_TC5_WO0 << 16) | MUX_PB14E_TC5_WO0)
#define PORT_PB14E_TC5_WO0                         ((1UL) << 14)

#define PIN_PA24E_TC5_WO0                          (24L)        
#define MUX_PA24E_TC5_WO0                          (4L)        
#define PINMUX_PA24E_TC5_WO0                       ((PIN_PA24E_TC5_WO0 << 16) | MUX_PA24E_TC5_WO0)
#define PORT_PA24E_TC5_WO0                         ((1UL) << 24)

#define PIN_PB10E_TC5_WO0                          (42L)        
#define MUX_PB10E_TC5_WO0                          (4L)        
#define PINMUX_PB10E_TC5_WO0                       ((PIN_PB10E_TC5_WO0 << 16) | MUX_PB10E_TC5_WO0)
#define PORT_PB10E_TC5_WO0                         ((1UL) << 10)

#define PIN_PA25E_TC5_WO1                          (25L)        
#define MUX_PA25E_TC5_WO1                          (4L)        
#define PINMUX_PA25E_TC5_WO1                       ((PIN_PA25E_TC5_WO1 << 16) | MUX_PA25E_TC5_WO1)
#define PORT_PA25E_TC5_WO1                         ((1UL) << 25)

#define PIN_PB11E_TC5_WO1                          (43L)        
#define MUX_PB11E_TC5_WO1                          (4L)        
#define PINMUX_PB11E_TC5_WO1                       ((PIN_PB11E_TC5_WO1 << 16) | MUX_PB11E_TC5_WO1)
#define PORT_PB11E_TC5_WO1                         ((1UL) << 11)

#define PIN_PB15E_TC5_WO1                          (47L)        
#define MUX_PB15E_TC5_WO1                          (4L)        
#define PINMUX_PB15E_TC5_WO1                       ((PIN_PB15E_TC5_WO1 << 16) | MUX_PB15E_TC5_WO1)
#define PORT_PB15E_TC5_WO1                         ((1UL) << 15)

/* ========== PORT definition for TC6 peripheral ========== */
#define PIN_PB16E_TC6_WO0                          (48L)        
#define MUX_PB16E_TC6_WO0                          (4L)        
#define PINMUX_PB16E_TC6_WO0                       ((PIN_PB16E_TC6_WO0 << 16) | MUX_PB16E_TC6_WO0)
#define PORT_PB16E_TC6_WO0                         ((1UL) << 16)

#define PIN_PB02E_TC6_WO0                          (34L)        
#define MUX_PB02E_TC6_WO0                          (4L)        
#define PINMUX_PB02E_TC6_WO0                       ((PIN_PB02E_TC6_WO0 << 16) | MUX_PB02E_TC6_WO0)
#define PORT_PB02E_TC6_WO0                         ((1UL) << 2)

#define PIN_PB17E_TC6_WO1                          (49L)        
#define MUX_PB17E_TC6_WO1                          (4L)        
#define PINMUX_PB17E_TC6_WO1                       ((PIN_PB17E_TC6_WO1 << 16) | MUX_PB17E_TC6_WO1)
#define PORT_PB17E_TC6_WO1                         ((1UL) << 17)

#define PIN_PB03E_TC6_WO1                          (35L)        
#define MUX_PB03E_TC6_WO1                          (4L)        
#define PINMUX_PB03E_TC6_WO1                       ((PIN_PB03E_TC6_WO1 << 16) | MUX_PB03E_TC6_WO1)
#define PORT_PB03E_TC6_WO1                         ((1UL) << 3)

/* ========== PORT definition for TC7 peripheral ========== */
#define PIN_PB22E_TC7_WO0                          (54L)        
#define MUX_PB22E_TC7_WO0                          (4L)        
#define PINMUX_PB22E_TC7_WO0                       ((PIN_PB22E_TC7_WO0 << 16) | MUX_PB22E_TC7_WO0)
#define PORT_PB22E_TC7_WO0                         ((1UL) << 22)

#define PIN_PA20E_TC7_WO0                          (20L)        
#define MUX_PA20E_TC7_WO0                          (4L)        
#define PINMUX_PA20E_TC7_WO0                       ((PIN_PA20E_TC7_WO0 << 16) | MUX_PA20E_TC7_WO0)
#define PORT_PA20E_TC7_WO0                         ((1UL) << 20)

#define PIN_PB00E_TC7_WO0                          (32L)        
#define MUX_PB00E_TC7_WO0                          (4L)        
#define PINMUX_PB00E_TC7_WO0                       ((PIN_PB00E_TC7_WO0 << 16) | MUX_PB00E_TC7_WO0)
#define PORT_PB00E_TC7_WO0                         ((1UL) << 0)

#define PIN_PB01E_TC7_WO1                          (33L)        
#define MUX_PB01E_TC7_WO1                          (4L)        
#define PINMUX_PB01E_TC7_WO1                       ((PIN_PB01E_TC7_WO1 << 16) | MUX_PB01E_TC7_WO1)
#define PORT_PB01E_TC7_WO1                         ((1UL) << 1)

#define PIN_PA21E_TC7_WO1                          (21L)        
#define MUX_PA21E_TC7_WO1                          (4L)        
#define PINMUX_PA21E_TC7_WO1                       ((PIN_PA21E_TC7_WO1 << 16) | MUX_PA21E_TC7_WO1)
#define PORT_PA21E_TC7_WO1                         ((1UL) << 21)

#define PIN_PB23E_TC7_WO1                          (55L)        
#define MUX_PB23E_TC7_WO1                          (4L)        
#define PINMUX_PB23E_TC7_WO1                       ((PIN_PB23E_TC7_WO1 << 16) | MUX_PB23E_TC7_WO1)
#define PORT_PB23E_TC7_WO1                         ((1UL) << 23)

/* ========== PORT definition for TCC0 peripheral ========== */
#define PIN_PA08F_TCC0_WO0                         (8L)         
#define MUX_PA08F_TCC0_WO0                         (5L)        
#define PINMUX_PA08F_TCC0_WO0                      ((PIN_PA08F_TCC0_WO0 << 16) | MUX_PA08F_TCC0_WO0)
#define PORT_PA08F_TCC0_WO0                        ((1UL) << 8)

#define PIN_PA09F_TCC0_WO1                         (9L)         
#define MUX_PA09F_TCC0_WO1                         (5L)        
#define PINMUX_PA09F_TCC0_WO1                      ((PIN_PA09F_TCC0_WO1 << 16) | MUX_PA09F_TCC0_WO1)
#define PORT_PA09F_TCC0_WO1                        ((1UL) << 9)

#define PIN_PA10F_TCC0_WO2                         (10L)        
#define MUX_PA10F_TCC0_WO2                         (5L)        
#define PINMUX_PA10F_TCC0_WO2                      ((PIN_PA10F_TCC0_WO2 << 16) | MUX_PA10F_TCC0_WO2)
#define PORT_PA10F_TCC0_WO2                        ((1UL) << 10)

#define PIN_PA11F_TCC0_WO3                         (11L)        
#define MUX_PA11F_TCC0_WO3                         (5L)        
#define PINMUX_PA11F_TCC0_WO3                      ((PIN_PA11F_TCC0_WO3 << 16) | MUX_PA11F_TCC0_WO3)
#define PORT_PA11F_TCC0_WO3                        ((1UL) << 11)

#define PIN_PB10F_TCC0_WO4                         (42L)        
#define MUX_PB10F_TCC0_WO4                         (5L)        
#define PINMUX_PB10F_TCC0_WO4                      ((PIN_PB10F_TCC0_WO4 << 16) | MUX_PB10F_TCC0_WO4)
#define PORT_PB10F_TCC0_WO4                        ((1UL) << 10)

#define PIN_PB11F_TCC0_WO5                         (43L)        
#define MUX_PB11F_TCC0_WO5                         (5L)        
#define PINMUX_PB11F_TCC0_WO5                      ((PIN_PB11F_TCC0_WO5 << 16) | MUX_PB11F_TCC0_WO5)
#define PORT_PB11F_TCC0_WO5                        ((1UL) << 11)

#define PIN_PA12F_TCC0_WO6                         (12L)        
#define MUX_PA12F_TCC0_WO6                         (5L)        
#define PINMUX_PA12F_TCC0_WO6                      ((PIN_PA12F_TCC0_WO6 << 16) | MUX_PA12F_TCC0_WO6)
#define PORT_PA12F_TCC0_WO6                        ((1UL) << 12)

#define PIN_PB12F_TCC0_WO6                         (44L)        
#define MUX_PB12F_TCC0_WO6                         (5L)        
#define PINMUX_PB12F_TCC0_WO6                      ((PIN_PB12F_TCC0_WO6 << 16) | MUX_PB12F_TCC0_WO6)
#define PORT_PB12F_TCC0_WO6                        ((1UL) << 12)

#define PIN_PA13F_TCC0_WO7                         (13L)        
#define MUX_PA13F_TCC0_WO7                         (5L)        
#define PINMUX_PA13F_TCC0_WO7                      ((PIN_PA13F_TCC0_WO7 << 16) | MUX_PA13F_TCC0_WO7)
#define PORT_PA13F_TCC0_WO7                        ((1UL) << 13)

#define PIN_PB13F_TCC0_WO7                         (45L)        
#define MUX_PB13F_TCC0_WO7                         (5L)        
#define PINMUX_PB13F_TCC0_WO7                      ((PIN_PB13F_TCC0_WO7 << 16) | MUX_PB13F_TCC0_WO7)
#define PORT_PB13F_TCC0_WO7                        ((1UL) << 13)

/* ========== PORT definition for TCC1 peripheral ========== */
#define PIN_PA16F_TCC1_WO0                         (16L)        
#define MUX_PA16F_TCC1_WO0                         (5L)        
#define PINMUX_PA16F_TCC1_WO0                      ((PIN_PA16F_TCC1_WO0 << 16) | MUX_PA16F_TCC1_WO0)
#define PORT_PA16F_TCC1_WO0                        ((1UL) << 16)

#define PIN_PA22F_TCC1_WO0                         (22L)        
#define MUX_PA22F_TCC1_WO0                         (5L)        
#define PINMUX_PA22F_TCC1_WO0                      ((PIN_PA22F_TCC1_WO0 << 16) | MUX_PA22F_TCC1_WO0)
#define PORT_PA22F_TCC1_WO0                        ((1UL) << 22)

#define PIN_PA17F_TCC1_WO1                         (17L)        
#define MUX_PA17F_TCC1_WO1                         (5L)        
#define PINMUX_PA17F_TCC1_WO1                      ((PIN_PA17F_TCC1_WO1 << 16) | MUX_PA17F_TCC1_WO1)
#define PORT_PA17F_TCC1_WO1                        ((1UL) << 17)

#define PIN_PA23F_TCC1_WO1                         (23L)        
#define MUX_PA23F_TCC1_WO1                         (5L)        
#define PINMUX_PA23F_TCC1_WO1                      ((PIN_PA23F_TCC1_WO1 << 16) | MUX_PA23F_TCC1_WO1)
#define PORT_PA23F_TCC1_WO1                        ((1UL) << 23)

#define PIN_PA18F_TCC1_WO2                         (18L)        
#define MUX_PA18F_TCC1_WO2                         (5L)        
#define PINMUX_PA18F_TCC1_WO2                      ((PIN_PA18F_TCC1_WO2 << 16) | MUX_PA18F_TCC1_WO2)
#define PORT_PA18F_TCC1_WO2                        ((1UL) << 18)

#define PIN_PB22F_TCC1_WO2                         (54L)        
#define MUX_PB22F_TCC1_WO2                         (5L)        
#define PINMUX_PB22F_TCC1_WO2                      ((PIN_PB22F_TCC1_WO2 << 16) | MUX_PB22F_TCC1_WO2)
#define PORT_PB22F_TCC1_WO2                        ((1UL) << 22)

#define PIN_PA19F_TCC1_WO3                         (19L)        
#define MUX_PA19F_TCC1_WO3                         (5L)        
#define PINMUX_PA19F_TCC1_WO3                      ((PIN_PA19F_TCC1_WO3 << 16) | MUX_PA19F_TCC1_WO3)
#define PORT_PA19F_TCC1_WO3                        ((1UL) << 19)

#define PIN_PB23F_TCC1_WO3                         (55L)        
#define MUX_PB23F_TCC1_WO3                         (5L)        
#define PINMUX_PB23F_TCC1_WO3                      ((PIN_PB23F_TCC1_WO3 << 16) | MUX_PB23F_TCC1_WO3)
#define PORT_PB23F_TCC1_WO3                        ((1UL) << 23)

/* ========== PORT definition for TCC2 peripheral ========== */
#define PIN_PC03F_TCC2_WO0                         (67L)        
#define MUX_PC03F_TCC2_WO0                         (5L)        
#define PINMUX_PC03F_TCC2_WO0                      ((PIN_PC03F_TCC2_WO0 << 16) | MUX_PC03F_TCC2_WO0)
#define PORT_PC03F_TCC2_WO0                        ((1UL) << 3)

#define PIN_PA20F_TCC2_WO0                         (20L)        
#define MUX_PA20F_TCC2_WO0                         (5L)        
#define PINMUX_PA20F_TCC2_WO0                      ((PIN_PA20F_TCC2_WO0 << 16) | MUX_PA20F_TCC2_WO0)
#define PORT_PA20F_TCC2_WO0                        ((1UL) << 20)

#define PIN_PA24F_TCC2_WO0                         (24L)        
#define MUX_PA24F_TCC2_WO0                         (5L)        
#define PINMUX_PA24F_TCC2_WO0                      ((PIN_PA24F_TCC2_WO0 << 16) | MUX_PA24F_TCC2_WO0)
#define PORT_PA24F_TCC2_WO0                        ((1UL) << 24)

#define PIN_PA25F_TCC2_WO1                         (25L)        
#define MUX_PA25F_TCC2_WO1                         (5L)        
#define PINMUX_PA25F_TCC2_WO1                      ((PIN_PA25F_TCC2_WO1 << 16) | MUX_PA25F_TCC2_WO1)
#define PORT_PA25F_TCC2_WO1                        ((1UL) << 25)

#define PIN_PA21F_TCC2_WO1                         (21L)        
#define MUX_PA21F_TCC2_WO1                         (5L)        
#define PINMUX_PA21F_TCC2_WO1                      ((PIN_PA21F_TCC2_WO1 << 16) | MUX_PA21F_TCC2_WO1)
#define PORT_PA21F_TCC2_WO1                        ((1UL) << 21)

#define PIN_PC05F_TCC2_WO1                         (69L)        
#define MUX_PC05F_TCC2_WO1                         (5L)        
#define PINMUX_PC05F_TCC2_WO1                      ((PIN_PC05F_TCC2_WO1 << 16) | MUX_PC05F_TCC2_WO1)
#define PORT_PC05F_TCC2_WO1                        ((1UL) << 5)



#endif /* _SAMC21N18A_GPIO_H_ */

