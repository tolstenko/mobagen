#include "UUID.hpp"

#include <atomic>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace mobagen {
  UUID UUID::Generate() {
	  UUID id;

	  static std::atomic<std::uint64_t> cnt{0};
	  ++cnt;

	  id.count = cnt;

	  auto now = std::chrono::high_resolution_clock::now();
	  id.time = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

	  return id;
  }

  std::string UUID::toString() {
	  std::stringstream ss;
	  ss << std::setw(16) << std::setfill('0') << std::hex << this->time;
	  ss << std::setw(16) << std::setfill('0') << std::hex << this->count;

	  return ss.str();
  }
}