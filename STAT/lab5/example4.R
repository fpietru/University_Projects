p <- .3
x <- sample(0:1, 100, replace=T, prob=c(1-p, p))
ks.test(x, function(t) pexp(t, rate=2))

plot(ecdf(x))
mgrid <- seq(-2,2,by=.1)
lines(mgrid, pexp(mgrid,2), col="blue")