using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using YourNamespaceHere; // Assuming HistoryStorage is within this namespace

public class HistoryPanel
{
    private HistoryStorage _historyStorage = new HistoryStorage();
    private List<string> _currentHistory = new List<string>();

    public HistoryPanel()
    {
        LoadHistoryAndPopulateUI();
    }

    private void LoadHistoryAndPopulateUI()
    {
        _currentHistory = _historyStorage.LoadHistory();
        foreach (var historyItem in _currentHistory)
        {
            // Assuming AddToUI is a method that adds each item to the history panel UI
            AddToUI(historyItem);
        }
    }

    public void AddHistoryEntry(string calculation)
    {
        _currentHistory.Add(calculation);
        AddToUI(calculation);
        SaveHistoryAsync(_currentHistory);
    }

    private void AddToUI(string historyItem)
    {
        // Implementation to add historyItem to the UI component displaying the history
    }

    private async void SaveHistoryAsync(List<string> history)
    {
        await Task.Run(() => _historyStorage.SaveHistory(history)).ConfigureAwait(false);
    }
}
