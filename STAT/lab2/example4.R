library(dplyr)

mtcars %>%
  filter(hp>100) %>%
  arrange(desc(mpg)) %>%
  head()