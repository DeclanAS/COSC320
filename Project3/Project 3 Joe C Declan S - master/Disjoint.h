#ifndef DISJOINT_H
#define DISJOINT_H

#include <vector>

typedef struct
{
    int parent;
    int rank;
    int size;
} Node;

typedef std::vector<Node> Forest;

/**
 * The Sudo code from Wiki was used to create our representation of a Disjoint Set
 * This methods was also referenced from the paper by 'Huttenlocher'
 * Forest Implementation: https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 * 
 * Functions Referenced:
 *  Find(x)  - Find root and update parents
 *  Merge(x) - Merge sets based on element color
 *  Size()   - simple getter function
 */

class Disjoint
{
public:
    Disjoint();
    Disjoint(int pixels);

    int find(int x);
    void merge(int x, int y);
    int size(int x) const;

private:
    Forest pixels;
};

#endif // DISJOINT_H
