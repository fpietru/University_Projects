library(ggplot2)
library(dplyr)
library(tidyr)

N_hat_1 <- function(x) 2 * mean(x)
N_hat_2 <- function(x) max(x)
N_hat_3 <- function(x) max(x + x/length(x))

experiment <- function(k, N_true) {
  x <- sample(1:N_true, k, replace=TRUE)
  return (c(N_hat_1(x), N_hat_2(x), N_hat_3(x)))
}

N_rep <- 1000
k <- 20
N_true <- 50

results <- replicate(N_rep, experiment(k, N_true)) %>% t() %>% data.frame()
colnames(results) < paste0("est", 1:3)

results_long <- results %>%
  pivot_longer(cols=1:3, names_to="est", values_to="val")

results_long %>%
  ggplot(aes(x=est, y=val)) +
  geom_hline(yintercept=N_true, linetype="dashed", color="red") +
  geom_jitter(aes(col=est), alpha=.5, width=.2) +
  theme_minimal() +
  geom_tile(
    data = results_long %>% group_by(est) %>% summarise(avg=mean(val)),
    aes(x=est, y=avg),
    height=.5, fill="orange"
  ) +
  geom_col(
    data = results_long %>% group_by(est) %>% summarise(sd=sd(val)),
    aes(x=est, y=sd),
    width=.2, fill="gray", alpha=.4
  )
  
bias_var <- results_long %>%
  group_by(est) %>%
  summarise(
    bias = mean(val) - N_true,
    variance = var(val)
  )
print(bias_var)
