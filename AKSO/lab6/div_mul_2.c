#include <stdint.h>

int64_t sddiv(int64_t x) {
  return x / 2;
}

int64_t ssdiv(int64_t x) {
  return x >> 1;
}

uint64_t uddiv(uint64_t x) {
  return x / 2;
}

uint64_t usdiv(uint64_t x) {
  return x >> 1;
}

int64_t smmul(int64_t x) {
  return x * 2;
}

int64_t ssmul(int64_t x) {
  return x << 1;
}

uint64_t ummul(uint64_t x) {
  return x * 2;
}

uint64_t usmul(uint64_t x) {
  return x << 1;
}
