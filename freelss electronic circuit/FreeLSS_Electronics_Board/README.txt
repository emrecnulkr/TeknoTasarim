                   .:                     :,                                          
,:::::::: ::`      :::                   :::                                          
,:::::::: ::`      :::                   :::                                          
.,,:::,,, ::`.:,   ... .. .:,     .:. ..`... ..`   ..   .:,    .. ::  .::,     .:,`   
   ,::    :::::::  ::, :::::::  `:::::::.,:: :::  ::: .::::::  ::::: ::::::  .::::::  
   ,::    :::::::: ::, :::::::: ::::::::.,:: :::  ::: :::,:::, ::::: ::::::, :::::::: 
   ,::    :::  ::: ::, :::  :::`::.  :::.,::  ::,`::`:::   ::: :::  `::,`   :::   ::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  :::::: ::::::::: ::`   :::::: ::::::::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  .::::: ::::::::: ::`    ::::::::::::::: 
   ,::    ::.  ::: ::, ::`  ::: ::: `:::.,::   ::::  :::`  ,,, ::`  .::  :::.::.  ,,, 
   ,::    ::.  ::: ::, ::`  ::: ::::::::.,::   ::::   :::::::` ::`   ::::::: :::::::. 
   ,::    ::.  ::: ::, ::`  :::  :::::::`,::    ::.    :::::`  ::`   ::::::   :::::.  
                                ::,  ,::                               ``             
                                ::::::::                                              
                                 ::::::                                               
                                  `,,`


http://www.thingiverse.com/thing:1298438
FreeLSS Electronics Board by C_D is licensed under the Creative Commons - Attribution - Non-Commercial license.
http://creativecommons.org/licenses/by-nc/3.0/

# Summary

This is a small Raspberry Pi 'shield' for controlling a FreeLSS based 3D scanner.

The board measures just 42x52mm, and mounts directly on the Raspberry Pi GPIO port. It has an on board buck converter module which powers the stepper driver (Pololu-style DRV8825 or DRV8832) and also the Rasppberry Pi, so all you need is a single 12-24V plug pack.

-----------------------------------------

I have had enough interest in the PCB's that I have ordered a second batch. Send me a message if you are interested in getting hold of one!

-----------------------------------------

Assembly is pretty straight forward, all components are marked on the board. The only catch is the two MosFETs, check the pinout of the part you are using and make sure you put it in the right way round, the VN10LP for example has the pins the other way round to the outline marked on the board.

Make sure you adjust your DC-DC converter before attaching the board to the Raspberry Pi, you want your 5V output set at 4.9-5.1V

NOTE:
It has been brought to my attention that using an A4988 stepper driver module can be unreliable when using 5V supply and 3V3 logic signals. The minimum logic high voltage is 0.7*VDD or 3.5V, so 3V3 logic may not work on some boards. I have an A4988 driver on my board at home and it does work, however I cannot guarantee it will work in all cases.