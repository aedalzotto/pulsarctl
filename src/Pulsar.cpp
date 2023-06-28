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
 * @file Pulsar.cpp
 * 
 * @brief This class defines the packet format and USB communication for the 
 * Xanova Pulsar keyboard.
 */

#include <Pulsar.hpp>

#include <vector>
#include <stdexcept>
#include <numeric>

Pulsar::Pulsar() :
	handle(nullptr)
{
	if(hid_init() < 0)
		throw std::runtime_error("Failed to initialize HIDAPI."); // std::string(hid_error(nullptr))

	hid_device_info *devinfo = hid_enumerate(0x1024, 0x2020);
	if(devinfo == nullptr){
		hid_exit();
		throw std::runtime_error("Xanova Pulsar XK400 is not present."); // std::string(hid_error(nullptr))
	}

	while(devinfo != nullptr){
		if(devinfo->interface_number == 2){
			handle = hid_open_path(devinfo->path);
			break;
		}
		devinfo = devinfo->next;
	};

	if(handle == nullptr){
		hid_exit();
		throw std::runtime_error("Failed to open device."); // std::string(hid_error(nullptr))
	}
}

Pulsar::~Pulsar()
{
	hid_close(handle);
	handle = nullptr;
	hid_exit();
}

void Pulsar::set_backlight(BacklightMode mode, uint8_t speed)
{
	std::vector<uint8_t> buffer(65, 0x00);

	buffer[4] = static_cast<uint8_t>(Mode::BACKLIGHT);
	buffer[5] = 0x01;
	std::copy(reinterpret_cast<uint8_t*>(&mode), reinterpret_cast<uint8_t*>(&mode) + sizeof(BacklightMode), buffer.begin() + 6);
	buffer[9] = 15 + speed*(-14)/255;

	buffer[63] = std::accumulate(buffer.begin() + 4, buffer.begin() + 10, 0x00, std::bit_xor<uint8_t>());	// Checksum

	if(hid_send_feature_report(handle, buffer.data(), buffer.size()) < 0)
		throw std::runtime_error("Failed to write to device."); // std::string(hid_error(handle))
}

void Pulsar::set_keylight(KeylightMode mode, uint8_t speed)
{
	std::vector<uint8_t> buffer(65, 0x00);

	buffer[4] = static_cast<uint8_t>(Mode::KEYLIGHT);
	buffer[5] = 0x01;
	buffer[6] = 0x04;
	buffer[7] = static_cast<uint8_t>(mode);
	buffer[8] = ((5 + speed/(-51)) << 4) | 0x0A;

	buffer[63] = std::accumulate(buffer.begin() + 4, buffer.begin() + 9, 0x00, std::bit_xor<uint8_t>());	// Checksum

	if(hid_send_feature_report(handle, buffer.data(), buffer.size()) < 0)
		throw std::runtime_error("Failed to write to device."); // std::string(hid_error(handle))
}

void Pulsar::set_brightness(uint8_t brightness)
{
	std::vector<uint8_t> buffer(65, 0x00);

	buffer[4] = static_cast<uint8_t>(Mode::BACKLIGHT);
	buffer[5] = 0x01;
	buffer[6] = 0x02;
	buffer[9] = brightness;

	buffer[63] = std::accumulate(buffer.begin() + 4, buffer.begin() + 10, 0x00, std::bit_xor<uint8_t>());	// Checksum

	if(hid_send_feature_report(handle, buffer.data(), buffer.size()) < 0)
		throw std::runtime_error("Failed to write to device."); // std::string(hid_error(handle))
}
