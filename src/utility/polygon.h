//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_IRG_POLYGON_H
#define FER_IRG_POLYGON_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "point.h"
#include "line.h"
#include "edge.h"
#include "color.h"

using namespace std;

enum RelativePositionToPolygon {
    INSIDE, OUTSIDE, AT_EDGE
};

enum ConvexityType {
    CONCAVE, CONVEX_CLOCKWISE, CONVEX_COUNTERCLOCKWISE
};

class Polygon {
public:
    Polygon() {}

    Polygon(const vector<Point<int>> &vertices) : vertices_(vertices) {
        refresh();
    }

    const vector<Point<int>> &getVertices() const {
        return vertices_;
    }

    void addPoint(Point<int> p) {
        vertices_.push_back(p);
        refresh();
    }

    bool addPointIfStillConvex(Point<int> p) {
        // TODO Need an remodeling idea to make it more optimal
        Polygon poCopy = Polygon(vertices_);
        poCopy.addPoint(p);

        ConvexityType convexity = determineIfConvex(poCopy.getEdges());
        if (convexity == CONCAVE) {
            return false;
        }

        addPoint(p);
        return true;
    }

    ConvexityType getConvexityType() const {
        return convexity_;
    }

    int getXmin() const {
        return xmin_;
    }

    int getXmax() const {
        return xmax_;
    }

    int getYmin() const {
        return ymin_;
    }

    int getYmax() const {
        return ymax_;
    }

    const vector<Edge<int>> &getEdges() const {
        return edges_;
    }

    RelativePositionToPolygon getRelativePosition(Point<int> p) const {
        if (convexity_ == CONCAVE) {
            throw invalid_argument("Cannot determine relative position of point to polygon that is concave.");
        }

        int above = 0, intersecting = 0, below = 0;
        for (const Edge<int> &e: edges_) {
            int r = e.getA() * p.getX() + e.getB() * p.getY() + e.getC();
            if (r == 0) {
                intersecting++;
            } else if (r > 0) {
                above++;
            } else {
                below++;
            }
        }

        if (above == 0 || below == 0) {
            if (intersecting == 0) {
                return INSIDE;
            } else {
                return AT_EDGE;
            }
        } else {
            return OUTSIDE;
        }
    }

protected:
    static ConvexityType determineIfConvex(const vector<Edge<int>> &edges) {
        int above = 0, intersecting = 0, below = 0;

        for (int i = 0, n = edges.size(), i0 = n - 2; i < n; i++, i0++) {
            if (i0 >= n) {
                i0 = 0;
            }
            int r = edges[i0].getA() * edges[i].getStart().getX() + edges[i0].getB() * edges[i].getStart().getY() +
                    edges[i0].getC();
            if (r == 0) {
                intersecting++;
            } else if (r > 0) {
                above++;
            } else {
                below++;
            }
        }

        if (above == 0) {
            return CONVEX_CLOCKWISE;
        } else if (below == 0) {
            return CONVEX_COUNTERCLOCKWISE;
        } else {
            return CONCAVE;
        }
    }

private:
    vector<Point<int>> vertices_;
    ConvexityType convexity_;
    int xmin_;
    int xmax_;
    int ymin_;
    int ymax_;
    vector<Edge<int>> edges_;

    void refresh() {
        auto lastPoint = vertices_.back();
        xmin_ = lastPoint.getX();
        xmax_ = lastPoint.getX();
        ymin_ = lastPoint.getY();
        ymax_ = lastPoint.getY();

        edges_.clear();
        for (auto p: vertices_) {
            xmin_ = min(xmin_, p.getX());
            xmax_ = max(xmax_, p.getX());
            ymin_ = min(ymin_, p.getY());
            ymax_ = max(ymax_, p.getY());
            edges_.emplace_back(Edge<int>(lastPoint, p));
            lastPoint = p;
        }

        convexity_ = determineIfConvex(edges_);
        cout << determineIfConvex(edges_) << endl;
    }
};

#endif //FER_IRG_POLYGON_H
