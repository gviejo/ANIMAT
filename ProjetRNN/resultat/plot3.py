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
ticks_size = 15

#################
data = np.loadtxt("resultats5/resultats_tour_1.txt")
subplot(311)
tick_params(labelsize = ticks_size)
for i in range(2, 7):
    plot(data[:,0], data[:,i], linewidth = 1.5)
grid()
ylabel("Gate Values", fontsize = 16)
xlim(0, 57000)
yticks([0.25, 0.5, 0.75, 1])
for i in range(20):
    axvspan(400+i*2850, 550+i*2850, facecolor='g', alpha=0.2)
    axvspan(1180+i*2850, 1320+i*2850, facecolor='g', alpha=0.2)
    axvspan(1850+i*2850, 1980+i*2850, facecolor='g', alpha=0.2)
    axvspan(2600+i*2850, 2750+i*2850, facecolor='g', alpha=0.2)
    axvspan(750+i*2850, 990+i*2850, facecolor='b', alpha=0.2)
    axvspan(2220+i*2850, 2400+i*2850, facecolor='b', alpha=0.2)
##################
data = np.loadtxt("resultats5/resultats_tour_2.txt")
subplot(312)
tick_params(labelsize = ticks_size)
for i in range(2, 7):
    plot(data[:,0], data[:,i], linewidth = 1.5)
grid()
ylabel("Gate Values", fontsize = 16)
xlim(0, 57000)
yticks([0.25, 0.5, 0.75, 1])
for i in range(20):
    axvspan(400+i*2850, 550+i*2850, facecolor='g', alpha=0.2)
    axvspan(1180+i*2850, 1320+i*2850, facecolor='g', alpha=0.2)
    axvspan(1850+i*2850, 1980+i*2850, facecolor='g', alpha=0.2)
    axvspan(2600+i*2850, 2750+i*2850, facecolor='g', alpha=0.2)
    axvspan(750+i*2850, 990+i*2850, facecolor='b', alpha=0.2)
    axvspan(2220+i*2850, 2400+i*2850, facecolor='b', alpha=0.2)
##################
data = np.loadtxt("resultats5/resultats_tour_3.txt")
subplot(313)
tick_params(labelsize = ticks_size)
for i in range(2, 7):
    plot(data[:,0], data[:,i], linewidth = 1.5)
grid()
ylabel("Gate Values", fontsize = 16)
xlim(0, 57000)
yticks([0.25, 0.5, 0.75, 1])
for i in range(20):
    axvspan(400+i*2850, 550+i*2850, facecolor='g', alpha=0.2)
    axvspan(1180+i*2850, 1320+i*2850, facecolor='g', alpha=0.2)
    axvspan(1850+i*2850, 1980+i*2850, facecolor='g', alpha=0.2)
    axvspan(2600+i*2850, 2750+i*2850, facecolor='g', alpha=0.2)
    axvspan(750+i*2850, 990+i*2850, facecolor='b', alpha=0.2)
    axvspan(2220+i*2850, 2400+i*2850, facecolor='b', alpha=0.2)


show()
