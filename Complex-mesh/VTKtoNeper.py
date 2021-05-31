#!/usr/bin/env python
import sys
import numpy as np

vtk_file=sys.argv[1]
orientation_file=sys.argv[2]

micro=np.loadtxt(vtk_file,skiprows=10)
ss=micro.shape

a_file = open(vtk_file)
for position, line in enumerate(a_file):
  if position==6:
        break


dim=np.float64(line.split()[1])

orientation=np.loadtxt(orientation_file,skiprows=10)


uni_g=np.unique(micro.flatten())

micro2=np.zeros(ss)
k=1
for ig in uni_g:
    idx,idy=np.where(micro==ig)
    micro2[idx,idy]=k
    k=k+1


new_mi=np.transpose(micro2).flatten()



tesr_out=open(vtk_file[0:-4]+'.tesr','w')
tesr_out.write('***tesr\n')
tesr_out.write(' **format\n')
tesr_out.write('   2.0 ascii\n')
tesr_out.write(' **general\n')

tesr_out.write('   2\n')
tesr_out.write('   '+str(ss[0])+' '+str(ss[1])+'\n')
tesr_out.write('   '+str(dim)+' '+str(dim)+'\n')


tesr_out.write('  *hasvoid 0\n')
tesr_out.write(' **cell\n')
tesr_out.write('   '+str(len(uni_g))+'\n')
tesr_out.write('  *id\n')
tesr_out.write('  ')
for ig in range(len(uni_g)):
    tesr_out.write(' '+str(int(ig+1)))
tesr_out.write('\n')
tesr_out.write('  *ori\n')
tesr_out.write('   rodrigues:active\n')

for i in range(len(orientation)):
    tesr_out.write('   '+str(orientation[i,2])+' '+str(orientation[i,3])+' '+str(orientation[i,4])+'\n')

tesr_out.write(' **data\n')
for i in range(len(new_mi)):
    tesr_out.write(str(int(new_mi[i])))
    if np.mod(i+1,ss[0])==0:
        tesr_out.write('\n')
    else:
        tesr_out.write(' ')


tesr_out.write('\n')
tesr_out.write('***end')




tesr_out.close()
