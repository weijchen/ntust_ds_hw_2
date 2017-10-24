#include <iostream>
#include "client.h"
// --------------------
// Serving clients
// 3 cases: 
// if current user departure time ( arrival time(if current user is the first user) or previous user departure time + service time )
//   less than next user (arrival time + allowable waiting time)
//     // case 1: no swap
//     compute current user departure time
//   more than next user (arrival time + allowable waiting time)
//     if next user ( arrival time(if current user is the first user) or previous user departure time + service time)
//       less than current user (allowable waiting time + arrival time)
//         // case 2: swap
//         swap(current user, next user)
//         computer (next user departure time)
//       more than current user  (allowable waiting time + arrival time)
//         // case 3: user leaves
//         compute (current user departure time)
//         quit(next user)
// 
// Start time has 2 types:
// 1. arrival time (if the user is the first user in the queue after considering swapping)
// 2. previous user departure time
// --------------------

// c_array: client queue array, client_number: number of clients, c: current client
void serve_client(Client *c_array, Client *result, const int client_number)
{
    for(int c = 0; c < client_number; c++)
    {
        int current_user = c;
        int previous_user = c - 1;
        int next_user = c + 1;
        if (c <= 0) { previous_user = 0; }
        if (c >= client_number - 1) { next_user = client_number -1; }
        int current_user_start;
        int next_user_start;

        // Current client left without being served. (Determined by the time taken by previous client.)
        if (c_array[current_user].departure_time == -1 && c_array[current_user].is_served == false)
        {
            result[c_array[current_user].user_id - 1] = c_array[current_user];
            continue;
            // return;
        }

        // Determine when the client, including current and next, is being served.
        if (c == 0)
        {  // Special case: first client
            current_user_start = c_array[current_user].arrival_time;
            next_user_start = c_array[next_user].arrival_time;
        }
        else
        {
            while (c_array[previous_user].departure_time == -1 && previous_user > 0) { previous_user -= 1; }
            current_user_start = c_array[previous_user].departure_time;
            next_user_start = c_array[previous_user].departure_time;
        }
        
        // Start serving clients.
        if ((current_user_start + c_array[current_user].service_time) < 
            (c_array[next_user].arrival_time + c_array[next_user].allowable_waiting_time))
        {  // case 1: no swap, current user is served, then compute current user departure time.
            c_array[current_user].serve_client( current_user_start + c_array[current_user].service_time, true);
        }
        else
        {
            if ((next_user_start + c_array[next_user].service_time) <
                (c_array[current_user].arrival_time + c_array[current_user].allowable_waiting_time))
            {  // case 2: swap, next user is the new current user and is served, then compute new current user departure time.
                swap(c_array[current_user], c_array[next_user]);
                c_array[current_user].serve_client(current_user_start + c_array[current_user].service_time, true);
            }
            else
            {  // case 3: next user quit, current user is served, then compute current user departure time.
                c_array[current_user].serve_client(current_user_start + c_array[current_user].service_time, true);
                c_array[next_user].serve_client( -1, false );
            }
        }

        // Store clients by the order of client's id determined by input order.
        result[c_array[current_user].user_id - 1] = c_array[current_user];
    }
}

// Sort by arrival time first, if both have the same arrival time, then sort by allowable waiting time.
void sort_by_time(Client *client_queue, const int client_number)
{
    for(int i = 0; i < client_number; i++)
    {
        int j = i;
        for(int k = i + 1; k < client_number - 1; k++)
        {
            if (client_queue[k].arrival_time < client_queue[j].arrival_time) { j = k; }
            else if (client_queue[k].arrival_time == client_queue[j].arrival_time)
            {
                if (client_queue[k].allowable_waiting_time < client_queue[j].allowable_waiting_time) j = k;
            }
            swap(client_queue[i], client_queue[j]);
        }
    }
}