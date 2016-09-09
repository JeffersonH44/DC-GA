//
// Created by jefferson on 8/09/16.
//

#ifndef HOLA_SELECTION_H
#define HOLA_SELECTION_H

#include <vector>

template <class T>
class Selection {
public:
    virtual int chooseOne(std::vector<T> population) = 0;
    std::vector<int> chooseElements(int n, std::vector<T> population);
};


#endif //HOLA_SELECTION_H
