// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include "CalculatorHistory.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace CalculationManager;
using json = nlohmann::json;

// Assuming HISTORYITEM is a struct that includes vectors of tokens and commands,
// and strings for expression and result.
// You might need to adapt this structure to whatever HISTORYITEM actually contains.

namespace {
    wstring GetGeneratedExpression(const vector<pair<wstring, int>>& tokens) {
        wstring expression;
        bool isFirst = true;

        for (auto const& token : tokens) {
            if (isFirst) {
                isFirst = false;
            } else {
                expression += L' ';
            }
            expression.append(token.first);
        }

        return expression;
    }

    json historyItemToJson(const shared_ptr<HISTORYITEM>& item) {
        json j;
        // Serialize relevant fields to JSON.
        // This is simplified; you'll need to handle complex types appropriately.
        j["expression"] = item->historyItemVector.expression;
        j["result"] = item->historyItemVector.result;
        return j;
    }

    shared_ptr<HISTORYITEM> jsonToHistoryItem(const json& j) {
        auto item = make_shared<HISTORYITEM>();
        // Deserialize JSON back into an HISTORYITEM.
        // Adjust according to the actual structure of HISTORYITEM.
        item->historyItemVector.expression = j["expression"].get<string>();
        item->historyItemVector.result = j["result"].get<string>();
        return item;
    }
}

CalculatorHistory::CalculatorHistory(size_t maxSize) : m_maxHistorySize(maxSize) {}

unsigned int CalculatorHistory::AddToHistory(_In_ shared_ptr<vector<pair<wstring, int>>> const& tokens,
                                              _In_ shared_ptr<vector<shared_ptr<IExpressionCommand>>> const& commands,
                                              wstring_view result) {
    shared_ptr<HISTORYITEM> spHistoryItem = make_shared<HISTORYITEM>();

    spHistoryItem->historyItemVector.spTokens = tokens;
    spHistoryItem->historyItemVector.spCommands = commands;
    spHistoryItem->historyItemVector.expression = GetGeneratedExpression(*tokens);
    spHistoryItem->historyItemVector.result = wstring(result);

    return AddItem(spHistoryItem);
}

unsigned int CalculatorHistory::AddItem(_In_ shared_ptr<HISTORYITEM> const& spHistoryItem) {
    if (m_historyItems.size() >= m_maxHistorySize) {
        m_historyItems.erase(m_historyItems.begin());
    }

    m_historyItems.push_back(spHistoryItem);
    SaveHistoryToFile(L"history.json"); // Save history after adding an item.
    return static_cast<unsigned>(m_historyItems.size() - 1);
}

bool CalculatorHistory::RemoveItem(unsigned int uIdx) {
    if (uIdx < m_historyItems.size()) {
        m_historyItems.erase(m_historyItems.begin() + uIdx);
        SaveHistoryToFile(L"history.json"); // Save history after removing an item.
        return true;
    }

    return false;
}

vector<shared_ptr<HISTORYITEM>> const& CalculatorHistory::GetHistory() {
    return m_historyItems;
}

shared_ptr<HISTORYITEM> const& CalculatorHistory::GetHistoryItem(unsigned int uIdx) {
    assert(uIdx < m_historyItems.size());
    return m_historyItems.at(uIdx);
}

void CalculatorHistory::ClearHistory() {
    m_historyItems.clear();
    SaveHistoryToFile(L"history.json"); // Save history after clearing.
}

void CalculatorHistory::SaveHistoryToFile(const wstring& filePath) {
    ofstream file(filePath);
    if (!file.is_open()) {
        // Handle file open error.
        return;
    }

    json historyList = json::array();
    for (auto& item : m_historyItems) {
        historyList.push_back(historyItemToJson(item));
    }

    file << historyList.dump(4); // Pretty print JSON.
    file.close();
}

void CalculatorHistory::LoadHistoryFromFile(const wstring& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        // Handle file open error.
        return;
    }

    json historyList = json::parse(file);
    file.close();

    m_historyItems.clear(); // Clear existing history before loading.

    for (const auto& itemJson : historyList) {
        auto historyItem = jsonToHistoryItem(itemJson);
        m_historyItems.push_back(historyItem);
    }
}

