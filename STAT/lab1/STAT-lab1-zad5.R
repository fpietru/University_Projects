df <- read.csv("h3units.csv", header=T)
# a) Jakie są możliwe nazwy zamków (kolumna Castle)
# w grze?
unique(df$Castle)

# b) Jaka jest mediana wartości ataku dla
# jednostek z Necropolis?
median(df[df$Castle == "Necropolis", "Attack"])

# c) Jaka jest średnia wartość obrony dla zaawansowanych
# (tzn. zawierających "+" w kolumnie Level) jednostek
# dla Twierdzy (Stronghold)?
mean(df[endsWith(df$Level, "+") & df$Castle == "Stronghold", "Defence"])

# d) Wyznacz średnią szybkość jednostek, które nie latają,
# w podziale na zamki.
df2 = df[grepl("Flying", df$Special_abilities) == F, ]
aggregate(df2$Speed, list(df2$Castle), FUN=mean)
