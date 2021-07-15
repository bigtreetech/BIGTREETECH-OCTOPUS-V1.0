/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <cstdlib>
#include <cstring>

#include "USARTClass.h"

// Constructors ////////////////////////////////////////////////////////////////

USARTClass::USARTClass(Usart* pUsart, IRQn_Type p_irqn, uint32_t p_id, size_t numTxSlots, size_t numRxSlots, OnBeginFn p_onBegin, OnEndFn p_onEnd) noexcept
  : AsyncSerial((Uart*)pUsart, p_irqn, p_id, numTxSlots, numRxSlots, p_onBegin, p_onEnd)
{
  // In case anyone needs USART specific functionality in the future
  _pUsart=pUsart;
}

// Public Methods //////////////////////////////////////////////////////////////

void USARTClass::begin(const uint32_t dwBaudRate) noexcept
{
  begin(dwBaudRate, Mode_8N1);
}

void USARTClass::begin(const uint32_t dwBaudRate, const UARTModes config) noexcept
{
  uint32_t modeReg = static_cast<uint32_t>(config);
  modeReg |= US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHMODE_NORMAL;
  init(dwBaudRate, modeReg);
}

void USARTClass::begin(const uint32_t dwBaudRate, const USARTModes config) noexcept
{
  uint32_t modeReg = static_cast<uint32_t>(config);
  modeReg |= US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK | US_MR_CHMODE_NORMAL;
  init(dwBaudRate, modeReg);
}

// End
