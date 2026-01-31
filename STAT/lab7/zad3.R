df <- read.table("pozyczka.csv", header=TRUE, sep=";")
head(df)

df$plec <- as.factor(df$plec)
df$stan_cyw <- as.factor(df$stan_cyw)
df$samozatr <- as.factor(df$samozatr)
df$historia <- as.factor(df$historia)
df$miejsce_zam <- as.factor(df$miejsce_zam)
df$pozyczka <- as.factor(df$pozyczka)

dim(df)

summary(df$pozyczka)
100*sum(df$pozyczka==1) / nrow(df)

model <- glm(pozyczka ~ ., data=df, family=binomial)
summary(model)

confint(model)

prawdopodobienstwa <- predict(model, type="response")

df2 = data.frame("P"=prawdopodobienstwa, "Pozyczka"=df$pozyczka)
ggplot(data=df2) + 
  geom_boxplot(aes(x=Pozyczka, y=P)) +
  theme_minimal()
