// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {
    struct Student {
        uint256 rollNo;
        string name;
        uint8 age;
    }

    Student[] public students;

    // Add new student
    function addStudent(uint256 _rollNo, string memory _name, uint8 _age) public {
        students.push(Student(_rollNo, _name, _age));
    }

    // Get student by index
    function getStudent(uint256 index) public view returns (uint256, string memory, uint8) {
        require(index < students.length, "Invalid index");
        Student memory s = students[index];
        return (s.rollNo, s.name, s.age);
    }

    // Total number of students
    function getTotalStudents() public view returns (uint256) {
        return students.length;
    }

    // Fallback function - to handle unexpected calls or ether transfers
    fallback() external payable {
        // You can log or revert here if needed
    }

    receive() external payable {}
}
