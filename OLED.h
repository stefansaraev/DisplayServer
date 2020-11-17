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

#if defined(OLED)

#define OLED_STATUSBAR 0
#define OLED_LINE1 8 //16
#define OLED_LINE2 18 //26 
#define OLED_LINE3 28 //36
#define OLED_LINE4 37 //46
#define OLED_LINE5 47 //56
#define OLED_LINE6 57

#include "Display.h"
#include "Defines.h"
#include "UserDBentry.h"

#include <string>

#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include "NetworkInfo.h"

class COLED : public CDisplay 
{
public:
  COLED(unsigned char displayType, unsigned char displayBrighness, bool displayInvert, bool displayScroll, bool displayRotate, bool displayLogoScreensaver, bool slot1Enabled, bool slot2Enabled);
  virtual ~COLED();

  virtual bool open() override;

  virtual void setIdleInt() override;

  virtual void setErrorInt(const char* text) override;
  virtual void setQuitInt() override;

  virtual void writeDMRInt(unsigned int slotNo, const std::string& src, bool group, const std::string& dst, const char* type) override;
  virtual int writeDMRIntEx(unsigned int slotNo, const class CUserDBentry& src, bool group, const std::string& dst, const char* type);
  virtual void clearDMRInt(unsigned int slotNo) override;

  virtual void writePOCSAGInt(uint32_t ric, const std::string& message) override;
  virtual void clearPOCSAGInt() override;

  virtual void writeCWInt() override;
  virtual void clearCWInt() override;

  virtual void close() override;

private:
  const char*   m_slot1_state;
  const char*   m_slot2_state;
  unsigned char m_mode;
  unsigned char m_displayType;
  unsigned char m_displayBrightness;
  bool          m_displayInvert;
  bool          m_displayScroll;
  bool          m_displayRotate;
  bool          m_displayLogoScreensaver;
  bool          m_slot1Enabled;
  bool          m_slot2Enabled;
  std::string   m_ipaddress;
  ArduiPi_OLED  m_display;

  void OLED_statusbar();
};
#endif
