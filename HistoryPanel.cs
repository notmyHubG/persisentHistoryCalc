using System.Collections.Generic;
using HistoryStorageNamespace;

public class HistoryPanel
{
    private List<string> calculationHistory;
    private HistoryDisplayComponent historyDisplayComponent;

    public HistoryPanel()
    {
        calculationHistory = HistoryStorage.LoadHistory();
        historyDisplayComponent = new HistoryDisplayComponent();
        UpdateHistoryDisplay();
    }

    public void AddHistoryEntry(string calculation)
    {
        calculationHistory.Add(calculation);
        HistoryStorage.SaveHistory(calculationHistory);
        UpdateHistoryDisplay();
    }

    private void UpdateHistoryDisplay()
    {
        historyDisplayComponent.Clear();
        foreach (string entry in calculationHistory)
        {
            historyDisplayComponent.AddEntry(entry);
        }
    }
}

public class HistoryDisplayComponent
{
    // Assuming this class is responsible for displaying the history in the UI.
    public void AddEntry(string entry)
    {
        // Code to add entry to the display.
    }

    public void Clear()
    {
        // Code to clear the display.
    }
}
