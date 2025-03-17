
h :: a -> b -> d

-- h = f o g
-- h x y =  (f o g) x y

o :: (c -> d) -> (a -> b -> c) -> (a -> b -> d)