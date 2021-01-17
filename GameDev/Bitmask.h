#pragma once
#include <stdint.h>
class Bitmask
{
public:
	Bitmask();

	// Overwrite the current mask
	void SetMask(Bitmask& other);

	// Returns the binary representation of the mask
	uint32_t GetMask() const;

	// Returns true if bit at pos == 1
	bool GetBit(int pos) const;

	// Set bit at location to 0 or 1
	void SetBit(int pos, bool on);

	// Sets bit at pos to 1
	void SetBit(int pos);

	// Sets bit at pos to 0
	void ClearBit(int pos);

	// Sets all bits to 0
	void Clear();

private:
	uint32_t bits;
};

