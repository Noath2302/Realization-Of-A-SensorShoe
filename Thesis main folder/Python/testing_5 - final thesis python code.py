#!/usr/bin/env python3
#----importing python modules----
import socket
import matplotlib.pyplot as plt
import numpy as np
#----declaring variables----
HOST = '192.168.137.1'				#the host name of the machine that run the server
try:
        HOST = socket.gethostbyname(socket.gethostname())
        print(HOST)
except:
        print("Unable to get host name")                
PORT = 22222						#the port that was used to make the socket

BLOCKSTREAM=120					#the data length used in representing the plot of the system 

dataList = []						#the List used to store all data
dataStream = []                                                                                       #the Steam used to update the plot area
lines = []
#----making the figure----
plt.style.use('dark_background')
fig,axs = plt.subplots(3,1)
fig.suptitle('SensorShoe Data', fontsize=16)
axs[0].set(xlabel = 'time', ylabel = 'angular velocity')
axs[0].set_ylim(-5,5)
axs[1].set(xlabel = 'time', ylabel = 'acceleration')
axs[1].set_ylim(-20,20)
axs[1].grid(b=None, which='major',axis='both')
axs[2].set(xlabel = 'time', ylabel = 'ground reaction force')
axs[2].set_ylim(2500,5000)
axs[2].grid(b=None, which='major',axis='both')

for i in range(3):
        axs[i].grid(b=True, which='major', color='#666666', linestyle='-')
        axs[i].minorticks_on()
        axs[i].grid(b=True, which='minor', color='#999999', linestyle='-', alpha=0.3)

fig.set_size_inches(5.56231,9)

time_ax = []						#time stamps of the data, in x axis
data_ax = []						#data represented on the y axis wrt time		

#----helping Function----
def listSplit(splitElement, dataN, ):
        newList=[]							#declare the returning list from function
        i=0
        j=0
        tempList = dataN.decode("utf-8").split(splitElement)
        for i in tempList:
                newList.append(i.split("\t"))
        for i in newList:
                for j in reversed(i):
                        if(j==''):
                                i.remove(j)
        for i in range(len(newList)):
                for j in range(len(newList[i])):
                        newList[i][j]=float(newList[i][j])
        newList = [x for x in newList if x]
        return newList

def generatePlotStream(stream):
    n = len(stream[0])
    m = len(stream)
    dataPlot = [ [] for i in range(n)]
    #print(stream)
    print(n,m)
    for i in range(n):
        for j in range(m):
            try:
                (dataPlot[i]).append((stream[j])[i])
            except:
                (dataPlot[i]).append(dataPlot[i][-1])
    return dataPlot[6],dataPlot

def updateData( theStream, theAdd):
    theStream.extend(theAdd)
    if(len(theStream)<BLOCKSTREAM):
        return theStream
    else:
        del theStream[0:(len(theStream)-BLOCKSTREAM)]
        return theStream

def updatePlot():
        time_ax, data_ax=generatePlotStream(dataStream)
        if not(lines):
                lines1, = axs[0].plot(time_ax,data_ax[10],'#1de9b6')
                lines2, =axs[0].plot(time_ax,data_ax[11],'#ff80ab')
                lines3, =axs[0].plot(time_ax,data_ax[12],'#42a5f5')
                
                
                lines4, =axs[1].plot(time_ax,data_ax[7],'#1de9b6')
                lines5, =axs[1].plot(time_ax,data_ax[8],'#ff80ab')
                lines6, =axs[1].plot(time_ax,data_ax[9],'#42a5f5')
                
                lines7, =axs[2].plot(time_ax,data_ax[0],'#1de9b6')
                lines8, =axs[2].plot(time_ax,data_ax[1],'#ff80ab')
                lines9, =axs[2].plot(time_ax,data_ax[2],'#42a5f5')
                lines10, =axs[2].plot(time_ax,data_ax[3],'#a7ffeb')
                lines11, =axs[2].plot(time_ax,data_ax[4],'#ea80fc')
                lines12, =axs[2].plot(time_ax,data_ax[5],'#ffff8d')
        else:
                lines1.set_data(time_ax,data_ax[10])
                lines2.set_data(time_ax,data_ax[11])
                lines3.set_data(time_ax,data_ax[12])
                
                lines4.set_data(time_ax,data_ax[7])
                lines5.set_data(time_ax,data_ax[8])
                lines6.set_data(time_ax,data_ax[9])
                
                lines7.set_data(time_ax,data_ax[0])
                lines8.set_data(time_ax,data_ax[1])
                lines9.set_data(time_ax,data_ax[2])
                lines10.set_data(time_ax,data_ax[3])
                lines11.set_data(time_ax,data_ax[5])
        for i in range(3):
                try:
                        axs[i].set_xlim(dataStream[0][6],dataStream[-1][6])
                except IndexError:
                        print(dataStream[0])
                        print(dataStream[-1]) 
        plt.draw()
        plt.pause(0.0001)
#----main function----
if __name__ == "__main__":
        print("Initiating SensorShoe server <>")
        with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
                #HOST = input("insert server device IP : ")
                s.bind((HOST,PORT))
                s.listen()
                conn, addr = s.accept()
                print("SensorShoe online on ", addr, " <>")
                while True:
                        data = conn.recv(1024)
                        if "END" in data.decode("utf-8"):
                                print("END message detected, done receiving data <>")
                                break
                        a = listSplit("Z",data)
                        dataList.extend(a);
                        dataStream = updateData(dataStream,a)
                        updatePlot()
                        
                        
                        
#----write to file----
        with open("data.txt", 'w') as file:
                file.writelines('\t'.join(str(j) for j in i) + '\n' for i in dataList)                
