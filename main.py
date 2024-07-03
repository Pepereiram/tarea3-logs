from bloom import BloomFilter as bf
from primePy import primes as pr
import csv
import random
import math
from timeit import default_timer as timer

def searchCsv(name):
  '''
  Busqueda del str 'name' en el csv de nombres populares.
  '''
  df = csv.reader(open('Popular-Baby-Names-Final.csv', "r", encoding='utf8'), delimiter=",")
  for row in df:
    if row[0] == name:
      return True

  return False

def bloomTest(size, _m, _k):
  print('######## Inicializando test con N = 2^',size,' ########')
  N = 1 << size # Busquedas

  # * Listas con los nombres
  babyNames = csv.reader(open('Popular-Baby-Names-Final.csv', "r", encoding='utf8'), delimiter=",")
  lenBabyNames = sum(1 for row in babyNames) - 1
  m = _m * lenBabyNames # Bits
  k = math.ceil(_k)

  # * Genero k primos, uno por cada hash
  primeFloor = 29791 # Numero muy utilizado en progcomp para este hash
  primeBound = 30030 # Con el maximo, k no pasa de este numero
  primesList = pr.between(primeFloor, primeBound)
  primesList = primesList[0:k]

  # * Inicializar bloom filter
  bloom = bf(m, primesList, k)

  
  # * Añado los nombres al bloom
  babyNames = csv.reader(open('Popular-Baby-Names-Final.csv', "r", encoding='utf8'), delimiter=",")
  for name in babyNames:
    if name[0] == 'Name':
      pass
    bloom.add(name[0])

  #todo: creo arr de busqueda
  search = []
  alpha = 0.2 # porcentaje de arr con nombres falsos
  moviesTotal = math.ceil(alpha * N) # cantidad de nombres falsos
  namesTotal = N - moviesTotal # cantidad de nombres
  filmCount = 0 # contador de nombres falsos
  namesCount = 0 # contador de nombres

  while filmCount < moviesTotal:
    filmNames = csv.reader(open('Film-Names.csv', "r", encoding='utf8'), delimiter=",")
    for filmName in filmNames:
      if type(filmName[0]) != str: # evita problemas de NA
        pass
      if filmCount == moviesTotal:
        break
      search.append(filmName[0])
      filmCount += 1

  while namesCount < namesTotal:
    babyNames = csv.reader(open('Popular-Baby-Names-Final.csv', "r", encoding='utf8'), delimiter=",")
    for babyName in babyNames:
      if babyName[0] == 'Name' or type(babyName[0]) != str: # evita problemas de NA y salta nombre de col
        pass
      if namesCount == namesTotal:
        break
      search.append(babyName[0])
      namesCount += 1
  random.shuffle(search) # simula busquedas reales, no es obligatorio

  # * Busco en el bloom
  negative = 0 # Bloom dice que no esta
  falsePositive = 0 # bloom dice que está pero es mentira

  start = timer() # inicio timer en segundos
  for i in range(len(search)):
    name = search[i]
    inBloom = bloom.check(name) # busco en filtro

    # Si está en filtro, busco
    if (inBloom):
      inNames = searchCsv(name) # busca en el csv

      # Si no encontre, entonces era una pelicula
      if not inNames:
        falsePositive += 1

    # Si no esta en filtro, cuento y sigo y sigo    
    else:
      negative += 1
      
  end = timer() # termino timer
  print('search done at: ', 1000 * (end - start), ' miliseconds') # print en ms

  fp = falsePositive / (falsePositive + negative) # calculo false positive
  print('La tasa de fp con m: ', m, ' y k: ', k, ' es: ', fp, '\n')

  print('brute search')
  start = timer()
  for i in range(len(search)):
    searchCsv(search[i])
  end = timer()
  
  print('search done at: ', 1000 * (end - start), ' miliseconds')

  return

def test(m, k):
  sizes = [15,16,17]

  for i in range(len(sizes)):
    bloomTest(sizes[i], m, k)

  return

def main():

  mList = [5, 10 ,20]
  kList = [0.5, math.log(2), 1] # (m)*este K
  pairs = []
  for m in mList:
    for k in kList:
      pairs.append([m, m*k]) # m = numero * N entonces m/N = m

  for pair in pairs:
    print('--------------- EMPEZANDO TEST CON EL PAR',pair,'---------------')
    test(pair[0], pair[1])
  return

main()