data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)

instance Show Expr where
     show (Const n) = show n
     show (e1 :+: e2) = "(" ++ show e1 ++ "+" ++ show e2 ++ ")"
     show (e1 :*: e2) = "(" ++ show e1 ++ "" ++ show e2 ++ ")"

evalExp :: Expr -> Int
evalExp (Const n) = n
evalExp (e1 :+: e2) = (evalExp e1) + (evalExp e2)
evalExp (e1 :*: e2) = (evalExp e1) * (evalExp e2)

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16


expToArb :: Expr -> Tree
expToArb (Const n) = Lf n
expToArb (a :+: b) = Node Add (expToArb a) (expToArb b)
expToArb (a :*: b) = Node Mult (expToArb a) (expToArb b)

evalArb :: Tree -> Int
evalArb (Lf n)= n
evalArb (Node Add a b) = evalArb a + evalArb b
evalArb (Node Mult a b) = evalArb a * evalArb b

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

class Collection c where
  empty :: c key value
  singleton :: key -> value -> c key value
  insert
      :: Ord key
      => key -> value -> c key value -> c key value
  clookup :: Ord key => key -> c key value -> Maybe value
  delete :: Ord key => key -> c key value -> c key value
  keys :: c key value -> [key]
  keys c = map fst $ toList c

  values :: c key value -> [value]
  values c = map snd $ toList c
  toList :: c key value -> [(key, value)]
  fromList :: Ord key => [(key,value)] -> c key value
  fromList [] = empty
  fromList ((k, v):xs) = insert k v (fromList xs)
  
newtype PairList k v
  = PairList { getPairList :: [(k, v)] }


data SearchTree key value
  = Empty
  | BNode
      (SearchTree key value) -- elemente cu cheia mai mica
      key                    -- cheia elementului
      (Maybe value)          -- valoarea elementului
      (SearchTree key value) -- elemente cu cheia mai mare
