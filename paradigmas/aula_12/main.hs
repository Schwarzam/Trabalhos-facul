-- Escreva uma função para concatenar uma lista de listas. Utilizar casamento de padrões.
concatenar [] = []
concatenar (x : xs) = x ++ concatenar xs

-- Dada uma lista de inteiros, escreva uma função que some todos os elementos. Não utilize a função sum.
soma [] = 0
soma (x : xs) = x + soma xs

-- Escreva uma função para verificar se um número está na lista na lista de inteiros
check :: [Int] -> Int -> IO ()
check list x =
  print (x `elem` list)

-- Usando expressões case, faça uma função que receba um número n, e uma lista L, devolva os n elementos de L.
nElements :: Int -> [a] -> [a]
nElements n list =
  case list of
    [] -> []
    [x] -> [x]
    (x : xs) -> take n list

-- Fazer uma função para concatenar uma lista de listas. Neste exercício deve-se usar, necessariamente, notação em compreensão.
concatenarCompreensao :: [[a]] -> [a]
concatenarCompreensao xss = [x | xs <- xss, x <- xs]

-- Escreva uma função que verifique se uma lista está em ordem crescente.
crescente :: (Ord a) => [a] -> Bool
crescente [] = True
crescente [x] = True
crescente (x : y : xs) = x <= y && crescente (y : xs)

main :: IO ()
main =
  print (crescente [0, 5, 2, 3])