library(ggplot2)
library(dplyr)

n <- 100
N <- 10

x <- sample(0:1, n*N, replace=T, prob=c(1-p, p))
x <- matrix(sample(0:1, n*N, replace=T, prob=c(1-p, p)), N)

xbar <- apply(x, 1, mean)

deviation <- qnorm(1-alpha/2) / sqrt(n) * sqrt(xbar*(1-xbar))

left1 <- xbar - deviation
right1 <- xbar + deviation

s <- n * xbar

# teraz lewe i prawe krańce przedziałów
left2 <- qbeta(alpha/2, s, n-s+1)
right2 <- qbeta(1-alpha/2, s+1, n-s)
# możemy rysować
# najpierw zaznaczymy niebieską pionową linię wycentrowaną na x=p
# tzn. prawdziwą wartość parametru p
plot( c(p,p), c(0,N+1), type="l", col="blue", xlab="", ylab="" )
# teraz zaznaczymy w poziomie N standardowych przedziałów ufności
# oraz N przedziałów Cloppera-Pearsona
eps = .2
for( i in 1:N ){
  lines( c(left1[i], right1[i]), c(i,i), col="red" )
  lines( c(left2[i], right2[i]), c(i+eps,i+eps), col="orange" )
}