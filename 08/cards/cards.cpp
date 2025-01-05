#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr), bottom_(nullptr) {
}

Cards::~Cards() {
    while ( bottom_ != nullptr ) {
        Card_data* item_to_be_released = bottom_;
        bottom_ = bottom_->next;

        delete item_to_be_released;
    }
}

void Cards::print_from_bottom_to_top(std::ostream& s) {

    if (is_empty()) {
            return;
        }

    Card_data* current = bottom_;
    int running_number = 1;

    while (current != nullptr) {
        s << running_number << ". " << current->data << std::endl;
        current = current->next;
        running_number++;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s) {
    int running_number = 1;
    recursive_print(bottom_, s, running_number);
}

void Cards::add(int id) {
    Card_data* new_card = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_card;
        bottom_ = new_card;
    } else {
        top_->next = new_card;
        top_ = new_card;
    }
}

bool Cards::bottom_to_top() {
    if ( is_empty() || bottom_== top_ ) {
       return false;

    } else {
        Card_data* new_top = new Card_data{bottom_->data, nullptr};
        top_->next = new_top;
        top_ = new_top;

        Card_data* item_to_be_released = bottom_;
        bottom_ = bottom_->next;
        delete item_to_be_released;
    }
    return true;
}

bool Cards::top_to_bottom() {
    if ( is_empty() || bottom_== top_ ) {
       return false;
    }

    reverse_dect();
    bottom_to_top();
    reverse_dect();
    return true;
}

bool Cards::remove(int& id) {
    if (is_empty()) {
        return false;
    }

    id = top_->data;
    Card_data* item_to_be_released = top_;

    if (bottom_ == top_) {

        bottom_ = nullptr;
        top_ = nullptr;
    } else {

        Card_data* current = bottom_;
        while (current->next != top_) {
            current = current->next;
        }
        top_ = current;
        top_->next = nullptr;
    }

    delete item_to_be_released;
    return true;
}

bool Cards::reverse_dect() {
    if (is_empty() || bottom_ == top_) {
        return false;
    } else {
        Card_data* current = bottom_;
        Card_data* prev = nullptr;
        Card_data* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        top_ = bottom_;
        bottom_ = prev;

        return true;
    }
    return true;
}

Card_data* Cards::get_botmost() {
    if (is_empty())  {
        return nullptr;
    } else {
        return bottom_;
    }
}

Card_data* Cards::get_topmost() {
    if (is_empty())  {
        return nullptr;
    } else {
        return top_;
    }
}

bool Cards::is_empty() const {
   if ( bottom_ == nullptr ) {
      return true;
   } else {
      return false;
   }
}

void Cards::recursive_print(Card_data* bottom, std::ostream& s, int& running_number) {
    if (bottom == nullptr) {
            return;
        }

    recursive_print(bottom->next, s, running_number);
    s << running_number << ": " << bottom->data << std::endl;
    ++running_number;
}
