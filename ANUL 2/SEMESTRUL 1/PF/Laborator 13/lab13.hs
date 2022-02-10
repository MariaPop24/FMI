import Data.Monoid

elem1 :: (Foldable t, Eq a) => a -> t a -> Bool 
elem1 el t_a = getAny $ foldMap (\el_c -> Any (el_c == el)) t_a

elem2 :: (Foldable t, Eq a) => a -> t a -> Bool 
elem2 el t_a = foldr (\c ac -> (c == el) || ac) False t_a

nulll :: (Foldable t) => t a -> Bool 
nulll t_a = foldr (\_ ac -> ac + 1) 0 t_a == 0

nulll1 :: (Foldable t) => t a -> Bool 
nulll1 t_a = (getAny $ foldMap (\el_c -> Any( True )) t_a) == False

length :: (Foldable t) => t a -> Int
length t_a = foldr (\_ ac -> ac + 1) 0 t_a

length2 :: (Foldable t) => t a -> Int 
length2 t_a = getSum $ foldMap (\el -> Sum 1) t_a

toList :: (Foldable t) => t a -> [a]
toList t_a = foldr (\c ac -> c : ac) [] t_a

toList2 :: (Foldable t) => t a -> [a]
toList2 t_a = foldMap (\el -> [el]) t_a

fold :: (Foldable t, Monoid m) => t m -> m
fold = undefined -- Hint: folosiți foldMap

data Constant a b = Constant b

instance Foldable (Constant a) where
    foldMap f (Constant b1) = f b1

data Two a b = Two a b

instance Foldable (Two a) where
    foldMap f (Two _ b1) = f b1

data Three a b c = Three a b c

instance Foldable (Three a b) where
    foldMap f (Three _ _ c1) = f c1

data Three' a b = Three' a b b

instance Foldable (Three' a) where
    foldMap f (Three' _ b1 b2) = f b1 <> f b2

data Four' a b = Four' a b b b

instance Foldable (Four' a) where
    foldMap f (Four' _ b1 b2 b3) = f b1 <> f b2 <> f b3

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

instance Foldable (GoatLord) where
    foldMap f NoGoat = mempty 
    foldMap f (OneGoat a1) = f a1 
    foldMap f (MoreGoats g1 g2 g3) = foldMap f g1 <> foldMap f g2 <> foldMap f g3
