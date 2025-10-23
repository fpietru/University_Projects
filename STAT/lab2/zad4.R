library(ggplot2)

X <- rnorm(n=200, mean=4, sd=2)
X <- data.frame(X)

x <- seq(-5, 15, 0.2)
y <- dnorm(x, 4, 2)
d <- data.frame(x, y)

d

ggplot(X) + geom_histogram(aes(x=X, y=..density..)) +
  geom_line(aes(x=x, y=y), data=d)
