By Van Borm Joren & Bontenakel Lenny

 CONTRACT: Parser
===================

---

  #### elemContent:

  ##### in:

    int index:

      index of top-level tag to search

    std::string key:

      searchkey for specific item to return. By default it is a nullstring,    
      in which case every item within the tag will be returned in a vector.

  ##### out:
    ```c++
    vector<const string&>
    ```

  ##### Précondition:

    None

  ##### Postcondition:

    None

---

  #### parseRoadSystem:    

  ##### in:     

    const string& filename:

      Name of file to parse

  ##### out:    

    RoadSystem*

  #####  Précondition:    

    File must be located in IO folder and it has to be a .xml-file.

  ##### Postcondition:    

    None
