import numpy as np


def dir_vec(A,B):
  return B-A

def norm_vec(A,B):
  return omat@dir_vec(A,B)

#Generate line points
def line_gen(A,B):
  len =10
  x_AB = np.zeros((2,len))
  lam_1 = np.linspace(0,1,len)
  for i in range(len):
    temp1 = A + lam_1[i]*(B-A)
    x_AB[:,i]= temp1.T
  return x_AB

#Centre and Radius  of the circumcircle
def ccircle(A,B,C):
  p = np.zeros(2)
  n1 = dir_vec(B,A)
  p[0] = 0.5*(np.linalg.norm(A)**2-np.linalg.norm(B)**2)
  n2 = dir_vec(C,B)
  p[1] = 0.5*(np.linalg.norm(B)**2-np.linalg.norm(C)**2)
  #Intersection
  N=np.vstack((n1,n2))
  O=np.linalg.inv(N)@p
  r = np.linalg.norm(A -O)
  return O,r

#Intersection
def line_intersect(n1,c1,n2,c2):
  N=np.vstack((n1,n2))
  p = np.zeros(2)
  p[0] = c1
  p[1] = c2
  P=np.linalg.inv(N)@p
  return P

#y intercept
def y_icept(n,c):
  A = np.zeros(2)
  m_y = np.array([0,1])
  A[0] = 0
  A[1] = c/(n@m_y)
  return A

#Generate line points
def line_dir_pt(m,A,k1,k2):
  len =10
  x_AB = np.zeros((2,len))
  lam_1 = np.linspace(k1,k2,len)
  for i in range(len):
    temp1 = A + lam_1[i]*m
    x_AB[:,i]= temp1.T
  return x_AB

dvec = np.array([-1,1]) 
omat = np.array([[0,1],[-1,0]]) 



