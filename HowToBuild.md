Check the PartsList to make sure you have all of the required pieces before you start assembly.  This requires a fair amount of soldering, so you should have a soldering iron, solder, and any additional tools that you want ready.

![http://bitspinner.googlecode.com/git/images/blank.jpg](http://bitspinner.googlecode.com/git/images/blank.jpg)

**Step 1.** Bend the leads for each of the 7 1K ohm resisters (brown-black-red-gold) and insert them into the holes above and below the 7 rectangles.  Flip the board over and solder each of the leads to the associated pads, and then trim the leads short.

![http://bitspinner.googlecode.com/git/images/resisters.jpg](http://bitspinner.googlecode.com/git/images/resisters.jpg)

**Step 2.** If you obtained a 28-pin DIP socket into the holes at the upper right of the board.  Line up the notch in the socket with the notch printed on the silkscreen.  Solder the pins, and insert the ATmega328 chip into the socket.  If you do not have a socket, just solder the chip directly to the board.  Double-check the orientation first.

**Step 3.** Insert the L4HC595N chip into the holes below the ATmega328 chip.  Line up the notch in the chip with the notch printed on the silkscreen.  Solder the pins.

**Step 4.** Find the 5V voltage regulator.  Bend the leads at a 90 degree angle just below where they thin out.  Insert the leads into the 3 holes below the outline on the silkscreen.  The large hole in the regulator's heat sink should line up with the large hole in the board, although you don't need to fasten them together.  Solder the pins and trim the leads short.

![http://bitspinner.googlecode.com/git/images/regulator.jpg](http://bitspinner.googlecode.com/git/images/regulator.jpg)

**Step 5.** Insert the 4 digit 7-segment LED display into the holes at the bottom of the board.  The decimal point for each digit should be at the bottom.  Solder the pins on the back and trim them short.

**Step 6.** Insert the 10-segment LED bargraph into the appropriate holes.  This part is wired upside-down, so the word 'Up' and the part number printed on the back should be upside-down.  Solder the pins and trim them short.

![http://bitspinner.googlecode.com/git/images/bargraph.jpg](http://bitspinner.googlecode.com/git/images/bargraph.jpg)

**Step 7.** Insert the two 330 ohm resister networks into the holes.  The pin with the dot above it (and a B next to it) should go in the square pad, and the rest of the pins go in the round pads.  Solder the pins.

![http://bitspinner.googlecode.com/git/images/res-network.jpg](http://bitspinner.googlecode.com/git/images/res-network.jpg)

**Step 8.** Insert the two mini switches into the holes marked S1 and S2.  Solder the pins and trim them.

**Step 9.** Insert the rotary encoder into the appropriate space.  Solder the pins in the back, including the two larger brackets for stability.

![http://bitspinner.googlecode.com/git/images/encoder.jpg](http://bitspinner.googlecode.com/git/images/encoder.jpg)

**Step 10.** Loosen the thumbscrew on the knob and place it over the rotary encoder so the screw is facing the flat part of the encoder shaft.  Leave a few millimeters of room between the bottom of the knob and the top of the encoder, and then tighten the thumbscrew.  You should be able to hear a click when you press on the button -- if not, you put the knob on too low.  Loosen it, lift it up a little bit, and retighten.

**Step 11.** Feed the black and red wires from the back of the board through the holes that are marked JP1 on the front.  Make sure you switch the power switch marked S2 to OFF before inserting batteries.

![http://bitspinner.googlecode.com/git/images/power.jpg](http://bitspinner.googlecode.com/git/images/power.jpg)

**Step 12.**  There is one mistake on the PCB which is going to make this step a bit difficult.  The 3 pins for the ceramic resonator (small orange blob) need to be soldered onto the small pads on the front of the board between the two ICs.  You will need to bend the legs together slightly, place it on top of the board so the legs line up with the pads, and then put a glob of solder to connect each lead to the pad.  Although it may be  a bit easier to do this at the beginning when no pieces are crowding the board, I prefer to save it for the end so I can tell immediately if I did it right.  (Without all three pins soldered properly none of the components will work.)

![http://bitspinner.googlecode.com/git/images/resonator.jpg](http://bitspinner.googlecode.com/git/images/resonator.jpg)

**Step 13.** If you soldered everything properly, you should now be able to flip S2 to ON and you should see a 0 on the display.  If not, try turning the knob.  If nothing happens, check all of your connections starting with the resonator.

![http://bitspinner.googlecode.com/git/images/working.jpg](http://bitspinner.googlecode.com/git/images/working.jpg)

**Step 14.** Unless you are mounting this somewhere, you will want to attach the battery pack to the back of the circuit board.  You could probably do this with foam tape or velcro, but I used a hot glue gun.  This has the added advantage that you can glue over any exposed leads on the back so you don't accidentally scratch yourself on them.  Just put a huge glob of hot glue on the back of the PCB, push the battery holder onto it, and then force more glue into the edges all the way around.

![http://bitspinner.googlecode.com/git/images/hotglue.jpg](http://bitspinner.googlecode.com/git/images/hotglue.jpg)

Read OperatingInstructions for information on how to use the device.