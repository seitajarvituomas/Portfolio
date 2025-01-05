#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

using namespace std;

Queue::Queue(unsigned int cycle) : first_(nullptr), last_(nullptr), is_green_ (false), cycle_(cycle), queue_length() {

}

Queue::~Queue() {
    while ( first_ != nullptr ) {
       Vehicle* item_to_be_released = first_;
       first_ = first_->next;

       delete item_to_be_released;
    }
}

void Queue::enqueue(string const& reg) {


    if (is_green_ && vehicles_passed<cycle_) {
        cout << get_color()<< ": The vehicle " << reg << " need not stop to wait" << endl;
        vehicles_passed += 1;

        if (vehicles_passed == cycle_) {
            vehicles_passed = 0;
            is_green_ = false;
        }

    } else {
        Vehicle* new_vehicle = new Vehicle{reg, nullptr};

        if (first_ == nullptr) {
            first_ = new_vehicle;
            last_ = new_vehicle;
        } else {
            last_->next = new_vehicle;
            last_ = new_vehicle;
        }
        queue_length += 1;
    }
}

void Queue::print() const {

    if (is_empty()) {
        cout << get_color() << ": No vehicles waiting in traffic lights" << endl;
    } else {

        cout << get_color() << ": Vehicle(s) ";
        Vehicle* current = first_;
        while (current != nullptr) {
            cout << current->reg_num << " ";
            current = current->next;
        }

        if (is_green_) {
            cout << "can go on";
        } else {
            cout << "waiting in traffic lights";
        }
        cout << endl;
    }
}

void Queue::switch_light() {
    if (is_green_) {
        is_green_ = false;
        if (queue_length == 0) {
            cout << get_color() << ": No vehicles waiting in traffic lights" << endl;

        }
    } else {
        is_green_ = true;

        if (queue_length == 0) {
            cout << get_color() << ": No vehicles waiting in traffic lights" << endl;

        } else {
            cout << get_color() << ": Vehicle(s) ";
            Vehicle* current = first_;
            unsigned int count = 0;

            while (current != nullptr && count < cycle_) {
                cout << current->reg_num << " ";
                Vehicle* removed_vehicle = current;
                current = current->next;
                delete removed_vehicle;
                count++;
                queue_length -= 1;
                vehicles_passed +=1;

            }

            if (vehicles_passed == cycle_) {
                vehicles_passed = 0;
            }

            cout << "can go on" << endl;
            is_green_ = false;

            first_ = current;
        }
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
    vehicles_passed = 0;

}

bool Queue::is_empty() const {
   if ( first_ == nullptr ) {
      return true;
   } else {
      return false;
   }
}

string Queue::get_color() const {
    if (is_green_) {
        return "GREEN";
    } else {
        return "RED";
    }
}
