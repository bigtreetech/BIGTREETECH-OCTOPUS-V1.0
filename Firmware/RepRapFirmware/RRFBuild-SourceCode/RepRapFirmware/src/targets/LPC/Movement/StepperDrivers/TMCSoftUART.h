



#ifndef TMCSOFTUART_H_
#define TMCSOFTUART_H_

void TMCSoftUARTAbort() noexcept;
void TMCSoftUARTStartTransfer(uint8_t driver, volatile uint8_t *WritePtr, uint32_t WriteCnt, volatile uint8_t *ReadPtr, uint32_t ReadCnt) noexcept;
bool TMCSoftUARTCheckComplete() noexcept;
void TMCSoftUARTInit() noexcept;
void TMCSoftUARTShutdown() noexcept;
#endif