function [ s,flag ] = setupSerial( comPort )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

% Initialize the serial port comunication between Arduino and MATLAB
% The input value is the COMPORT should be changed as per requirement
% We ensure that the arduino is also communicating with MATLAB at this 
% time. A predefined code on the arduino acknowledges this.
% If setup is complete then the value of flag is returned as 1 else 0

s = serial(comPort);
set(s,'DataBits', 8);
set(s, 'StopBits', 2);
set(s, 'BaudRate', 9600);
set(s, 'Parity', 'none');
fopen(s);

c = 'b';
while (c ~= 'c')
    c=fread(s,1,'uchar');
end

if (c == 'c')
    disp('serial read')
end

fprintf(s,'%c','c');
flag = 1;
disp('Serial COmmunication setup.');
fscanf(s,'%u')

end

