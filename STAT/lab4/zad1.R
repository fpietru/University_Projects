library(ggplot2)
library(dplyr)

N <- 100
n = 10
a <- 5
alpha = .05

exper <- function(n) {
  X <- runif(n, min=0, max=a)
  a_hat <- max(X)
  l_end <- a_hat
  r_end <- a_hat / alpha^(1/n)
  c(l_end, r_end)
}

results <- replicate(N, exper(n))
success <- results[1,] < a & results[2,] > a
mean(success)
