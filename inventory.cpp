#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to check if input is a valid numeric string
bool isValidNum(const string &input)
{
    bool Decimal = false;

    for (char ch : input)
    {
        if (ch == '.')
        {
            if (Decimal)
            {
                return false;
            }
            Decimal = true;
        }
        else if (!isdigit(ch))
        {
            return false;
        }
    }
    return !input.empty();
}

// Function to get a valid price from the user
void getValidPrice(const string &label, double &amount)
{
    string input;
    while (true)
    {
        cout << "\nEnter " << label << ": ";
        cin >> input;

        if (isValidNum(input))
        {
            amount = stod(input);
            if (amount <= 0)
            {
                cout << "Error: input must be greater than zero." << endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "Error: Please enter a valid positive numeric amount." << endl;
        }
    }
}

// Function to get a valid quantity from the user
void getValidQuantity(const string &label, int &amount)
{
    string input;
    while (true)
    {
        cout << "\nEnter " << label << ": ";
        cin >> input;

        // Check if the input contains a decimal point or is non-numeric
        bool isValid = true;
        for (char ch : input)
        {
            if (!isdigit(ch) && ch != '.')
            {
                isValid = false;
                break;
            }
        }

        // If the input is invalid, prompt again
        if (!isValid || (input.find('.') != string::npos))
        {
            cout << "Error: Please enter a valid positive whole number." << endl;
            continue;
        }

        // Convert input to integer
        amount = stoi(input);

        if (amount <= 0)
        {
            cout << "Error: input must be greater than zero." << endl;
        }
        else
        {
            break;
        }
    }
}

class Items
{
private:
    string id, name, category;
    int quantity;
    double price;

public:
    // Constructor
    Items(string i, string n, int q, double p, string c) : id(i), name(n), quantity(q), price(p), category(c) {}

    // getter
    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    // Setter functions
    void setId(const string &newId) { id = newId; }
    void setName(const string &newName) { name = newName; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
    void setCategory(const string &newCategory) { category = newCategory; }

    // Static function to initialize a list of items inside the Items class
    static vector<Items> getDefaultItems()
    {
        return {
            Items("P001", "Black and Gray Athletic Cotton Socks - 6 Pairs", 26, 180, "clothing"),
            Items("P002", "Intermediate Size Basketball", 3, 1999, "entertainment"),
            Items("P003", "Adults Plain Cotton T-Shirt - 2 Pack", 400, 799, "clothing"),
            Items("P004", "Slot Toaster - Black", 120, 3000, "electronics"),
            Items("P005", "White Dinner Plate Set", 123, 1499, "entertainment"),
            Items("P006", "Nonstick, Carbon Steel Oven Bakeware Set", 4, 499, "entertainment"),
            Items("P007", "Plain Hooded Fleece Sweatshirt", 83, 1199, "clothing"),
            Items("P008", "Luxury Towel Set - Graphite Gray", 2, 999, "clothing"),
            Items("P009", "Liquid Laundry Detergent, 110 Loads", 6, 799, "entertainment"),
        };
    }
};

class Inventory
{
protected:
    vector<Items> items;

public:
    Inventory()
    {
        items = Items::getDefaultItems();
    }

    virtual void displayAllItems() = 0;
    virtual void addItem() = 0;
    virtual void handleInput() = 0;

    virtual void updateItem(string id) = 0;
};

class InventoryManager : public Inventory
{
public:
    void addItem() override
    {
        string id, name, category;
        int quantity;
        double price;

        cout << "Adding item...\n";
        cout << "Enter ID: ";
        cin >> id;

        cout << "\nEnter Product Name: ";
        cin.ignore();
        getline(cin, name);

        getValidQuantity("quantity", quantity);
        getValidPrice("price", price);

        cout << "\nEnter Product Category: ";
        cin >> category;

        // Create a new Items object
        Items newItem(id, name, quantity, price, category);

        items.push_back(newItem);

        cout << "\nItem added successfully!\n";
    }

    void updateItem(string id) override
    {
        bool found = false;
        for (auto &item : items)
        {
            if (item.getId() == id)
            {
                found = true;
                char choice;
                cout << "\nID FOUND\n";
                cout << "Press P to update price\nPress Q to update quantity: ";
                cin >> choice;
                choice = toupper(choice);

                while (choice != 'P' && choice != 'Q')
                {
                    cout << "Enter P or Q only: ";
                    cin >> choice;
                    choice = toupper(choice);
                }

                if (choice == 'P')
                {
                    double newPrice;
                    getValidPrice("new price", newPrice);

                    while (newPrice < 0)
                    {
                        cout << "Invalid input. Please enter a valid price (0 or higher): ";
                        cin >> newPrice;
                    }
                
                    cout << "\nSUCCESS!\nPrice of Item " << item.getName() << " updated from " << item.getPrice() << " to " << newPrice << endl;
                    item.setPrice(newPrice);
                }
                else if (choice == 'Q')
                {
                    int newQuantity;
                    getValidQuantity("new quantity", newQuantity);

                    while (newQuantity < 0)
                    {
                        cout << "Invalid input. Please enter a valid quantity (0 or higher): ";
                        cin >> newQuantity;
                    }

                    cout << "Quantity of Item " << item.getName() << " updated from " << item.getQuantity() << " to " << newQuantity << endl;
                    item.setQuantity(newQuantity);
                }
            }
        }

        if (!found)
        {
            cout << "Item with ID " << id << " not found!" << endl;
        }
    }
};

class Display : public InventoryManager
{
public:
    void menu()
    {
        cout << "\nInventory Menu: \n"
             << "1 - Add Item\n"
             << "2 - Update Item\n"
             << "3 - Remove Item\n"
             << "4 - Display Items by Category\n"
             << "5 - Display All Items\n"
             << "6 - Search Item\n"
             << "7 - Sort Items\n"
             << "8 - Display Low Stock Items\n"
             << "9 - Exit\n";
    }

    void handleInput() override
    {
        string choice;
        while (choice != "9")
        {
            menu();
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == "1") // add items
            {
                addItem();
            }
            else if (choice == "2") // update items
            {
                string id;
                cout << "Input ID: ";
                cin >> id;

                updateItem(id);
            }
            else if (choice == "3")
            {
                // Remove item
            }
            else if (choice == "4")
            {
                // Display items by category
            }
            else if (choice == "5")
            {
                displayAllItems();
            }
            else if (choice == "6")
            {
                // Search item
            }
            else if (choice == "7")
            {
                // Sort items
            }
            else if (choice == "8")
            {
                // Display low stock items
            }
            else if (choice == "9")
            {
                cout << "Exiting program...\n";
                exit(0); // exit the program
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void displayAllItems() override
    {
        for (const auto &item : items)
        {
            cout << "ID: " << item.getId() << endl;
            cout << "Name: " << item.getName() << endl;
            cout << "Quantity: " << item.getQuantity() << endl;
            cout << "Price: " << item.getPrice() << endl;
            cout << "Category: " << item.getCategory() << endl
                 << endl;
        }
    }
};

int main()
{
    Display display;
    display.handleInput();

    return 0;
}
