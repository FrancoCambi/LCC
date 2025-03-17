{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE FunctionalDependencies #-}

data TTree k v = Node k (Maybe v) (TTree k v) (TTree k v) (TTree k v)
                | Leaf k v
                | E
    deriving (Show, Eq)


--a)

search :: Ord k => [k] -> TTree k v -> Maybe v
search l E = Nothing
search [] t = Nothing
search l t = searchAux l t

    where
        searchAux :: Ord k => [k] -> TTree k v -> Maybe v
        searchAux l E = Nothing
        searchAux [] (Node k v t1 tm td) = v
        searchAux l (Leaf k v) = if (head l) == k && (tail l) == [] then (Just v) else Nothing
        searchAux l t@(Node k v ti tm td) | (head l) < k = (searchAux l ti)
                                          | (head l) == k = if (tail l == []) then (searchAux (tail l) t) else (searchAux (tail l) tm)
                                          | (head l) > k = (searchAux l td)

--b)

-- Funcion auxiliar.
replace :: v -> TTree k v -> TTree k v
replace val E = E
replace val (Leaf k v) = (Leaf k val)
replace val (Node k v ti tm td) = (Node k (Just val) ti tm td)

insert :: Ord k => [k] -> v -> TTree k v -> TTree k v
insert [] v E = E
insert [k] v E = (Leaf k v)
insert [] v t = t

insert l val E = (Node (head l) Nothing E (insert (tail l) val E) E)

insert l val t@(Leaf k v) | (tail l) == [] && (head l) == k = replace val t

                          | (head l) < k && (tail l) == [] = (Node k (Just v) (Leaf (head l) val) E E)
                          | (head l) == k && (tail l) == [] = (Node k (Just v) E (Leaf (head l) val) E)
                          | (head l) > k && (tail l) == [] = (Node k (Just v) E E (Leaf (head l) val))

                          | (head l) < k  = (Node k (Just v) (insert l val E) E E)
                          | (head l) == k  = (Node k (Just v) E (insert (tail l) val E) E)
                          | (head l) > k  = (Node k (Just v) E E (insert l val E))

insert l val t@(Node k v ti tm td) | (tail l) == [] && (head l) == k = replace val t
                                   | (head l) < k = Node k v (insert l val ti) tm td
                                   | (head l) == k = Node k v ti (insert (tail l) val tm) td
                                   | (head l) > k = Node k v ti tm (insert l val td)

--c)

delete :: Ord k => [k] -> TTree k v -> TTree k v
delete l E = E
delete [] t = t
delete l t@(Leaf k v) = if (head l) == k && (tail l) == [] then E else t
delete l t@(Node k v ti tm td) | ((head l) == k) && ((tail l) == []) && (not (isEmpty tm)) = (Node k Nothing ti tm td)
                               | ((head l) == k) && ((tail l) == []) && (not (isEmpty ti)) && (isEmpty td) = ti
                               | ((head l) == k) && ((tail l) == []) && (isEmpty ti) && (not (isEmpty td)) = td
                               | ((head l) == k) && ((tail l) == []) && (not (isEmpty ti)) &&  (not (isEmpty td)) = (stickRight ti td)
                               | ((head l) < k) = (Node k v (delete l ti) tm td)
                               | ((head l) == k) = (Node k v ti (delete (tail l) tm) td)
                               | ((head l) > k) = (Node k v ti tm (delete l td))
        where

            isEmpty :: TTree k v -> Bool
            isEmpty E = True
            isEmpty _ = False

            -- Toma dos arboles y pone al segundo lo mas a la derecha posible en el primero
            -- respetando la propiedad de bst
            stickRight :: Ord k => TTree k v -> TTree k v -> TTree k v
            stickRight E E = E
            stickRight t E = t
            stickRight E t = t
            stickRight (Leaf k v) t2@(Leaf k2 _) | (k > k2) = (Node k (Just v) t2 E E)
                                                 | (k < k2) = (Node k (Just v) E E t2)

            stickRight (Leaf k v) t2@(Node k2 _ _ _ _) | (k > k2) = (Node k (Just v) t2 E E)
                                                       | (k < k2) = (Node k (Just v) E E t2)

            stickRight (Node k v ti tm td) t = (Node k v ti tm (stickRight td t))
                        
--d)

keys :: TTree k v -> [[k]]
keys E = []
keys (Leaf k v) = [[k]]
keys t@(Node k v ti tm td) = case v of 

    Nothing -> (keys ti) ++ (keysAux tm [k]) ++ (keys td)
    (Just v) -> (keys ti) ++ [[k]] ++ (keysAux tm [k]) ++ (keys td)

    where
        
        keysAux :: TTree k v -> [k] -> [[k]]
        keysAux E l = []
        keysAux (Leaf k v) l = [(l ++ [k])] 
        keysAux (Node k Nothing ti tm td) l = (keysAux ti l) ++ (keysAux tm (l ++ [k])) ++ (keysAux td l)
        keysAux (Node k v ti tm td) l = let claveMedio = [(l ++ [k])] in (keysAux ti l) ++ claveMedio ++ (keysAux tm (l ++ [k])) ++ (keysAux td l)                    

--e)

class Dic k v d | d -> k v where
    vacio :: d
    insertar :: Ord k => k -> v -> d -> d
    buscar :: Ord k => k -> d -> Maybe v
    eliminar :: Ord k => k -> d -> d
    claves :: Ord k => d -> [k]

 
instance Ord k => Dic [k] v (TTree k v) where
    vacio = E

    insertar = insert

    buscar = search

    eliminar = delete

    claves = keys
