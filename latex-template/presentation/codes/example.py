#Code by GVV Sharma
#August 15, 2019
#released under GNU GPL
import numpy as np
import matplotlib.pyplot as plt
from coeffs import *
#from circumcentre import  ccircle

#if using termux
import subprocess
import shlex
#end if

#Generate line points
len = 100

#Given points
P = np.array([-2,4]) 
Q = np.array([0,2]) 

#Matrix equation
mat = np.array([[0,1],[1,-1]])
c =  np.array([2,-4]) 

#Circle centre and radius
O = np.linalg.inv(mat)@c
r = np.linalg.norm(O-P)
print(O,r)

#(i)
n_1 =  np.array([4,5]) 
c_1 =  6

#(ii)
n_2 =  np.array([2,-3]) 
c_2 =  -10

#(iii)
n_3 =  np.array([3,4]) 
c_3 =  3

#(iv)
n_4 =  np.array([5,2]) 
c_4 =  -4

if n_1@O == c_1:
	print('(i) is  a diameter')
else:
	print('(i) is not a diameter')

if n_2@O == c_2:
	print('(ii) is a diameter')
else:
	print('(ii) is not a diameter')

if n_3@O == c_3:
	print('(iii) is  a diameter')
else:
	print('(iii) is not a diameter')

if n_4@O == c_4:
	print('(iv) is  a diameter')
else:
	print('(iv) is not a diameter')


#Direction vectors of the lines
m_1 = omat@n_1
A_1 = y_icept(n_1,c_1)

m_2 = omat@n_2
A_2 =  y_icept(n_2,c_2)

m_3 = omat@n_3
A_3 =  y_icept(n_3,c_3)

m_4 = omat@n_4
A_4 =  y_icept(n_4,c_4)

k1=-1
k2=1

##Generating all lines
x_1= line_dir_pt(m_1,A_1,k1,k2)
x_2= line_dir_pt(m_2,A_2,k1,k2)
x_3= line_dir_pt(m_3,A_3,k1,k2)
x_4= line_dir_pt(m_4,A_4,k1,k2)


#Generating Circumcircle
theta = np.linspace(0,2*np.pi,len)
x_circ = np.zeros((2,len))
x_circ[0,:] = r*np.cos(theta)
x_circ[1,:] = r*np.sin(theta)
x_circ = (x_circ.T + O).T


#Plotting all lines
plt.plot(x_1[0,:],x_1[1,:],label='$(i)$')
plt.plot(x_2[0,:],x_2[1,:],label='$(ii)$')
plt.plot(x_3[0,:],x_3[1,:],label='$(iii)$')
plt.plot(x_4[0,:],x_4[1,:],label='$(iv)$')
plt.plot(x_circ[0,:],x_circ[1,:],label='$C$')
plt.plot(O[0], O[1], 'o')
plt.text(O[0] * (1 + 0.1), O[1] * (1 - 0.1) , 'O')

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')
#
#if using termux
plt.savefig('../figs/circle_diameter.pdf')
plt.savefig('../figs/circle_diameter.eps')
subprocess.run(shlex.split("termux-open ../figs/circle_diameter.pdf"))
#else
#plt.show()







