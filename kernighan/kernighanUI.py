#sg
from kernighan import *

def main(argv):
    k = Kernighan("data/se.txt")
    '''the candidates dict has a set for each type of mistakes that can happen'''

    while(1):
        ip = raw_input("> ")
        if(ip == "exit"):
            return
        for iw in str(ip).split(' '):
            print k.correction(iw)
    end


if __name__ == "__main__":
    main(sys.argv[0:])
