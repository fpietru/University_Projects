library(dplyr)
library(ggplot2)

df = read.csv("starwars.csv")

# a)
df %>%
  filter(name == "Darth Maul") %>%
  select(c("height"))

# b)
df %>%
  filter(grepl("The Empire Strikes Back", films)) %>%
  select(c("name", "mass")) %>%
  arrange(desc(mass))

df %>%
  filter(mass >= 140.0) %>%
  select(c("name", "mass"))

# c)
df %>%
  mutate(bmi = height / mass ^ 2) %>%
  group_by(homeworld) %>%
  summarise(mi = min(bmi), avg = mean(bmi), mx = max(bmi))

# d)
df %>%
  filter(lengths(regmatches(films, gregexpr(",", films))) + 1 >= 3) %>%
  select(c("name", "films"))

# e)
ggplot(df, aes(x=mass, y=birth_year)) +
  geom_point() +
  geom_smooth(method="lm") +
  facet_grid(vars(sex))