#include "Network.h"
#include "OutputMemory.h"
#include <Platform.h>
#include <RepRap.h>
const char * const notSupportedText = "Networking is not supported on this hardware";

#if SUPPORT_OBJECT_MODEL
// Object model table and functions
// Note: if using GCC version 7.3.1 20180622 and lambda functions are used in this table, you must compile this file with option -std=gnu++17.
// Otherwise the table will be allocated in RAM instead of flash, which wastes too much RAM.

constexpr ObjectModelArrayDescriptor Network::interfacesArrayDescriptor =
{
    nullptr,
    [] (const ObjectModel *self, const ObjectExplorationContext& context) noexcept -> size_t { return NumNetworkInterfaces; },
    [] (const ObjectModel *self, ObjectExplorationContext& context) noexcept -> ExpressionValue { return ExpressionValue(nullptr); }
//    [] (const ObjectModel *self, ObjectExplorationContext& context) noexcept -> ExpressionValue { return ExpressionValue(((Network*)self)->interfaces[context.GetIndex(0)]); }
};

// Macro to build a standard lambda function that includes the necessary type conversions
#define OBJECT_MODEL_FUNC(_ret) OBJECT_MODEL_FUNC_BODY(Network, _ret)

constexpr ObjectModelTableEntry Network::objectModelTable[] =
{
    // These entries must be in alphabetical order
    { "interfaces", OBJECT_MODEL_FUNC_NOSELF(&interfacesArrayDescriptor),    ObjectModelEntryFlags::none },
    { "name",        OBJECT_MODEL_FUNC_NOSELF(reprap.GetName()),             ObjectModelEntryFlags::none },
};

constexpr uint8_t Network::objectModelTableDescriptor[] = { 1, 2 };

DEFINE_GET_OBJECT_MODEL_TABLE(Network)

#endif


GCodeResult Network::EnableProtocol(unsigned int interface, NetworkProtocol protocol, int port, int secure, const StringRef& reply) noexcept
{
	reply.copy(notSupportedText);
	return GCodeResult::error;
}

GCodeResult Network::DisableProtocol(unsigned int interface, NetworkProtocol protocol, const StringRef& reply) noexcept
{
	reply.copy(notSupportedText);
	return GCodeResult::error;
}

GCodeResult Network::ReportProtocols(unsigned int interface, const StringRef& reply) const noexcept
{
	reply.copy(notSupportedText);
	return GCodeResult::error;
}

GCodeResult Network::EnableInterface(unsigned int interface, int mode, const StringRef& ssid, const StringRef& reply) noexcept
{
	reply.copy(notSupportedText);
	return GCodeResult::error;
}

GCodeResult Network::GetNetworkState(unsigned int interface, const StringRef& reply) noexcept
{
	reply.copy(notSupportedText);
	return GCodeResult::error;
}

void Network::HandleHttpGCodeReply(OutputBuffer *buf) noexcept
{
	OutputBuffer::ReleaseAll(buf);
}

void Network::HandleTelnetGCodeReply(OutputBuffer *buf) noexcept
{
	OutputBuffer::ReleaseAll(buf);
}

// End
