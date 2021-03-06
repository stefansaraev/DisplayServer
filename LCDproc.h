/*
 *   Copyright (C) 2016,2017 by Tony Corbett G0WFV
 *   Copyright (C) 2018,2020 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#pragma once

#include "Display.h"
#include "Timer.h"

#include <sys/types.h>
#include <string>

#define BUFFER_MAX_LEN 128

class CLCDproc : public CDisplay
{
public:
  CLCDproc(std::string address, unsigned int port, unsigned short localPort, const std::string& callsign, unsigned int dmrid, bool displayClock, bool utc, bool duplex, bool dimOnIdle);
  virtual ~CLCDproc();

  virtual bool open() override;

  virtual void close() override;

protected:
  virtual void setIdleInt() override;
  virtual void setErrorInt(const char* text) override;
  virtual void setQuitInt() override;

  virtual void writeDMRInt(unsigned int slotNo, const std::string& src, bool group, const std::string& dst, const char* type) override;
  virtual void writeDMRRSSIInt(unsigned int slotNo, unsigned char rssi) override;
  virtual void clearDMRInt(unsigned int slotNo) override;

  virtual void writePOCSAGInt(uint32_t ric, const std::string& message) override;
  virtual void clearPOCSAGInt() override;
  virtual void writeCWInt() override;
  virtual void clearCWInt() override;

  virtual void clockInt(unsigned int ms) override;

private:
	std::string  m_address;
	unsigned int m_port;
	unsigned short m_localPort;
	std::string  m_callsign;
	unsigned int m_dmrid;
	bool         m_displayClock;
	bool         m_utc;
	bool         m_duplex;
	bool         m_dimOnIdle;
	bool         m_dmr;
	CTimer       m_clockDisplayTimer;
	unsigned int m_rssiCount1; 
	unsigned int m_rssiCount2; 

	int  socketPrintf(int fd, const char *format, ...);
	void defineScreens();

	int            m_socketfd;
	char           m_buffer[BUFFER_MAX_LEN];
	fd_set         m_readfds, m_writefds;
	struct timeval m_timeout;
	int            m_recvsize;
	unsigned int   m_rows;
	unsigned int   m_cols;
	bool           m_screensDefined;
	bool           m_connected;
	char           m_displayBuffer1[BUFFER_MAX_LEN];
	char           m_displayBuffer2[BUFFER_MAX_LEN];
};
