--a)
-- Esta bien formada, es como un not.

func x = if true then false else true 
        where false = True; true = False

--b)

-- Esta mal formada por un error de sintaxis.

--if if then then else else

--c)

-- Esta bien formada y devuelve False.

--False == (5 >= 4)

--d)

-- Esta mal, pues no se pueden mezclar operadores infijos con la misma 
-- precedencia.

-- 1 < 2 < 3

--e)

-- Esta bien formada, y devuelve 1 + - 1 = 0

func2 x = 1 + if ('a' < 'z') then (-1) else 0

--f)

-- No funciona y hay un problema de tipos

--func3 x = if fst p then fst p else snd p where p = (True, 2)

--g)

-- Esta bien y devuelve la primer componente, True.

-- if fst p then fst p else snd p where p = (True, False)