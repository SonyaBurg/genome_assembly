#include "genome.h"

#include <stack>
#include <unordered_map>
#include <vector>

namespace genome {

std::string assembly(const std::size_t k, const std::vector<std::string> & reads)
{
    if (k == 0 || reads.empty()) {
        return "";
    }

    std::unordered_map<std::string_view, std::vector<std::string_view>> graph;
    std::unordered_map<std::string_view, std::size_t> deg_in;
    for (const auto & i : reads) {
        for (std::size_t j = 0; j < i.size() - k; ++j) {
            graph[{i.data() + j, k}].push_back({i.data() + j + 1, k});
            ++deg_in[{i.data() + j + 1, k}];
        }
    }

    std::stack<std::string_view> st;
    std::string_view first = graph.begin()->first;
    std::vector<std::string_view> res;
    for (const auto & i : graph) {
        if (deg_in[i.first] < i.second.size()) {
            first = i.first;
            break;
        }
    }

    st.push(first);
    while (!st.empty()) {
        std::string_view v = st.top();
        auto & vertex = graph[v];
        if (vertex.empty()) {
            res.push_back(v);
            st.pop();
        }
        else {
            st.push(vertex.back());
            vertex.pop_back();
        }
    }
    std::string s{res.back()};
    s.pop_back();
    for (std::size_t i = res.size(); i >= 1; --i) {
        s += res[i - 1].back();
    }
    return s;
}

} // namespace genome
