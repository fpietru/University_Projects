library(ggplot2)
library(dplyr)


mu <- 3
sigma <- .5
alpha <- .05

exper <- function(n){
  x <- rnorm(n, mean=mu, sd=sigma)
  mhat <- mean(x)
  sdhat <- sd(x)
  d <- qt(1-alpha/2, df=n-1)*sdhat/sqrt(n)
  c(mhat-d, mhat+d)
}
res <- replicate(1000, exper(10))
mean(res[1,] < mu & res[2,] > mu)