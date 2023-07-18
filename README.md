# STO
It's a simple Server and BT client project where ESP32 triggers some PC shortcuts based on the Server's input array via Bluetooth and COM port.
In this example, it switches the desktop to the right one and then switches it back to the previous one.

You are able to change the shortcut to whatever you want, but remember to resize the array at line 151 (INPUT inputs[6] = {};) if the new shortcut has a different number of keys than the current one.
