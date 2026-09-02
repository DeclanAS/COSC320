#include <opencv2/opencv.hpp>
#include "Graph.h"

Graph::Graph()
{
    // Default Constructor
}

void Graph::SegmentImage(cv::Mat &image, int threshold, int min_size)
{
    int height = image.rows;
    int width = image.cols;

    /* What this does is perforam a blur on all of the pixels
    *  of the images to make segmentation easier
    */
    
    cv::Mat smoothed(image);
    smoothed.convertTo(smoothed, CV_32FC3);
    GaussianBlur(smoothed, smoothed, cv::Size(5, 5), 0.5);
    std::vector<Edge> edges = build_graph(smoothed);
    Disjoint forest = segment_graph(height * width, edges, threshold);

    // sort vector pixels and merge into forest
    for (Edge &edge : edges)
    {
        int a = forest.find(edge.a);
        int b = forest.find(edge.b);

        if ((a != b) && ((forest.size(a) < min_size) || (forest.size(b) < min_size)))
        {
            forest.merge(a, b);
        }
    }
    // recolor the disjoint set to the average color of the forest
    ForestColor(image, forest);
}

void Graph::ForestColor(cv::Mat &image, Disjoint &forest)
{
    int height = image.rows;
    int width = image.cols;

    // calculate average colors for all pixels in the forest
    std::unordered_map<int, Vertex> forest_set;
    std::unordered_map<int, cv::Vec3f> rgb_avg;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int v = forest.find(y * width + x);
            forest_set[v] += Vertex{1, image.at<cv::Vec3b>(y, x)};
        }
    }

    // iterate over average colors
    for (auto itr : forest_set)
        rgb_avg[itr.first] = itr.second.AverageColor();

    // change the color of all verticies/pixels to the average color
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int v = forest.find(y * width + x);
            image.at<cv::Vec3b>(y, x) = rgb_avg[v];
        }
    }
}

float Graph::Dif(const cv::Mat &image, int q1, int p1, int q2, int p2)
{
    // get the (r,g,b) of two verticies/pixels
    cv::Vec3f pix1 = image.at<cv::Vec3f>(p1, q1);
    cv::Vec3f pix2 = image.at<cv::Vec3f>(p2, q2);

    return sqrt((pix1 - pix2).dot((pix1 - pix2)));
}

std::vector<Edge> Graph::build_graph(const cv::Mat &image)
{
    int height = image.rows;
    int width = image.cols;

    int size = 4 * height * width;
    std::vector<Edge> edges(static_cast<unsigned long>(size));

    int num = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int current = width * y + x;
            if (x > 0)
            {
                edges[num].a = current;
                edges[num].b = width * y + (x - 1);
                edges[num].weight = Dif(image, x, y, x - 1, y);
                num++;
            }

            if (y > 0)
            {
                edges[num].a = current;
                edges[num].b = width * (y - 1) + x;
                edges[num].weight = Dif(image, x, y, x, y - 1);
                num++;
            }

            if (x > 0 && y > 0)
            {
                edges[num].a = current;
                edges[num].b = width * (y - 1) + (x - 1);
                edges[num].weight = Dif(image, x, y, x - 1, y - 1);
                num++;
            }

            if (x > 0 && y < height - 1)
            {
                edges[num].a = current;
                edges[num].b = width * (y + 1) + (x - 1);
                edges[num].weight = Dif(image, x, y, x - 1, y + 1);
                num++;
            }
        }
    }
    edges.resize(static_cast<unsigned long>(num));
    return edges;
}

Disjoint Graph::segment_graph(int num_vertices, std::vector<Edge> &edges, float threshold)
{
    // Sort the edges by weight
    sort(edges.begin(), edges.end());
    // Creates a forest from the edges
    Disjoint forest = Disjoint(edges.size());
    // Threshold is given by user
    std::vector<float> thresholds(static_cast<unsigned long>(num_vertices), threshold);

    // Iterate each edge over all edges
    /*
     * for each vertex a and b find() each vertex
     * then find if they are withen the threshold for the given forest with it's seed pixel
     * if withen threshold merge elemnts into the forest and compute new threshold 
     * (based on the current edge wight plus the given threshold / forest.size(a))
     */
    
    for (Edge &edge : edges)
    {
        int a = forest.find(edge.a);
        int b = forest.find(edge.b);

        // vertex a != b
        // edge.weight <= thresholds[a]
        // edge.weight <= thresholds[b]
        if (a != b && edge.weight <= thresholds[a] && edge.weight <= thresholds[b])
        {
            forest.merge(a, b);
            a = forest.find(a);
            thresholds[a] = edge.weight + threshold / forest.size(a);
        }
    }
    // return the forest
    return forest;
}
