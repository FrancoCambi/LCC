--a)

f :: a -> a
f x = x

--b)

greater :: (Eq x, Num x, Ord x) => (x, x) -> Bool
greater (x, y) | x > y = True
               | otherwise = False

--c)

--f2 (x , y) = let z = x + y in g (z , y) where g (a, b) = a - b

f2 :: Num a => (a, a) -> a
f2 (x, y) = fst (x, y)

