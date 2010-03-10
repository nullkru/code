using System;

class Hello
{
	static void Main()
	{
		string blah = "hallo welt muetterfigger";
		Console.WriteLine(blah);
		
		string timestamp = DateTime.Now.ToString("HH:mm dd/mm/yyyy");
		Console.WriteLine("The time is now:" + timestamp);

		
	}
}
