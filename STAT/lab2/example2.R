n <- 10
x <- c(0,1)
for (i in 1:n) {
  print(x[1])
  x <- c(x[2], sum(x))
}