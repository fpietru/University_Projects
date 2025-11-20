library(ggplot2)
library(dplyr)

p <- .7
alpha <- .05
N <- 1000

#standardowy przedział ufności
exper1 <- function(n) {
  x <- sample(0:1, n, prob=c(1-p, p), replace=T)
  phat <- mean(x)
  sigma <- sqrt(phat*(1-phat))
  d <- qnorm(1-alpha/2) * sigma/sqrt(n)
  c(phat-d, phat+d)
}

res1 <- replicate(N, exper1(10))
ans1 <- mean(res1[1,] < p & res1[2,] > p)

# przedział Cloppera-Pearsona
exper2 <- function(n) {
  x <- sample(0:1, n, prob=c(1-p, p), replace=T)
  s <- sum(x)
  c(qbeta(alpha/2, s, n-s+1), qbeta(1-alpha/2, s+1, n-s))
}

res2 <- replicate(N, exper2(10))
ans2 <- mean(res2[1,] < p & res2[2,] > p)

sprintf("%f - standardowy przedzial ufnosci", ans1)
sprintf("%f - przedział Cloppera-Pearsona", ans2)