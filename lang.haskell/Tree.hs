module Tree (
  Tree (Leaf, Branch)
, fringe
, treeMap
, treeFold
)
where 

data Tree a 
  = Leaf a 
  | Branch (Tree a) (Tree a) 
  deriving (Show)

fringe :: Tree a -> [a] 
fringe (Leaf x) = [x] 
fringe (Branch left right) = fringe left ++ fringe right

treeMap :: (a -> b) -> Tree a -> Tree b
treeMap f (Leaf x) = Leaf (f x)
treeMap f (Branch left right) = Branch(treeMap f left) (treeMap f right)

treeFold :: (b -> b -> b) -> (a -> b) -> Tree a -> b
treeFold fbranch fleaf = g where
  g (Leaf x) = fleaf x
  g (Branch left right) = fbranch (g left) (g right)
