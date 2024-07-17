# ATM_Controller

### overview
This C++ Program simulate basic ATM operations such as
Insert Card -> PIN number -> Select Account -> See Balance/Deposit/Withdraw

### usage
- creating ATM Object:

  ``` cpp
  ATM atm;
  ```

- add Customers:

  ```cpp
  atm.addCustomer("1234",5678) // cardNumber="1234", Pin=5678
  ```

- insert Card, PIN:

  ```cpp
  atm.insertCard("1234",5678) // cardNumber="1234", Pin=5678
  ```

- Select Account:

  ```cpp
  if (atm.selectAccount()){
      // Acount selected
  } else {
      // invalid card or Pin
  }
  ```

- Check Balance:

  ```cpp
  int balance = atm.checkBalance();
  ```

- Deposit:

  ```cpp
  atm.deposit(amount);
  ```

- Withdraw:

  ```cpp
  atm.withdraw(amount);
  ```

### test
- 1) git clone https://github.com/AltairKosmoTale/ATM_Controller.git
- 2) g++ -o atm atm.cpp
- 3) ./atm

