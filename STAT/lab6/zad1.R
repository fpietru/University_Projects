library(GGally)

ais <- read.table("ais.txt", header=T)

# a) Ile ma obserwacji, a ile zmiennych? Które zmienne są ilościowe,
# a które jakościowe.
# Odp. 202 obs, 13 zmiennych. Jakościowe: "Sex", "Sport".
# Ilościowe: wszystkie pozostałe

nrow(ais)
ncol(ais)

# b) Jaka jest średnia oraz wariancja każdej ze zmiennych ilościowych?

summary(ais)

# c) 

ggpairs(ais, aes(col=Sex), columns=c(9,10,5,13))