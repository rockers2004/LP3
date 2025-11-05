// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract ProductInventory {
    struct Product {
        uint256 id;
        string name;
        uint256 quantity;
    }

    mapping(uint256 => Product) public products;
    uint256 public productCount = 0;

    // Receive (add) new product
    function receiveProduct(string memory _name, uint256 _quantity) public {
        productCount++;
        products[productCount] = Product(productCount, _name, _quantity);
    }

    // Sell product (reduce quantity)
    function saleProduct(uint256 _id, uint256 _quantity) public {
        require(_id <= productCount, "Invalid product ID");
        require(products[_id].quantity >= _quantity, "Not enough stock");
        products[_id].quantity -= _quantity;
    }

    // Display stock of a specific product
    function displayStock(uint256 _id) public view returns (string memory, uint256) {
        require(_id <= productCount, "Invalid product ID");
        Product memory p = products[_id];
        return (p.name, p.quantity);
    }
}
