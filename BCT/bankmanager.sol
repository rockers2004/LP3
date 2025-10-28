// SPDX-License-Identifier: MIT
pragma solidity ^0.8.18;


contract BankAccount {
    uint public balance;                        // A state variable to store the balance of the account in Wei.
    address public owner;                       // The address of the person who deployed the contract.
    event Deposit(address indexed account, uint amount);// Event to log deposit transactions.
    event Withdrawal(address indexed account, uint amount);// Event to log withdrawal transactions.

    
    constructor() {
        owner = msg.sender;
    }

    
    //A modifier to restrict function access to the owner only.
    modifier onlyOwner() {
        require(msg.sender == owner, "You are not the owner of this account.");
        _;
    }

    
    //Allows the owner to deposit Ether into the contract. 
    function deposit() public payable onlyOwner {
        require(msg.value > 0, "Deposit amount must be greater than zero.");
        balance += msg.value;
        emit Deposit(msg.sender, msg.value);
    }

    //Allows the owner to withdraw a specified amount of Ether. 
    function withdraw(uint _amount) public onlyOwner {
        require(balance >= _amount, "Insufficient balance for withdrawal.");
        require(_amount > 0, "Withdrawal amount must be greater than zero.");
        
        balance -= _amount;
        
        // Transfer the amount to the owner's address.
        (bool success, ) = owner.call{value: _amount}("");
        require(success, "Failed to send Ether.");
        
        emit Withdrawal(msg.sender, _amount);
    }

    //Returns the current balance of the contract.
    function getBalance() public view returns (uint) {
        return balance;
    }
}
