
#include "othello_cut.h"
#include <iostream>

#include <tr1/unordered_map>

using namespace std;

struct stored_info_t {
    // [information to be stored in hash table]
    stored_info_t() { } // need at least one ctor without arguments
};

struct hash_function_t : public tr1::hash<state_t> {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};

class hash_table_t : public tr1::unordered_map<state_t, stored_info_t, hash_function_t> {
};

int main(int argc, const char **argv) {
    hash_table_t my_hash_table;

    // stores one state in hash table
    state_t state;
    stored_info_t info;
    my_hash_table.insert(make_pair(state, info));

    // print some statistics about hash table
    cout << "#elements in hash table = " << my_hash_table.size() << endl;
    cout << "#buckets in hash table = " << my_hash_table.bucket_count() << endl;

    // search the hash table for state just inserted
    hash_table_t::iterator it = my_hash_table.find(state);
    if( it == my_hash_table.end() ) {
        cout << "Element NOT FOUND in hash table" << endl;
    } else {
        cout << "Element FOUND in hash table" << endl;
    }

    return 0;
}

