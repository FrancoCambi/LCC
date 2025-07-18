module Ej22025 where

import Seq
import ArrSeq

fibSeq :: Seq s => Int -> s Int
fibSeq n =
  let f (a, b) _ = (a + b, a)  -- Recurrencia: genera el siguiente par
      neutro = (1, 0)        -- Corresponde a (F₁, F₀)
      dummyInput = tabulateS (\_ -> (0, 0)) n  -- no importa el contenido
      (pares, _) = scanS f neutro dummyInput
  in mapS snd pares

test :: Arr Int
test = fibSeq 50