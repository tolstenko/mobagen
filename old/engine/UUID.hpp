#pragma once
#include <string>

namespace mobagen {
  struct UUID {
  private:
	uint64_t time;
	uint64_t count;
  public:
	static UUID Generate();

	std::string toString();

	bool operator==(const UUID &other) { return this->count == other.count && this->time == other.time; }
  };

}