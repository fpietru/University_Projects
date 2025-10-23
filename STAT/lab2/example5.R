library(dplyr)

births = read.csv("births.csv")

births %>%
  group_by(RaceMom) %>%
  summarise(avg = mean(BirthWeightGm))

births %>% mutate(massKg = BirthWeightGm / 1000)