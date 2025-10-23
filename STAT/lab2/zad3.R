library(dplyr)

births = read.csv("births.csv")

births %>%
  filter(BirthWeightGm > 3000) %>%
  select(c("Weeks", "RaceMom")) %>%
  distinct() %>%
  arrange(Weeks)
