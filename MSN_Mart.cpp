#include <bits/stdc++.h>
using namespace std;
// FUNCTIONS FOR "COLOURS"
int sales=0;
int amount=0;

void blue() {
    cout << "\033[1;34m";
}

void red() {
    cout << "\033[3;31m";
}

void yellow() {
    cout << "\033[1;33m";
}

void purple() {
    cout << "\033[4;35m";
}

void reset() {
    cout << "\033[0m";
}

string cleanString(const string& str) {
    string cleanedStr;
    for (char c : str) {
        if (isdigit(c) || c == '.' || c == ',') {
            cleanedStr += c;
        }
    }
    return cleanedStr;
}

// class for taking username and password
class Data {
    public:
    char username[25];
    char password[25];
};

Data datalist[3] = {
    {"Nikhil", "nikhil@123"},
    {"Manikanta", "mani@123"},
    {"Sowmith", "sowmith@123"},
};

// External variable for storing who is operating the system
char provider[20];

// Function for checking who is logging into the MSN-MART Login page
int checking() {
    char user[25], login[25];
    int i, k, n;
    static int flag = 0, pass = 0;
    cout << "USERNAME: ";
    cin >> user;
    strcpy(provider, user);

    for (i = 0; i < 3; i++) {
        k = strcmp(user, datalist[i].username);
        if (k == 0) {
            flag = 1;
            break;
        }
    }

    if (flag == 1) {
        cout << "PASSWORD: ";
        cin >> login;

        for (i = 0; i < 3; i++) {
            k = strcmp(login, datalist[i].password);
            if (k >= 0) {
                pass = 1;
                break;
            }
        }
    }

    if (flag == 0 || pass == 0) {
        red();
        cout << "You entered an invalid USERNAME/PASSWORD\n";
        cout << "1 - Try again\n2 - Exit\nPress any index: ";
        reset();
        cin >> n;

        if (n == 1) {
            checking();
        } else if (n == 2) {
            exit(9);
        }
    }

    if (pass == 1 && flag == 1) {
        return 1;
    } else {
        return 0;
    }
}

// class for the main product list
class Product {
    public:
    string name;
    int quantity;
    float price;
};

// Function for checking the existing stock
int stock_checking() {
    
    ifstream file("DMart.csv");
    Product me[499];
    int i = 0;

    if (!file) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;

    while (i < 499 && getline(file, line)) {
        istringstream iss(line);
        string name, priceStr, quantityStr;
        char comma;

        if (getline(iss, name, ',') && getline(iss, priceStr, ',') && getline(iss, quantityStr, ',')) {
            me[i].name = name;

            try {
                me[i].price = stof(cleanString(priceStr)); // Clean the "price" string
            } 
            catch (const invalid_argument& e) {
                cerr << "Invalid price format: " << e.what() << endl;
                continue; // Skip this entry if price conversion fails
            }

            try {
                me[i].quantity = stoi(cleanString(quantityStr)); // Clean the "quantity" string and convert to int
            }
             catch (const invalid_argument& e) {
                cerr << "Invalid quantity format: " << e.what() << endl;
                continue; // Skip this entry if quantity conversion fails
            }

            i++;
        }
    }

    int check_product;
    blue();
    cout << "Enter the number of different products you want to check: " << endl;
    reset();
    cin >> check_product;
    string check[check_product];

    for (int h = 0; h < check_product; h++) {
        cout << "Enter the name of the " << h + 1 << " product: " << endl;
        cin >> check[h];
    }

    int h, g;

    for (g = 0; g < check_product; g++) {
        for (h = 0; h < 499; h++) {
            int y = check[g].compare(me[h].name);

            if (y == 0) {
                yellow();
                cout << "Stock of " << me[h].name << " product is " << me[h].quantity << endl;
                reset();
                break;
            }
        }

        if (h == 499) {
            red();
            cout << "!!" << check[g] << " product is \"NOT FOUND\"!!" << endl;
            reset();
        }
    }

    file.close();
    return 0;
}


// Function for adding new stock
int adding() {

    ifstream file("DMart.csv");
    Product me[499];
     int i = 0;

    if (!file) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;

    while (i < 499 && getline(file, line)) {
        istringstream iss(line);
        string name, priceStr, quantityStr;
        char comma;

        if (getline(iss, name, ',') && getline(iss, priceStr, ',') && getline(iss, quantityStr, ',')) {
            me[i].name = name;

            try {
                me[i].price = stof(cleanString(priceStr)); // Clean the "price" string
            } 
            catch (const invalid_argument& e) {
                // cerr << "Invalid price format: " << e.what() << endl;
                continue; // Skip this entry if price conversion fails
            }

            try {
                me[i].quantity = stoi(cleanString(quantityStr)); // Clean the "quantity" string and convert to int
            }
             catch (const invalid_argument& e) {
                // cerr << "Invalid quantity format: " << e.what() << endl;
                continue; // Skip this entry if quantity conversion fails
            }

            i++;
        }
    }


    int add_num;
    blue();
    cout << "Enter the number of different kinds of products you want to add: " << endl;
    reset();
    cin >> add_num;
    string add[add_num];
    int num_prod[add_num];

    for (int h = 0; h < add_num; h++) {
        cout << "Enter the name of " << h + 1 << " product" << endl;
        cin >> add[h];
        cout << "Enter the number to add of " << h + 1 << " product" << endl;
        cin >> num_prod[h];
    }

    int h, g;

    for (g = 0; g < add_num; g++) {
        for (h = 0; h < 499; h++) {
            int y = add[g].compare(me[h].name);

            if (y == 0) {
                me[h].quantity += num_prod[g];
                purple();
                cout << me[h].name << " --> " << me[h].quantity << endl;
                reset();
                break;
            }
        }

        if (h == 499) {
            red();
            cout << "!!" << add[g] << " product is \"NOT FOUND\"!!" << endl;
            reset();
        }
    }

    file.close();

    // Updating the new stock in the main list (file)
    ofstream outFile("DMart.csv");
    
    if (!outFile) {
        cerr << "Error: File can't be opened." << endl;
        exit(1);
    }

    int d = 0;
    while (d < 499) {
        outFile << me[d].name << ',' << me[d].price << ',' << me[d].quantity<< endl;
        d++;
    }

    outFile.close();
    return 0;
}

// External integer variable to find the index of the given product in the list
int index;

// Function for finding the index of the particular product
int searching(const string& str, Product me[499]) {
    int k, i, ans;

    for (i = 0; i < 499; i++) {
        k = str.compare(me[i].name);

        if (k == 0) {
            index = i;
            ans = 10;
            break;
        }
    }

    if (i == 499) {
        ans = 1;
    }

    return ans;
}

// Function for finding the price of the given product
float find_price(const string& str, Product me[499]) {
    int k, i;
    float price;

    for (i = 0; i < 499; i++) {
        k = str.compare(me[i].name);

        if (k == 0) {
            price = me[i].price;
            break;
        }
    }

    return price;
}

// Function for calculating the length of a string
int length_of_name(const string& str) {
    return str.length();
}

// Function for billing
int billing() {

    ifstream file_1("DMart.csv");
    Product me[499];
     int i = 0;

    if (!file_1) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;

    while (i < 499 && getline(file_1, line)) {
        istringstream iss(line);
        string name, priceStr, quantityStr;
        char comma;

        if (getline(iss, name, ',') && getline(iss, priceStr, ',') && getline(iss, quantityStr, ',')) {
            me[i].name = name;

            try {
                me[i].price = stof(cleanString(priceStr)); // Clean the "price" string
            } 
            catch (const invalid_argument& e) {
                // cerr << "Invalid price format: " << e.what() << endl;
                continue; // Skip this entry if price conversion fails
            }

            try {
                me[i].quantity = stoi(cleanString(quantityStr)); // Clean the "quantity" string and convert to int
            }
             catch (const invalid_argument& e) {
                // cerr << "Invalid quantity format: " << e.what() << endl;
                continue; // Skip this entry if quantity conversion fails
            }

            i++;
        }
    }
   

    string name_customer;
    blue();
    cout << "Enter the name of the customer: ";
    reset();
    cin >> name_customer;
    int num_prod;
    blue();
    cout << "Enter the number of different products you need: ";
    reset();
    cin >> num_prod;

    struct Prescription {
        string items;
        int quant;
    };

    float billing_amount[num_prod];
    Prescription mem[num_prod];
    int k;

    for (int i = 0; i < num_prod; i++) {
        cout << "Enter the name of the " << i + 1 << " product: ";
        cin >> mem[i].items;
        k = searching(mem[i].items, me);

        if (k == 10) {
            cout << "Enter the quantity you need: ";
            cin >> mem[i].quant;

            if (me[index].quantity >= mem[i].quant) {
                billing_amount[i] = me[index].price * mem[i].quant;
                me[index].quantity -= mem[i].quant;
            } else {
                red();
                cout << mem[i].items << " Products's Stock is not available" << endl;
                reset();
                billing_amount[i] = 0.00;
            }
        } else {
            red();
            cout << mem[i].items << " Product is not available" << endl;
            reset();
            billing_amount[i] = 0.00;
        }
    }

    float total_amount = 0;

    for (int i = 0; i < num_prod; i++) {
        total_amount += billing_amount[i];
    }

    file_1.close();


    ofstream outFile("DMart.csv");

    if (!outFile) {
        cerr << "Error: File can't be opened." << endl;
        exit(1);
    }

    int d = 0;

    while (d < 499) {
        outFile << me[d].name << ',' << me[d].price << ',' << me[d].quantity<< endl;
        d++;
    }

    outFile.close();

    // string nani=name_customer+".txt";
    ofstream fp_bill(name_customer);

    if (!fp_bill) {
        cerr << "Error: File can't be opened." << endl;
        exit(1);
    }

    fp_bill << "'''===================================MSN-MART===================================" << endl;
    fp_bill << "Address:";

    for (int z = 0; z < 61; z++) {
        fp_bill << " ";
    }

    fp_bill << "DATE: " << __DATE__ << endl;
    fp_bill << "MSN-mart,";

    for (int z = 0; z < 60; z++) {
        fp_bill << " ";
    }

    fp_bill << "TIME: " << __TIME__ << endl;
    fp_bill << "Nagpur," << endl;
    fp_bill << "Maharashtra,";

    for (int z = 0; z < 57; z++) {
        fp_bill << " ";
    }

    fp_bill << "P.No: 73044 41207" << endl;
    fp_bill << "440006." << endl;

    for (int z = 0; z < 86; z++) {
        fp_bill << "_";
    }

    fp_bill << endl << endl;
    fp_bill << "Name of customer: " << name_customer << endl;
    fp_bill << "***** PRODUCTS LIST *****" << endl;

    for (int z = 0; z < 22; z++) {
        fp_bill << " ";
    }

    fp_bill << "NAME";

    for (int z = 0; z < 22; z++) {
        fp_bill << " ";
    }

    fp_bill << "|  QUANTITY |   PRICE   | SUB_TOTAL" << endl;

    int lth;

    for (int z = 0; z < num_prod; z++) {
        if (billing_amount[z] != 0) {
            fp_bill << z + 1 << ") " << mem[z].items;
            lth = length_of_name(mem[z].items);

            for (int r = 0; r < 45 - lth; r++) {
                fp_bill << " ";
            }

            fp_bill << "|";
            fp_bill << "    " << mem[z].quant << "   |";
            fp_bill << "   " << find_price(mem[z].items, me) << "   |";
            fp_bill << "   " << (mem[z].quant * find_price(mem[z].items, me)) << "   " << endl;
        }

        fp_bill << endl;
    }

    for (int s = 0; s < 67; s++) {
        fp_bill << " ";
    }

    fp_bill << "TOTAL: " << total_amount << endl;

    for (int d = 0; d < 42; d++) {
        fp_bill << "_ ";
    }

    fp_bill << endl;

    for (int y = 0; y < 48; y++) {
        fp_bill << " ";
    }

    fp_bill << "Bill Issued by: - " << provider << endl;

    for (int y = 0; y < 31; y++) {
        fp_bill << " ";
    }
    sales++;
    amount+=total_amount;
    fp_bill << "Thank You for visiting, VISIT AGAIN !!!!!'''" << endl << endl << endl;
    fp_bill.close();
    ifstream fp_bill_read(name_customer);
    char ch;
    purple();
    cout << "****************************************BILL*****************************************" << endl;
    reset();

    while (1) {
        ch = fp_bill_read.get();

        if (fp_bill_read.eof()) {
            break;
        } else {
            cout << ch;
        }
    }

    cout << endl;
    return 0;
}
void end_of_program()
{

    cout <<"==================================MSN STORES Private Limited=================================" << endl;
    cout<<"|                                                                                             |\n";
    cout<<"|                                                                                             |\n";
    cout<<"|                         ";
    blue();
    cout<<"The number of sales done today are "<<sales;
    reset();
    cout<<"                                |\n";
    cout<<"|                         ";
    purple();
    cout<<"The amount earned today is "<<amount;
    reset();
    cout<<"                                      |\n";
    cout<<"|                                                                                             |\n";
    cout<<"|                                                                                             |\n";
    cout <<"==================================MSN STORES Private Limited=================================" << endl;

}
int main() {
    blue();
    cout << "==================================WELCOME TO MSN-MART LOGIN PAGE=================================" << endl;
    reset();
    red();
    cout << "!!!***Kindly enter your login details***!!!" << endl;
    reset();
    int n;
    int k = checking();
    if (k == 0) {
        return 100;
    } else {
    entry:
        int b = 10;
        while (b != 0) {
            yellow();
            cout << "\n1-Stock checking" << endl;
            cout << "2-Add a new stock" << endl;
            cout << "3-billing" << endl;
            reset();
            red();
            cout << "Enter the input:";
            reset();
            cin >> n;
            if (n == 1) {
                stock_checking();
            } else if (n == 2) {
                adding();
            } else if (n == 3) {
                billing();
            } else {
                cout << "Entered an invalid input!!" << endl;
                goto entry;
            }
            blue();
            cout << "Enter any number to continue and for exit enter \"0\":" << endl;
            reset();
            cin >> b;
        }
    }
            end_of_program();
    return 0;
}
