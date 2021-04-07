//
// Created by marcos on 06/04/2021.
//
#include <ltr.hpp>

#include <memory>
#include <cstdlib>

using ltr::Ranker;
using ltr::DataSet;
using ltr::MAPScorer;
using ltr::AdaRank;

int main() {
    string base_path = std::getenv("OHSUMED");
    DataSet training_samples = ltr::load_svmlight(base_path + "/Data/All/OHSUMED.txt");
    AdaRank ranker(std::move(training_samples), std::make_unique<MAPScorer>(), {}, {}, 50, 0.003, 3);
    ranker.fit(true);
    return 0;
}