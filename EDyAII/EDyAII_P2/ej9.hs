zip3_ :: [a] -> [b] -> [c] -> [(a, b, c)]
zip3_ [] l2 l3 = []
zip3_ l1 [] l3 = []
zip3_ l1 l2 [] = []
zip3_ (x1:xs1) (x2:xs2) (x3:xs3) = [(x1, x2, x3)] ++ zip3_ xs1 xs2 xs3
 
zip3nr  :: [a] -> [b] -> [c] -> [(a, b, c)]
zip3nr l1 l2 l3 = (map (\ ((x, y), z) -> (x, y, z)) (zip (zip l1 l2) l3))

