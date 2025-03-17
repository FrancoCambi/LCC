import Parsing
import Control.Applicative hiding (many)

data Expr = Num Int | BinOp Op Expr Expr
data Op = Add | Mul | Min | Div

{-
expr -> term expr'
expr' -> e | ('+' term | '-' term) expr'
term -> factor term'
term' -> e | ('*' factor | '/' factor) term'
-}

expr :: Parser Expr
expr = do {t <- term;
           f <- expr'; -- f:: expr -> expr
           return (f t)}

expr' :: Parser (Expr -> Expr)
expr' = do symbol "+";
           t <- term;
           f <- expr';
           return (\e f (BinOp Add e t))
           <|> do symbol "-";
                  t <- term;
                  f <- expr';
                  return (\e f (BinOpp Min e t))
                  <|> return id
