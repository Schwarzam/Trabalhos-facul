
import Data.Char

-- Escreva uma função que verifique se uma lista está em ordem crescente.
crescente :: [Int] -> [Int]
crescente [] = []
crescente [x] = [x]

-- Escreva uma função que dado um elemento devolva a lista dos índices que esse elemento se encontra na lista. 
indices :: Eq a => a -> [a] -> [Int]
indices x ys = [i | (i, y)<- zip [0 .. n] ys, x == y]
 where n = length ys - 1


-- Escreva uma função que converta uma cadeia de caracteres em maiúsculas (Use a função toUpper() do módulo Char).
strUpper :: String -> String
strUpper str = map toUpper str


-- Escreva uma função chamada conta que conta a ocorrência de uma determinada letra em uma string
count :: Eq a => a -> [a] -> Int
count x = length . filter (==x)

-- Escreva uma função que usa um gerador para verificar se um número é primo. A função recebe como argumento um número natural maior que 1, se o número informado é primo é devolvido True e caso contrário False.
primo k = if k > 1 then null [ x | x <- [2..k - 1], k `mod` x == 0] else False

-- Dado um vetor de números inteiros, escreva a função quicksort que devolve um permutação do vetor com os elementos em ordem crescente.
quicksort :: Ord a => [a] -> [a]
quicksort []     = []
quicksort (p:xs) = (quicksort menor) ++ [p] ++ (quicksort maior)
    where
        menor  = filter (< p) xs
        maior = filter (>= p) xs

main :: IO ()
main =
  print(quicksort [1, 3, 4, 5, 2, 40, 30])