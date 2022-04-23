module Main where

data Row =
  Row
    { rowChar :: Char
    , rowRange :: (Int, Int)
    , rowPassword :: String
    }
  deriving (Show)

tail' :: [a] -> [a]
tail' (_:xs) = xs
tail' [] = []

splitOn :: Eq a => a -> [a] -> [[a]]
splitOn _ [] = []
splitOn d s = x : splitOn d (tail' s')
  where
    (x, s') = span (/= d) s

sample :: String
sample = "1-3 a: abcde"

rowFromString :: String -> Row
rowFromString s = Row c (read low, read high) password
  where
    [policy, ' ':password] = splitOn ':' s
    [range, c:_] = splitOn ' ' policy
    [low, high] = splitOn '-' range

isCorrect :: Row -> Bool
isCorrect (Row c (low, high) password) = low <= n && n <= high
  where
    n = length $ filter (== c) password

main :: IO ()
main =
  interact $
  (++ "\n") . show . length . filter isCorrect . map rowFromString . lines
