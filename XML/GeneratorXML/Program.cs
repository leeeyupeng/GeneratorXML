using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GeneratorXML
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("GeneratorAttribute  start");
            GeneratorAttribute ag = new GeneratorAttribute();
            ag.m_fileOutDir = "E:\\users\\administrator.user-ho7ku9ob20\\documents\\visual studio 2012\\Projects\\XML\\out\\xml";
            ag.m_xmlFileDir = "E:\\users\\administrator.user-ho7ku9ob20\\documents\\visual studio 2012\\Projects\\XML\\out\\db";
            ag.Dispatch();
            Console.WriteLine("GeneratorAttribute  success");

            Console.WriteLine("press enter quit!");
            Console.Read();
        }
    }
}
