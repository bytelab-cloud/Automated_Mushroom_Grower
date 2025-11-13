# Automated Mushroom Grower

Below is a list of components that are required for the project along with advice for assembling everything.

Youtube Video - https://youtu.be/puENLGAer3o


<h2>Components</h2>

<h3>Main</h3>

 - Switches - https://amzn.to/43ZM5kb

 - 2.1mm x 5.5mm Barrel Plug (Power) - https://amzn.to/488htiZ

 - Buck Converter 3.0-40V to 1.5-35V - https://amzn.to/49MK26M

 - Humidifier Module - https://amzn.to/47Rz90S

 - 24V Relay Module - https://amzn.to/4paiQUi

 - Arduino Uno - https://amzn.to/47DPRCc

 - Prototype PCB Board - https://amzn.to/3JXiYaw

 - 1.8" SPI LCD Display Module - https://amzn.to/4nQIpbJ

 - 1 Inch Diameter tube - https://amzn.to/4hRGUIU

 - 12v LED Strip - https://amzn.to/443jgU0

 - 12v Power Supply - https://amzn.to/4paiY6e

 - 60mm Fan - https://amzn.to/3JTiFO1

 - SHT 31 sensor - https://amzn.to/48c7MQA

   - I havent tested it but the code should also work with a cheaper SHT 30 sensor you just sacrifice some accuracy in readings

 - Resistors

 - Transistors

 - 100uf Capacitors

 - Wire / Jumper Wires

<h3>Optional</h3>

 - Pin Headers (For easier connection of jumpoer wires to pcb board)

 - Heat Set Inserts (I did not use them but it could make it easier)

 - Heat Shrink

<h2>Assembly</h2>

<h3>3D Printed Parts</h3>

Almost all of the 3D printed parts can just be screwed together except for the top part of the humidifier and the top of the case for the electronics. The case is designed this way so there isnt a need for a lot of supports when printing the case.

 - For the case for the electronics the top can welded together using acetone or glue the rest of assembly for the case just requires screws and is simple and straight foward to assemble.

 - The humidifier is made up of 3 different parts that require some form of welding or gluing.

     - For connecting the top plate of the humidifier to the bottom exhaust port you can use acetone to weld the parts together and use hot glue to create a seal around the edges.
  
     - For connecting the bottom exhaust to the top exhaust you can do the same acetone welding process to connect the 2 parts but to make sure it is sealed it is preferred to use silicone but hot glue works too.

 <h3>Electronics</h3>

 Most of the electronics are stright foward except for the screen which I have forund to work better when the LED power pin is connected the arduino rather then drawing 5v from the pcb.

  - <h3>Transistors (Humidifier Module and LED Strip)</h3>
  
    - 2 transistors are used in the machine 1 controls the humidifier module which is connected to pin 6 on the arduino along with the LED strip which gets connected to pin 3 on the arduino.
   
    - The humidifier module requires a simple modification for proper fuction you simply need to remove the push button on the module board so that when the board receives power it turns on automatically.

 - <h3>Relay (LED Strip)</h3>

    - The relay connects to the fan and requires 12v and is connected to pin 7 on the arduino

- <h3>Buck Converter</h3>

  - Depending on your power supply you with either need 1 or 2 buck converters if your using a 12v power supply you need to split it into 2 channels 1 that will directly connect to the pcb to powwer the 12v fan and LED strip and 1 channel that is stepped down to 5v in the buck converter that then connects to the pcb to power the rest of the electronics. If you are using a higher voltage power supply youll need 2 buck converters 1 that steps down to 12v and one that steps down to 5v both are connected the same way after passing through the buck converter.

- <h3>Switch</h3>

  - the switch gets connecteed to pin 12 on the arduino and ground.
