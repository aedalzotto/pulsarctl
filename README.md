# pulsarctl
Control Xanova Pulsar XK400 backlight and keylight effects

## About
This program controls de backlight, keylight and brightness of Xanova Pulsar XK400 keyboard without the need of Xanova Control Panel.
To do this, the program uses hidapi to send feature to hidraw2.
Check the [source code](src/Cmdline.cpp) to understand the packet format.

## Building

You will need meson, ninja, hidapi and [argparse](https://github.com/p-ranav/argparse).

```
meson setup build
meson compile -C build
```

## Installing
After building the project, you can install using meson.
```
meson install -C build
```

## To do

- [ ] CustomerBreathing backlight
- [ ] CustomerStatic backlight 
- [ ] "Equalizer" mode (music mode)
