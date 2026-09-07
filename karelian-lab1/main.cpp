#include <iostream>

int main() {
    int input;
    while (True) {
        std::cin >> input;
        switch (input) {
            case (1): 
                pipline->count++;
                break;
            case (2): 
                ks->count++;
                break;
            case (3): 
                print_obj();
                break;
            case (4): 
                redacted_pipline();
                break;
            case (5): 
                redacted_ks();
                break;
            case (6): 
                save();
                break;
            case (0): return 0;
            default:
                std::cout >> "Soory, write 0-6 in input"
                break;
        }
    }
}