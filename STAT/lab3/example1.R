library(ggplot2)
library(dplyr)
library(tidyr)

hat_th_1 <- function(x) sqrt(mean(x==1))
hat_th_2 <- function(x) 1 - sqrt(mean(x==3))
hat_th_3 <- function(x) mean(x==1) + mean(x==2) / 2

experiment <- function(n, th=.3) {
  probs <- c(th^2, 2*th*(1-th), (1-th)^2)
  x <- sample(1:3, n, replace=T, probs)
  return (c(hat_th_1(x), hat_th_2(x), hat_th_3(x)))
}

N <- 100
replicate(N, experiment(20)) %>% t() %>%
  data.frame() -> results

colnames(results) <- paste0("est", 1:3)

results_long <- results %>%
  pivot_longer(cols=1:3, names_to="est", values_to="val")

th <- 0.3

results_long %>% ggplot() +
  aes(x=est, y=val) +
  geom_hline(yintercept=th, linetype="dashed") +
  geom_jitter(aes(col=est)) +
  theme_minimal() +
  geom_tile(
    data=results_long %>% group_by(est) %>% summarise(avg=mean(val)),
    aes(x=est, y=avg),
    height=.01, fill="orange"
  ) +
  theme(
    axis.title = element_blank(),
    legend.position = "none"
  ) +
  geom_col(
    data=results_long %>% group_by(est) %>% summarise(sd=sd(val)),
    aes(x=est, y=sd),
    width=.2, fill="gray", alpha=.5
  )
