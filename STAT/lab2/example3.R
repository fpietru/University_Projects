collatz <- function(n) {
  seq <- c(n)
  while (n > 1) {
    if (n %% 2 == 0) {
      n <- n / 2
    } else {
      n <- 3*n + 1
    }
    seq <- c(seq, n)
  }
  return(seq)
}

collatz(10)