#include "spch.h"

int main()
{
	int a = 1;
	LOG_INFO("info {0}, {1}, {2}, {3}", 1, 0.1111111111f, true, "lol");
	LOG_WARN("warn {0}", 1);
	LOG_ERROR("error {0}", 1);
	LOG_CRITICAL("critical {0}", 1);

	ASSERT(a == 1, "Message");

	return 0;
}