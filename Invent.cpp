#include <iostream>
#include <vector>
#include <iomanip>
#include <limits> 
using namespace std;

class Product {
public:
    string name;
    int id;
    double price;
    int quantity;

    Product(const string& _name, int _id, double _price, int _quantity)
        : name(_name), id(_id), price(_price), quantity(_quantity) {}

    void display() const {
        cout << setw(5) << id << setw(20) << name << setw(10) << price << setw(8) << quantity << endl;
    }
};

class InventoryManager {
private:
    vector<Product> products;

public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void addProductManually() {
        string name;
        double price;
        int quantity;

        cout << "Enter product name: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        getline(cin, name);

        cout << "Enter product price: ";
        cin >> price;

        cout << "Enter product quantity: ";
        cin >> quantity;

        int nextId = products.empty() ? 1 : (products.back().id + 1);

        Product newProduct(name, nextId, price, quantity);
        addProduct(newProduct);

        cout << "Product added successfully!\n";
    }

    void displayInventory() const {
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(8) << "Quantity" << endl;
        cout << "-----------------------------------------\n";
        for (const Product& product : products) {
            product.display();
        }
    }

    void updateQuantity(int productId, int newQuantity) {
        for (Product& product : products) {
            if (product.id == productId) {
                product.quantity = newQuantity;
                cout << "Quantity updated successfully!\n";
                return;
            }
        }
        cout << "Product not found.\n";
    }

    void sellProduct(int productId, int quantitySold) {
        for (Product& product : products) {
            if (product.id == productId) {
                if (product.quantity >= quantitySold) {
                    product.quantity -= quantitySold;
                    cout << "Sale successful!\n";
                } else {
                    cout << "Insufficient stock for the sale.\n";
                }
                return;
            }
        }
        cout << "Product not found.\n";
    }
};

int main() {
    InventoryManager inventory;

    inventory.addProduct(Product("Laptop", 1, 75000, 30));
    inventory.addProduct(Product("Printer", 2, 10000, 30));
    inventory.addProduct(Product("Mouse", 3, 4000, 30));

    int choice;
    do {
        cout << "1. Display Inventory\n";
        cout << "2. Update Quantity\n";
        cout << "3. Sell Product\n";
        cout << "4. Add Product \n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Display Inventory
                inventory.displayInventory();
                break;

            case 2:
                // Update Quantity
                int productId, newQuantity;
                cout << "Enter product ID: ";
                cin >> productId;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                inventory.updateQuantity(productId, newQuantity);
                break;

            case 3:
                // Sell Product
                int sellProductId, sellQuantity;
                cout << "Enter product ID to sell: ";
                cin >> sellProductId;
                cout << "Enter quantity to sell: ";
                cin >> sellQuantity;
                inventory.sellProduct(sellProductId, sellQuantity);
                break;

            case 4:
                // Add Product
                inventory.addProductManually();
                break;

            case 5:
                // Exit
                cout << "Exiting program. Thank You!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}
