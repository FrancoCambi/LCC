data Bin a = Hoja | Nodo (Bin a) a (Bin a)
    deriving Show


insertBST :: Ord a => a -> Bin a -> Bin a
insertBST a Hoja = Nodo Hoja a Hoja
insertBST a (Nodo l b r) | a <= b = Nodo (insertBST a l) b r
                         | otherwise = Nodo l b (insertBST a r)

minimumBST :: Ord a => Bin a -> a
minimumBST Hoja = error "El arbol es solo una hoja"
minimumBST (Nodo Hoja a r) = a
minimumBST (Nodo l a r) = minimumBST l

maximumBST :: Ord a => Bin a -> a
maximumBST Hoja = error "El arbol es solo una hoja"
maximumBST (Nodo l a Hoja) = a
maximumBST (Nodo l a r) = maximumBST r


checkBST :: Ord a => Bin a -> Bool
checkBST Hoja = True
checkBST (Nodo Hoja a Hoja) = True
checkBST (Nodo l a r) | isLeaf l = a < getRoot r && checkBST r
                      | isLeaf r = a >= getRoot l && checkBST l
                      | otherwise = getRoot l <= a && getRoot r > a && checkBST l && checkBST r
    where 
        getRoot :: Bin a -> a
        getRoot Hoja = error "El arbol es una hoja"
        getRoot (Nodo l a r) = a

        isLeaf :: Bin a -> Bool
        isLeaf Hoja = True
        isLeaf _ = False


joinBST :: Ord a => Bin a -> Bin a -> Bin a
joinBST Hoja Hoja = Hoja
joinBST Hoja t@(Nodo l a r) = t
joinBST t@(Nodo l a r) Hoja = t
joinBST t1@(Nodo l a r) t2@(Nodo l2 b r2) = let tt = (insertBST b t1) in (joinBST tt (joinBST l2 r2))

splitBST :: Ord a => Bin a -> a -> (Bin a, Bin a)
splitBST Hoja a = (Hoja, Hoja)
splitBST t@(Nodo l b r) a = let tt@(Nodo lr c rr) = (joinBST (Nodo Hoja a Hoja) t) in (lr, rr)


testTree = Nodo (Nodo Hoja 1 Hoja) 2 (Nodo Hoja 3 (Nodo Hoja 4 (Nodo Hoja 5 Hoja)))
test1 = Nodo Hoja 650 Hoja