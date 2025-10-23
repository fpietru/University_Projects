library(ggplot2)

births = read.csv("births.csv")

ggplot(births, aes(x=Weeks, y=BirthWeightGm)) + 
  geom_point(size=.5, aes(col=as.factor(Smoke))) +
  theme_minimal() +
  xlab("Week")

birth_plot <- ggplot(births) + theme_minimal()
birth_plot + aes(group=RaceMom, x=RaceMom, y=BirthWeightGm) + geom_violin()

birth_plot + aes(x=RaceMom) + geom_bar() +
  geom_violin(aes(group=RaceMom, y=BirthWeightGm))

birth_plot + aes(x=Weeks, y=BirthWeightGm) + geom_point(size=.5) +
  geom_smooth(method="lm") + facet_grid(vars(HispMom), vars(Smoke))
