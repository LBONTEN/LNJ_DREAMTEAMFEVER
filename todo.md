# TODO lists

## General remarks
- see also `//TODO`- comments in the c++ code (can be checked in CLion)
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

https://cdn.fbsbx.com/v/t59.2708-21/50189806_417819825625524_2384854451656589312_n.gif?_nc_cat=111&_nc_ht=cdn.fbsbx.com&oh=32e5dd4d102a3033becfe9d3b6d3f222&oe=5C8078E2
