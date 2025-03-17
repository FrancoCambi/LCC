scalarproduct :: [Int] -> [Int] -> Int
scalarproduct [] [] = 0
scalarproduct l1 l2 
    | length l1 == length l2 = sum [(x*y) | (x, y) <- zip l1 l2]
    | otherwise = error "Listas de distinto tamaño"
