module Lib 
  ( countScore
  ) where

countScore :: String -> Int
countScore txt = sum (map process (lines txt))

process :: String -> Int
process txt = sum (summ (proc (format (take 3) txt)) (format (drop 3) txt))

summ :: ([Int], [Int]) -> [Int] -> [Int]
summ (l1, l2) l3 = map (\(num, val) -> fst (foldl (check num val) (0, 1) l3)) (zip l1 l2)
  where
    check num val (c, seen) x
      | x == num  = (c + (val * seen), seen + 1)
      | otherwise = (c, seen)



proc :: [Int] -> ([Int], [Int])
proc l1 = (l2, zipWith (*) l3 l4)
  where
    l2     = removeDup (sort l1)
    l3     = map (\x -> 2 ^ (x `div` 10)) l2
    counts = countOcc l1 l2
    l4     = map (\c -> 2 ^ (c - 1)) counts

-- Formatting the string:
format :: ([String] -> [String]) -> String -> [Int]
format f txt = read <$> (f (words txt))


-- Insertion sort:
sort :: [Int] -> [Int]
sort [] = []
sort (x:xs) = insert x (sort xs)
  where
    insert y [] = [y]
    insert y (z:zs) = if y < z then y : z : zs else z : insert y zs


-- Removing duplicates.
removeDup :: [Int] -> [Int]
removeDup [] = []
removeDup (x:xs) = x : removeDup (filter (/= x) xs)


-- Counting number of occurrances
countOcc :: [Int] -> [Int] -> [Int]
countOcc l1 [] = []
countOcc l1 (x:xs) = length (filter (== x) l1) : countOcc l1 xs

