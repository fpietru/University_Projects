n <- 10000000
x <- runif(n, min=-1, max=1)
y <- runif(n, min=-1, max=1)
d <- sqrt(x^2 + y^2)
w <- sum(d <= 1)
P <- w / n
P * 4
