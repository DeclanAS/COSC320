#ifndef GRAPH_H
#define GRAPH_H

#include <opencv2/opencv.hpp>
#include <unordered_map>
#include "Disjoint.h"

struct Vertex
{
    int count;
    cv::Vec3f colors;

    struct Vertex &operator+=(const Vertex &rhs)
    {
        count += rhs.count;
        colors += rhs.colors;
        return *this;
    }

    cv::Vec3f AverageColor()
    {
        return colors / count;
    }
};

struct Edge
{
    int a, b;
    float weight;

    bool operator<(const Edge &rhs) const
    {
        return weight < rhs.weight;
    }

    /*
    bool operator<(const Edge &lhs, const Edge &rhs) const
    {
        return lhs.weight < rhs.weight;
    }
    */
    
};

class Graph
{
public:
    Graph();

    /* performs image segmentiaion and creates the graph
     * This also creates all of the disjoint sets of forest
     * 
     * Guassian Blur: https://en.wikipedia.org/wiki/Gaussian_blur
     */
    
    void SegmentImage(cv::Mat &image, int threshold, int min_size);

    /* For the Dif() function we used opencv: 'cv::Vec3f', 'cv::Mat'
    * 
    * Euclidean Distance: https://en.wikipedia.org/wiki/Euclidean_distance
    * opencv: https://docs.opencv.org/3.4/dc/d84/group__core__basic.html
    * 
    * finds difference of two pixels by performing the euclidian diastance algolrithm using dot product
    */
    
    float Dif(const cv::Mat &image, int q1, int p1, int q2, int p2);

    /* Builds the graph
    * References 'Huttenlocher' paper on construction of pixels into the graph
    * This also relies of the datastructure cv::Mat for loading the image pixels
    */
    
    std::vector<Edge> build_graph(const cv::Mat &image);

    /* Builds the segmented graph
    * References 'Huttenlocher' paper on disjoint sets and forest
    */
    
    Disjoint segment_graph(int num_vertices, std::vector<Edge> &edges, float threshold);

private:
    
    /* Takes the image plus a disjoint set forest
     * recolors all of the pixels inside of the disjoin set
     * to the color of the average of all the pixels on that threshold range
     */
    
    void ForestColor(cv::Mat &image, Disjoint &forest);
};

#endif // GRAPH_H
