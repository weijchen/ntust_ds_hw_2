# Data Structures HW 2

隨班附讀f126162 王立言

### OS

macOS Sierra (Version 10.12.6)

### IDE

Visual Studio Code (Version 1.17.2)

### Compiler

g++ (C++11)

### 包含檔案

* Source code
  * main.cpp
  * client.h
  * service.cpp
* Execution file
  * hw2.exe

### 程式執行步驟示範

```shell
// 1. 執行程式，請依序輸入 arrival time、 service time 和 allowable waiting time，並用逗號隔開。
$ ./hw2.exe
Please enter time values of each client in order of: Arrival Time, Service Time and Allowable Waiting Time.
And separate time values by comma(,).
For example, If the arrival time, service time and allowable waiting time of a client is:
3, 5 and 7, then you should enter '3,5,7'.
$ Enter times for user[1]:

// 2. 依序輸入 10 個 client
$ Enter times for client[1]:3,5,7
$ Enter times for client[2]:5,7,8
$ Enter times for client[3]:9,9,5
$ Enter times for client[4]:12,3,10
$ Enter times for client[5]:13,2,4
$ Enter times for client[6]:16,6,3
...

// 3. 輸出結果
Client: 1, Served or not?: Yes, Departure Time: 8
Client: 2, Served or not?: Yes, Departure Time: 15
Client: 3, Served or not?: No
Client: 4, Served or not?: Yes, Departure Time: 20
Client: 5, Served or not?: Yes, Departure Time: 17
Client: 6, Served or not?: No
...

```



