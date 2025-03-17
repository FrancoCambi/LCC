import Ej6

data PHeaps a = Empty | Root a [PHeaps a] deriving Show

getMinPHeap :: Ord a => PHeaps a -> a
getMinPHeap Empty = error "PHeaps vacio"
getMinPHeap (Root a p) = a

isPHeap :: Ord a => PHeaps a -> Bool
isPHeap Empty = True
isPHeap (Root a []) = True
isPHeap arg@(Root a l) = a < (minList (valuesPHeap arg)) && (isPHeapList l)
    where
        isPHeapList :: Ord a => [PHeaps a] -> Bool
        isPHeapList [] = True
        isPHeapList (x:xs) = (isPHeap x) && (isPHeapList xs)

        minList :: Ord a => [a] -> a
        minList [] = error "Lista vacia"
        minList [x] = x
        minList (x:xs) = if x <= minList xs then x else minList xs

        valuesPHeap :: Ord a => PHeaps a -> [a]
        valuesPHeap Empty = []
        valuesPHeap (Root a [x]) = [getMinPHeap x]
        valuesPHeap (Root a (x:xs)) = getMinPHeap x : (valuesPHeap (Root a xs))



mergePHeap :: Ord a => PHeaps a -> PHeaps a -> PHeaps a
mergePHeap Empty Empty = Empty
mergePHeap Empty p1 = p1
mergePHeap p1 Empty = p1
mergePHeap p1@(Root a1 l1) p2@(Root a2 l2) = if a1 < a2 then (addChild p1 p2)
                                        else (addChild p2 p1)

    where
        
        addChild:: Ord a => PHeaps a -> PHeaps a -> PHeaps a
        addChild Empty Empty = Empty
        addChild p1 Empty = p1
        addChild Empty p1 = p1
        addChild p@(Root a l) p2 = (Root a (p2 : l))


insertPHeap :: Ord a => PHeaps a -> a -> PHeaps a
insertPHeap Empty a = Root a []
insertPHeap p@(Root a l) b = mergePHeap p (Root b [])

concatHeaps :: Ord a => [PHeaps a] -> PHeaps a
concatHeaps [] = Empty
concatHeaps [x] = x
concatHeaps (x:xs) = mergePHeap x (concatHeaps xs)

delMinHeaps :: Ord a => PHeaps a -> Maybe (a, PHeaps a)
delMinHeaps Empty = Nothing
delMinHeaps p@(Root a l) = Just (a, (concatHeaps l))

testPHeap = Root 3 [(Root 4 [(Root 5 [])])]
testPHeap2 = Root 2 []

testLista = [(Root 4 []), (Root 2 []), (Root 3 []), (Root 0 [(Root 1 [])])]