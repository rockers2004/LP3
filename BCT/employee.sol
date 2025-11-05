// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract EmployeeData {
    struct Employee {
        uint256 id;
        string name;
        uint256 salary;
    }

    Employee[] public employees;

    // Add new employee
    function addEmployee(uint256 _id, string memory _name, uint256 _salary) public {
        employees.push(Employee(_id, _name, _salary));
    }

    // Get employee details
    function getEmployee(uint256 index) public view returns (uint256, string memory, uint256) {
        require(index < employees.length, "Invalid index");
        Employee memory e = employees[index];
        return (e.id, e.name, e.salary);
    }

    // Get total number of employees
    function totalEmployees() public view returns (uint256) {
        return employees.length;
    }

    // Fallback function
    fallback() external payable {}
    receive() external payable {}
}
