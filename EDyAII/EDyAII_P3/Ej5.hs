module Ej5 where

import Ej4

parseRPN :: String -> Exp
parseRPN input = parseRPNAux (words input) []

parseRPNAux :: [String] -> [Exp] -> Exp
parseRPNAux [] l = head l
parseRPNAux (x:xs) stack 
    | isNumber x = parseRPNAux xs (Lit (read x) : stack)
    | otherwise = case x of
        "+" -> let e = (Add (head (tail stack)) (head stack)) in 
                parseRPNAux xs (e : (drop 1 (drop 1 stack)))
        "-" -> let e = (Sub (head (tail stack)) (head stack)) in 
                parseRPNAux xs (e : (drop 1 (drop 1 stack)))
        "*" -> let e = (Prod (head (tail stack)) (head stack)) in 
                parseRPNAux xs (e : (drop 1 (drop 1 stack)))
        "/" -> let e = (Div (head (tail stack)) (head stack)) in 
                parseRPNAux xs (e : (drop 1 (drop 1 stack)))
        _   -> error "ERROR SINTAXIS INCORRECTA"
    where
        isNumber :: String -> Bool
        isNumber str = all (\c -> c >= '0' && c <= '9') str


evalRPN :: String -> Int
evalRPN "" = error "String vacia"
evalRPN str = eval (parseRPN str)