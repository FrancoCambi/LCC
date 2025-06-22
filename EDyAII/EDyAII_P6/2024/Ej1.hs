import Par

data BTree a = E | Node Int (BTree a) a (BTree a) deriving Show


nth :: BTree a -> Int -> a
nth E a = error "No definido para secuencias vacias o index out of range"
nth (Node tam ti a td) pos | (pos + (tamaño td) == tam) = a
                           | (pos > (tamaño ti)) = nth td (pos - (tamaño ti) - 1)
                           | otherwise = nth ti pos
    where
        tamaño :: BTree a -> Int
        tamaño E = 0
        tamaño (Node tam _ _ _) = tam

cons :: a -> BTree a -> BTree a
cons a E = Node 1 E a E
cons a (Node tam ti val td) = (Node (tam + 1) (cons a ti) val td)

tabulate :: Ord a => (Int -> a) -> Int -> BTree a
tabulate f 0 = E 
tabulate f n | (even n) = let (pm, sm) = ((tabulateAux f 1 ((div n 2) - 1)) ||| (tabulateAux f ((div n 2) + 1) n))
                in (Node n pm (f (div n 2)) sm)
             |(odd n) = let (pm, sm) = (tabulateAux f 1 ((div (n + 1) 2) - 1)) ||| (tabulateAux f ((div (n + 1) 2) + 1) n)
                in (Node n pm (f (div (n + 1) 2)) sm)

    where

        tabulateAux :: Ord a => (Int -> a) -> Int -> Int -> BTree a
        tabulateAux f min max | (min == max) = (Node 1 E (f min) E)
                              | otherwise = (consBst (f min) (tabulateAux f (min + 1) max))

            where

                consBst :: Ord a => a -> BTree a -> BTree a
                consBst a E = (Node 1 E a E)
                consBst a (Node tam ti val td) | (a <= val) = (Node (tam + 1) (consBst a ti) val td)
                                               | (a > val) = (Node (tam + 1) ti val (consBst a td))
     

mapBST :: (a -> b) -> BTree a -> BTree b
mapBST f E = E
mapBST f (Node tam l val r) = let (l', r') = (mapBST f l) ||| (mapBST f r) 
                              in (Node tam l' (f val) r')

takeBST :: Int -> BTree a -> BTree a
takeBST 0 t = E
takeBST n E = E
takeBST n t = (consFinal (nth t n) (takeBST (n-1) t))

    where 
        consFinal :: a -> BTree a -> BTree a
        consFinal a E = Node 1 E a E
        consFinal a (Node tam ti val td) = (Node (tam + 1) ti val (consFinal a td))


dropBST :: Int -> BTree a -> BTree a
dropBST 0 t = t
dropBST n E = E
dropBST n t@(Node tam l val r) | (n == tam) = E
                               | otherwise = (cons (nth t (n + 1)) (dropBST (n + 1) t))



suma :: Int -> Int
suma a = a

t1 = (Node 7 (Node 3 (Node 1 E 1 E) 2 (Node 1 E 3 E)) 4 (Node 3 (Node 1 E 5 E) 6 (Node 1 E 7 E))) 
t2 = tabulate suma 8