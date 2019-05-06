=== LCD and PS/2 Keyboard serial terminal ===

This is a simple serial terminal that can use any character LCD supported by 
the standard Arduino `LiquidCrystal` library. Adjust the `NUM_COL` and 
`NUM_ROW` to match your particular display.

**Remember that PS/2 keyboards are not hot-swapable!** You must plug your
keyboard into the circuit before applying power.

This uses the `NeoSWSerial` software serial drop-in replacement because
its speed and efficiency was required to prevent dropped characters.

The originating use-case was for a small Z80 single-board computer.
For more details on my modifications to the original software for the
board, see this repo:

https://github.com/eparadis/z80-mbc2-ios-lite

=== TODO ===

- properly working backspace
- store a scroll-back buffer that can be viewed with PgUp and PgDn
- change cursor behavior to stay on bottom row with text scrolling up
- recordable macros for play-back with the Fn keys
- allow a wide set of virtual columns that can be shifted left and
  right using the Home and End keys
- typing control characters
- setup menu for baud rate, caps lock, local echo, or other settings

