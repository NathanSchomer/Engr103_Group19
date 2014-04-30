comPort = '/dev/tty.usbmodem1411';

if (~exist('serialFlag','var'))
    [arduino.s,serialFlag] = setupSerial(comPort)
end

while (true)
    [time, lat, latD, lng, lngD] = readGPS(arduino.s);
    
    fprintf('Time: %f\n', time);
    fprintf('Lat: %f%s\n', lat, latD);
    fprintf('Long: %f%s\n', lng, lngD);
    pause(0.5);
end