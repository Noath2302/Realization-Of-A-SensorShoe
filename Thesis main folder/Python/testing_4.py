#!/usr/bin/env python3
import socket
import asyncio
BLOCKSTREAM = 120
HOST = '192.168.137.1'      # Standard loopback interface address (localhost)
PORT = 22222                    # Port to listen on (non-privileged ports are > 1023)
dataList=[]                          #data of the List
stepStream=[]
dataStream = []
#==================================figure for plotting =====================================
import matplotlib.pyplot as plt
plt.style.use('dark_background')
fig, axs = plt.subplots(3,1)

axs[0].set(xlabel = 'time', ylabel = 'angular velocity')
axs[0].set_ylim(-5,5)
axs[1].set(xlabel = 'time', ylabel = 'acceleration')
axs[1].set_ylim(-10,10)
axs[2].set(xlabel = 'time', ylabel = 'ground reaction force')
axs[2].set_ylim(2500,7500)
xs = []
ys = []

#==================================== helpFunction =======================================
def listShift(*theList , nextElement):
    l=len(theList)
    for i in range(l-1):
        theList[i] = theList[i+1]
    theList[l-1]=nextElement
    return theList

def listSplit(splitElement, *theList ,):
    #print(theList)
    newList=[]
    i=0
    j=0
    splitIndexOccurrence = [i for i, x in enumerate(theList) if x == splitElement]
    #print(splitIndexOccurrence)
    for ele in theList:
        if(ele==splitElement):
            #print(True)
            temp = theList[i:(splitIndexOccurrence[j])]
            temp2= [float(i) for i in temp]
            #print(temp2)
            newList.append(temp2)
            i=splitIndexOccurrence[j]+1
            j+=1
    return newList

def plotStream(stream):
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
    return dataPlot[7],dataPlot
    
def updateData( theStream, theAdd):
    theStream.extend(theAdd)
    if(len(theStream)<BLOCKSTREAM):
        return theStream
    else:
        del theStream[0:(len(theStream)-BLOCKSTREAM)]
        #axs[0].clear()
        #axs[1].clear()
        try:
            axs[0].set_xlim(theStream[0][7],theAdd[-1][7])
            axs[1].set_xlim(theStream[0][7],theAdd[-1][7])
            axs[2].set_xlim(theStream[0][7],theAdd[-1][7])
        except IndexError:
            print("END found stop program ... ")
        return theStream
#====================================== main ============================================
if __name__ == "__main__":
    print("Starting Smartshoe server ...")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                #-- receiving data -- 
                data = conn.recv(1024)

                #-- preprocessing raw data --
                tempRaw = data.decode("utf-8").split('\t')
                for element in tempRaw:
                    if element == '':
                        tempRaw.remove('')
                tempRaw = listSplit("Z",*tempRaw)
                print(tempRaw)
                dataList.extend(tempRaw)
                
                dataStream = updateData(dataStream,tempRaw)
                #print(dataStream)
                #print()
                xs,ys = plotStream(dataStream)
                
                
                axs[0].plot(xs,ys[11],'#1de9b6')
                axs[0].plot(xs,ys[12],'#ff80ab')
                axs[0].plot(xs,ys[13],'#42a5f5')
                
                
                axs[1].plot(xs,ys[8],'#1de9b6')
                axs[1].plot(xs,ys[9],'#ff80ab')
                axs[1].plot(xs,ys[10],'#42a5f5')
                
                axs[2].plot(xs,ys[0],'#1de9b6')
                axs[2].plot(xs,ys[1],'#ff80ab')
                axs[2].plot(xs,ys[2],'#42a5f5')
                axs[2].plot(xs,ys[3],'#a7ffeb')
                axs[2].plot(xs,ys[4],'#ea80fc')
                axs[2].plot(xs,ys[5],'#ffff8d')
                
                plt.draw()
                plt.pause(0.0001)
                #-- condition for breaking loop --
                if "END" in data.decode("utf-8"):
                    break
    print(dataList)
with open("data.txt", 'w') as file:
    file.writelines('\t'.join(str(j) for j in i) + '\n' for i in dataList)
