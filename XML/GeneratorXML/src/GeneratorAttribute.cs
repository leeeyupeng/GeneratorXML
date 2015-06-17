using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Xml;

namespace GeneratorXML
{
    class GeneratorAttribute
    {
        public string m_fileOutDir;
        public string m_xmlFileDir; 
        public void Dispatch()
        {
            string[] fileNames = Directory.GetFiles(m_xmlFileDir);
            Directory.CreateDirectory(m_fileOutDir + "\\struct");
            Directory.CreateDirectory(m_fileOutDir + "\\generator");

            foreach (string file in fileNames)
            {
                if (file.Substring(file.LastIndexOf(".") + 1) == "xml")
                {
                    string fileName = file.Substring(file.LastIndexOf("\\") + 1,file.LastIndexOf(".") - file.LastIndexOf("\\") - 1);
                    string outFileStruct = m_fileOutDir + "\\struct\\db_" + fileName + ".cs";

                    FileStream fileStream = new FileStream(outFileStruct, FileMode.Create);
                    StreamWriter sw = new StreamWriter(fileStream);

                    sw.Write("using System;\nusing System.Collections;\n\n");

                    XmlDocument xmlDoc = new XmlDocument();
                    try
                    {
                        xmlDoc.Load(file);
                        XmlElement root = xmlDoc.DocumentElement;

                        XmlNodeList nodeList = root.GetElementsByTagName("Attribute");
                        IEnumerator ie = nodeList.GetEnumerator();

                        while (ie.MoveNext())
                        {
                            XmlElement record = ie.Current as XmlElement;

                            if (record != null)
                            {
                                Attribute at = new Attribute();
                                at.m_fileName = fileName;
                                at.m_stream = sw;
                                at.m_dataXML = record;
                                //at.Dispatch();

                                //Console.WriteLine(at.GeneratorStruct());
                                sw.Write(at.GeneratorStruct());
                            }
                        }

                        sw.Close();
                        fileStream.Close();
                    }
                    catch (Exception e)
                    {
                    }
                }
            }
        }
    }
}
