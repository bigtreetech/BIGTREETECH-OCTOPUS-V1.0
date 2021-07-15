/*
 * IPAddress.h
 *
 *  Created on: 16 Oct 2018
 *      Author: David
 */

#ifndef SRC_GENERAL_IPADDRESS_H_
#define SRC_GENERAL_IPADDRESS_H_

#include <cstdint>

// Class to represent an IP address. Currently it only supports IPV4 addresses, but eventually it will be expanded to support IPV6 too.
class IPAddress
{
public:
	constexpr IPAddress() noexcept : v4Address(0) {  }
	explicit IPAddress(const uint8_t ip[4]) noexcept { SetV4(ip); }
	explicit constexpr IPAddress(uint32_t v) : v4Address(v) { }

	constexpr bool operator==(const IPAddress& other) const noexcept { return v4Address == other.v4Address; }
	constexpr bool operator!=(const IPAddress& other) const noexcept { return v4Address != other.v4Address; }

	IPAddress& operator=(const IPAddress& other) noexcept { v4Address = other.v4Address; return *this; }

	constexpr bool IsV4() const noexcept { return true; }
	constexpr bool IsV6() const noexcept { return false; }
	constexpr uint32_t GetV4LittleEndian() const noexcept { return v4Address; }
	constexpr uint8_t GetQuad(unsigned int n) const noexcept { return (v4Address >> (8 * n)) & 0x00FF; }
	constexpr bool IsNull() const noexcept { return v4Address == 0; }
	constexpr bool IsBroadcast() const noexcept { return v4Address == 0xFFFFFFFF; }

	void SetV4LittleEndian(uint32_t ip) noexcept { v4Address = ip; }
	void SetV4(const uint8_t ip[4]) noexcept;
	void SetNull() noexcept { v4Address = 0; }
	void SetBroadcast() noexcept { v4Address = 0xFFFFFFFF; }

#if 0		// these functions are not currently used
	uint32_t GetV4BigEndian() const noexcept { return __builtin_bswap32(v4Address); }
	void SetV4BigEndian(uint32_t ip) noexcept { v4Address = __builtin_bswap32(ip); }
#endif

	void UnpackV4(uint8_t rslt[4]) const noexcept;

private:
	uint32_t v4Address;
};

#endif /* SRC_GENERAL_IPADDRESS_H_ */
