# LNJ_DREAMTEAMFEVER
Lenny and Joren's Software Engineering Project. 

## Design
- RoadSystem contains a set of roads & vehicles.
At each step of the simulation, each vehicle in the system is stepped as well. This is done in a two step process: first all vehicles gather the required information about the system, then all cars update their own information accordingly. This prevents being dependent on the order in wich vehicles are updated.

- Roads contain a set of vehicles (a subset of those of the system) by their licence plate (and by their position on the road), as well as some attributes such as length and connections, a name and a pointer to the roadsystem it is a part of.
Roads do not change over time, thus they need not be stepped in the simulation.

- Vehicles contain a series of attributes such as acceleration, speed and position, as well as a licence plate (used as a UUID), the street they're on (by name) and a pointer to the roadsystem it is a part of.
At each step of the simulation, the vehicle's acceleration, speed and position (and possibly the road it's on) are updated.

                                         `-----`                                                
                                      `:+/-----/++++++/``                                       
                                     .s-       -   ````//++-                                    
                                    `y.        -y...      .o-                                   
                                   -y`          /NNhys.:   /o                                   
                                  -s..         .mNhsyyso   /o                                   
                                 .hsy-        `ym+syhNNh  `o/                                   
                                  .`d         /Nm/::+oyd  :s                                    
                                   ++       .sNMMm+s/yho `h`                                    
                                  -s.     .sNMmdMMNm:yy .s-       OH YES                              
                                 -s`  ..:/hMNNddNdNN:o- ++                                      
                                 /o+++:o-`sMhossosNm-: -`s/                                     
                                  ```` .y-:omNhyNNy-`.:o/+y                                     
                  `//+sss+++++ssssss+//-://:.oyyy-.::+::/+oosssso++++osso//:                    
                   ...:::+++::/:::://..+d+. `````` `:yh-.-+:::://:/++/::-..`                    
                           y/oo+-     `s+/////////////s:     `:+++`                             
                           h:s.os+.  `o:--/..    .:`/-.o-   /+-s:y                              
                          :s+/.`/++- +/./:-/:.  /dd`hm+.y`.:s`./+s-                             
                          o+y-/hh``:+y:.+/-+/-  +mNhNNo h+/.dy/:yo+                             
                         -yo- .y-   `:+-..:.-    -oo+-.:+.  -y. :oy-                            
                         y++-.s:      `:o.++osooss++-:o.     /o.-++y`                           
                        o+o/:oo`        +om-dmmhmmo+ss.      `so:++o+                           
                       :d// +s.       `-/om`+dMMNy-+sy.`      .s/ ++h-                          
                      .so/+sh`       -/:+om```+y-``oos./:`     .hs+/so`                         
                     -s/+`:s.     `-+-` ``+//:--://+-   .+:`    .s-.//o-                        
           ````    -/s//+y+.     -+:`       ``::-`        -/:`   .+y+//s:-    ````              
          /hdmds//o+s+`./+     -/:                          .+:`   +/..+s+o//smmhy:             
          `-oddmMdsho++:`    -+:`       ````------`````       -/:`  .:++shsmMmddo-`             
         .+sdmmNNd+/`      -/:`    `..://///:-----/////:-..     -/:`    `/+mMNmmds+`            
       `+shhhNmo:`       `/+`    ./oso.`               ./so/-`    :+.      `:sNNhdys+`          
       `osymms.        `/+.    .//.`                       .:+-    `/+.       .smmyoo`          
        ``--.        `:/:/:...++`                            `:o-..://:/.       .-..`           
                   `/+.  `.//+y+                              -yo//-`  `:+.                     
                 `:/.      `:/-                                `//.      `:+.                   
               `/+.      `:+.                                    `//.      `//.                 
             `:/.       :+-                                        `/+       `/+.               
           `/+.      `` o/                                          `d ``      `//.             
         `:+.       :od.o:                                          `h.yo+       `/+.           
       `/+-`````-////.-/.                                            `//`:+//:`````.++.         
       :+////////```                                                      ```-///////+/  
