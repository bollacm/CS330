#Colin Swain and Marcus Bollacker
import threading
import time

class BankAccount:
    def __init__(self, x):
        self.balance = x
        self.lock = threading.Lock()
    def deposit(self, x):
        with self.lock:
            if(x>0):
                self.balance += x
                print(f"{self.balance}")
            else:
                print("can only deposit values greater than 0")
    def withdraw(self, y):
        with self.lock:
            if self.balance>=y:
                self.balance -= y
                print(f"{self.balance}")
            else:
                print("not enought funds")
    def amount(self) -> str:
        return self.balance

    def depositTest(self):
        count = 0
        while count < 10000:
            self.deposit(2)
            count +=1

    def withdrawTest(self):
        count = 0
        while count < 10000:
            self.withdraw(1)
            count +=1
       
            


#intitalizes with an account and amount being deposited/withdrawn

class DepositThread(threading.Thread):
    def __init__(self, account, amount):
        super().__init__()
        self.account  = account
        self.amount = amount
    def run(self):
        self.account.deposit(self.amount)

class WithdrawThread(threading.Thread):
    def __init__(self, account, amount):
        super().__init__()
        self.account = account
        self.amount = amount

    def run(self):
        self.account.withdraw(self.amount)


accounts = []
count = 0
while count <5:
    accounts.append(BankAccount(100))
    count+=1

depositThread = []
withdrawThread = []
# Create multiple deposit and withdrawal threads in lists for accounts
for account in accounts:
    depositThread.append(DepositThread(account, 5))
    withdrawThread.append(WithdrawThread(account, 1))

startThread = time.time() #start timer for testing purposes
for thread in depositThread + withdrawThread:
    thread.start()

for thread in depositThread + withdrawThread:
    thread.join()
endThread = time.time()


print(f"Multithreaded: {endThread - startThread}") 

print("press enter to continue")
input()

#Test efficency of multithreading vs sequential single thread one account
account1 = BankAccount(100)
depositThread2 = []
withdrawThread2 = []
count = 0

while count < 10000:
    depositThread2.append(DepositThread(account1, 5))
    withdrawThread2.append(WithdrawThread(account1, 1))
    count +=1

 #start timer for testing purposes
startThread2 = time.time()
for thread in depositThread2 + withdrawThread2:
    thread.start()

for thread in depositThread2 + withdrawThread2:
    thread.join()
endThread2 = time.time()

# accounts with sequential threading
account2 = BankAccount(100)
count = 0
startSequential = time.time()
while count <10000:
    account2.deposit(5)
    account2.withdraw(1)
    count+=1


endSequential = time.time()

print(f"Sequential: {endSequential - startSequential} vs Multithreaded: {endThread2 - startThread2}") 
print(f"Account2 Balance: {account2.amount()} vs Account1 Balance: {account1.amount()}") 

print("press enter to continue")
input()

# two  accounts thread test
testAccount1 = BankAccount(100)
testAccount2 = BankAccount(100)
fread = threading.Thread(target = testAccount1.depositTest)
dread = threading.Thread(target = testAccount1.withdrawTest)

startMulti = time.time()
fread.start()
dread.start()
fread.join()
dread.join()
endMulti = time.time()

startSequential = time.time()
testAccount2.depositTest()
testAccount2.withdrawTest()
endSequential = time.time()

print(f"Sequential: {endSequential - startSequential} vs Multithreaded: {endMulti - startMulti}") 
print(f" Account2 Balance: {testAccount2.amount()} vs Account1 Balance: {testAccount1.amount()}") 
