--a)

divisors :: Int -> [Int]
divisors x | x < 0 = []
           | otherwise = [n | n <- [1..x], mod x n == 0]

--b)

matches ::  Int -> [Int] -> [Int]
matches x l = [n | n <- l, x == n]

--c)

cuadruplas :: Int -> [(Int, Int, Int, Int)]
cuadruplas n | n < 0 = []
             | otherwise = [(a, b, c, d) | a <- [1..n], b <- [1..n], 
             c <- [1..n], d <- [1..n], a^2 + b^2 == c^2 + d^2]

--d)

pertenece :: Int -> [Int] -> Bool
pertenece x [] = False
pertenece x (y:ys) 
    | x == y = True
    | otherwise = pertenece x ys

maxLista :: [Int] -> Int
maxLista [] = error "Lista vacia"
maxLista [x] = x
maxLista (x:xs) 
    | x > maxTail = x
    | otherwise = maxTail
    where maxTail = maxLista xs

unique :: [Int] -> [Int]
unique [] = []
unique xs = [n | n <- [1..maxLista xs], pertenece n xs]