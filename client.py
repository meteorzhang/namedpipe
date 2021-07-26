import os
import time
import win32pipe, win32file
import datetime
import win32file


pipeRead = win32file.CreateFile(r'\\.\Pipe\pipeWrite',
                              win32file.GENERIC_READ | win32file.GENERIC_WRITE,
                              0, None,
                              win32file.OPEN_EXISTING,
                              0, None)

print("connect write server")

time.sleep(2)

pipeWrite = win32file.CreateFile(r'\\.\Pipe\pipeRead',
                              win32file.GENERIC_READ | win32file.GENERIC_WRITE,
                              0, None,
                              win32file.OPEN_EXISTING,
                              0, None)
print("connect read server")


# t = time.time()
# print (int(round(t * 1000000))) #微秒级时间戳


# data = "[[0,1,22,33.33,33.222],[0,1,22,33.33,33.222],[0,1,22,33.33,33.222],[0,1,22,33.33,33.222],[0,1,22,33.33,33.222]]"
# data=data.encode()
# win32file.WriteFile(pipeWrite, data)

# data1 = win32file.ReadFile(pipeRead, 4096)
# data1 = data1[1].decode()
# da = data1[:-1]
# a = eval(da)
# print (a)
# t1 = time.time()
# print (int(round(t1 * 1000000))) #微秒级时间戳
#


while 1:
    data1 = win32file.ReadFile(pipeRead, 4096)
    data1 = data1[1].decode()
    da = data1[:-1]
    a = eval(da)
    print (a)

    data = "fufu"
    data=data.encode()
    win32file.WriteFile(pipeWrite, data)
    time.sleep(2)

#
# data = [11.00, 23, 45.3, 23.4, [[0,11.11,11],[1,22.22,22]]]
# #data = 11.11
# data = str(data)
# data=data.encode()
# win32file.WriteFile(fileHandle, data)
#
# data1 = win32file.ReadFile(fileHandle, 4096)
# data1 = data1[1].decode()
#
# da = data1[:-1]
#
#
# a = eval(da)
# print (a)
# print(type(a))
# print(a[0])
# print(a[3])

os.close(pipeWrite)
os.close(pipeRead)