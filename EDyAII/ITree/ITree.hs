{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use second" #-}
{-# HLINT ignore "Use bimap" #-}
type Interval = (Int, Int)
data ITree = E | N ITree Interval ITree 
  deriving (Show, Eq)

right :: ITree -> Int 
right E = 0
right (N E (a,b) E) = b
right (N _ _ t2) = right t2


checkIT :: ITree -> Bool
checkIT E = True
checkIT (N E (a, b) E) = a <= b
checkIT (N l (a, b) r) = a <= b && checkL (< (a-1)) l && checkR (> (b + 1)) r && checkIT l && checkIT r

    where
        checkL :: (Int -> Bool) -> ITree -> Bool
        checkL _ E = True
        checkL c (N l (a, b) r) = c b && checkL c l && checkR c r

        checkR :: (Int -> Bool) -> ITree -> Bool
        checkR _ E = True
        checkR c (N l (a, b) r) = c a && checkL c l && checkR c r

splitMax :: ITree -> (Interval, ITree)
splitMax E = undefined
splitMax (N l i E) = (i, l)
splitMax (N l i r) = let split = splitMax r
                     in (fst split, N l i (snd split))


merge :: ITree -> ITree -> ITree
merge l r = let split = splitMax l
            in N (snd split) (fst split) r

delElem :: ITree -> Int -> ITree
delElem E _ = E 
delElem (N l i r) n | i == (n, n) = merge l r
                    | fst i == n = N l (n + 1, snd i) r
                    | snd i == n = N l (fst i, n - 1) r
                    | fst i < n && snd i > n = let izq = (fst i, n - 1)
                                                   der = (n + 1, snd i)
                                               in N l izq (N E der r)
                    | n < fst i = N (delElem l n) i r
                    | otherwise = N l i (delElem r n)

arbol1 :: ITree
arbol1 = N (N E (5,7) E) (9,10) (N E (12,13) E)
arbol2 :: ITree
arbol2 = N (N E (21, 23) E) (26,28) (N E (30,35) E)

arbol3 :: ITree
arbol3 = N arbol1 (15,19) arbol2

-- Caso 1: Árbol vacío
testTree1 :: ITree
testTree1 = N (N E (1,3) (N E (5,7) E)) (5,9) (N E (15,20) E)

-- Caso 2: Árbol con un solo nodo
testTree2 :: ITree
testTree2 = N E (4, 6) E

-- Caso 3: Árbol con varios nodos, todos en el lado izquierdo
testTree3 :: ITree
testTree3 = N (N (N E (1, 2) E) (3, 4) E) (5, 6) E

-- Caso 4: Árbol con varios nodos, todos en el lado derecho
testTree4 :: ITree
testTree4 = N E (1, 2) (N E (4, 5) (N E (7, 8) E))

-- Caso 5: Árbol balanceado con nodos en ambos lados
testTree5 :: ITree
testTree5 = N (N E (1, 3) E) (5, 7) (N E (10, 12) E)
