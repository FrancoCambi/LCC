module Ej6
    where

type Rank = Int
data Heap a = E | N Rank a (Heap a) (Heap a)
    deriving Show

merge :: Ord a => Heap a -> Heap a -> Heap a
merge h1 E = h1
merge E h2 = h2
merge h1@(N _ x a1 b1) h2@(N _ y a2 b2) =
    if x <= y then makeH x a1 (merge b1 h2)
    else makeH y a2 (merge h1 b2)

rank :: Heap a -> Rank
rank E = 0
rank (N r _ _ _ ) = r

makeH :: Ord a => a -> Heap a -> Heap a -> Heap a
makeH x a b = if rank a >= rank b then N (rank b + 1) x a b
              else N (rank a + 1) x b a   

insert :: Ord a => a -> Heap a -> Heap a
insert x h = merge (N 1 x E E) h

findMin :: Ord a => Heap a -> a
findMin E = error "Heap vacio"
findMin (N _ x a b) = x

deleteMin :: Ord a => Heap a -> Heap a
deleteMin (N _ x a b) = merge a b

fromList :: Ord a => [a] -> Heap a
fromList [] = E
fromList (x:xs) = merge (N 0 x E E) (fromList xs)

isHeap :: Ord a => Heap a -> Bool
isHeap E = True
isHeap (N _ a E E) = True
isHeap (N _ a l E) = a < (findMin l) && isHeap l
isHeap (N _ a E r) = a < (findMin r) && isHeap r
isHeap (N _ a l r) = a < (findMin l) && a < (findMin r) && isHeap l && isHeap r
