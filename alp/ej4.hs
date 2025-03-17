import Parsing
import Control.Applicative hiding (many)
import Data.Char (digitToInt)

data Expr = Num Int | BinOp Op Expr Expr
data Op = Add | Mul | Min | Div

expr :: Parser Expr
expr = do
        t <- term
        do symbol "+"
           e <- expr
           return (BinOp Add t e)
           <|> do symbol "-"
                  e <- expr
                  return (BinOp Min t e)
                  <|> return t

term :: Parser Expr
term = do
        f <- factor
        do symbol "*"
           t <- term
           return (BinOp Mul f t)
           <|> do symbol "/"
                  t <- term
                  return (BinOp Div f t)
                  <|> return f

factor :: Parser Expr
factor = parentExpr <|> digitExpr
    where
        parentExpr = do symbol "("
                        e <- expr
                        symbol ")"
                        return e

        digitExpr = do d <- digit
                       return (Num (digitToInt d))

        
