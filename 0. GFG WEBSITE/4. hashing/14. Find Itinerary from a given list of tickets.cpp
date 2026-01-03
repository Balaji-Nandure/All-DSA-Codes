/*
Problem:
Find Itinerary from a Given List of Tickets

Given a list of airline tickets represented as (source, destination) pairs,
find the complete travel itinerary in order.

Constraints / Assumptions:
- Each ticket is used exactly once.
- There is exactly one valid itinerary.
- The itinerary forms a continuous path.
- There is a unique starting point (source that is never a destination).

Examples:
Input:
Tickets = {
    ("Chennai", "Bangalore"),
    ("Bombay", "Delhi"),
    ("Goa", "Chennai"),
    ("Delhi", "Goa")
}

Output:
Bombay -> Delhi -> Goa -> Chennai -> Bangalore


Approach (Expected / Optimal – Hashing):
1. Store all tickets in a hash map: source → destination.
2. Also track all destination cities in another set/map.
3. The starting city is the one which:
   - Appears as a source
   - Does NOT appear as a destination
4. Once the start is found:
   - Repeatedly follow source → destination using the map
   - Print/store the path until no further destination exists.

Why this works:
- Since each ticket is used once and forms a single path,
  the start must be a source with no incoming edge.
- Hash map allows O(1) lookup of next destination.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-itinerary-from-a-given-list-of-tickets/

LeetCode:
No direct equivalent problem.
(Related to graph path reconstruction problems)
*/

vector<string> findItinerary(vector<pair<string, string>>& tickets) {
    unordered_map<string, string> next;
    unordered_set<string> destinations;

    // Step 1: Build mapping and destination set
    for (auto& t : tickets) {
        next[t.first] = t.second;
        destinations.insert(t.second);
    }

    // Step 2: Find starting point
    string start = "";
    for (auto& t : tickets) {
        if (destinations.find(t.first) == destinations.end()) {
            start = t.first;
            break;
        }
    }

    // Step 3: Build itinerary
    vector<string> itinerary;
    while (next.find(start) != next.end()) {
        itinerary.push_back(start);
        start = next[start];
    }
    itinerary.push_back(start); // last city

    return itinerary;
}
