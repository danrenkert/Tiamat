# Tiamat
A wireless lighting system for Mines Little Theater using Arduino micro-controllers and nrf24l01+ radio frequency chips

This program integrates a python file reading system with the setup and running of a show.

Our network is made up of a single transmitter nrf-Arduino chip and multiple nrf-Arduino receivers

# File Reader/Main
    This runs the program. On startup it will ask for a file of cues for the show. The file has the
    following format:

        5H
        [# of receivers]
        [Cue Desciption],[First queue for the show]
        [Cue Description],[Second queue, etc.]
        ...

    5H at the start is just a confirmation the file typed is correct. The number of receivers determines the
    size of the following queues and lets the program know how many receivers to establish. The cues are an
    ordered list of binary strings, e.g. "100010101", where each one or zero refers to a single receiver's state.
    For example the queue "000" means we have 3 receivers, all of which are off. "111" is 3 receivers all on.
    "010" is 3 receivers where only the receiver with ID 2 is on.

# Transmitter
    Listens to the tiamat.py program for cues then processes and send a character array containing the cue to all
    recievers. 
    
    The transmitter code only needs the number of recievered updated for new shows.

# Receivers
    Each receiver has a unique, sequential ID which it will use to check if it needs to turn lights on or off.
    Upon receiving a code the chip will check the digit matching it's ID. If the digit is a 0, the relay is set
    to open, turing off the circuit. If it is a 1, the circuit is closed, turning on the lights.
    
    The reciever needs the number of recievers updated for new shows. Each reciever needs a new, sequential ID number
