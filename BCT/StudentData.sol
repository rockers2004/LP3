// SPDX-License-Identifier: MIT
pragma solidity ^0.8.18;


contract StudentData {

    // 1. STRUCTURES: Defines a custom data type for a Student.
    struct Student {
        uint studentId;
        string name;
        uint grade;
    }

    // 2. ARRAYS: A dynamic array to store all student records.
    // The 'public' keyword automatically creates a getter function for it.
    Student[] public students;

    // A mapping to prevent duplicate student IDs and for quick lookups.
    mapping(uint => bool) private studentExists;

    // Event to log when a new student is added.
    event StudentAdded(uint indexed studentId, string name, uint grade);
    
    // Event to log when a special function is triggered.
    event EtherReceived(address indexed sender, uint value);

    
    //Adds a new student's data to the blockchain.
    //_studentId The unique ID of the student.
    //_name The name of the student.
    //_grade The grade or score of the student.
    
    function addStudent(uint _studentId, string memory _name, uint _grade) public {
        // Check to ensure the student ID is not already in use.
        require(!studentExists[_studentId], "Student ID already exists.");
        
        // Add the new student to the array.
        students.push(Student(_studentId, _name, _grade));
        
        // Mark the student ID as used in the mapping.
        studentExists[_studentId] = true;
        
        // Emit an event to log the action.
        emit StudentAdded(_studentId, _name, _grade);
    }

    /**
     * @dev Returns the total number of students stored.
     * 'view' function means it only reads data and does not cost gas to call.
     */
    function getStudentCount() public view returns (uint) {
        return students.length;
    }

    // 3. RECEIVE ETHER: This function is automatically executed when the contract
    // receives plain Ether (e.g., through a simple transfer with no data).
    // This is the recommended way to handle incoming ETH since Solidity v0.6.0.
    receive() external payable {
        // Log that Ether was received.
        emit EtherReceived(msg.sender, msg.value);
    }

    // 4. FALLBACK: This function is executed if someone calls a function
    // that doesn't exist. If the receive() function did not exist, this
    // would also handle plain Ether transfers.
    fallback() external payable {
        // Log that the fallback function was called.
        emit EtherReceived(msg.sender, msg.value);
    }
}

