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
 * @file main.cpp
 * 
 * @brief pulsarctl - Control Galax Xanova Pulsar backlight
 */

#include <iostream>
#include <memory>

#include <Pulsar.hpp>
#include <Cmdline.hpp>

int main(int argc, char *argv[])
{
	try {
		auto cmdline = std::make_unique<Cmdline>(argc, argv);
		
		auto pulsar = std::make_unique<Pulsar>();

		std::optional<uint8_t> level = cmdline->get_level();
		switch(cmdline->get_subcommand()){
			case Cmdline::Subcommand::BACKLIGHT:
				pulsar->set_backlight(cmdline->get_backlight_mode(), level.value_or(0));
				break;
			case Cmdline::Subcommand::KEYLIGHT:
				pulsar->set_keylight(cmdline->get_keylight_mode(), level.value_or(0));
				break;
			case Cmdline::Subcommand::BRIGHTNESS:
				pulsar->set_brightness(level.value());
				break;
			case Cmdline::Subcommand::PLAY_PAUSE:
				pulsar->toggle_effect();
				break;
		}
	} catch(std::invalid_argument const& e){
		std::cerr << e.what() << std::endl;
		return -1;
	} catch(std::runtime_error const& e){
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}
