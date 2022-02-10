import Data.List (nub)
import Data.Maybe (fromJust)


type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not(Var "P") :&: Not(Var "Q"))

p3 :: Prop
p3 =  (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not(Var "P"):|: Not(Var "Q")):&:(Not(Var"P"):|:Not(Var"R")))

instance Show Prop where
  show (Var p) = p
  show T = "True"
  show F = "False"
  show (Not a) = "(~" ++ show a ++ ")"
  show (a :|: b) = "(" ++ show a ++ "|"  ++ show b ++ ")"
  show (a :&: b) = "(" ++ show a ++ "&" ++ show b ++ ")"
 
test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval (Var x) list = impureLookup x list
eval (Not (Var x)) list = not (eval (Var x) list)
eval (x :&: y) list = eval x list && eval y list
eval (x :|: y) list = eval x list || eval y list
eval T list = True
eval F list = False 
 
test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

variabile :: Prop -> [Nume]
variabile (Var p) = [p]
variabile (Not p)=nub $ variabile p
variabile (p :|: q)=nub $ variabile p ++ variabile q
variabile (p :&: q)=nub $ variabile p ++ variabile q
variabile _ = []
 
test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env]
envs [] = []
envs [x] = [[(x, False)], [(x, True)]]
envs (hd : xs) = map (\x -> (hd, False) : x) (envs xs) ++ map (\x -> (hd, True) : x) (envs xs)
 
test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

satisfiabila :: Prop -> Bool
satisfiabila p = or $ map (eval p) $ envs (variabile p)

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False


valida :: Prop -> Bool
valida = undefined

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

echivalenta :: Prop -> Prop -> Bool
echivalenta p q= all (\env -> eval (p :<->: q) env) $ envs $ nub $ variabile p ++ variabile q

test_echivalenta1 =
  True
  == (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))

test_echivalenta2 = 
  False
  == (Var "P") `echivalenta` (Var "Q")

test_echivalenta3 =
  True
  == (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))