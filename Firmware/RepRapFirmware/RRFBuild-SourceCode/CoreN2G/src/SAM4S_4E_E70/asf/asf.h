/*
 * asf.h
 *
 *  Created on: 13 Mar 2016
 *      Authors: David and Christian
 */

#ifndef ASF_H_
#define ASF_H_

#include "sam/utils/compiler.h"

#include "sam/drivers/pio/pio.h"
#include "sam/drivers/pmc/pmc.h"
#include "sam/drivers/pwm/pwm.h"
#include "sam/drivers/spi/spi.h"
#include "sam/drivers/wdt/wdt.h"

#if SAM4E || SAME70
#include "sam/drivers/rswdt/rswdt.h"
#endif

#endif /* ASF_H_ */
