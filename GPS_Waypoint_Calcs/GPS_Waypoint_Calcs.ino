#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const double waypoint[] = {39.957, -75.1885};
TinyGPSPlus gps;
int target = 0;

SoftwareSerial ss(4, 3);

void setup()
{
  Serial.begin(115200);
  ss.begin(4800);
}

void loop()
{
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

unsigned long distance()
{
  unsigned long distMeters = (unsigned long)TinyGPSPlus::distanceBetween(gps.location.lat(),gps.location.lng(),waypoint[target], waypoint[target+1]);
  return distMeters;
}

double bearing()
{
  double bearing = TinyGPSPlus::courseTo(gps.location.lat(),gps.location.lng(),waypoint[target], waypoint[target+1]);
  return bearing;
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
