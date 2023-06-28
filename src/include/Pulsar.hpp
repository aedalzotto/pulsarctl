/** 
 * pulsarctl - Control Galax Xanova Pulsar backlight
 * Copyright (C) 2023 aedalzotto
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * @file Pulsar.hpp
 * 
 * @brief This class defines the packet format and USB communication for the 
 * Xanova Pulsar keyboard.
 */

#pragma once

#include <cstdint>
#include <hidapi.h>

class Pulsar {
public:
	/**
	 * @brief Keylight mode enumerator.
	 * 
	 * @details This corresponds to the 7th byte
	*/
	enum class KeylightMode : uint8_t {
		OFF,
		FADE,
		HEXAGON,
		RIPPLE,
		RUNOUTSIG,
		RUNINSIG = 0x06,
		RUNIN
	};

	/**
	 * @brief Backlight mode enumerator.
	 * 
	 * @details This corresponds to the 7th and 8th bytes. There seems to be no 
	 * correlation between a field and the direction (left, right, or down).
	*/
	enum class BacklightMode : uint16_t {
		OFF				= 0x0000,
		BREATHING		= 0x0200,
		STATIC			= 0x0100,
		ALTERNATEWAVE	= 0x0402,
		SCANWAVE		= 0x0403,
		WAVE_RIGHT		= 0x0404,
		WAVE_DOWN		= 0x0407,
		RIPPLING_LEFT	= 0x0701,
		RIPPLING_RIGHT	= 0x0700,
		FIREWORKS 		= 0x0600,
		STAR			= 0x0A00,
		BOOM			= 0x0B00
	};

	Pulsar();
	~Pulsar();

	/**
	 * @brief Set the backlight mode.
	 * 
	 * @param mode The backlight mode.
	 * @param speed Effect speed value from 0 to 255. Ignored for certain modes.
	*/
	void set_backlight(BacklightMode mode, uint8_t speed = 0xFF);

	/**
	 * @brief Set the keylight mode.
	 * 
	 * @param mode The keylight mode.
	 * @param speed Effect speed value from 0 to 255. Ignored for certain modes.
	*/
	void set_keylight(KeylightMode mode, uint8_t speed = 0xFF);

	/**
	 * @brief Set the brightness.
	 * 
	 * @param brightness Brightness value from 0 to 255.
	*/
	void set_brightness(uint8_t brightness);

private:
	/**
	 * @brief Mode enumerator.
	 * 
	 * @details This corresponds to the 4th byte.
	*/
	enum class Mode : uint8_t {
		KEYLIGHT	= 0x02,
		BACKLIGHT	= 0x03
	};

	hid_device *handle;

};
