Van Borm Joren & Bontenakel Lenny

  ~~ CONTRACT: XmlParser ~~

==============================================================================

operator []:

  input:    std::string key
    Name of a top-level tag in the xml-inputfile.

  output:   std:: vector<TiXmlElement>
    all instances with tag key. If there arent any, the returned vector will be empty

  préconditon: None

  postcondition:  No direct alterations to object.

==============================================================================
