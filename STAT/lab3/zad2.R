library(ggplot2)
library(dplyr)
library(tidyr)

var_hat_1 <- function(x) mean((x - mean(x))^2) * length(x) / (length(x) - 1)
var_hat_2 <- function(x) mean((x - mean(x))^2)
var_hat_3 <- function(x) mean((x - mean(x))^2) * length(x) / (length(x) + 1)

experiment <- function(n, mu = 0, sigma = 1) {
  x <- rnorm(n, mean = mu, sd = sigma)
  return(c(var_hat_1(x), var_hat_2(x), var_hat_3(x)))
}

N_rep <- 1000
n <- 5
mu <- 0
sigma <- 1

results <- replicate(N_rep, experiment(n, mu, sigma)) %>% t() %>% data.frame()
colnames(results) <- paste0("est", 1:3)

results_long <- results %>%
  pivot_longer(cols = 1:3, names_to = "est", values_to = "val")

true_var <- sigma^2

mse_summary <- results_long %>%
  group_by(est) %>%
  summarise(
    bias = mean(val) - true_var,
    variance = var(val),
    mse = mean((val - true_var)^2)
  )

print(mse_summary)

results_long %>%
  ggplot(aes(x = est, y = val)) +
  geom_hline(yintercept = true_var, linetype = "dashed", color = "red") +
  geom_jitter(aes(col = est), alpha = 0.4, width = 0.15) +
  geom_tile(
    data = results_long %>% group_by(est) %>% summarise(avg = mean(val)),
    aes(x = est, y = avg),
    height = .02, fill = "orange"
  ) +
  geom_col(
    data = results_long %>% group_by(est) %>% summarise(sd = sd(val)),
    aes(x = est, y = sd),
    width = .2, fill = "gray", alpha = .4
  ) +
  theme_minimal()

