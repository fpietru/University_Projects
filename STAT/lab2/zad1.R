h3units <- read.csv("h3units.csv")
# a)
goodCastle <- h3units[h3units$Castle %in% c("Castle", "Rampart", "Tower"), ]
hist(goodCastle$Health)
# b)
boxplot(Maximum.Damage~Castle, data=h3units)