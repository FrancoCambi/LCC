module Lab1C where

import Data.List
import Data.Ord

{-
   Definir una función que dado un caracter y un texto calcule la frecuencia 
   con la que ocurre el caracter en el texto
   Por ejemplo: frecuency 'a' "casa" = 0.5 
-}

frequency :: Char -> String -> Float
frequency c text = 
  let total = length text
      count = length (filter (== c) text)
  in if total == 0 
     then 0 
     else fromIntegral count / fromIntegral total

{-                      
  Definir una función frecuencyMap que dado un texto calcule la frecuencia 
  con la que ocurre cada caracter del texto en éste.
  La lista resultado debe estar ordenada respecto a la frecuencia con la que ocurre 
  cada caracter, de menor a mayor frecuencia. 
    
  Por ejemplo: frecuencyMap "casa" = [('c',0.25),('s',0.25),('a',0.5)]

-}

frequencyMap :: String -> [(Char, Float)]
frequencyMap s = sortBy (comparing snd) (nub (map (\c -> (c, frequency c s)) s))

{-
  Definir una función subconjuntos, que dada una lista xs devuelva una lista 
  con las listas que pueden generarse con los elementos de xs.

  Por ejemplo: subconjuntos [2,3,4] = [[2,3,4],[2,3],[2,4],[2],[3,4],[3],[4],[]]
-}

subconjuntos :: [a] -> [[a]]
subconjuntos [] = [[]]
subconjuntos (x:xs) = let sinX = subconjuntos xs
                      in sinX ++ map (x:) sinX

{-
 Definir una función intercala :: a -> [a] -> [[a]]
 tal que (intercala x ys) contiene las listas que se obtienen
 intercalando x entre los elementos de ys. 
 
 Por ejemplo: intercala 1 [2,3]  ==  [[1,2,3],[2,1,3],[2,3,1]]
-}

intercala :: a -> [a] -> [[a]]
intercala x [] = [[x]]
intercala x (y:ys) = (x:y:ys) : map (y:) (intercala x ys)

{- 
  Definir una función permutaciones que dada una lista calcule todas las permutaciones
  posibles de sus elementos. Ayuda: la función anterior puede ser útil. 

  Por ejemplo: permutaciones "abc" = ["abc","bac","cba","bca","cab","acb"]
-}                  

permutaciones :: [a] -> [[a]]
permutaciones [] = [[]]
permutaciones (x:xs) = concatMap (intercala x) (permutaciones xs)

