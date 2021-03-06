/*
 *   Copyright (C) 2016,2017,2018,2020 by Jonathan Naylor G4KLX
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
#include "Defines.h"
#include "SerialPort.h"
#include "Timer.h"
#include "Thread.h"
#include <string>

class CNextion : public CDisplay
{
public:
  CNextion(const std::string& callsign, unsigned int dmrid, ISerialPort* serial, unsigned int brightness, bool displayClock, bool utc, unsigned int idleBrightness, unsigned int screenLayout, unsigned int txFrequency, unsigned int rxFrequency, bool displayTempInF);
  virtual ~CNextion();

  virtual bool open() override;

  virtual void close() override;

protected:
  virtual void setIdleInt() override;
  virtual void setErrorInt(const char* text) override;
  virtual void setQuitInt() override;

  virtual void writeDMRInt(unsigned int slotNo, const std::string& src, bool group, const std::string& dst, const char* type) override;
  virtual void writeDMRRSSIInt(unsigned int slotNo, unsigned char rssi) override;
  virtual void writeDMRTAInt(unsigned int slotNo, unsigned char* talkerAlias, const char* type) override;

  virtual void writeDMRBERInt(unsigned int slotNo, float ber) override;
  virtual void clearDMRInt(unsigned int slotNo) override;

  virtual void writePOCSAGInt(uint32_t ric, const std::string& message) override;
  virtual void clearPOCSAGInt() override;

  virtual void writeCWInt() override;
  virtual void clearCWInt() override;

  virtual void clockInt(unsigned int ms) override;

private:
  std::string   m_callsign;
  std::string   m_ipaddress;
  unsigned int  m_dmrid;
  ISerialPort*  m_serial;
  unsigned int  m_brightness;
  unsigned char m_mode;
  bool          m_displayClock;
  bool          m_utc;
  unsigned int  m_idleBrightness;
  unsigned int  m_screenLayout;
  CTimer        m_clockDisplayTimer;
  unsigned int  m_rssiAccum1;
  unsigned int  m_rssiAccum2;
  float         m_berAccum1;
  float         m_berAccum2;
  unsigned int  m_rssiCount1;
  unsigned int  m_rssiCount2;
  unsigned int  m_berCount1;
  unsigned int  m_berCount2;
  unsigned int  m_txFrequency;
  unsigned int  m_rxFrequency;
  double        m_fl_txFrequency;
  double        m_fl_rxFrequency;
  bool          m_displayTempInF;
  
  void sendCommand(const char* command);
  void sendCommandAction(unsigned int status);
};
