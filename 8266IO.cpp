#include <ESP8266WiFi.h>
#include "8266IO.h"

ReadResult::ReadResult(bool time, bool run, bool conn, int size) {
	Timeout = time;
	Overrun = run;
	Connected = conn;
	Size = size;
}
//Reads until timeout or terminator or buffer full.  Returns true if all succeed, false if timeout or overrun. It always terminates with /0
//terminator charaacter IS INCLUDED in the string
ReadResult readBytesUntil(WiFiClient& client, char* dest, char terminator, int len, unsigned long timeout_ms) {
	unsigned long start;
	int pos = 0;
	start = millis();
	while ((millis() - start) < timeout_ms) {
		if (client.available()) {
			char c = client.read();
			dest[pos++] = c;
			if (c == terminator) {
				dest[pos] = 0;
				return ReadResult(false, false, true, pos);
			}
			if (pos >= len) {
				dest[len - 1] = 0;
				return ReadResult(false, true, true, len);
			}
		}
		delay(1);
	}
	dest[len - 1] = 0;
	return ReadResult(true, false, true, pos);
}