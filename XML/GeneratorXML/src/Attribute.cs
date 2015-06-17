using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

using System.IO;

namespace GeneratorXML
{
    class Attribute
    {
        public string m_fileName;
        public XmlElement m_dataXML;

        public StreamWriter m_stream;

        public void Dispatch()
        {
            GeneratorStruct();
        }

        public string GeneratorStruct()
        {
            string str = "";
            //Console.WriteLine( string.Format("{0}", m_fileName));
            str += string.Format("public struct db_{0}\n{1}\n", m_fileName,"{");
            XmlAttributeCollection ac = m_dataXML.Attributes;

            IEnumerator ie = ac.GetEnumerator();

            while (ie.MoveNext())
            {
                XmlAttribute record = ie.Current as XmlAttribute;
                //Console.WriteLine("attritubte : " + record.Name + "  " + record.Value);
                str += string.Format("  public  {0} {1};\n", record.Value, record.Name);
            }

            str += "}\n";

            return str;
        }

        public void GeneratorCS()
        {
        }
    }
}
