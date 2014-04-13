function [time, lat, latD, lng, lngD] = readGPS(s)

fprintf(s,'T');         %send time request
time = fscanf(s,'%f');  %read time
fprintf(s,'A');         %send lat request
lat = fscanf(s,'%f');   %read lat
fprintf(s,'a');         %send lat direction request
latD = fscanf(s,'%s');  %read lat direction
fprintf(s,'O');         %send longitude request
lng = fscanf(s,'%f');   %read longitude
fprintf(s,'o');         %send longitude direction request
lngD = fscanf(s,'%s');  %read longitude direction

end

