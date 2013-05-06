from matplotlib import *
from pylab import *
from itertools import combinations
import os
from optparse import OptionParser
import numpy as np
#from matplotlib.backends.backend_pdf import PdfPages

parser = OptionParser()
parser.add_option("-i", "--input", action = "store")
parser.add_option("-c", "--column", action = "store")
(options, args) = parser.parse_args()

data = np.loadtxt(options.input)

subplot(211)
for i in range(1, 6):
    plot(data[:,0], data[:,i], linewidth = 1.5)
for i in range(4):
    axvspan(400+i*2860, 550+i*2860, facecolor='g', alpha=0.3)
    axvspan(1180+i*2860, 1320+i*2860, facecolor='g', alpha=0.3)
    axvspan(1850+i*2860, 1980+i*2860, facecolor='g', alpha=0.3)
    axvspan(2600+i*2860, 2750+i*2860, facecolor='g', alpha=0.3)
    axvspan(750+i*2860, 990+i*2860, facecolor='b', alpha=0.3)
    axvspan(2220+i*2860, 2400+i*2860, facecolor='b', alpha=0.3)

subplot(212)
pl=plot(data[:,0], data[:,6], linewidth = 1.5)
for i in range(4):
    axvspan(400+i*2860, 550+i*2860, facecolor='g', alpha=0.3)
    axvspan(1180+i*2860, 1320+i*2860, facecolor='g', alpha=0.3)
    axvspan(1850+i*2860, 1980+i*2860, facecolor='g', alpha=0.3)
    axvspan(2600+i*2860, 2750+i*2860, facecolor='g', alpha=0.3)
    axvspan(750+i*2860, 990+i*2860, facecolor='b', alpha=0.3)
    axvspan(2220+i*2860, 2400+i*2860, facecolor='b', alpha=0.3)
xlabel("Iterations")
ylabel("Gate")
    
ylim(-1, 5)
grid()

show()
