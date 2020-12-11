import classes
import functions 
import threading
import gui

classes.ser1.read()
classes.ser1.write('1\n' .encode())
print("게임을 시작합니다.")
print("어떤 플레이어가 게임을 합니까?")

guiThread = threading.Thread(target=gui.root)
guiThread.daemon = True
guiThread.start()

c = 0
a = []

while(1):
    if(classes.ser1.inWaiting()):
        a.append(int(classes.ser1.read().decode()))
        print("{}가 게임을 합니다." .format(a[c]))
        c += 1
        if(len(a)>1):
            gui.startFlg = 1
    if(gui.startFlg == 2):    
        classes.ser1.write('1\n' .encode())
        break

a.sort()
        
while(1):
    if(gui.startFlg == 3):break

print(1)

classes.ser1.write('1\n' .encode())

for i in a:            
    globals()['p{}'.format(i)] = classes.player(gui.startMoney,1,i)
    functions.pList.append(globals()['p{}'.format(i)])

if (gui.timeoutTurn == 0): gui.timeoutTurn = 500 

for i in range(1, gui.timeoutTurn):
    for a in functions.pList:
        functions.turn(a)
        if(len(functions.pList) == 1):
            classes.ser1.write("2{}000000" .format(functions.pList[0].number) .encode())
            break

if((len(functions.pList)>1) and (gui.poormanFlg == 0)):
    for a in functions.pList:
        for b in a.estList:
            a.mon += functions.calPrice(b)
    d = functions.pList[0]
    for a in functions.pList:
        if (d.mon < a.mon):
            d = a
    print("{}P가 승리하였습니다." .format(d.number))
    classes.ser1.write("2{}000000\n" .format(d.number) .encode())
    
elif((len(functions.pList)>1) and (gui.poormanFlg == 1)):
    for a in functions.pList:
        for b in a.estList:
            a.mon += functions.calPrice(b)
    d = functions.pList[0]
    for a in functions.pList:
        if (d.mon > a.mon):
            d = a
    print("{}P가 승리하였습니다." .format(d.number))
    classes.ser1.write("2{}000000\n" .format(d.number) .encode())
    #승리 코드 추가 d가 승리
    
