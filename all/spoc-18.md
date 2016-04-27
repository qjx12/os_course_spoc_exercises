# 同步互斥(lec 18) spoc 思考题

## 小组思考题38

博物馆-公园问题 Jurassic公园有一个恐龙博物馆和一个花园，有m 个旅客租卫辆车，每辆车仅能乘 一个一旅客。旅客在博物馆逛了一会，然后，排队乘坐旅行车，挡一辆车可用喊飞它载 入一个旅客，再绕花园行驶任意长的时间。若n 辆车都己被旅客乘坐游玩，则想坐车的 旅客需要等待。如果一辆车己经空闲，但没有游玩的旅客了，那么，车辆要等待。试用 信号量和P 、V 操作同步m 个旅客和n 辆车子。

这是一个汇合机制，有两类进程：顾客进程和车辆进程，需要进行汇合、即顾客要坐进车辆后才能游玩，开始时让车辆进程进入等待状态

解答:

var sc1 , sck xc ，mutex : semaphore ;
sck:=kx:=0；
sc1:=n ；mutex : = 1 ;
sharearea ：一个登记车辆被服务乘客信息的共享区；
cobegin
    process 顾客i ( i = 1 , 2 ，… ）
    begin
        P (sc1) ; /*车辆最大数量信号量
        P (mutex) ; /*封锁共享区，互斥操作
        在共享区sharearea登记被服务的顾客的信息：
        起始和到达地点，行驶时间
        P(xc); /* 待游玩结束之后，顾客等待下车
        V(sc1) ; /*空车辆数加1
    End
    Process 车辆j(j=1,2,3…)
    Begin
        L:P(sck); /*车辆等待有顾客来使用
        在共享区sharearea登记一辆车被使用，并与顾客进程汇合；
        V(mutex); /*这时可开放共享区，让另一顾客雇车
        车辆载着顾客开行到目的地；
        V(xc); /*允许顾客下车
        Goto L;
    End
coend

Condition:
```
#coding=utf-8
import threading  
import random  
import time
class myCondition():

    def __init__(self,num,name):
        self.num = num
        self.name = name;
        self.condition = threading.Condition()
    def acquire(self):
        #print "acquire %d %s\n" % (self.num,self.name),
   
        if self.condition.acquire():
            if self.num>=1:
                self.num=self.num-1
                self.condition.notify()
            else:
                self.condition.wait()
            self.condition.release()
            
  
    def release(self):
         #print "release %d %s\n" % (self.num,self.name),
         if self.condition.acquire():
            self.num=self.num+1
            self.condition.notify()
            self.condition.release()
       
    
car_num = 2;
person_num = 5;

per_sem=myCondition(0,'pre');
car_sem=myCondition(car_num,'car');
mutex_sem =myCondition(1,'mutex');
play_sem = myCondition(0,'play');

class Car(threading.Thread):  
    def __init__(self):  
       threading.Thread.__init__(self)
       
    def run(self):
        while True:
            print "car %s is waiting\n" % self.name,
            per_sem.acquire();
            mutex_sem.release();
            print "car %s is driving\n" % self.name,
            time.sleep(1);
            play_sem.release();

class Person(threading.Thread):  
    def __init__(self):  
       threading.Thread.__init__(self)  
       
    def run(self):
        print "preson %s wait a car!\n" %  self.name,
        car_sem.acquire();
        mutex_sem.acquire();
        #print"??" 
        per_sem.release();
        print "preson %s is playing!\n" %  self.name,
        play_sem.acquire();
        print "preson %s play end\n" %  self.name,
        car_sem.release();
        
if __name__ == "__main__":
    
    for p in range(0, person_num):  
        p = Person()  
        p.start()  

    for c in range(0, car_num):  
        c = Car()  
        c.start() 
        
       
    
```

Semaphore:
```
#coding=utf-8
import threading  
import random  
import time

car_num = 2;
person_num = 5;

per_sem=threading.Semaphore(0);
car_sem=threading.Semaphore(car_num);
mutex_sem =threading.Semaphore(1);
play_sem = threading.Semaphore(0);

class Car(threading.Thread):  
    def __init__(self):  
       threading.Thread.__init__(self)
       
    def run(self):
        while True:
            print "car %s is waiting\n" % self.name,
            per_sem.acquire();
            mutex_sem.release();
            print "car %s is driving\n" % self.name,
            time.sleep(1);
            play_sem.release();

class Person(threading.Thread):  
    def __init__(self):  
       threading.Thread.__init__(self)  
       
    def run(self):
        print "preson %s wait a car!\n" %  self.name,
        car_sem.acquire();
        mutex_sem.acquire();
        per_sem.release();
        print "preson %s is playing!\n" %  self.name,
        play_sem.acquire();
        print "preson %s play end\n" %  self.name,
        car_sem.release();
        
if __name__ == "__main__":
    
    for p in range(0, person_num):  
        p = Person()  
        p.start()  

    for c in range(0, car_num):  
        c = Car()  
        c.start() 
```
       
