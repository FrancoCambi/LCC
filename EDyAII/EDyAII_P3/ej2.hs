type Linea = ([Char], Int)

vacia :: Linea
vacia = ([], -1)

moverIzq :: Linea -> Linea
moverIzq (sec, cursor) = (sec, cursor - 1)

moverDer :: Linea -> Linea
moverDer (sec, cursor) = (sec, cursor + 1)

moverIni :: Linea -> Linea
moverIni (sec, cursor) = (sec, 0)

moverFin :: Linea -> Linea
moverFin (sec, cursor) = (sec, length sec)

insertar :: Char -> Linea -> Linea
insertar c l = ((fst l) ++ [c], (snd l) + 1)

borrar :: Linea -> Linea
borrar (sec, cursor) = (drop cursor sec, cursor)
