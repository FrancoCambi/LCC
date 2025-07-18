module ArrSeq (Arr, emptyArr, singletonArr, lengthArr, nthArr, tabulateArr, mapArr, 
filterArr, appendArr, takeArr, dropArr, showtArr, showlArr, 
joinArr, reduceArr, scanBueno, fromListArr) where

import Seq
import Par

import qualified Arr as A
import Arr ((!))
import Arr (Arr) 

data Tree a = Leaf a | Node (Tree a) (Tree a)

instance Seq Arr where

  emptyS     = emptyArr  
  singletonS = singletonArr
  lengthS    = lengthArr
  nthS       = nthArr
  tabulateS  = tabulateArr
  mapS       = mapArr
  filterS    = filterArr
  appendS    = appendArr
  takeS      = takeArr
  dropS      = dropArr
  showtS     = showtArr
  showlS     = showlArr
  joinS      = joinArr
  reduceS    = reduceArr
  scanS      = scanBueno
  fromList   = fromListArr


emptyArr :: Arr a
emptyArr = A.empty

singletonArr :: a -> Arr a
singletonArr x = A.fromList [x]

lengthArr :: Arr a -> Int
lengthArr = A.length

nthArr :: Arr a -> Int -> a
nthArr ar i = ar ! i

tabulateArr :: (Int -> a) -> Int -> Arr a 
tabulateArr = A.tabulate

mapArr :: (a -> b) -> Arr a -> Arr b
mapArr f arr = (fromListArr [(f (arr ! i)) | i <- [0..(lengthArr arr) - 1]])

filterArr :: (a -> Bool) -> Arr a -> Arr a
filterArr f arr = (fromListArr [arr ! i | i <- [0..(lengthArr arr) - 1], (f (arr ! i)) == True])

appendArr :: Arr a -> Arr a -> Arr a
appendArr a b = (A.append) a b

takeArr :: Arr a -> Int -> Arr a
takeArr arr n = (fromListArr [arr ! i | i <- [0..(min (lengthArr arr) n) - 1]])

dropArr :: Arr a -> Int -> Arr a
dropArr arr n = (fromListArr [arr ! i | i <- [n..(lengthArr arr) - 1]])

showtArr :: Arr a -> TreeView a (Arr a)
showtArr arr | (lengthArr arr) == 0 = EMPTY
             | (lengthArr arr) == 1 = ELT (arr ! 0)
             | otherwise = NODE (takeArr arr p) (dropArr arr p)
        where 
            p = if (even (lengthArr arr)) then (div (lengthArr arr) 2) else (div (lengthArr arr - 1) 2)

showlArr :: Arr a -> ListView a (Arr a)
showlArr = undefined

joinArr :: Arr (Arr a) -> Arr a
joinArr arr = (A.flatten) arr

reduceArr :: (a -> a -> a) -> a -> Arr a -> a
reduceArr f b arr | (lengthArr arr) == 0 = b
                  | otherwise = (f b v)

    where
        v = reduceT f (toTree arr)

            where
                toTree :: Arr a -> Tree a
                toTree arr | (lengthArr arr) == 1 = (Leaf (arr ! 0))
                           | otherwise = let (l', r') = let pp = if (even (lengthArr arr)) then p else p - 1 in (toTree (takeArr arr p)) ||| (toTree (dropArr arr p))
                                        in (Node l' r')
                    where
                        p = if (even (lengthArr arr)) then (div (lengthArr arr) 2) else (div ((lengthArr arr) + 1) 2)
                
                reduceT :: (a -> a -> a) -> Tree a -> a
                reduceT f (Leaf x) = x
                reduceT f (Node l r) = let (l', r') = (reduceT f l) ||| (reduceT f r)
                                       in (f l' r')

toList :: Seq s => s a -> [a]
toList s = map (nthS s) [0 .. lengthS s - 1]

scanBueno :: (a -> b -> a) -> a -> Arr b -> (Arr a, a)
scanBueno f b arr =
  let n = lengthArr arr
      go i acc
        | i == n    = []
        | otherwise = 
            let xi = nthArr arr i
                acc' = f acc xi
            in acc : go (i+1) acc'
      accList = go 0 b
      final = foldl f b (toList arr)
  in (fromList accList, final)


fromListArr :: [a] -> Arr a
fromListArr = A.fromList

suma :: Integer -> Integer -> Integer
suma a b = a + b

t1 = fromListArr [1..4]

ts = fromListArr [fromListArr [1..5], fromListArr [6..10]]