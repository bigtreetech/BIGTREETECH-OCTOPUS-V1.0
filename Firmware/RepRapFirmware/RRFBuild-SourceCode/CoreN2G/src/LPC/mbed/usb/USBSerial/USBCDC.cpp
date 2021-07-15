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

//SD:: Removed MBED RTOS dependency

#include "stdint.h"
#include "USBCDC.h"
#include "EndpointResolver.h"
#include "usb_phy_api.h"

#ifdef USE_STATIC_ENDPOINTS
// These are static versions of _bulk_in, _bulk_out, _int_in, using these values allows us to
// place the config data into flash rather than RAM.
#define BULK_IN 130
#define BULK_OUT 2
#define INT_IN 129
#else
#define BULK_IN _bulk_in
#define BULK_OUT _bulk_out
#define INT_IN _int_in
#endif

static const uint8_t cdc_line_coding_default[7] = {0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08};

#define DEFAULT_CONFIGURATION (1)

#define CDC_SET_LINE_CODING        0x20
#define CDC_GET_LINE_CODING        0x21
#define CDC_SET_CONTROL_LINE_STATE 0x22

// Control Line State bits
#define CLS_DTR   (1 << 0)
#define CLS_RTS   (1 << 1)

#define CDC_MAX_PACKET_SIZE    64


USBCDC::USBCDC(bool connect_blocking, uint16_t vendor_id, uint16_t product_id, uint16_t product_release)
    : USBDevice(get_usb_phy(), vendor_id, product_id, product_release)

{
    _init();
    if (connect_blocking) {
        connect();
    } else {
        init();
    }
}

USBCDC::USBCDC(USBPhy *phy, uint16_t vendor_id, uint16_t product_id, uint16_t product_release)
    : USBDevice(phy, vendor_id, product_id, product_release)
{
    _init();
}

USBCDC::~USBCDC()
{
    deinit();
}

void USBCDC::_init()
{
    memcpy(_cdc_line_coding, cdc_line_coding_default, sizeof(_cdc_line_coding));

    EndpointResolver resolver(endpoint_table());
    resolver.endpoint_ctrl(CDC_MAX_PACKET_SIZE);
    _bulk_in = resolver.endpoint_in(USB_EP_TYPE_BULK, CDC_MAX_PACKET_SIZE);
    _bulk_out = resolver.endpoint_out(USB_EP_TYPE_BULK, CDC_MAX_PACKET_SIZE);
    _int_in = resolver.endpoint_in(USB_EP_TYPE_INT, CDC_MAX_PACKET_SIZE);

#ifdef USE_STATIC_ENDPOINTS
    MBED_ASSERT(_bulk_in == BULK_IN);
    MBED_ASSERT(_bulk_out == BULK_OUT);
    MBED_ASSERT(_int_in == INT_IN);
#endif

    MBED_ASSERT(resolver.valid());

    _terminal_connected = false;

    _tx_in_progress = false;
    _tx_buf = _tx_buffer;
    _tx_size = 0;

    _rx_in_progress = false;
    _rx_buf = _rx_buffer;
    _rx_size = 0;
}

void USBCDC::callback_reset()
{
    assert_locked();
    /* Called in ISR context */

    _change_terminal_connected(false);
};

void USBCDC::callback_state_change(DeviceState new_state)
{
    assert_locked();
    /* Called in ISR context */

    if (new_state != Configured) {
        _change_terminal_connected(false);
    }
#ifndef USB_CDC_USE_DTR
    else
        _change_terminal_connected(true);
#endif

}

void USBCDC::callback_request(const setup_packet_t *setup)
{
    assert_locked();
    /* Called in ISR context */

    RequestResult result = PassThrough;
    uint8_t *data = NULL;
    uint32_t size = 0;

    /* Only process class-specific requests */
    if (setup->bmRequestType.Type == CLASS_TYPE) {
        switch (setup->bRequest) {
            case CDC_GET_LINE_CODING:
                result = Send;
                data = _cdc_line_coding;
                size = 7;
                break;
            case CDC_SET_LINE_CODING:
                result = Receive;
                data = _cdc_new_line_coding;
                size = 7;
                break;
            case CDC_SET_CONTROL_LINE_STATE:
#if CDC_USE_DTR
                if (setup->wValue & CLS_DTR) {
                    _change_terminal_connected(true);
                } else {
                    _change_terminal_connected(false);
                }
#endif
                result = Success;
                break;
            default:
                result = Failure;
                break;
        }
    }
    complete_request(result, data, size);
}


void USBCDC::callback_request_xfer_done(const setup_packet_t *setup, bool aborted)
{
    assert_locked();
    /* Called in ISR context */

    if (aborted) {
        complete_request_xfer_done(false);
        return;
    }

    bool success = false;

    /* Process class-specific requests */
    if (setup->bmRequestType.Type == CLASS_TYPE) {
        if ((setup->bRequest == CDC_SET_LINE_CODING) && (setup->wLength == 7)) {
            if (memcmp(_cdc_line_coding, _cdc_new_line_coding, 7)) {
                memcpy(_cdc_line_coding, _cdc_new_line_coding, 7);

                const uint8_t *buf = _cdc_line_coding;
                int baud = buf[0] + (buf[1] << 8)
                           + (buf[2] << 16) + (buf[3] << 24);
                int stop = buf[4];
                int bits = buf[6];
                int parity = buf[5];

                line_coding_changed(baud, bits, parity, stop);
            }
            success = true;
        }
        if (setup->bRequest == CDC_GET_LINE_CODING) {
            success = true;
        }
    }

    complete_request_xfer_done(success);
}

void USBCDC::callback_set_configuration(uint8_t configuration)
{
    assert_locked();
    /* Called in ISR context */

    bool ret = false;
    if (configuration == DEFAULT_CONFIGURATION) {
        // Configure endpoints > 0
        endpoint_add(_int_in, CDC_MAX_PACKET_SIZE, USB_EP_TYPE_INT);
        endpoint_add(_bulk_in, CDC_MAX_PACKET_SIZE, USB_EP_TYPE_BULK, &USBCDC::_send_isr);
        endpoint_add(_bulk_out, CDC_MAX_PACKET_SIZE, USB_EP_TYPE_BULK, &USBCDC::_receive_isr);

        read_start(_bulk_out, _rx_buf, sizeof(_rx_buffer));
        _rx_in_progress = true;

        ret = true;
    }

    complete_set_configuration(ret);
}

void USBCDC::callback_set_interface(uint16_t interface, uint8_t alternate)
{
    assert_locked();
    complete_set_interface(true);
}

void USBCDC::_change_terminal_connected(bool connected)
{
    assert_locked();

    _terminal_connected = connected;
    if (!_terminal_connected) {
        // Abort TX
        if (_tx_in_progress) {
            endpoint_abort(_bulk_in);
            _tx_in_progress = false;
        }
        _tx_buf = _tx_buffer;
        _tx_size = 0;

        // Abort RX
        if (_rx_in_progress) {
            endpoint_abort(_bulk_in);
            _rx_in_progress = false;
        }
        _rx_buf = _rx_buffer;
        _rx_size = 0;
    }
}

bool USBCDC::ready()
{
    return _terminal_connected;
}

void USBCDC::send_nb(uint8_t *buffer, uint32_t size, uint32_t *actual, bool now)
{
    lock();

    *actual = 0;
    uint32_t free = sizeof(_tx_buffer) - _tx_size;
    uint32_t write_size = free > size ? size : free;

    if (_terminal_connected) {
        // if we can write the data directly to the device
        if (_tx_size == 0 && !_tx_in_progress) {
            if (USBDevice::write_start(_bulk_in, buffer, write_size)) {
                _tx_in_progress = true;
                size -= write_size;
                buffer += write_size;
                *actual = write_size;
                write_size = free > size ? size : free;
            }
        }
        // user the buffer
        if (write_size > 0) {
            memcpy(_tx_buf, buffer, write_size);
            _tx_size += write_size;
            _tx_buf += write_size;
            *actual += write_size;
            if (now) {
                _send_isr_start();
            }
        }
    }
    unlock();
}

void USBCDC::_send_isr_start()
{
    assert_locked();

    if (!_tx_in_progress && _tx_size) {
        if (USBDevice::write_start(_bulk_in, _tx_buffer, _tx_size)) {
            _tx_buf = _tx_buffer;
            _tx_size = 0;
            _tx_in_progress = true;
        }
    }
}

/*
* Called by when CDC data is sent
* Warning: Called in ISR
*/
void USBCDC::_send_isr()
{
    assert_locked();

    uint32_t len = write_finish(_bulk_in);
    _tx_in_progress = false;
    if (_tx_size)
    {
        // more data to send
        _send_isr_start();
    }
    else if (len == CDC_MAX_PACKET_SIZE)
    {
        // Previous packet was a full one and we have no more data to send
        // we need to send a zero length packet to indicate that there may be no
        // more output for a while (See USBCDC spec for details)
        if (USBDevice::write_start(_bulk_in, _tx_buffer, 0))
            _tx_in_progress = true;
    }
}

void USBCDC::receive_nb(uint8_t *buffer, uint32_t size,  uint32_t *size_read)
{

    *size_read = 0;
    if (_terminal_connected && !_rx_in_progress) {
        // Copy data over
        uint32_t copy_size = _rx_size > size ? size : _rx_size;
        memcpy(buffer, _rx_buf, copy_size);
        *size_read = copy_size;
        _rx_buf += copy_size;
        _rx_size -= copy_size;
        if (_rx_size == 0) {
            _receive_isr_start();
        }
    }
}

void USBCDC::_receive_isr_start()
{
    if ((_rx_size == 0) && !_rx_in_progress) {
        // Refill the buffer
        _rx_in_progress = true;
        read_start(_bulk_out, _rx_buffer, sizeof(_rx_buffer));
    }
}

/*
* Called by when CDC data is received
* Warning: Called in ISR
*/
void USBCDC::_receive_isr()
{
    assert_locked();

    MBED_ASSERT(_rx_size == 0);
    _rx_buf = _rx_buffer;
    _rx_size = read_finish(_bulk_out);
    _rx_in_progress = false;
}

const uint8_t *USBCDC::device_desc()
{
    uint8_t ep0_size = endpoint_max_packet_size(0x00);
    uint8_t device_descriptor_temp[] = {
        18,                   // bLength
        1,                    // bDescriptorType
        0x10, 0x01,           // bcdUSB
        2,                    // bDeviceClass
        0,                    // bDeviceSubClass
        0,                    // bDeviceProtocol
        ep0_size,             // bMaxPacketSize0
        (uint8_t)(LSB(vendor_id)), (uint8_t)(MSB(vendor_id)),  // idVendor
        (uint8_t)(LSB(product_id)), (uint8_t)(MSB(product_id)),// idProduct
        0x00, 0x01,           // bcdDevice
        1,                    // iManufacturer
        2,                    // iProduct
        3,                    // iSerialNumber
        1                     // bNumConfigurations
    };
    MBED_ASSERT(sizeof(device_descriptor_temp) == sizeof(device_descriptor));
    memcpy(device_descriptor, device_descriptor_temp, sizeof(device_descriptor));
    return device_descriptor;
}

const uint8_t *USBCDC::string_iinterface_desc()
{
    static const uint8_t stringIinterfaceDescriptor[] = {
        0x08,
        STRING_DESCRIPTOR,
        'C', 0, 'D', 0, 'C', 0,
    };
    return stringIinterfaceDescriptor;
}

const uint8_t *USBCDC::string_iproduct_desc()
{
//    static const uint8_t stringIproductDescriptor[] = {
//        0x16,    //Length
//        STRING_DESCRIPTOR, //DescriptorType
//        'C', 0, 'D', 0, 'C', 0, ' ', 0, 'D', 0, 'E', 0, 'V', 0, 'I', 0, 'C', 0, 'E', 0 //String
//    };
    static const uint8_t stringIproductDescriptor[] = {
        0x1c,    //Length
        STRING_DESCRIPTOR, //DescriptorType
        'S', 0, 'm', 0, 'o', 0, 'o', 0, 't', 0, 'h', 0, 'i', 0, 'e', 0, 'b', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0 //String
    };

    
    
    return stringIproductDescriptor;
}


#define CONFIG1_DESC_SIZE (9+8+9+5+5+4+5+7+9+7+7)

const uint8_t *USBCDC::configuration_desc(uint8_t index)
{
#ifdef USE_STATIC_ENDPOINTS
    static constexpr uint8_t config_descriptor_temp[] = {
#else
    uint8_t config_descriptor_temp[] = {
#endif
        // configuration descriptor
        9,                      // bLength
        2,                      // bDescriptorType
        LSB(CONFIG1_DESC_SIZE), // wTotalLength
        MSB(CONFIG1_DESC_SIZE),
        2,                      // bNumInterfaces
        1,                      // bConfigurationValue
        0,                      // iConfiguration
        0x80,                   // bmAttributes
        250,                    // bMaxPower //SD:: set to 500mA (value = 500/2)

        // IAD to associate the two CDC interfaces
        0x08,                   // bLength
        0x0b,                   // bDescriptorType
        0x00,                   // bFirstInterface
        0x02,                   // bInterfaceCount
        0x02,                   // bFunctionClass
        0x02,                   // bFunctionSubClass
        0,                      // bFunctionProtocol
        0,                      // iFunction

        // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
        9,                      // bLength
        4,                      // bDescriptorType
        0,                      // bInterfaceNumber
        0,                      // bAlternateSetting
        1,                      // bNumEndpoints
        0x02,                   // bInterfaceClass
        0x02,                   // bInterfaceSubClass
        0x01,                   // bInterfaceProtocol
        0,                      // iInterface

        // CDC Header Functional Descriptor, CDC Spec 5.2.3.1, Table 26
        5,                      // bFunctionLength
        0x24,                   // bDescriptorType
        0x00,                   // bDescriptorSubtype
        0x10, 0x01,             // bcdCDC

        // Call Management Functional Descriptor, CDC Spec 5.2.3.2, Table 27
        5,                      // bFunctionLength
        0x24,                   // bDescriptorType
        0x01,                   // bDescriptorSubtype
        0x03,                   // bmCapabilities
        1,                      // bDataInterface

        // Abstract Control Management Functional Descriptor, CDC Spec 5.2.3.3, Table 28
        4,                      // bFunctionLength
        0x24,                   // bDescriptorType
        0x02,                   // bDescriptorSubtype
        0x06,                   // bmCapabilities

        // Union Functional Descriptor, CDC Spec 5.2.3.8, Table 33
        5,                      // bFunctionLength
        0x24,                   // bDescriptorType
        0x06,                   // bDescriptorSubtype
        0,                      // bMasterInterface
        1,                      // bSlaveInterface0

        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        ENDPOINT_DESCRIPTOR_LENGTH,     // bLength
        ENDPOINT_DESCRIPTOR,            // bDescriptorType
        INT_IN,                         // bEndpointAddress
        E_INTERRUPT,                    // bmAttributes (0x03=intr)
        LSB(CDC_MAX_PACKET_SIZE),       // wMaxPacketSize (LSB)
        MSB(CDC_MAX_PACKET_SIZE),       // wMaxPacketSize (MSB)
        16,                             // bInterval

        // interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
        9,                          // bLength
        4,                          // bDescriptorType
        1,                          // bInterfaceNumber
        0,                          // bAlternateSetting
        2,                          // bNumEndpoints
        0x0A,                       // bInterfaceClass
        0x00,                       // bInterfaceSubClass
        0x00,                       // bInterfaceProtocol
        0,                          // iInterface

        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        ENDPOINT_DESCRIPTOR_LENGTH, // bLength
        ENDPOINT_DESCRIPTOR,        // bDescriptorType
        BULK_IN,                    // bEndpointAddress
        E_BULK,                     // bmAttributes (0x02=bulk)
        LSB(CDC_MAX_PACKET_SIZE),   // wMaxPacketSize (LSB)
        MSB(CDC_MAX_PACKET_SIZE),   // wMaxPacketSize (MSB)
        0,                          // bInterval

        // endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
        ENDPOINT_DESCRIPTOR_LENGTH, // bLength
        ENDPOINT_DESCRIPTOR,        // bDescriptorType
        BULK_OUT,                   // bEndpointAddress
        E_BULK,                     // bmAttributes (0x02=bulk)
        LSB(CDC_MAX_PACKET_SIZE),   // wMaxPacketSize (LSB)
        MSB(CDC_MAX_PACKET_SIZE),   // wMaxPacketSize (MSB)
        0                           // bInterval
    };

    if (index == 0) {
#ifdef USE_STATIC_ENDPOINTS
        return config_descriptor_temp;
#else
        MBED_ASSERT(sizeof(config_descriptor_temp) == sizeof(_config_descriptor));
        memcpy(_config_descriptor, config_descriptor_temp, sizeof(_config_descriptor));
        return _config_descriptor;
#endif
    } else {
        return NULL;
    }
}
