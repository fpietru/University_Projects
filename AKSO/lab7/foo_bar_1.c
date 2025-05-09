void bar1(void);

void foo1(void) {
  int i;
  for (i = 0; i < 100; ++i)
    bar1();
}
