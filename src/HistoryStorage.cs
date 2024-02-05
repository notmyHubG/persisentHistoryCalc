using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace YourNamespaceHere
{
    public class HistoryStorage
    {
        private readonly string _historyFilePath;

        public HistoryStorage()
        {
            _historyFilePath = "path/to/history_file.json"; // Adjust the path as necessary
        }

        public void SaveHistory(List<string> history)
        {
            try
            {
                var jsonString = JsonSerializer.Serialize(history);
                File.WriteAllText(_historyFilePath, jsonString);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred while saving history: {ex.Message}");
                // Consider logging the exception or handling it as per your application's error handling policy
            }
        }

        public List<string> LoadHistory()
        {
            try
            {
                if (File.Exists(_historyFilePath))
                {
                    var jsonString = File.ReadAllText(_historyFilePath);
                    return JsonSerializer.Deserialize<List<string>>(jsonString) ?? new List<string>();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred while loading history: {ex.Message}");
                // Consider logging the exception or handling it as per your application's error handling policy
            }

            return new List<string>();
        }
    }
}
