import System.Win32 (COORD(yPos))
type Name = String

data  Value  =  VBool Bool
     |VInt Int
     |VFun (Value -> Value)
     |VError

data  Hask  = HTrue | HFalse
     |HIf Hask Hask Hask
     |HLit Int
     |Hask :==: Hask
     |Hask :+:  Hask
     |HVar Name
     |HLam Name Hask
     |Hask :$: Hask

infix 4 :==:
infixl 6 :+:
infixl 9 :$:

type  HEnv  =  [(Name, Value)]

instance Show Value where
     show(VBool n) = show n
     show(VInt n) = show n
     show(VFun _) = "Nu se pot afisa functii"
     show(VError) = "Nu se pot afisa erori"

instance Eq Value where
     VBool x == VBool y = (x == y)
     VInt x == VInt y = (x == y)
     VFun x == VFun y = error "Eroare"
     VError == VError = error "Eroare"
     _ == _ = False

hEval :: Hask -> HEnv -> Value
hEval HTrue r      =  VBool True
hEval HFalse r        =  VBool False
hEval (HIf c d e) r   = hif (hEval c r) (hEval d r) (hEval e r)
  where  hif (VBool b) v w  =  if b then v else w
         hif _ _ _ = VError
hEval _ _ = undefined

run :: Hask -> String
run pg = show (hEval pg [])
