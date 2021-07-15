/*
 * Copyright (c) 2018-2019, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdint.h"
#include "USBSerial.h"
#include "usb_phy_api.h"


USBSerial::USBSerial(bool connect_blocking, uint16_t vendor_id, uint16_t product_id, uint16_t product_release):
    USBCDC(get_usb_phy(), vendor_id, product_id, product_release)
{
    if (connect_blocking) {
        connect();
    } else {
        init();
    }
}

USBSerial::USBSerial(USBPhy *phy, uint16_t vendor_id, uint16_t product_id, uint16_t product_release):
    USBCDC(phy, vendor_id, product_id, product_release)
{
}

USBSerial::~USBSerial()
{
    deinit();
}


uint8_t USBSerial::available()
{
    MBED_ASSERT(_rx_size < 0xff);
    return _rx_size;
}

bool USBSerial::connected()
{
    return _terminal_connected;
}


//
void USBSerial::flush()
{
    while(_terminal_connected && _tx_in_progress){}

}
