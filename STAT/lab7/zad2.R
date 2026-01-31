library(ggplot2)
library(GGally)
library(ggfortify)

ggpairs(iris[, 1:4])

var(iris[, -5])

iris_pca <- prcomp(iris[,-5], scale=TRUE)
summary(iris_pca)
iris_pca$x
ggpairs(data.frame(iris_pca$x))
str(iris_pca)
plot(iris_pca)

cumsum(iris_pca$sdev) / sum(iris_pca$sdev)

autoplot(iris_pca, loadings=TRUE, loadings.label=TRUE)