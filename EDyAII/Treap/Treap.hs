data Treap p k = E | N (Treap p k) p k (Treap p k)
    deriving Show


key :: Treap p k -> k
key E = error "Treap vacio"
key (N t1 p k t2) = k

priority :: Treap p k -> p
priority E = error "Treap vacio"
priority (N t1 p k t2) = p

isTreap :: (Ord k, Ord p) => Treap p k -> Bool
isTreap E = True
isTreap (N E p k E) = True
isTreap (N t1 p k E) = p >= (priority t1) && k >= (key t1) && (isTreap t1)
isTreap (N E p k t2) = p >= (priority t2) && k < (key t2) && (isTreap t2)
isTreap (N t1 p k t2) = p >= (priority t1) && p >= (priority t2) && k >= (key t1) 
                    && k < (key t2) && (isTreap t1) && (isTreap t2)

insert :: (Ord p, Ord k) => p -> k -> Treap p k -> Treap p k
insert p k E = N E p k E
insert p k (N t1 p2 k2 t2) = if k > k2 then if (isTreap (N t1 p2 k2 (insert p k t2))) then (N t1 p2 k2 (insert p k t2))
                            else (rotateL (N t1 p2 k2 (insert p k t2))) else if (isTreap (N (insert p k t1) p2 k2 t2)) then (N (insert p k t1) p2 k2 t2)
                            else (rotateR (N (insert p k t1) p2 k2 t2))
    where
        rotateL (N l1 p1 k1 (N l2 p2 k2 r2)) = N (N l1 p1 k1 l2) p2 k2 r2
        rotateR (N (N l2 p2 k2 r2) p1 k1 r1) = N l2 p2 k2 (N r2 p1 k1 r1)


split :: (Ord k, Ord p, Num p) => k -> Treap p k -> (Treap p k, Treap p k)
split k E = (E, E)
split k t = let t2 = (insert ((priority t) + 1) k t) in ((leftT t2), (rightT t2))

    where
        leftT E = E
        leftT (N t1 _ _ _) = t1

        rightT E = E
        rightT (N _ _ _ t2) = t2

    
test = N (N E 4 4 E) 5 8 (N E 4 9 E)