<html><body><h1>Pametna hisica!</h1>
<p>To je prototip pametne hisice!</p>



<?php
include 'PhpSerial.php';

// Let's start the class
$serial = new PhpSerial;

// First we must specify the device. This works on both linux and windows (if
// your linux serial device is /dev/ttyS0 for COM1, etc)
$serial->deviceSet("/dev/ttyACM0");

// Then we need to open it
$serial->deviceOpen();


// We can change the baud rate, parity, length, stop bits, flow control
$serial->confBaudRate(115200);
$serial->confParity("none");
$serial->confCharacterLength(8);
$serial->confStopBits(1);
$serial->confFlowControl("none");
// To write into
$serial->sendMessage("c");

// Or to read from
//$read = $serial->readPort();

// If you want to change the configuration, the device must be closed
$serial->deviceClose();

// We can change the baud rate
//$serial->confBaudRate(2400);
?>




</body></html>
