using System;

public class CSharpApp
{
  static void Main()
  {
    ShowMessage(name= "Jane", age: 17);
    ShowMessage(age: 20, name: "Tarjan");
    int a = 1;
  }

  public static void ShowMessage(int age, string name)
  {
    Console.WriteLine("{0} is {1} years old", name, age);
  }
}
