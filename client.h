#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <string>

using namespace std;

class Client
{
public:
    int user_id;
    int arrival_time;
    int service_time;
    int allowable_waiting_time;
    int departure_time;
    bool is_served;

    void create_client(int customer_id)
    {
        user_id = customer_id;
        string time_string;
        cout << "Enter times for client[" << customer_id << "]:";
        cin >> time_string;

        string delimiter = ",";
        size_t pos = 0;
        string token;
        int count = 0;
        int TIME_NUMBER = 3; // arrival time, service time and allowable waiting time.
        // Split input string
        while ((pos = time_string.find(delimiter)) != std::string::npos && count < TIME_NUMBER - 1)
        {
            if (count < TIME_NUMBER)
            {
                token = time_string.substr(0, pos);
                if (count == 0) { arrival_time = stoi(token); }
                else { service_time = stoi(token); }
                time_string.erase(0, pos + delimiter.length());
                count++;
            }
        }
        allowable_waiting_time = stoi(time_string);
    }

    void print_info()
    {
        cout << "Client: " << user_id << ", ";
        cout << "Arrival Time: " << arrival_time << ", ";
        cout << "Service Time: " << service_time << ", ";
        cout << "Allowable Waiting Time: " << allowable_waiting_time << endl;
    }

    void print_result()
    {
        string served_result;
        if (is_served == true) { served_result = "Yes"; }
        else { served_result = "No"; }

        cout << "Client: " << user_id << ", ";
        cout << "Served or not?: " << served_result;
        if (is_served) { cout << ", " << "Departure Time: " << departure_time; }
        cout << endl;
    }

    void serve_client(int departure = 0, bool served = false)
    {
        departure_time = departure;
        is_served = served;
    }

};

#endif
