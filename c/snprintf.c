#include <stdio.h>

int main() {
	 static char buf[64];
	 snprintf (buf, sizeof buf, "Signal %d", signo);
	 return buf;
}
