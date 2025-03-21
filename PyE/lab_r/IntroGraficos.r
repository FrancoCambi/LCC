# Preparación de los datos

download.file(
  url = "https://raw.githubusercontent.com/jboscomendoza/r-principiantes-bookdown/master/datos/bank.csv", 
  destfile = "bank.csv"
)

banco <- read.csv(file = "bank.csv", sep = ";")

lapply(banco, class)

banco$job <- as.factor(banco$job)
banco$marital <- as.factor(banco$marital)
banco$default <- as.factor(banco$default)
banco$education <- as.factor(banco$education)
banco$housing <- as.factor(banco$housing)
banco$loan <- as.factor(banco$loan)
banco$contact <- as.factor(banco$contact)
banco$month <- as.factor(banco$month)
banco$poutcome <- as.factor(banco$poutcome)
banco$y <- as.factor(banco$y)

lapply(banco, class)

# Gráfico de barras
plot(x = banco$education, main = "Gráfica de Educacíón",
     xlab = "Nivel educativo", ylab = "Frecuencia", 
     col = "seagreen")

# Gráfico de torta
es_civil <- table(banco$marital)
porcentaje <- round(es_civil / sum(es_civil) * 100, 2)
options <- c("divorciadx", "casadx", "solterx") # según orden de los factores
labels <- paste(options, porcentaje, c("%"), sep = " ")
pie(es_civil, labels = labels, clockwise = TRUE, main = "Estado civil", 
    col = c("black", "pink", "green"))


# Gráfico de Pareto 
# install and Load qcc package
install.packages('qcc')
library(qcc)

defect <- c(27, 789, 9, 65, 12, 109, 30, 15, 45, 621)
names(defect) <- c("Too noisy", "Overpriced", "Food not fresh",
                   "Food is tasteless", "Unfriendly staff",
                   "Wait time", "Not clean", "Food is too salty",
                   "No atmosphere", "Small portions")

pareto.chart(defect,
             ylab="Frequency", 
             # colors of the chart		 
             col=heat.colors(length(defect)),
             cumperc = seq(0, 100, by = 20),
             ylab2 = "Cumulative Percentage",
             main = "Complaints of different customers"
)


# Histograma
breaks_edad <- seq(17,88,5)
hist(x = banco$age, breaks = breaks_edad, main = "Histograma de Edad", 
     xlab = "Edad", ylab = "Frecuencia",
     col = "purple")

# poligono de frecuencia y poligono acumulativo para EDAD
tabla_edad <- table(cut(banco$age,breaks = breaks_edad,right = FALSE))
tabla_edad <- round(tabla_edad/sum(tabla_edad),4)
# poligono de frecuencia:
plot(tabla_edad,type = "l",main = "Polígono de Frecuencia de Edad",
     ylab = "Frecuencia Relativa",xlab = "Edad (en años)",ylim = c(0,0.3))
grid()
# poligono acumulativo:
tabla_edad_acum <- as.table(cumsum(tabla_edad))
plot(tabla_edad_acum,type = "l",main = "Polígono Acumulativo de Edad", xaxt = "n", 
     ylab = "Frecuencia Relativa Acumulada",xlab = "Edad (en años)",ylim = c(0,1))
grid()
valores_eje_x <- c(17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72, 77, 82)
axis(1, at = 1:14, labels = valores_eje_x)

# Gráfico de bastones
install.packages("readxl")
library(readxl) 

Base <- read_excel("Base_partos.xls")
View(Base)
tab.partos <- table(Base$`Partos previos`)
plot(tab.partos, type="h",main = strsplit(c("Número de partos previos de mujeres atendidas \n en la Maternidad Martin durante el año 2014"), split = ";"), xlab=NA, ylab = "Número de casos", 
sub="Fuente: Elaboración propia a partir de datos suministrados \npor la secretaría de salud pública de la ciudad de Rosario")
mtext("Número de partos previos", side=1 , line=2)

# Así es como deberíamos presentar los gráficos para informes: con títulos 
# explicativos, que no presten a dudas, y con fuentes

# Gráfico de caja 
boxplot(x = banco$age, col = "red")

# Actividad: investiguen qué tipo de gráfico genera plot(..., type = "s") y 
# qué hace la función stem y generen gráficos a partir de ellos

