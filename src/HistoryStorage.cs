using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class HistoryStorage
{
    private static readonly string filePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "calc_history.dat");

    public static void SaveHistory(List<string> history)
    {
        using (FileStream stream = File.Create(filePath))
        {
            BinaryFormatter formatter = new BinaryFormatter();
            formatter.Serialize(stream, history);
        }
    }

    public static List<string> LoadHistory()
    {
        if (!File.Exists(filePath))
        {
            return new List<string>();
        }

        using (FileStream stream = File.OpenRead(filePath))
        {
            BinaryFormatter formatter = new BinaryFormatter();
            return (List<string>)formatter.Deserialize(stream);
        }
    }
}
