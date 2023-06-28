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
 * @file Cmdline.cpp
 * 
 * @brief This class treats the command line for pulsarctl.
 */

#include <Cmdline.hpp>

std::unordered_map<std::string, Pulsar::BacklightMode> const Cmdline::BACKLIGHT_MAP {
	{"off", Pulsar::BacklightMode::OFF},
	{"breathing", Pulsar::BacklightMode::BREATHING},
	{"static", Pulsar::BacklightMode::STATIC},
	{"alternatewave", Pulsar::BacklightMode::ALTERNATEWAVE},
	{"scanwave", Pulsar::BacklightMode::SCANWAVE},
	{"wave-right", Pulsar::BacklightMode::WAVE_RIGHT},
	{"wave-down", Pulsar::BacklightMode::WAVE_DOWN},
	{"rippling-left", Pulsar::BacklightMode::RIPPLING_LEFT},
	{"rippling-right", Pulsar::BacklightMode::RIPPLING_RIGHT},
	{"fireworks", Pulsar::BacklightMode::FIREWORKS},
	{"star", Pulsar::BacklightMode::STAR},
	{"boom", Pulsar::BacklightMode::BOOM}
};

std::unordered_map<std::string, Pulsar::KeylightMode> const Cmdline::KEYLIGHT_MAP {
	{"off", Pulsar::KeylightMode::OFF},
	{"fade", Pulsar::KeylightMode::FADE},
	{"hexagon", Pulsar::KeylightMode::HEXAGON},
	{"ripple", Pulsar::KeylightMode::RIPPLE},
	{"runoutsig", Pulsar::KeylightMode::RUNOUTSIG},
	{"runinsig", Pulsar::KeylightMode::RUNINSIG},
	{"runin", Pulsar::KeylightMode::RUNIN}
};

Cmdline::Cmdline(int argc, char *argv[])
{
	argparse::ArgumentParser parser("pulsarctl", "1.0.0", argparse::default_arguments::help);
	
	argparse::ArgumentParser backlight_parser("backlight");
	backlight_parser.add_description("Change backlight effect");
  	backlight_parser.add_argument("mode")
		.help(
			"Backlight effect mode: off, breathing, static, alternatewave, scanwave, wave-right, wave-down, rippling-left, rippling-right, fireworks, star, or boom"
		)
	;
	backlight_parser.add_argument("-s", "--speed")
    	.help("Set the effect speed (some effects ignore this setting): 0-255")
		.nargs(1)
		.scan<'u', uint8_t>()
	;

	argparse::ArgumentParser keylight_parser("keylight");
	keylight_parser.add_description("Change keylight effect");
	keylight_parser.add_argument("mode")
		.help(
			"Keylight effect mode: off, fade, hexagon, ripple, runoutsig, runinsig, or runin"
		)
	;
	keylight_parser.add_argument("-s", "--speed")
    	.help("Set the effect speed (some effects ignore this setting): 0-255")
		.nargs(1)
		.scan<'u', uint8_t>()
	;

	argparse::ArgumentParser brightness_parser("brightness");
	brightness_parser.add_description("Change backlight brightness");
	brightness_parser.add_argument("level")
		.help("Brightness level: 0-255")
		.scan<'u', uint8_t>()
	;

	parser.add_subparser(backlight_parser);
	parser.add_subparser(keylight_parser);
	parser.add_subparser(brightness_parser);

	parser.parse_args(argc, argv);

	try {
		if(parser.is_subcommand_used("backlight")){
			subcommand = Subcommand::BACKLIGHT;
			backlight_mode = BACKLIGHT_MAP.at(backlight_parser.get<std::string>("mode"));
			level.emplace(backlight_parser.get<std::uint8_t>("--speed"));
		} else if(parser.is_subcommand_used("keylight")){
			subcommand = Subcommand::KEYLIGHT;
			keylight_mode = KEYLIGHT_MAP.at(keylight_parser.get<std::string>("mode"));
			level.emplace(keylight_parser.get<std::uint8_t>("--speed"));
		} else if(parser.is_subcommand_used("brightness")){
			subcommand = Subcommand::BRIGHTNESS;
			level.emplace(brightness_parser.get<std::uint8_t>("level"));
		} else {
			throw std::invalid_argument("No subcommand specified");
		}
	} catch(std::out_of_range const& e){
		throw std::invalid_argument("Invalid operation mode");
	} catch(std::logic_error const& e){
		level.reset();
	}

}
