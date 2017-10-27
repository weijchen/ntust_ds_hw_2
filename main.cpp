//
//  main.cpp
//
//  Created by Liyan Wang, 2017/10/24.
//

#include <iostream>
#include "client.h"
#include "service.cpp"

const int MAX_CLIENT = 10;

int main()
{
    Client result[MAX_CLIENT];
    Client client_queue[MAX_CLIENT];
    int real_client_number = 0;
    
    // Create client queue array.
    cout << "Please enter time values for at most 10 clients row by row in order of: " << endl;
    cout << "Arrival Time, Service Time and Allowable Waiting Time." << endl;
    cout << "and separate time values by comma(,)." << endl;
    cout << "For example, ";
    cout << "If the arrival time, service time and allowable waiting time of a client are: " << endl;
    cout << "3, 5 and 7, then please enter: '3,5,7'." << endl;
    cout << "And please enter '-1' when there are no more entries." << endl << endl;

    for(int i = 0; i < MAX_CLIENT; i++)
    {
        int customer_id = i + 1;
        string time_string;
        cout << "Enter times for client[" << customer_id << "]:";
        cin >> time_string;
        if (time_string == "-1")
        {
            break;
        }
        real_client_number++;
        client_queue[i].create_client(customer_id, time_string);
    }

    // Selection sort by arrival time and allowable waiting time.
    sort_by_time(client_queue, real_client_number);

    // Start serving clients.
    serve_client(client_queue, result, real_client_number);

    // Print service result.
    for(int i = 0; i < real_client_number; i++)
    {
        result[i].print_result();
    }

    return 0;
}
