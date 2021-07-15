/**
 * \file
 *
 * \brief Top header file for SAMC21
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMC21_
#define _SAMC21_

/**
 * \defgroup SAMC21_definitions SAMC21 Device Definitions
 * \brief SAMC21 CMSIS Definitions.
 */

#if   defined(__SAMC21N17A__) || defined(__ATSAMC21N17A__)
  #include "samc21n17a.h"
#elif defined(__SAMC21N18A__) || defined(__ATSAMC21N18A__)
  #include "samc21n18a.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAMC21_ */
