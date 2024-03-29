#pragma once
#include <vector>
#include <deque>

#include "document.h"
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
        // напишите реализацию
        std::vector<Document> found_documents = search_server_.FindTopDocuments(raw_query, document_predicate);
        QueryResult query_result;
        query_result.request_amount = found_documents.size();
        for (size_t i = 0; i < requests_.size(); ++i) {
            query_result.request_time += 1;
        }
        requests_.push_back(query_result);
        if ( requests_.size() > min_in_day_) {
            requests_.pop_front();
        }
        return found_documents;
    }
    
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const;
private:
    struct QueryResult {
        // определите, что должно быть в структуре
        int request_time;
        int request_amount;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    // возможно, здесь вам понадобится что-то ещё
    const SearchServer& search_server_;
}; 