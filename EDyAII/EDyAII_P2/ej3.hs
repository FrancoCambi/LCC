--a)

func_a :: (Int -> Int) -> Int
func_a f = f 0

--b)

func_b :: Int -> (Int -> Int)
func_b x = f 
            where f a = 0

--c)

func_c :: (Int -> Int) -> (Int -> Int)
func_c f = f

--d)

func_d :: Int -> Bool
func_d 0 = False
func_d 1 = True

--e)

func_e :: Bool -> (Bool -> Bool)
func_e True = not
func_e False = not

--f)

func_f :: (Int, Char) -> Bool
func_f (1, '1') = True
func_f (0, '0') = True
func_f (a, b) = False

--g)

func_g :: (Int, Int) -> Int
func_g (1, a) = 1
func_g (0, a) = 0

--h)

func_h :: Int -> (Int, Int)
func_h x = (x, x)

--i)

func_i :: a -> Bool
func_i a = True

--j)

func_j :: a -> a
func_j a = a

