df <- mtcars

# a) Ile wynosi maksymalny przebieg (w milach/galon)
# i który samochód go osiągnął?
mxMpg <- max(mtcars["mpg"])
mxMpgCars <- df[df$mpg == mxMpg, ]
mxMpgCars

# b) Jak wygląda pierwsza trójka samochodów o największej
# liczbie koni mechanicznych?
head(df[order(df$hp, decreasing=T), ], 3)
#c) Jakie są średnie przyspieszenia dla:
#  • wszystkich samochodów,
mean(df$qsec)
#  • samochodów z/bez automatycznej skrzyni biegów,
mean(df[df$am == 0, "qsec"])
mean(df[df$am == 1, "qsec"])
#  • mercedesów,
mean(df[startsWith(rownames(df), "Merc"), "qsec"])
#  • czołowych 20% samochodów po względem liczby
#    koni mechanicznych.
percent <- 20
lim <- floor(nrow(df) * percent / 100)
mean(head(df[order(df$hp, decreasing=T), "qsec"], lim))
