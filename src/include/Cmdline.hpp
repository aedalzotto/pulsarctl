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
 * @file Cmdline.hpp
 * 
 * @brief This class treats the command line for pulsarctl.
 */

#pragma once

#include <cstdint>
#include <optional>

#include <argparse/argparse.hpp>

#include <Pulsar.hpp>

class Cmdline {
public:

	enum class Subcommand {
		BACKLIGHT,
		KEYLIGHT,
		BRIGHTNESS
	};

	Cmdline(int argc, char *argv[]);

	Subcommand get_subcommand() { return subcommand; };
	Pulsar::BacklightMode get_backlight_mode() { return backlight_mode; };
	Pulsar::KeylightMode get_keylight_mode() { return keylight_mode; };
	std::optional<uint8_t> get_level() { return level; };

private:
	static std::unordered_map<std::string, Pulsar::BacklightMode> const BACKLIGHT_MAP;
	static std::unordered_map<std::string, Pulsar::KeylightMode> const KEYLIGHT_MAP;
	Subcommand subcommand;
	Pulsar::BacklightMode backlight_mode;
	Pulsar::KeylightMode keylight_mode;
	std::optional<uint8_t> level;
};
