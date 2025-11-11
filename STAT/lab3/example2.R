library(stats4)
library(ggplot2)
library(dplyr)
library(tidyr)

alpha <- .5
lambda <- .2
n <- 20

ahat_mm <- function(x) mean(x)^2 / mean((x-mean(x))^2)
ahat_mle <- function(x) {
  fit <- mle(
    function(a, l) -sum(dgamma(x, shape=a, rate=l, log=TRUE)),
    start = list(a=1, l=1),
    method = "L-BFGS-B",
    lower = c(1e-6, 1e-6)
  )
  coef(fit)["a"]
}

experiment <- function(n, alpha=.5) {
  x <- rgamma(n, alpha, rate=lambda)
  return (c(ahat_mm(x), ahat_mle(x)))
}

N <- 100
replicate(N, experiment(20)) %>% t() %>%
  data.frame() -> results

colnames(results) <- paste0("est", 1:2)
results_long <- results %>%
  pivot_longer(cols=1:2, names_to="est", values_to="val")

summary_stats <- results_long %>%
  group_by(est) %>%
  summarise(mean=mean(val), sd=sd(val))

ggplot(results_long, aes(x=est, y=val, color=est)) +
  geom_jitter(width=0.1, alpha=0.6) +
  geom_hline(yintercept=alpha, linetype="dashed", color="black") +
  geom_point(data=summary_stats, aes(y=mean), color="orange", size=4) +
  geom_text(
    data = summary_stats,
    aes(y=mean, label=sprintf("%.3f", mean)),
    vjust=-1, color="orange"
  ) +
  theme_minimal() +
  labs(
    title = "Porownanie estymatorow parametru alpha w rozkladzie Gamma",
    subtitle = sprintf("Prawdziwe alpha = %.2f, lambda = %.2f, n = %d, N = %d", alpha, lambda, n, N),
    x = "Typ estymatora",
    y = "Wartosc estymacji"
  ) +
  theme(legend.position="none")


