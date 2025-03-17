data Color = R | B
    deriving Show
data RBT a = E | T Color (RBT a) a (RBT a)
    deriving Show


lbalance :: Color -> RBT a -> a -> RBT a -> RBT a
lbalance B (T R (T R a x b) y c) z d = T R (T B a x b) y (T B c z d)
lbalance B (T R a x (T R b y c)) z d = T R (T B a x b) y (T B c z d)
lbalance c l a r = T c l a r

rbalance :: Color -> RBT a -> a -> RBT a -> RBT a
rbalance B a x (T R (T R b y c) z d) = T R (T B a x b) y (T B c z d)
rbalance B a x (T R b y (T R c z d)) = T R (T B a x b) y (T B c z d)
rbalance c l a r = T c l a r

insert :: Ord a => a -> RBT a -> RBT a
insert x t = makeBlack (ins x t)
    where ins x E = T R E x E
          ins x (T c l y r) | x < y = lbalance c (ins x l) y r
                            | x > y = rbalance c l y (ins x r)
                            | otherwise = T c l y r
          makeBlack E = E
          makeBlack (T _ l x r) = T B l x r


        
testTree = T B (T B E 1 E) 2 (T R E 3 E)