/*
 * ThermocoupleSensor31855.h
 *
 *  Created on: 8 Jun 2021
 *      Author: GA
 */

#ifndef SRC_HEATING_THERMOCOUPLESENSOR6675_H_
#define SRC_HEATING_THERMOCOUPLESENSOR6675_H_

#include "SpiTemperatureSensor.h"

class ThermocoupleSensor6675 : public SpiTemperatureSensor
{
public:
	ThermocoupleSensor6675(unsigned int sensorNum) noexcept;
	GCodeResult Configure(GCodeBuffer& gb, const StringRef& reply, bool& changed) override THROWS(GCodeException);
	void Poll() noexcept override;
	const char *GetShortSensorType() const noexcept override { return TypeName; }

	static constexpr const char *TypeName = "thermocouplemax6675";
};

#endif /* SRC_HEATING_THERMOCOUPLESENSOR6675_H_ */
