import json
import os

class Product:
    def __init__(self, name, product_id, price, quantity):
        self.name = name
        self.id = product_id
        self.price = price
        self.quantity = quantity

    def display(self):
        print(f"{self.id:<5}{self.name:<20}{self.price:<10}{self.quantity:<8}")

    def to_dict(self):
        return {
            "name": self.name,
            "id": self.id,
            "price": self.price,
            "quantity": self.quantity
        }

    @staticmethod
    def from_dict(data):
        return Product(data["name"], data["id"], data["price"], data["quantity"])


class InventoryManager:
    def __init__(self, filename="inventory.json"):
        self.filename = filename
        self.products = []
        self.load_inventory()

    def load_inventory(self):
        if os.path.exists(self.filename):
            with open(self.filename, "r") as f:
                data = json.load(f)
                self.products = [Product.from_dict(p) for p in data]
        else:
            self.products = []

    def save_inventory(self):
        with open(self.filename, "w") as f:
            json.dump([p.to_dict() for p in self.products], f, indent=4)

    def add_product(self, product):
        self.products.append(product)
        self.save_inventory()

    def add_product_manually(self):
        name = input("Enter product name: ").strip()
        price = float(input("Enter product price: "))
        quantity = int(input("Enter product quantity: "))

        next_id = 1 if not self.products else self.products[-1].id + 1
        new_product = Product(name, next_id, price, quantity)
        self.add_product(new_product)

        print("Product added successfully!")

    def display_inventory(self):
        print(f"{'ID':<5}{'Name':<20}{'Price':<10}{'Quantity':<8}")
        print("-" * 50)
        for product in self.products:
            product.display()

    def update_quantity(self, product_id, new_quantity):
        for product in self.products:
            if product.id == product_id:
                product.quantity = new_quantity
                self.save_inventory()
                print("Quantity updated successfully!")
                return
        print("Product not found.")

    def sell_product(self, product_id, quantity_sold):
        for product in self.products:
            if product.id == product_id:
                if product.quantity >= quantity_sold:
                    product.quantity -= quantity_sold
                    self.save_inventory()
                    print("Sale successful!")
                else:
                    print("Insufficient stock for the sale.")
                return
        print("Product not found.")


def main():
    inventory = InventoryManager()

    # Add default products only if inventory is empty
    if not inventory.products:
        inventory.add_product(Product("Laptop", 1, 75000, 30))
        inventory.add_product(Product("Printer", 2, 10000, 30))
        inventory.add_product(Product("Mouse", 3, 4000, 30))

    while True:
        print("\n1. Display Inventory")
        print("2. Update Quantity")
        print("3. Sell Product")
        print("4. Add Product")
        print("5. Exit")
        choice = input("Enter your choice: ").strip()

        if choice == "1":
            inventory.display_inventory()
        elif choice == "2":
            try:
                product_id = int(input("Enter product ID: "))
                new_quantity = int(input("Enter new quantity: "))
                inventory.update_quantity(product_id, new_quantity)
            except ValueError:
                print("Invalid input. Please enter numbers.")
        elif choice == "3":
            try:
                sell_product_id = int(input("Enter product ID to sell: "))
                sell_quantity = int(input("Enter quantity to sell: "))
                inventory.sell_product(sell_product_id, sell_quantity)
            except ValueError:
                print("Invalid input. Please enter numbers.")
        elif choice == "4":
            inventory.add_product_manually()
        elif choice == "5":
            print("Exiting program. Thank You!")
            break
        else:
            print("Invalid choice. Please enter a valid option.")


if __name__ == "__main__":
    main()