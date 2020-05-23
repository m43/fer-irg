//
// Created by m43 on 17. 05. 2020..
//

#ifndef FER_IRG_IFS_DATA_MODEL_H
#define FER_IRG_IFS_DATA_MODEL_H

#include <utility>
#include <vector>

using namespace std;

struct IfsFractalFunctionRow {
public:
    double a, b, c, d, e, f, pi;
};

class IfsFractal {
public:
    IfsFractal(const string &path) {
        ifstream infile(path);
        if (!infile) {
            throw invalid_argument("Nothing here. " + path);
        }

        string inputInOneLine;
        string line;
        while (getline(infile, line)) {
            line.erase(find_if(line.begin(), line.end(), [](int ch) {
                return ch == '#';
            }), line.end());

            if (!line.empty()) {
                inputInOneLine.append(line);
                inputInOneLine.append("\n");
            }
        }
        cout << inputInOneLine << endl;

        istringstream infileWithoutComments(inputInOneLine);

        infileWithoutComments >> n >> depth >> eta1 >> eta2 >> eta3 >> eta4;
        double pi_total = 0;
        while (getline(infileWithoutComments, line)) {
            line.erase(find_if(line.rbegin(), line.rend(), [](int ch) {
                return !isspace(ch);
            }).base(), line.end());

            if (line.empty()) {
                continue;
            }

            istringstream iss(line);
            IfsFractalFunctionRow row{};
            iss >> row.a >> row.b >> row.c >> row.d >> row.e >> row.f >> row.pi;
            functionRows.push_back(row);
            pi_total += row.pi;
        }
        if (pi_total - 1 > 0.000001) {
            throw invalid_argument(
                    "Total probabilities must add up to one in IFS fractal definition file. Found pi_total=" +
                    to_string(pi_total));
        }
    }

    int n;
    int depth;
    double eta1, eta2, eta3, eta4;
    vector<IfsFractalFunctionRow> functionRows;
};

class IfsDataModel {
public:
    IfsDataModel(int width, int height, shared_ptr<IfsFractal> ifs) :
            width_(width), height_(height), ifs_(std::move(ifs)) {}

    [[nodiscard]] int getWidth() const {
        return width_;
    }

    void setWidth(int width) {
        width_ = width;
    }

    [[nodiscard]] int getHeight() const {
        return height_;
    }

    void setHeight(int height) {
        height_ = height;
    }

    void increaseRecursionDepth() {
        ifs_->depth++;
    }

    void decreaseRecursionDepth() {
        if (ifs_->depth > 0) {
            ifs_->depth--;
        }
    }

    void decreaseNumberOfPoints(int n) {
        if (ifs_->n > n) {
            ifs_->n -= n;
        }
    }

    void increaseNumberOfPoints(int n) {
        ifs_->n += n;
    }

    [[nodiscard]] const shared_ptr<IfsFractal> &getIfs() const {
        return ifs_;
    }

    void setIfs(const shared_ptr<IfsFractal> &ifs) {
        ifs_ = ifs;
    }

private:
    int width_;
    int height_;
    shared_ptr<IfsFractal> ifs_;
};

#endif //FER_IRG_IFS_DATA_MODEL_H
