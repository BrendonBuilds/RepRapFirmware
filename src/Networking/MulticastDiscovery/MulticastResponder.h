/*
 * MulricastResponder.h
 *
 *  Created on: 12 Jul 2022
 *      Author: David
 */

#ifndef SRC_NETWORKING_MULTICASTRESPONDER_H_
#define SRC_NETWORKING_MULTICASTRESPONDER_H_

#include <RepRapFirmware.h>
#include <NetworkDefs.h>

#if SUPPORT_MULTICAST_DISCOVERY

namespace MulticastResponder
{
	void Init() noexcept;
	void Spin() noexcept;
	void Start(TcpPort port) noexcept;
	void Stop() noexcept;
	void SendResponse(uint8_t *data, size_t length) noexcept;
	void Diagnostics(MessageType mtype) noexcept;
}

#endif

#endif /* SRC_NETWORKING_MULTICASTRESPONDER_H_ */
