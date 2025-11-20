library(ggplot2)
library(dplyr)

N <- 1000
n = 100
mu <- 0
sigma <- 1
alpha = .05

exper <- function(n) {
  x <- rnorm(n, mean=mu, sd=sigma)
  mu_hat <- mean(x)
  sigma_hat = ?????
  c(l_end, r_end)
}

results <- replicate(N, exper(n))
success <- results[1,] < a & results[2,] > a
mean(success)
