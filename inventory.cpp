#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
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

        if (amount < 0)
        {
            cout << "Error: input must be greater than zero." << endl;
        }
        else
        {
            break;
        }
    }
}
void toUpperCase(string &str)
{
    for (char &c : str)
    {
        c = toupper(c);
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
            Items("P001", "Black and Gray Athletic Cotton Socks", 26, 180, "CLOTHING"),
            Items("P002", "Intermediate Size Basketball", 3, 1999, "ENTERTAINMENT"),
            Items("P003", "Adults Plain Cotton T-Shirt - 2 Pack", 400, 799, "CLOTHING"),
            Items("P004", "Slot Toaster - Black", 120, 3000, "ELECTRONICS"),
            Items("P005", "Legion 5 Laptop", 2, 45000, "ENTERTAINMENT"),
            Items("P007", "Plain Hooded Fleece Sweatshirt", 83, 1199, "CLOTHING"),
            Items("P008", "Parasonic Rice cooker", 12, 1500, "ELECTRONICS"),
            Items("P009", "PLAYSTATION 5", 5, 34000, "ENTERTAINMENT"),
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
    virtual void displayItemsByCategory() = 0;
    virtual void searchItem() = 0;
    virtual void sortItems() = 0;
    virtual void displayLowStockItems() = 0;
    virtual void updateItem() = 0;
    virtual void removeItems() = 0;
};

class InventoryManager : public Inventory
{
public:
    string getCategory()
    {
        string category;

        cout << "Input category: ";
        cin >> category;
        toUpperCase(category);

        while (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT")
        {
            cout << "\nERROR: Category should only be\nCLOTHING\nELECTRONICS\nENTERTAINMENT\n\n";
            cout << "Input category: ";
            cin >> category;
            toUpperCase(category);
        }

        return category; 
    }

    void addItem() override
    {
        string id, name, category;
        int quantity;
        double price;

        category = getCategory();

        cout << "Adding item...\n";

        bool isDuplicate = true;
        while (isDuplicate)
        {
            cout << "Enter ID: ";
            cin >> id;
            toUpperCase(id);

            isDuplicate = false; 
            for (const auto &item : items)
            {
                if (item.getId() == id)
                {
                    isDuplicate = true; 
                    cout << "ERROR: An item already has that ID, please enter another ID.\n";
                    break;
                }
            }
        }

        cout << "\nEnter Product Name: ";
        cin.ignore();
        getline(cin, name);

        getValidQuantity("quantity", quantity);
        getValidPrice("price", price);

        // Create a new Items object
        Items newItem(id, name, quantity, price, category);

        items.push_back(newItem);

        cout << "\nItem added successfully!\n";
    }

    void updateItem() override
    {
        string id;
        cout << "Input ID: ";
        cin >> id;
        toUpperCase(id);

        bool found = false;
        for (auto &item : items)
        {
            if (item.getId() == id)
            {
                found = true;
                string choiceInput;
                cout << "\nID FOUND\n";
                cout << item.getName() << endl;

                // Input choice for update
                while (found)
                {
                    cout << "Press 1 to update price\nPress 2 to update quantity: ";
                    cin >> choiceInput;

                    if (choiceInput == "1" || choiceInput == "2")
                    {
                        break;
                    }
                    else
                    {
                        cout << "\nError: Please enter 1 or 2 only." << endl;
                    }
                }

                if (choiceInput == "1")
                {
                    double newPrice;
                    getValidPrice("new price", newPrice);
                    cout << "\nSUCCESS!\nPrice of Item " << item.getName() << " updated from " << item.getPrice() << " to " << newPrice << endl;
                    item.setPrice(newPrice);
                }
                else if (choiceInput == "2")
                {
                    int newQuantity;
                    getValidQuantity("new quantity", newQuantity);
                    cout << "\nSUCCESS!\nQuantity of Item " << item.getName() << " updated from " << item.getQuantity() << " to " << newQuantity << endl;
                    item.setQuantity(newQuantity);
                }
            }
        }

        if (!found)
        {
            cout << "Item with ID " << id << " not FOUND!" << endl;
        }
    }

    void removeItems() override
    {
        bool found = false;
        string id;
        cout << "Input ID to remove: ";
        cin >> id;
        toUpperCase(id);

        for (auto it = items.begin(); it != items.end();)
        {
            if (it->getId() == id)
            {
                found = true;
                it = items.erase(it);
                cout << "\nItem " << it->getName() << " \nwith ID of " << it->getId() << " has been removed.\n";
            }
            else
            {
                ++it;
            }
        }
        if (!found)
        {
            cout << "\nID " << id << " NOT FOUND\n";
        }
    }

    void searchItem() override
    {
        bool found = false;
        string id;

        cout << "Enter product's ID to search: ";
        cin >> id;
        toUpperCase(id);

        cout << "------------------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << left << setw(40) << "Name"
             << right << setw(10) << "Quantity"
             << right << setw(10) << "Price"
             << right << setw(20) << "Category" << endl;
        cout << "------------------------------------------------------------\n";

        for (const auto &item : items)
        {
            if (item.getId() == id)
            {
                found = true;

                cout << left << setw(10) << item.getId()
                     << left << setw(40) << item.getName()
                     << right << setw(10) << item.getQuantity()
                     << right << setw(10) << fixed << setprecision(2) << item.getPrice()
                     << right << setw(20) << "Category" << endl;
                cout << "------------------------------------------------------------\n";
                break;
            }
        }

        if (!found)
        {
            cout << "Product with ID: " << id << " not FOUND!" << endl;
        }
    }

    void sortItems()
    {
        string choice;
        string order;

        cout << "\nSort by: \n1 - Quantity\n2 - Price\n";
        cin >> choice;

        while (choice != "1" && choice != "2")
        {
            cout << "ERROR: input 1 or 2 only \n";
            cout << "\nSort by: \n1 - Quantity\n2 - Price\n";
            cin >> choice;
        }

        cout << "\nSort order: \n1 - Ascending\n2 - Descending\n";
        cin >> order;

        while (order != "1" && order != "2")
        {
            cout << "ERROR: input 1 or 2 only \n";
            cout << "\nSort order: \n1 - Ascending\n2 - Descending\n";
            cin >> order;
        }

        bool ascending = (order == "1");

        // Bubble Sort
        for (size_t i = 0; i < items.size() - 1; ++i)
        {
            for (size_t j = 0; j < items.size() - i - 1; ++j)
            {
                bool swapNeeded = false;

                if (choice == "1")
                { // Sort by Quantity
                    if ((ascending && items[j].getQuantity() > items[j + 1].getQuantity()) ||
                        (!ascending && items[j].getQuantity() < items[j + 1].getQuantity()))
                    {
                        swapNeeded = true;
                    }
                }
                else if (choice == "2")
                { // Sort by Price
                    if ((ascending && items[j].getPrice() > items[j + 1].getPrice()) ||
                        (!ascending && items[j].getPrice() < items[j + 1].getPrice()))
                    {
                        swapNeeded = true;
                    }
                }

                if (swapNeeded)
                {
                    Items temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }

        displaySortedItems();
    }

    void displaySortedItems()
    {
        cout << "\nSorted Items:\n";
        cout << "------------------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << left << setw(40) << "Name"
             << right << setw(10) << "Quantity"
             << right << setw(10) << "Price"
             << right << setw(20) << "Category" << endl;

        cout << "------------------------------------------------------------\n";

        for (const auto &item : items)
        {
            cout << left << setw(10) << item.getId()
                 << left << setw(40) << item.getName()
                 << right << setw(10) << item.getQuantity()
                 << right << setw(10) << fixed << setprecision(2) << item.getPrice()
                 << right << setw(20) << item.getCategory() << endl;
        }

        cout << "------------------------------------------------------------\n";
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
                updateItem();
            }
            else if (choice == "3") // remove items
            {
                removeItems();
            }
            else if (choice == "4") // Display items by category
            {
                displayItemsByCategory();
            }
            else if (choice == "5") // display all items
            {
                displayAllItems();
            }
            else if (choice == "6") // Search item
            {
                searchItem();
            }
            else if (choice == "7") // Sort items
            {
                sortItems();
            }
            else if (choice == "8") // Display low stock items
            {

                displayLowStockItems();
            }
            else if (choice == "9") // exit the program
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void displayAllItems() override
    {
        cout << "------------------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << left << setw(40) << "Name"
             << right << setw(10) << "Quantity"
             << right << setw(10) << "Price"
             << right << setw(20) << "Category" << endl;
        cout << "------------------------------------------------------------\n";

        for (const auto &item : items)
        {
            cout << left << setw(10) << item.getId()
                 << left << setw(40) << item.getName()
                 << right << setw(10) << item.getQuantity()
                 << right << setw(10) << fixed << setprecision(2) << item.getPrice()
                 << right << setw(20) << item.getCategory() << endl;
        }

        cout << "------------------------------------------------------------\n";
    }

    void displayItemsByCategory() override
    {
        string category;
        bool found = false;

        cout << "Enter category to display (clothing, electronics, entertainment): ";
        cin >> category;
        toUpperCase(category);

        cout << "------------------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << left << setw(40) << "Name"
             << right << setw(10) << "Quantity"
             << right << setw(10) << "Price"
             << right << setw(20) << "Category" << endl;
        cout << "------------------------------------------------------------\n";

        for (const auto &item : items)
        {
            if (category == item.getCategory())
            {
                found = true;
                cout << left << setw(10) << item.getId()
                     << left << setw(40) << item.getName()
                     << right << setw(10) << item.getQuantity()
                     << right << setw(10) << fixed << setprecision(2) << item.getPrice()
                     << right << setw(20) << item.getCategory() << endl;
            }
        }

        cout << "------------------------------------------------------------\n";

        if (!found)
        {
            cout << "\nNo items found in the category: " << category << endl;
        }
    }

    void displayLowStockItems() override
    {
        cout << "------------------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << left << setw(40) << "Name"
             << right << setw(10) << "Quantity"
             << right << setw(10) << "Price"
             << right << setw(20) << "Category" << endl;

        cout << "------------------------------------------------------------\n";

        for (const auto item : items)
        {
            if (item.getQuantity() <= 5)
            {

                cout << left << setw(10) << item.getId()
                     << left << setw(40) << item.getName()
                     << right << setw(10) << item.getQuantity()
                     << right << setw(10) << fixed << setprecision(2) << item.getPrice()
                     << right << setw(20) << item.getCategory() << endl;
            }
        }
    }
};

int main()
{
    Display display;
    display.handleInput();

    return 0;
}
