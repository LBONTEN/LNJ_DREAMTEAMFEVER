# TODO lists

## General remarks
- Try to find a way to lock in setters to prevent editing of e.g. licence plates during the simulation
- Include tests for all items
- set up test & release targets

## Implementation
- [ ] class: RoadSystem
	- [ ] load simulation
	*maybe move this to a seperate parser class?*
	- [ ] dump simulation
	*should this be a part of the parser class as well?*
	- [ ] advance simulation
	- [ ] add, get/traverse car(s)
	- [ ] add, get/traverse road(s)
	- [ ] simulation empty?
	- [ ] i dunno, more querries

- [ ] class: Road
	- [ ] get & set name
	- [ ] get & set length
	- [ ] get & set connection
	- [ ] add, has?, get/traverse car(s)

- [ ] class: Vehicle
	- [ ] get & set licence plate
	- [ ] get & set road
	- [ ] get, set & advance acceleration
	- [ ] get, set & advance speed 
	- [ ] get, set & advance position

- [ ] class: Vehicle::Car
	- [ ] advance acceleration
	- [ ] advance speed
	- [ ] advance position

░░░░░░░░░░░▄▀▄▀▀▀▀▄▀▄░░░░░░░░░░░░░░░░░░ 
░░░░░░░░░░░█░░░░░░░░▀▄░░░░░░▄░░░░░░░░░░ 
░░░░░░░░░░█░░▀░░▀░░░░░▀▄▄░░█░█░░░░░░░░░ 
░░░░░░░░░░█░▄░█▀░▄░░░░░░░▀▀░░█░░░░░░░░░ 
░░░░░░░░░░█░░▀▀▀▀░░░░░░░░░░░░█░░░░░░░░░ 
░░░░░░░░░░█░░░░░░░░░░░░░░░░░░█░░░░░░░░░ 
░░░░░░░░░░█░░░░░░░░░░░░░░░░░░█░░░░░░░░░ 
░░░░░░░░░░░█░░▄▄░░▄▄▄▄░░▄▄░░█░░░░░░░░░░ 
░░░░░░░░░░░█░▄▀█░▄▀░░█░▄▀█░▄▀░░░░░░░░░░ 
░░░░░░░░░░░░▀░░░▀░░░░░▀░░░▀░░░░░░░░░░░░ 
╔═════════════════════════════════════╗
║ * You feel like you're going to     ║
║ have a ruff time.                   ║
║                                     ║
╚═════════════════════════════════════╝
┌───────┐ ┌───────┐ ┌───────┐ ┌───────┐
│/ FIGHT| │ ) PET | |6 ITEM | |X MERCY| 
└───────┘ └───────┘ └───────┘ └───────┘
