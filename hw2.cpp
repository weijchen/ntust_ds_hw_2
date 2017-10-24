#include <iostream>
#include "client.h"

const int MAX_CLIENT = 6;

// Serve clients
// 3 cases: 
// if current user departure time ( arrival time(if current user is the first user) or previous user departure time + service time )
//   less than next user (arrival time + allowable waiting time)
//     no swap // case 1
//     compute current user departure time
//   more than next user (arrival time + allowable waiting time)
//     if next user ( arrival time(if current user is the first user) or previous user departure time + service time)
//       less than current user allowable waiting time + ( current user arrival time(if current user is the first user) or previous user departure time)
//         swap(current user, next user) // case 2
//         computer next user departure time
//       more than current user allowable waiting time + ( current user arrival time(if current user is the first user) or previous user departure time)
//         quit(next user)  // case 3
//         compute current user departure time
// 
// Start time has 2 types:
// 1. arrival time (if the user is the first user in the queue after considering swapping)
// 2. previous user departure time

// c_array: client queue array, c_number: number of clients, c: current client
void serve_client(Client *c_array, Client *result, int c_number, int c)
{
    int current_user = c;
    int previous_user = c - 1;
    int next_user = c + 1;
    if (c <= 0) { previous_user = 0; }
    if (c >= c_number - 1) { next_user = c_number -1; }

    // cout << "user: " << c + 1 << " ";
    // cout << "previous departure time: " << c_array[previous_user].departure_time << " ";
    // cout << "current service time: " << c_array[current_user].service_time << " ";
    // cout << "next arrival time: " << c_array[next_user].arrival_time << " ";
    // cout << "next allowable waiting time: " << c_array[next_user].allowable_waiting_time << " ";

    if(c_array[current_user].departure_time == -1 && c_array[current_user].is_served == false)
    {
        result[c_array[current_user].user_id - 1] = c_array[current_user];
        return;
    }

    if (c == 0)
    {
        // int current_user_start_time = c_array[current_user].arrival_time;
        // int next_user_start_time = c_array[next_user].arrival_time;

        if ((c_array[current_user].arrival_time + c_array[current_user].service_time) < 
            (c_array[next_user].arrival_time + c_array[next_user].allowable_waiting_time))
        {  // case 1: no swap, current user is served, then compute current user departure time.
            c_array[current_user].serve_client(
                c_array[current_user].arrival_time + c_array[current_user].service_time, 
                true
            );
        }
        else
        {
            if ((c_array[next_user].arrival_time + c_array[next_user].service_time) <
                (c_array[current_user].arrival_time + c_array[current_user].allowable_waiting_time))
            {  // case 2: swap, next user is the new current user and is served, then compute new current user departure time.
                Client temp;
                temp = c_array[current_user];
                c_array[current_user] = c_array[next_user];
                c_array[next_user] = temp;
                c_array[current_user].serve_client(
                    c_array[current_user].arrival_time + c_array[current_user].service_time, 
                    true
                );
            }
            else
            {  // case 3: next user quit, current user is served, then compute current user departure time.
                c_array[current_user].serve_client(
                    c_array[current_user].arrival_time + c_array[current_user].service_time, 
                    true
                );
                c_array[next_user].serve_client( -1, false );
            }
        }
    }
    else
    {
        // int start_time = c_array[previous_user].departure_time;
        // int next_user_start_time = c_array[previous_user].departure_time;

        while (c_array[previous_user].departure_time == -1 && previous_user > 0) { previous_user -= 1; }

        if ((c_array[previous_user].departure_time + c_array[current_user].service_time) < 
        (c_array[next_user].arrival_time + c_array[next_user].allowable_waiting_time))
        {  // case 1: no swap, current user is served, then compute current user departure time.
            c_array[current_user].serve_client(
                c_array[previous_user].departure_time + c_array[current_user].service_time, 
                true
            );
        }
        else
        {
            if ((c_array[previous_user].departure_time + c_array[next_user].service_time) <
                (c_array[current_user].arrival_time + c_array[current_user].allowable_waiting_time))
            {  // case 2: swap, next user is the new current user and is served, then compute new current user departure time.
                Client temp;
                temp = c_array[current_user];
                c_array[current_user] = c_array[next_user];
                c_array[next_user] = temp;
                c_array[current_user].serve_client(
                    c_array[previous_user].departure_time + c_array[current_user].service_time, 
                    true
                );
            }
            else
            {  // case 3: next user quit, current user is served, then compute current user departure time.
                c_array[current_user].serve_client(
                    c_array[previous_user].departure_time + c_array[current_user].service_time, 
                    true
                );
                c_array[next_user].serve_client( -1, false );
            }
        }
    }
    result[c_array[current_user].user_id - 1] = c_array[current_user];
}

int main()
{
    Client result[MAX_CLIENT];

    // Create client queue array.
    Client client_queue[MAX_CLIENT];
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        client_queue[i].create_client(i+1);
        // client_queue[i].print_info();
    }

    // Selection sort by arrival time and allowable waiting time.
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        int j = i;
        for(int k = i + 1; k < MAX_CLIENT - 1; k++)
        {
            if (client_queue[k].arrival_time < client_queue[j].arrival_time) { j = k; }
            else if (client_queue[k].arrival_time == client_queue[j].arrival_time)
            {
                if (client_queue[k].allowable_waiting_time < client_queue[j].allowable_waiting_time) j = k;
            }
            swap(client_queue[i], client_queue[j]);
        }
    }

    // Start serving clients.
    for(int c = 0; c < MAX_CLIENT; c++)
    {
        serve_client(client_queue, result, MAX_CLIENT, c);
    }

    // Print service result.
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        // client_queue[i].print_result();
        result[i].print_result();
    }

    return 0;
}