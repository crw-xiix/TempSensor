#pragma once

//Same as the stock one but is better about errors, see code file

struct ReadResult {
	bool Timeout = false;
	bool Overrun = false;
	bool Connected = false;
	int  Size = 0;
	ReadResult(bool time, bool run, bool conn, int size);
};
ReadResult readBytesUntil(WiFiClient& client, char* dest, char terminator, int len, unsigned long timeout_ms);
