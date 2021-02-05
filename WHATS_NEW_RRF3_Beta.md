RepRapFirmware 3.3beta1 (in preparation)
=======================

Upgrade notes:
- All extruders must be declared explicitly using M584. In previous firmware versions, one default extruder was assign to driver 3.
- [Duet 3 + expansion/tool boards] You must update the expansion and/or tool board firmware to 3.3beta1 also, otherwise movement will not work

New features:
- M17 is implemented
- [Duet WiFi/Ethernet] When using extended step timings (M569 T parameter), maximum step pulse rates should be improved a little
- [Duet 3 Mini] M954 is partially implemented. A Duet 3 Mini used as an expansion board can support axis motors, extruder motors (but extruders with nonzero pressure advance has not been tested), thermistor, PT100 and thermocouple temperature sensors, GpIn and GpOut pins (including servos). Heaters, fans, filament monitors, endstop switches, Z probes and other types of temperature sensor are not yet supported.
- [Duet 3 MB6HC] The maximum number of axes supported on Duet 3 MB6HC is increased to 15. Axis letters abcdefghijkl may be used in addition to XYZUVWABCD. Because GCode is normally case insensitive, these must be prefixed with a single quote character in GCode commands. For example, M584 'A1.2 would assign axis 'a' to driver 1.2, and G1 'A10 would move the 'a' axis to the 10mm or 10 degree position (or by 10mm or 10 degrees if in relative mode).
- [Duet 3 main boards] M122 now reports the peak CAN time sync message transmit delay
- [Duet 3 + expansion/tool boards] Improved the accuracy of CAN clock synchronisation between main and expansion boards
- [Duet 3 expansion/tool boards] Increased maximum step rates on on tool and expansion boards, expecially on EXP1XD boards
- [Duet 3 EXP1XD] All step pulses generated by the EXP1XD now have exactly the same step high time as set by M569. The first M569 T value (step high time) will be rounded up to the next multiple of 0.0833us subject to a minimum of 0.25us (previously it was rounded up to the next multiple of 1.33us). The remaining T values will be rounded up to the next multiple of 1.33us as before. The fourth T value (direction hold time from trailing edge of step pulse) can now be negative, down to minus the step-high time.
- [Duet 3 expansion/tool boards] M122 now reports CAN clock sync jitter, peak receive delay, steps commanded and steps generated.
- [SAMMYC21] The sample firmware for SAMMYC21 now sends a diagnostic report to the USB port if character D is received from the USB port

Bug fixes:
- It was not possible to delete a temperature sensor using M308 S# P"nil"
- When a sensor was configured on a CAN expansion board and M308 was subsequently used to create a sensor with the same number on a different board, the old sensor was not deleted
- It was not possible to compare an object model value of character type (e.g. move.axes[N]) with a string
- [Duet 3] At high step rates, in RRF 3.2 the step pulses sent to stepper drivers did not always meet the minimum pulse width specified for the TMC5160. This might have resulted in lost steps; however we have not observed this and have no reports of it happening.
- [Duet + SBC] It was not possible to use an expression as a parameter where the parameter accepts multiple values. It is now possible to use an expression if only one value needs to be passed.
- [Duet 3 expansion/tool boards] Under certain conditions, moves could be omitted. We have only been able to reproduce this when using high step pulse rates.
- [Duet 3 expansion/tool boards] Under conditions of heavy load (e.g. a series of short moves at high step pulse rates), the board could stop responding to CAN commands and lose CAN sync
- [Duet 3 with expansion/tool boards] When DAA ie enabled, expansion and tool boards would sometimes get out of sync and skip moves
- [Duet 3 expansion/tool boards] If a filament monitor was connected to a tool or expansion board, any F parameter in the M591 command used to configure it was ignored
- [Duet 3 expansion/tool boards] A small number of EXP3HC boards took a long time to start up when power was applied