from math import factorial
import sys
import time

if __name__ == '__main__':
    start_time = time.time()
    sys.set_int_max_str_digits(1000000000)
    with open('ans.txt', 'w') as f:
        f.write(str(factorial(100000)))
        
    end_time = time.time()
    print("Time taken:", end_time - start_time, "seconds")