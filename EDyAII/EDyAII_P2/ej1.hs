--a)

func :: Num a => a -> a
func x = x + 2

test :: Num a => (a -> a) -> a -> a
test f x = f x

--b)
esMenor :: (Ord y) => y -> y -> Bool
esMenor y z = y < z

--c)

eq :: Eq a => a -> a -> Bool
eq a b = a == b

--d)

showVal :: Show x => x -> [Char]
showVal x = "Valor " ++ show x
