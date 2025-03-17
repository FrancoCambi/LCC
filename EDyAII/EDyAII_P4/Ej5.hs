data Color = R | B
    deriving Show
data RBT a = E | T Color (RBT a) a (RBT a)
    deriving Show
data OTTT a = O | T2 a (OTTT a) (OTTT a) | T3 a a (OTTT a) (OTTT a) (OTTT a) 
                | T4 a a a (OTTT a) (OTTT a) (OTTT a) (OTTT a)
    deriving Show


parseOTTT :: RBT a -> OTTT a
parseOTTT E = O
parseOTTT (T B (T R l2 a2 r2) a1 (T R l3 a3 r3)) = T4 a2 a1 a3 (parseOTTT l2) (parseOTTT r2) (parseOTTT l3) (parseOTTT r3)
parseOTTT (T B (T R l2 a2 r2) a1 r1) = T3 a2 a1 (parseOTTT l2) (parseOTTT r2) (parseOTTT r1)
parseOTTT (T B l1 a1 (T R l2 a2 r2)) = T3 a1 a2 (parseOTTT l1) (parseOTTT l2) (parseOTTT r2)
parseOTTT (T B l a r) = T2 a (parseOTTT l) (parseOTTT r)


testTree = T B (T B (T R E 0 E) 1 E) 2 (T R E 3 E)