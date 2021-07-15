//Author: sdavi

//implementation of missing PWM driver


#ifndef __PWM_176X_H_
#define __PWM_176X_H_

#ifdef __cplusplus
extern "C" {
#endif


/*------------- Pulse-Width Modulation (PWM) ---------------------------------*/
//from lpc17xx.h
typedef struct
{
    __IO uint32_t IR;
    __IO uint32_t TCR;
    __IO uint32_t TC;
    __IO uint32_t PR;
    __IO uint32_t PC;
    __IO uint32_t MCR;
    __IO uint32_t MR0;
    __IO uint32_t MR1;
    __IO uint32_t MR2;
    __IO uint32_t MR3;
    __IO uint32_t CCR;
    __I  uint32_t CR0;
    __I  uint32_t CR1;
    __I  uint32_t CR2;
    __I  uint32_t CR3;
    uint32_t RESERVED0;
    __IO uint32_t MR4;
    __IO uint32_t MR5;
    __IO uint32_t MR6;
    __IO uint32_t PCR;
    __IO uint32_t LER;
    uint32_t RESERVED1[7];
    __IO uint32_t CTCR;
} LPC_PWM_TypeDef;
#define LPC_PWM1              ((LPC_PWM_TypeDef       *) LPC_PWM1_BASE     )


#define PWM_TCR_CNT_EN      0x00000001
#define PWM_TCR_RESET       0x00000002
#define PWM_TCR_PWM_EN      0x00000008

#define PWM_MR0_INT         (1 << 0)
#define PWM_MR1_INT         (1 << 1)
#define PWM_MR2_INT         (1 << 2)
#define PWM_MR3_INT         (1 << 3)
#define PWM_MR4_INT         (1 << 8)
#define PWM_MR5_INT         (1 << 9)
#define PWM_MR6_INT         (1 << 10)


//PCR Bits 2:6
#define PWM_SEL2            (1 << 2)
#define PWM_SEL3            (1 << 3)
#define PWM_SEL4            (1 << 4)
#define PWM_SEL5            (1 << 5)
#define PWM_SEL6            (1 << 6)

//PCR Bits 9:14
#define PWM_PWMENA1         (1 << 9)
#define PWM_PWMENA2         (1 << 10)
#define PWM_PWMENA3         (1 << 11)
#define PWM_PWMENA4         (1 << 12)
#define PWM_PWMENA5         (1 << 13)
#define PWM_PWMENA6         (1 << 14)


#define PWM_LER0_EN         (1 << 0)
#define PWM_LER1_EN         (1 << 1)
#define PWM_LER2_EN         (1 << 2)
#define PWM_LER3_EN         (1 << 3)
#define PWM_LER4_EN         (1 << 4)
#define PWM_LER5_EN         (1 << 5)
#define PWM_LER6_EN         (1 << 6)



typedef struct
{
    gpioPins_et pinNumber;
    uint8_t pwmChannelNumber;
    uint8_t PinFunSel;
} pwmChannelConfig_st;


constexpr uint8_t NumPwmChannels = 6;
// Definitions for PWM channels
enum EPWMChannel : int8_t
{
    NOT_ON_PWM=-1,
    PWM1_1=0,
    PWM1_2,
    PWM1_3,
    PWM1_4,
    PWM1_5,
    PWM1_6,
};


//  Pin, PWM Channel, PinSel
static const pwmChannelConfig_st PinMap_PWM[] =
{
    {P1_18, PWM1_1, 2},
    {P1_20, PWM1_2, 2},
    {P1_21, PWM1_3, 2},
    {P1_23, PWM1_4, 2},
    {P1_24, PWM1_5, 2},
    {P1_26, PWM1_6, 2},
    {P2_0 , PWM1_1, 1},
    {P2_1 , PWM1_2, 1},
    {P2_2 , PWM1_3, 1},
    {P2_3 , PWM1_4, 1},
    {P2_4 , PWM1_5, 1},
    {P2_5 , PWM1_6, 1},
    {P3_25, PWM1_2, 3},
    {P3_26, PWM1_3, 3},
};



#ifdef __cplusplus
}
#endif

#endif /* __PWM_176X_H_ */
