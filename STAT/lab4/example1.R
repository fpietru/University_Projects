library(ggplot2)
library(dplyr)

n <- 100
th <- .4
expr <- function(n) {
  x <- sample(0:1, n, prob=c(1-th, th), replace=T)
  mean(x)
}

N <- 1000
results <- replicate(N, expr(n))
normed <- sqrt(n)*(results - th) # normalizacja

hist(normed, freq=F, breaks=seq(-2,2,length.out=22))
mgrid <- seq(-2, 2, length.out=100)
lines(mgrid, dnorm(mgrid, sd=sqrt(th*(1-th))))

plot(ecdf(normed))
lines(mgrid, pnorm(mgrid, sd=sqrt(th*(1-th))), col="blue", lwd=2)
