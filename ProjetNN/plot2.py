from matplotlib import *
from pylab import *
from itertools import combinations
import os
from optparse import OptionParser
import numpy as np

parser = OptionParser()
parser.add_option("-i", "--input", action = "store")
parser.add_option("-c", "--column", action = "store")
(options, args) = parser.parse_args()

data = np.loadtxt(options.input)

ticks_size = 15
###########
subplot(311)
tick_params(labelsize = ticks_size)
for i in range(1, 6):
    plot(data[:,0], data[:,i], linewidth = 1.5)
grid()
ylabel("Gate Values", fontsize = 16)
yticks([0.25, 0.5, 0.75, 1])
##########
subplot(312)
tick_params(labelsize = ticks_size)
for i in range(8, 12):
    plot(data[:,0], data[:,i], linewidth = 1.5)
grid()
ylabel("Error", fontsize = 16)
########
subplot(313)
tick_params(labelsize = ticks_size)
plot(data[:,0], data[:,6], linewidth = 1.5)

for i in range(20):
    axvspan(100+i*800, 150+i*800, facecolor='g', alpha=0.3)
    axvspan(190+i*800, 245+i*800, facecolor='b', alpha=0.3)
    axvspan(320+i*800, 350+i*800, facecolor='g', alpha=0.3)
    axvspan(500+i*800, 540+i*800, facecolor='g', alpha=0.3)
    axvspan(580+i*800, 620+i*800, facecolor='b', alpha=0.3)
    axvspan(660+i*800, 710+i*800, facecolor='g', alpha=0.3)
    
xlabel("Iterations", fontsize = 16)
ylabel("Winning Gate", fontsize = 16)
#xlim(0, 1400)  
ylim(-0.5, 4.5)
yticks(range(0, 5))
grid()


show()
