#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "kol.h"

int main() {
  otwarcie_urzedu(3);
  // 0:  | 1:  | 2: 
  interesant *i0 = nowy_interesant(0);
  // 0: i0  | 1:  | 2: 
  interesant *i1 = nowy_interesant(1);
  // 0: i0  | 1: i1  | 2: 
  interesant *i2 = nowy_interesant(0);
  // 0: i0, i2  | 1: i1  | 2: 
  interesant *i3 = nowy_interesant(0);
  // 0: i0, i2, i3  | 1: i1  | 2: 
  assert(i0 == obsluz(0));
  // 0: i2, i3  | 1: i1  | 2: 
  free(i0);
  interesant *i4 = nowy_interesant(2);
  // 0: i2, i3  | 1: i1  | 2: i4
  interesant *i5 = nowy_interesant(0);
  // 0: i2, i3, i5  | 1: i1  | 2: i4
  zmiana_okienka(i4, 0);
  // 0: i2, i3, i5, i4  | 1: i1  | 2:
  naczelnik(0);
  // 0: i4, i5, i3, i2  | 1: i1  | 2:
  std::vector<interesant*> v(fast_track(i5, i2));
  // 0: i4  | 1: i1  | 2:
  assert(v.size() == 3U);
  assert(v[0] == i5);
  assert(v[1] == i3);
  assert(v[2] == i2);
  for (int i = 0; i < 3; ++i)
    free(v[i]);
  assert(!obsluz(2));
  // 0: i4  | 1: i1  | 2:
  naczelnik(0);
  // 0: i4  | 1: i1  | 2:
  interesant *i6 = nowy_interesant(2);
  // 0: i4  | 1: i1  | 2: i6
  interesant *i7 = nowy_interesant(1);
  // 0: i4  | 1: i1, i7  | 2: i6
  assert(i1 == obsluz(1));
  // 0: i4  | 1: i7  | 2: i6
  free(i1);
  zamkniecie_okienka(0, 1);
  // 0:  | 1: i7, i4  | 2: i6
  zamkniecie_okienka(2, 1);
  // 0:  | 1: i7, i4, i6  | 2:
  zamkniecie_okienka(1, 2);
  // 0:  | 1:  | 2: i7, i4, i6
  interesant *i8 = nowy_interesant(0);
  // 0: i8  | 1:  | 2: i7, i4, i6
  v = zamkniecie_urzedu();
  // 0:  | 1:  | 2:
  assert(v.size() == 4U);
  assert(v[0] == i8);
  assert(v[1] == i7);
  assert(v[2] == i4);
  assert(v[3] == i6);
  assert(numerek(v[0]) == 8);
  for (int i = 0; i < 4; ++i)
    free(v[i]);
}
