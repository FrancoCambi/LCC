type Interval = (Int, Int)
data ITree = E | N ITree Interval ITree
    deriving Show


right :: ITree -> Int
right E = error "ITree vacio"
right (N E (a,b) E) = b
right (N l (a,b) E) = b
right (N l i r) = right r


checkIT :: ITree -> Bool
checkIT E = True
checkIT (N E (a,b) E) = a <= b
checkIT (N E (a1,b1) (N E (a2, b2) E)) = a1 < b1 && b1 + 1 < a2
checkIT (N (N E (a2, b2) E) (a1, b1) E) = a1 < b1 && b2 < a1 - 1
checkIT (N l@(N l2 (a2, b2) r2) (a1, b1) r@(N l3 (a3, b3) r3)) = a1 <= b1 && (b1 + 1) < a3 && b2 < (a1 - 1) && (checkIT l) && (checkIT r)


test = (N (N E (1,3) E) (5,9) (N E (11,20) E))

