library(ggplot2)
library(dplyr)

mu <- 3
sigma <- .5
alpha <- .05
exper <- function(n){
  x <- rnorm(n, mean=mu, sd=sigma)
  mhat <- mean(x)
  d <- qnorm(1-alpha/2)*sigma/sqrt(n)
  c(mhat-d, mhat+d)
}
results <- replicate(1000, exper(10))
success <- results[1,] < mu & results[2,] > mu
mean(success)