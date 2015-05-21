import os

inputfile=raw_input("cloud file(.ply):")
outputfile=raw_input("mesh file:(.ply)")

name=os.path.basename(inputfile).split('.')[0]

out_name=os.path.basename(outputfile).split('.')[0]

s=os.system(r'rm %s %s'%("*.vtk","*.pcd"))
s=os.system(r'pcl_ply2pcd.exe %s %s'%(inputfile,name+".pcd"))
s=os.system(r'pcl_poisson.exe %s %s -depth 10 '%(name+".pcd",out_name+".vtk"))
s=os.system(r'pcl_vtk2ply.exe %s %s'%(out_name+".vtk",outputfile))

s=os.system(r'rm %s %s'%("*.vtk","*.pcd"))
