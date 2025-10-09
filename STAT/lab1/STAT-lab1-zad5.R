df <- read.csv("h3units.csv", header=T)
unique(df$Castle)

df[df$Castle == "Nekropolis", ]
