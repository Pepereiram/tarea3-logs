from bitarray import bitarray
  
  # todo: Hay que adaptarla para poder calcular fp, no queremos darlo sino ver como reacciona para m  y k
  
class BloomFilter(object):
  
    '''
    Class for Bloom filter, using murmur3 hash function
    '''
  
    def __init__(self, m, primes, k):
        '''
        items_count : int
            Number of items expected to be stored in bloom filter
        fp_prob : float
            False Positive probability in decimal
        '''
  
        # Size of bit array to use
        self.size = m
  
        # number of hash functions to use
        self.hash_count = k
  
        # Bit array of given size
        self.bit_array = bitarray(self.size)
  
        # initialize all bits as 0
        self.bit_array.setall(0)

        #initialize prime numbers, no cambian despues de inicializarse
        self.primes = primes

    # Hash adaptado de https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
    # string: str a aplicar hashing
    # p numero primo
    # m numero primo grande.
    def hash(self, string, p):
        # total
        sum = 0
        # valor de m (no el mismo del bloom)
        m = 10**9 + 7
        # potencia de p, p^i
        p_pow = 1
        # Para cada caracter, calculamos el aporte al hash
        for i in range(len(string)):
            sum = (sum + (1 + ord(string[i]) - ord('a')) * p_pow) % m
            p_pow = (p_pow * p) % m
        
        return sum

    def add(self, string):
        '''
        Add an string in the filter
        '''
        digests = []

        # Cada de estos es un hash distinto
        for i in range(self.hash_count):
  
            # primes[i] permite crear distintos hashes
            digest = self.hash(string, self.primes[i]) % self.size
            digests.append(digest)
  
            # set the bit True in bit_array
            self.bit_array[digest] = True
  
    def check(self, string):
        '''
        Check for existence of an item in filter
        '''
        for i in range(self.hash_count):
            digest = self.hash(string, self.primes[i]) % self.size
            if self.bit_array[digest] == False:
  
                # if any of bit is False then,its not present
                # in filter
                # else there is probability that it exist
                return False
        return True