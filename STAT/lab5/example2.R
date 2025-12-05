exper <- function(m) {
  x <- rnorm(100, mean=pi, sd=.5)
  t.test(x, mu=m)$p.value
}

wyn <- replicate(1000, exper(3))
hist(wyn)