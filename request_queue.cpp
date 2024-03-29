#include "request_queue.h"

using namespace std;

RequestQueue::RequestQueue(const SearchServer& search_server)
    : search_server_(search_server) {
}
    
vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
    // напишите реализацию
    vector<Document> found_documents = search_server_.FindTopDocuments(raw_query, status);
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

vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
    // напишите реализацию
    vector<Document> found_documents = search_server_.FindTopDocuments(raw_query);
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

int RequestQueue::GetNoResultRequests() const {
    // напишите реализацию
    int empty_results_requests = 0;
    for (QueryResult request : requests_) {
        if (request.request_amount == 0) {
            empty_results_requests += 1;
        }
    }
    return empty_results_requests;
}