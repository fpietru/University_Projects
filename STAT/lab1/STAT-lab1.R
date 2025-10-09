2+2
sin(.3)
log(2)
?log
pi
exp(1)
x <- sqrt(19)
y <- sin(10)
x+y
x <- c(1,4,2,6,7,8.2)
3:10
seq(5,17, by=0.3)
seq(5, 17, length.out=100)
x^2
sin(x)
x > 3
mean(x)
sum(x)
sum(x>3)
cumsum(x)
min(x)
max(x)
median(x)
quantile(x, probs=.2)
range(x)
var(x)
sd(x)
x[3]
x[3:5]
x[3:5] <- pi^(1:3)
x[-2]
x[x>3]
runif(1)
runif(1)
runif(10)
runif(10, min=3, max=7)
rnorm(5, mean=3)
pnorm(2)
dnorm(3)
help(dnorm)
qnorm(.2)
sample(x, 1)
sample(x, 3)
sample(x, 100, replace=T)
sample(x, length(x))
sample(1:6, 100, replace=T)
mtcars
?mtcars
dim(mtcars)
ncol(mtcars)
nrow(mtcars)
colnames(mtcars)
head(mtcars)
mtcars[2, 5]
mtcars[c(1, 3), ]
mtcars[ , c(2, 4)]
mtcars[ ,c("mpg", "carb")]
mtcars["carb"]
mtcars$carb
mtcars[ mtcars$carb > 2, ]
summary(mtcars)
mtcars$vs <- as.factor(mtcars$vs)
summary(mtcars)
exp(pi * sqrt(43))
