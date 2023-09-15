#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
    double x;
    double y;
};

// Function to calculate the area
double calculateArea(const vector<Point> &points)
{
    double area = 0.0;
    int n = points.size();

    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        area += (points[i].x * points[j].y - points[j].x * points[i].y);
    }

    return abs(area) / 2.0;
}

// Function to read points from a file
vector<Point> readPointsFromFile(const string &filename)
{
    vector<Point> points;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open the file " << filename << endl;
        return points;
    }

    string line;
    bool readingPoints = false;

    while (getline(file, line))
    {
        if (line == "PTS")
        {
            readingPoints = true;
            continue;
        }
        else if (line == "CON")
        {
            readingPoints = false;
            continue;
        }

        if (readingPoints)
        {
            istringstream iss(line);
            int id;
            double x, y;
            if (iss >> id >> x >> y)
            {
                points.push_back({x, y});
            }
        }
    }

    file.close();
    return points;
}

// function to find the point to remove for the largest area
int findPointToRemoveMaxArea(vector<Point> &points)
{
    double maxArea = 0.0;
    int pointToRemove = -1;

    for (int i = 0; i < points.size(); i++)
    {
        Point removedPoint = points[i];
        points.erase(points.begin() + i);

        double currentArea = calculateArea(points);
        if (currentArea > maxArea)
        {
            maxArea = currentArea;
            pointToRemove = i;
        }
        points.insert(points.begin() + i, removedPoint);
    }
    return (pointToRemove != -1) ? points[pointToRemove].x : -1;
}

// Function to calculate the centroid
Point calculateCentroid(const vector<Point> &points)
{
    Point centroid = {0.0, 0.0};
    int n = points.size();

    for (const Point &p : points)
    {
        centroid.x += p.x;
        centroid.y += p.y;
    }

    centroid.x /= n;
    centroid.y /= n;

    return centroid;
}

int main()
{
    // Read points from the file and calculate the largest area
    const string filename = "data.txt";
    vector<Point> points = readPointsFromFile(filename);
    if (!points.empty())
    {

        double largestArea = calculateArea(points);
        cout << "Largest area of the shape: " << largestArea << endl;

        int pointToRemove = findPointToRemoveMaxArea(points);
        if (pointToRemove != -1)
        {
            cout << "Remove point with X-coordinate: " << pointToRemove << " for the largest area." << endl;
        }
        else
        {
            cout << "No point to remove for the largest area." << endl;
        }

        Point centroid = calculateCentroid(points);
        cout << "Centroid coordinates: X = " << centroid.x << ", Y = " << centroid.x << endl;
    }

    return 0;
}
