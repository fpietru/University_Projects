library(ggplot2)

ais <- read.table("ais.txt", header=T)

ggplot(ais, aes(x=Ht, y=Wt)) + geom_point()

model <- lm(Wt ~ Ht, ais)
summary(model)

help(lm)

rezydua <- model$residuals

qqnorm(rezydua)

qqline(rezydua, col="blue")

confint(model)

predykcja <- predict(model, data.frame('Ht'=180), interval='prediction', level=0.9)

predykcja

puf <- predict(
  model,
  data.frame('Ht'=seq(120, 230, by=1)),
  interval='prediction',
  level=0.95
)

puf <- as.data.frame(puf)

puf$Wt <- seq(120, 230, by=1)

beta0 <- coef(model)[1]
beta1 <- coef(model)[2]
ggplot(ais, aes(x=Ht, y=Wt)) + geom_point() +
  geom_abline(slope=beta1, intercept=beta0, col='red') +
  geom_ribbon(aes(x=Wt, ymin=lwr, ymax=upr), data=puf, alpha=0.1)

