#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct User
{
    string username;
    string password;
    User(string u, string p) : username(u), password(p) {}
};
vector<User> readUsers(const string &filename)
{
    vector<User> users;
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string username, password;
            if (getline(iss, username, ',') && getline(iss, password))
            {
                users.push_back({username, password});
            }
        }
        file.close();
    }
    return users;
}
void Userinformation()
{
    int userid;
    string customer_id;
    string password;
    char usertype;
    int login_status = 0;
    cout << "Enter the following details for Create Customer Login Credential:\n" << endl;
    cout << "Customer ID: ";
    cin >> customer_id;
    cout << "Password: ";
    cin >> password;
    cout << "User type (B for Bank Clerk, C for Customer):\n ";
    cin >> usertype;
    // Generate unique numeric user ID
    // You can replace this with your own logic to generate unique user IDs
    userid = 1000 + rand() % 9000;
    // Check if the user ID already exists in the CSV file
    ifstream infile("userinformation.csv");
    string line;
    while (getline(infile, line))
    {
        if (line.find(to_string(userid)) != string::npos)
        {
            // User ID already exists, generate a new one
            userid = 1000 + rand() % 9000;
        }
    }
    infile.close();
    // Write user information to CSV file
    ofstream outfile("userinformation.csv", ios_base::app);
    outfile << userid << "," << customer_id << "," << password << "," << usertype << "," << login_status << endl;
    outfile.close();
    cout << "User information added successfully User ID is: " << userid << endl;
}
void CustomerAccount()
{
    cout << "Enter the following account details:" << endl;
    int account_number;
    string account_type, customer_id, account_status, opening_date;
    double balance;
    cout << "Account Number: ";
    cin >> account_number;
    cout << "Account Type: ";
    cin >> account_type;
    cout << "Customer ID: ";
    cin >> customer_id;
    cout << "Account Status: ";
    cin >> account_status;
    cout << "Opening Date: ";
    cin >> opening_date;
    cout << "Balance: ";
    cin >> balance;

    // Write account information to CSV file
    ofstream outfile("accountinformation.csv", ios_base::app);
    outfile << account_number << "," << account_type << "," << customer_id << "," << account_status << "," << opening_date << "," << balance << endl;
    outfile.close();

    cout << "Account information added successfully." << endl;
}
void writeUsers(const string &filename, const vector<User> &users)
{
    ofstream file(filename.c_str());
    if (file.is_open())
    {
        for (vector<User>::const_iterator it = users.begin(); it != users.end(); ++it)
        {
            file << it->username << "," << it->password <<endl;
        }
        file.close();
    }
}
bool isUserExists(const vector<User> &users, const string &username)
{
    for (vector<User>::const_iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it->username == username)
        {
            return true;
        }
    }
    return false;
}
void signUp(vector<User> &users)
{
    string username, password;
    cout << "Enter a username for: \n";
    cin >> username;
    if (isUserExists(users, username))
    {
        cout << "User already exists. Please choose a different username." << endl;
        return;
    }
    cout << "Enter a password: \n";
    cin >> password;
    // users.push_back({username, password});
    users.push_back(User(username, password));
    writeUsers("users.csv", users);
    cout << "User registered successfully!" << endl;
}
bool signIn(const vector<User> &users)
{
    string username, password;
    cout << "Enter your username: \n";
    cin >> username;
    cout << "Enter your password: \n";
    cin >> password;
    bool found = false;
    for (vector<User>::const_iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it->username == username && it->password == password)
        {
            found = true;
            break;
        }
    }
    return found;
}
bool clerk_login()
{
    int exit;
    string username, password;
    string un, pw;
    cout << "Enter Clerk Username:\n";
    cin >> username;
    cout << "Enter password:\n";
    cin >> password;
    ifstream input("clerk.csv");
    while (input >> un >> pw)
    {
        if (un == username && pw == password)
        {
            exit = 1;
        }
    }
    input.close();
    if (exit == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Customer
{
private:
public:
    void ViewDetails();
    void MoneyTransfer();
    void CustomerTransactions();
};
class BankStaff
{
public:
    void CreateAccount();
    void DeleteCustomer(string CustomerId);
    void ModifyDetails(string CustomerId);
    void CreditMoney();
    void DebitMoney();
    void TrasactionDetails();
};
void Customer ::ViewDetails()
{
    string customer_id, name, type, address1, address2, address3, city, state, country, pincode;
    
    cout<<"Enter customer Id for View Details :\n";
    cin>>customer_id;
    ifstream customer_file("customer.csv");
    string customer_line;
    while (getline(customer_file, customer_line))
    {
        stringstream customer_ss(customer_line);
        string customer_field;
        getline(customer_ss, customer_field, ',');
        if (customer_field == customer_id)
        {
            getline(customer_ss, name, ',');
            getline(customer_ss, type, ',');
            getline(customer_ss, address1, ',');
            getline(customer_ss, address2, ',');
            getline(customer_ss, address3, ',');
            getline(customer_ss, city, ',');
            getline(customer_ss, state, ',');
            getline(customer_ss, country, ',');
            getline(customer_ss, pincode, ',');

            break;
        }
    }
    customer_file.close();

    ifstream account_file("accountinformation.csv");
    string account_line;
    cout << "Account details for customer ID " << customer_id << ":\n";
    cout << "Account Number\tType\t\tStatus\tBalance\tOpening Date\n";
    while (getline(account_file, account_line))
    {
        stringstream account_ss(account_line);
        string account_field;
        getline(account_ss, account_field, ',');
        if (account_field == customer_id)
        {
            string account_number, account_type, account_status, account_balance, account_date;
            getline(account_ss, account_number, ',');
            getline(account_ss, account_type, ',');
            getline(account_ss, account_status, ',');
            getline(account_ss, account_balance, ',');
            getline(account_ss, account_date, ',');
            // std::cout <<"Account Number:"<< account_number <<endl;
            // cout <<"Account Type: "<< account_type <<endl;
            // cout<<"Account Status: "<< account_status << endl;
            // cout <<"Account Balance: "<<account_balance << endl;
            // cout<<"Account Opening Date: " <<account_date << std::endl;
            cout << account_number << "\t\t" << account_type << "\t\t" << account_status << "\t" << account_balance << "\t" << account_date << std::endl;
        }
    }
    account_file.close();

    cout << "\nCustomer details for ID " << customer_id << ":\n";
    cout << "Name: " << name<< std::endl;
    cout << "Type: " << type << std::endl;
    cout << "Address1: " << address1 << std::endl;
    cout << "Address2: " << address2 << std::endl;
    cout << "Address3: " << address3 << std::endl;
    cout << "City: " << city << std::endl;
    cout << "State: " << state << std::endl;
    cout << "Country: " << country << std::endl;
    cout << "Pincode: " << pincode << std::endl;
   
}


void Customer ::MoneyTransfer()
{
    cout << "Welcome to the MoneyTransfer Method:" << endl;
}
void Customer ::CustomerTransactions()
{
    cout << "Welcome to Customer Transaction Page:" << endl;
}
void BankStaff ::CreateAccount()
{
    
       
        string CustomerId, Name, Type, Address1, Address2, Address3, City, State, Country, Pincode;
        cout << "Enter customer details:" << endl;
        cout << "Customer ID: ";
        cin >> CustomerId;
        cout << "Name: ";
        cin >> Name;
        cout << "Type: ";
        cin >> Type;
        cout << "Address line 1: ";
        cin >> Address1;
        cout << "Address line 2: ";
        cin >> Address2;
        cout << "Address line 3: ";
        cin >> Address3;
        cout << "City: ";
        cin >> City;
        cout << "State: ";
        cin >> State;
        cout << "Country: ";
        cin>>Country;
        cout << "Pin code: ";
        cin>>Pincode;

        // Open the customer CSV file in append mode and write the new customer's details to it
        ofstream customer_file("customer.csv",ios::out | ios::app);
        // customer_file << "CustomerId, Name, Type, Address1, Address2, Address3, City, State, country, pincode" << endl;
        vector<string> customer_details;
        customer_details.push_back(CustomerId);
        customer_details.push_back(Name);
        customer_details.push_back(Type);
        customer_details.push_back(Address1);
        customer_details.push_back(Address2);
        customer_details.push_back(Address3);
        customer_details.push_back(City);
        customer_details.push_back(State);
        customer_details.push_back(Country);
        customer_details.push_back(Pincode);
        for (vector<string>::const_iterator i = customer_details.begin(); i != customer_details.end(); ++i)
        {
            customer_file << *i << ",";
        }
        customer_file<<endl;
        customer_file.close();
    }

void BankStaff ::DeleteCustomer(string CustomerId)
{
        ifstream customer_file("customer.csv");
        ofstream temp_file("temp.csv");
        string line;
        while (getline(customer_file, line))
        {
            stringstream ss(line);
            string id;
            getline(ss, id, ',');
            if (id != CustomerId)
            {
            temp_file << line << endl;
            }
        }
        customer_file.close();
        temp_file.close();

        // Remove the old customer CSV file and rename the temp file to customer.csv
        remove("customer.csv");
        rename("temp.csv", "customer.csv");
}
void BankStaff ::ModifyDetails(string CustomerId)
{
        
            ifstream customer_file("customer.csv");
            ofstream temp_file("temp.csv");
            bool customer_found = false;
            string line;
            while (getline(customer_file, line))
            {
            // Extract the customer ID from the line
            string id = line.substr(0, line.find(','));
            if (id == CustomerId)
            {
                customer_found = true;
                // Get the updated customer details from the user
                string Name, Type, Address1, Address2, Address3, City, State, Country, Pincode;
                cout << "Enter customer details:" << endl;
                cout << "Customer ID: ";
                cin >> CustomerId;
                cout << "Name: ";
                cin >> Name;
                cout << "Type: ";
                cin >> Type;
                cout << "Address line 1: ";
                cin >> Address1;
                cout << "Address line 2: ";
                cin >> Address2;
                cout << "Address line 3: ";
                cin >> Address3;
                cout << "City: ";
                cin >> City;
                cout << "State: ";
                cin >> State;
                cout << "Country: ";
                cin >> Country;
                cout << "Pin code: ";
                cin >> Pincode;
                // Write the updated customer details to the temp file
                temp_file << CustomerId << ',' << Name << ',' << Type << ',' << Address1 << ',' << Address2 << ',' << Address3 << ',' << City << ',' << State << ',' << Country << ',' << Pincode << endl;
                cout << "Customer details updated successfully." << endl;
            }

            else
            {
                // Write the current customer details to the temp file
                temp_file << line << endl;
            }
            }
            customer_file.close();
            temp_file.close();
            if (!customer_found)
            {
            cout << "Customer with ID " << CustomerId << " not found." << endl;
            remove("temp.csv");
            }
            else
            {
            // Remove the old customer CSV file and rename the temp file to customer.csv
            remove("customer.csv");
            rename("temp.csv", "customer.csv");
            }
        }
void BankStaff ::CreditMoney()
{
    cout << "Welcome to Credit Money Details:" << endl;
}
void BankStaff::DebitMoney()
{
    cout << "Welcome to DebitMoney Details:" << endl;
}
void BankStaff ::TrasactionDetails()
{
    
            int trans_id;
            char type;
            int account_id_src;
            int account_id_dst;
            double amount;
            int account_number;

            cout << "Enter the following transaction details:" << endl;
            cout << "Transaction ID: ";
            cin >> trans_id;
            cout << "Type (D for Debit, C for Credit): ";
            cin >> type;
            cout << "Source Account ID: ";
            cin >> account_id_src;
            cout << "Destination Account ID : ";
            cin >> account_id_dst;
            cout << "Amount: ";
            cin >> amount;
            cout << "Account Number: ";
            cin >> account_number;

            // Write transaction details to CSV file
            ofstream outfile("TransactionDetails.csv", ios_base::app);
            outfile << trans_id << "," << type << "," << account_id_src << "," << account_id_dst << "," << amount << "," << account_number << endl;
            outfile.close();

            cout << "Transaction details added successfully." << endl;
    
}
int main()
{
    vector<User> users = readUsers("users.csv");
    int n;
    cout << "Enter 1 for Customer login: \n";
    cout<< "Enter 2 to for BankStaff login: \n";
    cout<<"Enter 3 for Exit: \n";
    cin >> n;
    switch (n)
    {
    case 1:
        int choice1;
        while (true)
        {
            cout << "\nMenu:" << endl;
            cout << "1. Sign In " << endl;
            cout << "2. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice1;
            switch (choice1)
            {
            case 1:
                if (signIn(users) == true)
                {
                    Customer c1;
                    int n2;
                    cout << "Enter 1 for View Details\n";
                    cout << "Enter 2 for View MoneyTransfer\n";
                    cout << "Enter 3 for View Customer Transaction\n";
                    cout<<"Enter 4 for Exit:\n";
                    cin >> n2;
                    switch (n2)
                    {
                    case 1:
                        c1.ViewDetails();
                        break;
                    case 2:
                        c1.MoneyTransfer();
                        break;
                    case 3:
                        c1.CustomerTransactions();
                        break;
                    case 4:
                    main();
                    break;
                    default:
                        break;
                    }
                    break;
                }
                else
                {
                    cout << "Username and Password is not correct!!";
                    cout << "\n Try Again!!";
                }
                break;
            case 2:
                main();
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

    case 2:
        int choice;
        while (true)
        {
            cout << "\nMenu:" << endl;
            
            cout << "1. Sign In" << endl;
            cout << "2. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                if (clerk_login() == true)
                {
                    int n3;
                    cout << "Enter 1 for Create Account:\n";
                    cout << "Enter 2 for CreditMoney:\n";
                    cout << "Enter 3 for DebitMoney:\n";
                    cout << "Enter 4 for DeleteCustomer:\n";
                    cout << "Enter 5 for EditDetails:\n";
                    cout << "Enter 6 for TransactionDetails:\n";
                    cout<<"Enter 7 for Exit:\n";
                    cin >> n3;
                    BankStaff b1;
                    string customer_id;
                    switch (n3)
                    {
                    case 1:
                        b1.CreateAccount();
                        Userinformation();
                        signUp(users);
                        CustomerAccount();
                        break;
                    case 2:
                        b1.CreditMoney();
                        break;
                    case 3:
                        b1.DebitMoney();
                        break;
                    case 4:
                        cout << "Enter the customer ID to delete: ";
                        cin>>customer_id;
                        b1.DeleteCustomer(customer_id);
                        break;
                    case 5:
                        cout << "Enter Customer ID to modify: ";
                        // getline(cin, customer_id);
                        cin >> customer_id;
                        b1.ModifyDetails(customer_id);
                        break;
                    case 6:
                        b1.TrasactionDetails();
                        break;
                    case 7:
                        return main();
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    cout << "Failed";
                }
                break;
            case 2:
                main();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
        
        break;
    default:
        break;
    }
}