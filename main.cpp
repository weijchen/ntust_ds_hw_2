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

    // Create client queue array.
    cout << "Please enter time values of each client in order of: ";
    cout << "Arrival Time, Service Time and Allowable Waiting Time." << endl;
    cout << "And separate time values by comma(,)." << endl;
    cout << "For example, ";
    cout << "If the arrival time, service time and allowable waiting time of a client is: " << endl;
    cout << "3, 5 and 7, then you should enter: '3,5,7'." << endl;
    Client client_queue[MAX_CLIENT];
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        client_queue[i].create_client(i+1);
    }

    // Selection sort by arrival time and allowable waiting time.
    sort_by_time(client_queue, MAX_CLIENT);

    // Start serving clients.
    serve_client(client_queue, result, MAX_CLIENT);

    // Print service result.
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        result[i].print_result();
    }

    return 0;
}
