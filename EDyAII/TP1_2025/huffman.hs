module Huffman where

import Data.Map as DM (Map, fromList, insertWith, empty, foldrWithKey, lookup)
import Heap

{-  
Integrantes grupo:
- Franco Cambiaso
- Milton Pacheco
- 

-}

-- Bits y códigos

data Bit = Zero | One deriving (Eq, Show)

type Code = [Bit]

-- Árbol de codificación

data HTree = Leaf Char Int
           | Node HTree HTree Int
           deriving Show

weight :: HTree -> Int
weight (Leaf _ w)   = w
weight (Node _ _ w) = w

-- Diccionarios de frecuencias y códigos

type FreqMap = Map Char Int

type CodeMap = Map Char Code


-- Ejercicio 1

-- | Decimos que son iguales dos arboles de Huffman si tienen la misma frecuencia
-- | de los nodos hoja o la misma frecuencia de los nodos internos
-- | se puede restringir para que tambien los caracteres sean iguales
-- | pero no es necesario
instance Eq HTree where 
    (Leaf _ peso1) == (Leaf _ peso2) = peso1 == peso2 
    (Node _ _ peso1) == (Node _ _ peso2) = peso1 == peso2
    _ == _ = False

-- | Decimos que un arbol de Huffman es menor o igual que otro si su frecuencia
-- | es menor o igual que la frecuencia del otro
instance Ord HTree where
    (Leaf _ peso1) <= (Leaf _ peso2) = peso1 <= peso2
    (Leaf _ peso1) <= (Node _ _ peso2) = peso1 <= peso2
    (Node _ _ peso1) <= (Leaf _ peso2) = peso1 <= peso2
    (Node _ _ peso1) <= (Node _ _ peso2) = peso1 <= peso2


-- Ejercicio 2

buildFreqMap :: String -> FreqMap
buildFreqMap str = foldr (\c m -> DM.insertWith (+) c 1 m) DM.empty str

-- Ejercicio 3

buildHTree :: FreqMap -> HTree
buildHTree fm = buildHTreeAux (freqMapToHeap fm)

    where
        buildHTreeAux :: Heap (HTree) -> HTree
        buildHTreeAux h | isEmpty (deleteMin h) = findMin h
                        | otherwise = let min1 = findMin h
                                          min2 = findMin (deleteMin h)
                                          comb = Node min1 min2 (weight min1 + weight min2)
                                      in buildHTreeAux (insert comb (deleteMin (deleteMin h)))

        freqMapToHeap :: FreqMap -> Heap (HTree)
        freqMapToHeap fm = DM.foldrWithKey (\c f h -> (\tu he -> insert (Leaf (fst tu) (snd tu)) he) (c, f) h) Heap.empty fm

-- Ejercicio 4

buildCodeMap :: HTree -> CodeMap
buildCodeMap (Leaf c _) = fromList [(c, [Zero])]
buildCodeMap t = fromList (buildCodeMapAux t [] [] )
    
    where
        buildCodeMapAux :: HTree -> Code -> [(Char, Code)] -> [(Char, Code)]
        buildCodeMapAux (Leaf ch _) c m = m ++ [(ch, c)]
        buildCodeMapAux (Node l r _) c m = buildCodeMapAux l (c ++ [Zero]) m ++ buildCodeMapAux r (c ++ [One]) m

-- Ejercicio 5

encode :: CodeMap -> String -> Code
encode m s = foldr (\c acc -> fromMaybe (DM.lookup c m) ++ acc) [] s

    where 
        fromMaybe :: Maybe Code -> Code
        fromMaybe (Just c) = c
        fromMaybe Nothing = error "Char no presente en el CodeMap"

-- Ejercicio 6

decode :: HTree -> Code -> String
decode (Leaf c _) _ = [c]
decode t code = decodeAux t code t

    where
        decodeAux :: HTree -> Code -> HTree -> String
        decodeAux (Node l r _) [] _ = []
        decodeAux (Leaf c _) l root = c : decodeAux root l root
        decodeAux (Node l r _) (x:xs) root | x == Zero = decodeAux l xs root
                                           | otherwise = decodeAux r xs root


-- Ejercicio 7

engFM :: FreqMap
engFM = fromList [
    ('a', 691),
    ('b', 126),
    ('c', 235),
    ('d', 360),
    ('e', 1074),
    ('f', 188),
    ('g', 170),
    ('h', 515),
    ('i', 589),
    ('j', 13),
    ('k', 65),
    ('l', 340),
    ('m', 203),
    ('n', 571),
    ('o', 635),
    ('p', 163),
    ('q', 8),
    ('r', 506),
    ('s', 535),
    ('t', 766),
    ('u', 233),
    ('v', 83),
    ('w', 200),
    ('x', 13),
    ('y', 167),
    ('z', 6),
    (' ', 1370),
    (',', 84),
    ('.', 89)
    ]

-- 7-1) Usamos la función buildHTree para construir un Arbol de Huffman a partir del FreqMap dado
engHTree :: HTree
engHTree = buildHTree engFM

-- 7-2)

frases :: [String]
frases = ["in reading the lives of great men, i found that the first victory they won was over themselves... self discipline with all of them came first.",
        "every action we take, everything we do, is either a victory or defeat in the struggle to become what we want to be",
        "somewhere in the world there is a defeat for everyone. some are destroyed by defeat, and some made small and mean by victory. greatness lives in one who triumphs equally over defeat and victory.",
        "teamwork is the ability to work together toward a common vision. the ability to direct individual accomplishments toward organizational objectives. it is the fuel that allows common people to attain uncommon results.",
        "these advanced algorithms and models perform human tasks, like recognizing speech or images and making decisions.",
        "if fighting is sure to result in victory, than you must fight, even though the ruler forbid it if fighting will not result in victory, then you must not fight even at the rulers bidding.",
        "if a man achieves victory over this body, who in the world can exercise power over him",
        "victory at all costs, victory in spite of all terror, victory however long and hard the road may be for without victory, there is no survival.",
        "not all dreamers are winners, but all winners are dreamers. your dream is the key to your future.",
        "it is better to be feared than loved, if you cannot be both"]

comparar :: [String] -> [(Int, Int)]
comparar [] = []
comparar (x:xs) = let longitudFija = length x * 5
                      longitudArbol = length (encode (buildCodeMap engHTree) x)
                  in (longitudFija, longitudArbol) : comparar xs

-- 7-3) Podemos observar que en las frases testeadas, la diferencia en longitud entre la codificación con longitud fija de 5 bits por
-- carácter y la codificación de Huffman, es de aproximadamente un 15% (a favor de Huffman).
-- Ejecutar la función main o test para ver las diferencias.

test :: [(Int, Int)]
test = comparar frases

leafA :: HTree
leafA = Leaf 'a' 3

leafB :: HTree
leafB = Leaf 'b' 3

nodeAB :: HTree
nodeAB = Node leafA leafB 6

main :: IO ()
main = do
    print (leafA >= leafB)     -- True
    print (leafB >= nodeAB)    -- True
    print (nodeAB >= leafA)    -- False
    print test