# 1.1 Operadores de asignación

# generalmente se usa <-
x <- 2

# pero también vale
y = 4

# para asignar un atributo nombrado en el llamado a una función se usa =
example(typeof, package="base")

# 1.2 Operadores aritméticos

# tenemos +, -, *, /, ^

z1 <- 2^4

z2 <- 400%%2 # módulo

# 1.3 Operadores relacionales

# tenemos ==, !=, >=, >, <, <=

x > y

x == y

# 1.4 Operadores lógicos

# tenemos a|b, a&b, !a, isTRUE(a)

x<y & y>x

x|y # si son números distintos a 0 se toman como true

# 2. Definición de función y estructuras de control

promedio <- function(calificaciones) {
  media <- mean(calificaciones)
  
  if(media >= 6) {
    print("Aprobado")
  } else {
    print("Reprobado")
  }
  
  for(numero in 1:5) {
    print(numero)
  }
  
  umbral <- 5
  valor <- 0
  
  while(valor < umbral) {
    print("Todavía no.")
    valor <- valor + 1
  }
  
  return(media)
}

promedio(c(6, 7, 8, 9, 8))

# 3. Tipos de datos

# tenemos numeric, integer, double, complex, character, logical, raw (y factor*)

# * depende la bibliografía. A mi parecer es más correcto entender a factor como
# una estructura

typeof(2)

mode(2)

typeof(2.0)

typeof(as.integer(2))

typeof("hola")

# veamos un poquito en detalle factor:

mes_data <- c("Dic", "Abr", "Ene", "Mar", "Abr")

mes_levels <- c(
  "Ene", "Feb", "Mar", "Abr", "May", "Jun", 
  "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"
)

mes_data_factor <- factor(mes_data, levels = mes_levels)

print(mes_data_factor)

vector <- c("Alto", "Bajo", "Alto", "Bajo")

vector_factor <- as.factor(vector)
typeof(vector_factor)
class(vector_factor)
print(vector_factor)

# 4. ¿Cómo cargar scripts y paquetes?

?install.packages
?library
?source

install.packages("readxl")
library(readxl) 
?read_xls()
source("ejemplo.r")
ejemplo(1)
