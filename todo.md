# TODO lists

## General remarks
- see also `//TODO`- comments in the c++ code (can be checked in CLion)
- Try to find a way to lock in setters to prevent editing of e.g. licence plates during the simulation
- Include tests for all items
- set up test & release targets

- [ ] main
	- [ ] reading xml-file
 
## Implementation
- [ ] class: RoadSystem
	- [ ] load simulation – *maybe move this to a seperate parser class?*
	- [ ] dump simulation – *should this be a part of the parser class as well?*
	- [ ] start & stop simulation
	- [ ] advance simulation
	- [ ] add, get/traverse car(s)
	- [ ] add, get/traverse road(s)
	- [ ] simulation empty?
	- [ ] simulation active?

- [ ] class: Road
	- [x] constructor using XML-file
	- [ ] get & set name
	- [ ] get & set length
	- [ ] get & set connection
	- [ ] add, has?, get/traverse car(s)
	- [ ] provide location-based iterator for vehicles

- [ ] class: Vehicle
	- [x] get & set licence plate
	- [x] get & set road
	- [x] get& set acceleration
	- [x] get & set speed
	- [x] get & set position
	- [x] prepare update (gathers info)
	- [x] execute update (updates info)

- [x] class: Vehicle::Car
	- [x] advance acceleration
	- [x] advance speed
	- [x] advance position
