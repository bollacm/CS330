#todo: List of multiplle accounts, pass through to withdraw and dpeosit threads, with 3 threads per account
# implement a sync primitive
#
import threading
import time

class BankAccount:
    def __init__(self, x):
        self.balance = x
    def deposit(self, x):
        if(x>0):
            self.balance += x
            print(f"{self.balance}")
        else:
            print("can only deposit values greater than 0")
    def withdraw(self, y):
        if self.balance>=y:
            self.balance -= y
            print(f"{self.balance}")
        else:
            print("not enought funds")
    def amount(self) -> str:
        return self.balance

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



startThread = time.time()
account = BankAccount(1000)

# Create multiple deposit and withdrawal threads
deposit_threads = [DepositThread(account, 200) for _ in range(5)]
withdrawal_threads = [WithdrawThread(account, 300) for _ in range(3)]

# Start all threads
for thread in deposit_threads + withdrawal_threads:
    thread.start()

# Wait for all threads to finish
for thread in deposit_threads + withdrawal_threads:
    thread.join()
endThread = time.time()

print(f"{endThread - startThread}")
#print(f"{endThread - startThread} seconds elapsed \n Account1 Balance:{account1.balance} Account2 Balance: {account2.balance}") 
#print("----------------------")


# accounts with sequential threading
#startSequential = time.time()
#account1.depositTest()
#account2.depositTest()
#endSequential = time.time()

#print(f"{endSequential - startSequential} seconds elapsed \n Account1 Balance:{account1.amount()} Account2 Balance: {account2.balance}") 



    