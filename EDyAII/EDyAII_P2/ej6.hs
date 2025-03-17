--a)

--smallest (x, y, z) | \x -> (\y -> (\z -> ))

--b)

twice :: x -> x
second = \x -> x

--d)

f :: Int -> Int
f x = x + 1

twice :: (Int -> Int) -> Int -> Int
twice = (\f -> (\x -> f (f x)))

--e)

resta :: Int -> Int -> Int
resta x y = x - y

flipe :: (Int -> Int -> Int) -> Int -> Int -> Int
flipe = (\f -> (\x -> (\y -> f y x)))

--f)

inc = \x -> x + 1

