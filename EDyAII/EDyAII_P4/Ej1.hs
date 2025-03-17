data Bin a = Hoja | Nodo (Bin a) a (Bin a)
    deriving Show


completo :: a -> Int -> Bin a
completo a 0 = Hoja
completo a d = Nodo (completo a (d - 1)) a (completo a (d - 1))

-- Binary balanced sear tree

data Tree a = Nil | Node (Tree a) a (Tree a)
    deriving Show

height :: Tree a -> Int
height Nil = 0
height (Node l a r) = 1 + (max (height l) (height r))

findTree :: Ord a => Tree a -> a -> Bool
findTree Nil _ = False
findTree (Node l a r) x
    | a == x    = True
    | x < a     = findTree l x
    | otherwise = findTree r x


insertTree :: Ord a => Tree a -> a -> Tree a
insertTree Nil x = Node Nil x Nil
insertTree (Node l a r) x
    | x == a    = Node l a r
    | x < a     = rebalance (Node (insertTree l x) a r)
    | otherwise = rebalance (Node l a (insertTree r x))

deleteMax :: Ord a => Tree a -> (a, Tree a)
deleteMax (Node l a Nil) = (a, l)
deleteMax (Node l a r) = (z, Node l a tz)
    where (z, tz) = deleteMax r

deleteTree :: Ord a => Tree a -> a -> Tree a
deleteTree Nil x = Nil
deleteTree (Node l a r) x 
    | x < a = rebalance (Node (deleteTree l x) a r)
    | x > a = rebalance (Node r a (deleteTree r x))
deleteTree (Node Nil a r) x = r
deleteTree (Node l a r) x = rebalance (Node tz z r)
    where (z, tz) = deleteMax l

rebalance :: Ord a => Tree a -> Tree a
rebalance (Node l a r)
    | abs (sy) < 2          = Node l a r
    | sy == 2 && st1 /= -1  = rotateRight (Node l a r)
    | sy == 2 && st1 == -1  = rotateRight (Node (rotateLeft l) a r)
    | sy == -2 && st2 /= -1 = rotateLeft (Node l a r)
    | sy == -2 && st2 == -1 = rotateLeft (Node l a (rotateRight r))
    where
        sy  = slope (Node l a r)
        st1 = slope l
        st2 = slope r

        rotateRight (Node (Node l1 a r) x l2) = Node l1 a (Node r x l2)
        rotateLeft (Node l1 x (Node l2 a r)) = Node (Node l1 a l2) x r

        slope Nil = 0
        slope (Node l a r) = (height l) - (height r)




testTree = (insertTree (insertTree (insertTree (insertTree (insertTree Nil 2) 3) 4) 5) 6)