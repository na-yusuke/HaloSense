# Tips

## When Installing LED Tape

- When installing LED tape around corners, bending the tape directly can damage the LEDs or make installation difficult.
- In such cases, cut the LED tape and reconnect the cut surfaces with jumper wires to make it easier to bend around corners.

<img src=/resources/image/processed_leds1.jpg width= "400px" >

- At this time, carefully check the cut surfaces of the LED tape and connect them so that the order of GND, 5V, and Data matches.

<img src=/resources/image/processed_leds2.jpg width= "400px" >

- Once the processing is complete, cover thoroughly with insulating tape to prevent short circuits.

## Development with WSL2 and PlatformIO

- By following [Connect USB devices](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) and installing [usbipd-win](https://github.com/dorssel/usbipd-win?tab=readme-ov-file) on WSL2, you can use PlatformIO in VSCode on WSL2 to write to the Raspberry Pi Pico.
- However, in my environment, each time I write once, there is a connection failure, and I need to run the following commands again to reconnect the USB device.
  - If you encounter the same symptoms, I recommend developing in a Windows environment.

```bash
# Disconnect USB device
$ usbipd unbind --busid <busid>

# Reconnect USB device to WSL2
$ usbipd wsl attach --busid <busid>
```

### References

- [Getting Started with VSCode & PlatformIO! A Complete Guide to Building an Embedded Software Development Environment on WSL](https://developer.mamezou-tech.com/en/blogs/2025/04/10/develop-on-vscode-platformio-and-wsl/)
