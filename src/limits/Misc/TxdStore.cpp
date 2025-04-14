#include "LimitAdjuster.h"

using namespace injector;

class TxdStoreVC : public SimpleAdjuster {
public:
	const char* GetLimitName() { return GetGVM().IsVC() ? "TxdStore" : nullptr; }
	void ChangeLimit(int, const std::string& value)
	{
		int n = std::stoi(value);
		WriteMemory(0x58102D + 0, n, true);
		WriteMemory(0x41065D + 2, n, true);
		WriteMemory(0x580FD4 + 2, n, true);
		WriteMemory(0x61DAA5 + 1, n, true);
		WriteMemory(0x61DCFA + 2, n, true);
		WriteMemory(0x61DD39 + 1, n, true);
		WriteMemory(0x61D98B + 1, n, true);

	}
} TxdStoreVC;
