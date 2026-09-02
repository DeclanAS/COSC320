#include "Disjoint.h"

Disjoint::Disjoint()
{
    // Default Constructor
}

Disjoint::Disjoint(int num_pixels)
{
    pixels.clear();
    pixels.resize(num_pixels);

    for (int i = 0; i < num_pixels; i++)
    {
        pixels[i].parent = i;
        pixels[i].rank = 1;
        pixels[i].size = 1;
    }
}

int Disjoint::find(int x)
{
    int y = x;

    while (y != pixels[y].parent)
    {
        y = pixels[y].parent;
    }

    pixels[x].parent = y;

    return y;
}

void Disjoint::merge(int x, int y)
{
    x = find(x); // X coordinate of vertex/pixel Seed
    y = find(y); // Y coordinate of vertex/pixel Seed

    if (x != y)
    {
        if (pixels[x].rank < pixels[y].rank)
        {
            pixels[x].parent = y;
            pixels[y].size += pixels[x].size;
        }
        else
        {
            pixels[y].parent = x;
            pixels[x].size += pixels[y].size;

            if (pixels[x].rank == pixels[y].rank)
            {
                pixels[x].rank++;
            }
        }
    }
}

int Disjoint::size(int x) const
{
    return pixels[x].size;
}
