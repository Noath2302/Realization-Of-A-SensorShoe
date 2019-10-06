#!/usr/bin/env python3
import matplotlib.pyplot as plt
import socket
import asyncio

HOST = '192.168.137.1'      # Standard loopback interface address (localhost)
PORT = 22222                    # Port to listen on (non-privileged ports are > 1023)
dataList=[]                          #data of the List
stepStream=[]
#==================================== helpFunction =======================================
def listShift(*theList , nextElement):
    l=len(theList)
    for i in range(l-1):
        theList[i] = theList[i+1]
    theList[l-1]=nextElement
    return theList

def listSplit(splitElement, *theList ,):
    print(theList)
    newList=[]
    i=0
    j=0
    splitIndexOccurrence = [i for i, x in enumerate(theList) if x == splitElement]
    print(splitIndexOccurrence)
    for ele in theList:
        if(ele==splitElement):
            #print(True)
            temp = theList[i:(splitIndexOccurrence[j])]
            temp2= [float(i) for i in temp]
            print(temp2)
            newList.append(temp2)
            i=splitIndexOccurrence[j]+1
            j+=1
    return newList
#====================================== main ============================================
if __name__ == "__main__":
    print("Starting Smartshoe serer ...")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                #-- receiving data -- 
                data = conn.recv(1024)

                #-- preprocessing --
                tempRaw = data.decode("utf-8").split('\t')
                for element in tempRaw:
                    if element == '':
                        tempRaw.remove('')
                dataList.extend(tempRaw)
                plt.plot(tempRaw[0],tempRaw[])
                #-- condition for breaking loop --
                if "END" in data.decode("utf-8"):
                    break
            dataList = listSplit("zZz",*dataList)
            print(dataList)
