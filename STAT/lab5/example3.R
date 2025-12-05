smaki <- c("jablko", "malina", "cytryna")
zelki <- sample(smaki, 100, prob = c(.5, .25, .25), replace=T)

table(zelki)
chisq.test(table(zelki))