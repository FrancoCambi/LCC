data CList a = EmptyCL | CUnit a | Consnoc a (CList a) a
                deriving Show

headCL :: CList a -> a
headCL EmptyCL = error "No definido para listas vacias."
headCL (CUnit a) = a
headCL (Consnoc a1 list a2) = a1

tailCL :: CList a -> CList a
tailCL EmptyCL = error "No definido para listas vacias."
tailCL (CUnit a) = EmptyCL
tailCL (Consnoc a1 EmptyCL a2) = CUnit a2
tailCL (Consnoc a1 list a2) = Consnoc (headCL list) (tailCL list) a2

isEmptyCL :: CList a -> Bool
isEmptyCL EmptyCL = True
isEmptyCL _ = False

isCUnit :: CList a -> Bool
isCUnit (CUnit a) = True
isCUnit _ = False

reverseCL :: CList a -> CList a
reverseCL EmptyCL = EmptyCL
reverseCL (CUnit a) = CUnit a
reverseCL (Consnoc a1 list a2) = Consnoc a2 (reverseCL list) a1

dropLastCL :: CList a -> CList a
dropLastCL EmptyCL = EmptyCL
dropLastCL (CUnit a) = EmptyCL
dropLastCL arg@(Consnoc a1 list a2) = reverseCL (tailCL (reverseCL arg))

inits :: CList a -> CList (CList a)
inits EmptyCL = EmptyCL
inits (CUnit a) = Consnoc EmptyCL EmptyCL (CUnit a)
inits arg@(Consnoc a1 list a2) = Consnoc EmptyCL (tailCL (inits (dropLastCL arg))) arg

lasts :: CList a -> CList (CList a)
lasts EmptyCL = EmptyCL
lasts (CUnit a) = Consnoc (CUnit a) EmptyCL EmptyCL
lasts arg@(Consnoc a1 list a2) = Consnoc arg (dropLastCL (lasts (tailCL arg))) EmptyCL

lastCL :: CList a -> a
lastCL EmptyCL = error "No definido para listas vacias"
lastCL (CUnit a) = a
lastCL (Consnoc a1 list a2) = a2

concat2CL :: CList a -> CList a -> CList a
concat2CL EmptyCL EmptyCL = EmptyCL
concat2CL EmptyCL l2 = l2
concat2CL l1 EmptyCL = l1
concat2CL (CUnit a1) (CUnit a2) = Consnoc a1 EmptyCL a2
concat2CL (CUnit a1) l2 = Consnoc a1 (dropLastCL l2) (lastCL l2)
concat2CL l1 (CUnit a2) = Consnoc (headCL l1) (tailCL l1) a2
concat2CL l1 l2 = Consnoc (headCL l1) (concat2CL (tailCL l1) (dropLastCL l2)) (lastCL l2)

concatCL :: CList (CList a) -> CList a
concatCL EmptyCL = EmptyCL
concatCL (CUnit (CUnit a)) = CUnit a
concatCL (CUnit (Consnoc a1 list a2)) = Consnoc a1 list a2
concatCL arg@(Consnoc l1 EmptyCL l2) = concat2CL l1 l2
concatCL arg@(Consnoc l1 list EmptyCL) = (concatCL (Consnoc l1 (dropLastCL list) (lastCL list)))
concatCL arg@(Consnoc EmptyCL list l2) = (concatCL (Consnoc (headCL list) (tailCL list) l2))
concatCL arg@(Consnoc l1 list l2) = Consnoc (headCL l1) (concatCL (Consnoc (tailCL l1) list (dropLastCL l2))) (lastCL l2)

test1 = CUnit 1
test12 = Consnoc 1 EmptyCL 2
test123 = Consnoc 1 (CUnit 2) 3
test1234 = Consnoc 1 (Consnoc 2 EmptyCL 3) 4

testLista = Consnoc test1234 (CUnit test123) test123
