void bar2(int);

void foo2(void) {
  int i;
  for (i = 0; i < 100; ++i)
    bar2(i);
}
