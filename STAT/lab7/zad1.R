
df <- read.csv("walter.csv", header=FALSE)


srednia_podzbioru <- function(dane) {
  mean(dane[sample(nrow(dane), size=nrow(dane), replace=TRUE), ])
}

srednia_podzbioru(df)

n <- 1000
srednie <- replicate(n, srednia_podzbioru(df))
hist(srednie)
