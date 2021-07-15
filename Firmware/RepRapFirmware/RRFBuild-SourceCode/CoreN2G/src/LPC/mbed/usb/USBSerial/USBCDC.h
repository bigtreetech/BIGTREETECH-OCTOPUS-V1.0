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

//SD:: change buffer sizes


#ifndef USBCDC_H
#define USBCDC_H

#include "USBPhyTypes.h"

/* These headers are included for child class. */
#include "USBDescriptor.h"
#include "USBDevice_Types.h"

#include "USBDevice.h"
#include "OperationList.h"
#define USE_STATIC_ENDPOINTS
class USBCDC: public USBDevice {
public:

    /**
    * Basic constructor
    *
    * Construct this object optionally connecting and blocking until it is ready.
    *
    * @note Do not use this constructor in derived classes.
    *
    * @param connect_blocking true to perform a blocking connect, false to start in a disconnected state
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your product_release
    */
    USBCDC(bool connect_blocking = true, uint16_t vendor_id = 0x1f00, uint16_t product_id = 0x2012, uint16_t product_release = 0x0001);

    /**
    * Fully featured constructor
    *
    * Construct this object with the supplied USBPhy and parameters. The user
    * this object is responsible for calling connect() or init().
    *
    * @note Derived classes must use this constructor and call init() or
    * connect() themselves. Derived classes should also call deinit() in
    * their destructor. This ensures that no interrupts can occur when the
    * object is partially constructed or destroyed.
    *
    * @param phy USB phy to use
    * @param vendor_id Your vendor_id
    * @param product_id Your product_id
    * @param product_release Your product_release
    */
    USBCDC(USBPhy *phy, uint16_t vendor_id, uint16_t product_id, uint16_t product_release);

    /**
     * Destroy this object
     *
     * Any classes which inherit from this class must call deinit
     * before this destructor runs.
     */
    virtual ~USBCDC();

    /**
     * Check if this class is ready
     *
     * @return true if a terminal is connected, false otherwise
     */
    bool ready();

    /**
     * Send what there is room for
     *
     * @param buffer data to send
     * @param size maximum number of bytes to send
     * @param actual a pointer to where to store the number of bytes sent
     * @param now true to start data transmission, false to wait
     */
    void send_nb(uint8_t *buffer, uint32_t size, uint32_t *actual, bool now = true);


    /**
     * Read from the receive buffer
     *
     * @param buffer buffer to fill with data
     * @param size maximum number of bytes read
     * @param actual a pointer to where to store the number of bytes actually received
     */
    void receive_nb(uint8_t *buffer, uint32_t size, uint32_t *actual);

protected:
    /*
    * Get device descriptor. Warning: this method has to store the length of the report descriptor in reportLength.
    *
    * @returns pointer to the device descriptor
    */
    virtual const uint8_t *device_desc();

    /*
    * Get string product descriptor
    *
    * @returns pointer to the string product descriptor
    */
    virtual const uint8_t *string_iproduct_desc();

    /*
    * Get string interface descriptor
    *
    * @returns pointer to the string interface descriptor
    */
    virtual const uint8_t *string_iinterface_desc();

    /*
    * Get configuration descriptor
    *
    * @param index descriptor index
    * @returns pointer to the configuration descriptor
    */
    virtual const uint8_t *configuration_desc(uint8_t index);

    /*
    * Called by USBCallback_requestCompleted when CDC line coding is changed
    * Warning: Called in ISR
    *
    * @param baud The baud rate
    * @param bits The number of bits in a word (5-8)
    * @param parity The parity
    * @param stop The number of stop bits (1 or 2)
    */
    virtual void line_coding_changed(int baud, int bits, int parity, int stop) {};

protected:
    virtual void callback_reset();
    virtual void callback_state_change(DeviceState new_state);
    virtual void callback_request(const setup_packet_t *setup);
    virtual void callback_request_xfer_done(const setup_packet_t *setup, bool aborted);
    virtual void callback_set_configuration(uint8_t configuration);
    virtual void callback_set_interface(uint16_t interface, uint8_t alternate);

    void _init();

    void _change_terminal_connected(bool connected);

    void _send_isr_start();
    void _send_isr();

    void _receive_isr_start();
    void _receive_isr();

    usb_ep_t _bulk_in;
    usb_ep_t _bulk_out;
    usb_ep_t _int_in;

    uint8_t _cdc_line_coding[7];
    uint8_t _cdc_new_line_coding[7];
#ifndef USE_STATIC_ENDPOINTS
    uint8_t _config_descriptor[75];
#endif

    bool _terminal_connected;

    bool _tx_in_progress;
    uint8_t _tx_buffer[64] __attribute__ ((aligned (4)));
    uint8_t *_tx_buf;
    uint32_t _tx_size;

    bool _rx_in_progress;
    uint8_t _rx_buffer[64] __attribute__ ((aligned (4)));
    uint8_t *_rx_buf;
    uint32_t _rx_size;
};

#endif
